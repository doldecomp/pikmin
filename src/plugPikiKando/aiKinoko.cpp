#include "PikiAI.h"
#include "Navi.h"
#include "NaviMgr.h"
#include "Interactions.h"
#include "SoundMgr.h"
#include "DebugLog.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
DEFINE_PRINT("aiKinoko")

/*
 * --INFO--
 * Address:	800B4570
 * Size:	0000A4
 */
ActKinoko::ActKinoko(Piki* piki)
    : Action(piki, true)
{
	mName = "kinoko";
	mTarget.clear();
}

/*
 * --INFO--
 * Address:	800B4614
 * Size:	000080
 */
void ActKinoko::init(Creature* creature)
{
	mPiki->mActionState = 0;
	if (creature) {
		mTarget.set(creature);
	}

	mState = STATE_Boid;
}

/*
 * --INFO--
 * Address:	800B4694
 * Size:	00006C
 */
int ActKinoko::exec()
{
	switch (mState) {
	case STATE_Boid:
		return exeBoid();
	case STATE_Attack:
		return exeAttack();
	case STATE_Jump:
		return exeJump();
	case STATE_Stick:
		return exeStick();
	}

	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void ActKinoko::initStick()
{
	mState = STATE_Stick;
	mPiki->startMotion(PaniMotionInfo(PIKIANIM_Kuttuku, this), PaniMotionInfo(PIKIANIM_Kuttuku));
}

/*
 * --INFO--
 * Address:	800B4700
 * Size:	000080
 */
int ActKinoko::exeStick()
{
	if (!mPiki->mStickTarget) {
		initAttack();
		return ACTOUT_Continue;
	}

	if (!mPiki->mNavi->isAlive()) {
		mPiki->endStickObject();
		initBoid();
		return ACTOUT_Continue;
	}

	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A8
 */
void ActKinoko::initJump()
{
	mState         = STATE_Jump;
	f32 vertSpeed  = 170.0f;
	f32 horizSpeed = 50.0f;
	Vector3f vel(horizSpeed * sinf(mPiki->mFaceDirection), vertSpeed, horizSpeed * cosf(mPiki->mFaceDirection));
	mPiki->mVelocity       = vel;
	mPiki->mTargetVelocity = vel;
}

/*
 * --INFO--
 * Address:	800B4780
 * Size:	000128
 */
int ActKinoko::exeJump()
{
	if (mPiki->mGroundTriangle) {
		initAttack();
		return ACTOUT_Continue;
	}

	Vector3f sep = mPiki->mNavi->mPosition - mPiki->mPosition;
	f32 dist     = sep.normalise();
	if (dist < 12.0f) {
		mPiki->startStickObject(mPiki->mNavi, mPiki->mNavi->mCollInfo->getSphere('head'), -1, 0.0f);
		initStick();
		return ACTOUT_Continue;
	}
	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	800B48A8
 * Size:	00000C
 */
void ActKinoko::initAttack()
{
	mState = STATE_Attack;
}

/*
 * --INFO--
 * Address:	800B48B4
 * Size:	0001C0
 */
int ActKinoko::exeAttack()
{
	Creature* target = mTarget.getPtr();
	if (!target || !target->isAlive()) {
		return ACTOUT_Fail;
	}

	f32 dist = qdist2(target, mPiki);
	if (dist > 500.0f) {
		initBoid();
		return ACTOUT_Continue;
	}

	Vector3f sep = mPiki->mNavi->mPosition - mPiki->mPosition;
	dist         = sep.normalise();
	if (dist < 25.0f) {
		initJump();
		return ACTOUT_Continue;
	}

	mPiki->setSpeed(1.0f, sep);
	return ACTOUT_Continue;
}

/*
 * --INFO--
 * Address:	800B4A74
 * Size:	000288
 */
void ActKinoko::initBoid()
{
	// this needs 0x10 more stack, mostly from inlines.
	// however, it also can't have TOO much going on or it stops inlining in exeBoid
	// weird balance.
	// also, DLL doesn't have any more inlines than this so idek.

	mState           = STATE_Boid;
	Creature* target = mTarget.getPtr();
	if (!target) {
		return;
	}

	mStateTimer  = 2.0f * gsys->getRand(1.0f) + 1.5f;
	Vector3f sep = target->mPosition - mPiki->mPosition;
	f32 dist     = sep.normalise();
	Vector3f orthoDir(sep.z, 0.0f, -sep.x);
	if (gsys->getRand(1.0f) > 0.5f) {
		orthoDir.multiply(-1.0f);
	}

	orthoDir = orthoDir + (0.2f * (gsys->getRand(1.0f) - 0.5f)) * sep;
	orthoDir.normalise();
	mTargetDirection = orthoDir;

	mPiki->playEventSound(target, SE_KINOKOPIKI_DANCE);
	u32 badCompiler[3];
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  li        r0, 0
	  stwu      r1, -0xB8(r1)
	  stfd      f31, 0xB0(r1)
	  stfd      f30, 0xA8(r1)
	  stfd      f29, 0xA0(r1)
	  stw       r31, 0x9C(r1)
	  addi      r31, r3, 0
	  stw       r30, 0x98(r1)
	  stw       r0, 0x1C(r3)
	  lwz       r30, 0x18(r3)
	  cmplwi    r30, 0
	  beq-      .loc_0x264
	  bl        0x1635C4
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x94(r1)
	  lis       r0, 0x4330
	  lfs       f3, -0x6F5C(r2)
	  stw       r0, 0x90(r1)
	  lfs       f2, -0x6F60(r2)
	  lfd       f1, 0x90(r1)
	  lfs       f0, -0x6F54(r2)
	  fsubs     f4, f1, f4
	  lfs       f1, -0x6F58(r2)
	  fdivs     f3, f4, f3
	  fmuls     f2, f2, f3
	  fmuls     f0, f0, f2
	  fadds     f0, f1, f0
	  stfs      f0, 0x20(r31)
	  lwz       r3, 0xC(r31)
	  lfsu      f1, 0x94(r3)
	  lfs       f3, 0x94(r30)
	  lfs       f2, 0x98(r30)
	  lfs       f0, 0x4(r3)
	  fsubs     f31, f3, f1
	  lfs       f1, 0x9C(r30)
	  fsubs     f30, f2, f0
	  lfs       f0, 0x8(r3)
	  fsubs     f29, f1, f0
	  fmuls     f1, f31, f31
	  fmuls     f0, f30, f30
	  fmuls     f2, f29, f29
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA6EEC
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0xD4
	  fdivs     f31, f31, f1
	  fdivs     f30, f30, f1
	  fdivs     f29, f29, f1

	.loc_0xD4:
	  stfs      f29, 0x70(r1)
	  fneg      f0, f31
	  lfs       f1, -0x4C00(r13)
	  stfs      f1, 0x74(r1)
	  stfs      f0, 0x78(r1)
	  bl        0x163514
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x94(r1)
	  lis       r0, 0x4330
	  lfs       f2, -0x6F5C(r2)
	  stw       r0, 0x90(r1)
	  lfs       f1, -0x6F60(r2)
	  lfd       f3, 0x90(r1)
	  lfs       f0, -0x6F50(r2)
	  fsubs     f3, f3, f4
	  fdivs     f2, f3, f2
	  fmuls     f1, f1, f2
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x14C
	  lfs       f0, 0x70(r1)
	  lfs       f1, -0x6F4C(r2)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x70(r1)
	  lfs       f0, 0x74(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x74(r1)
	  lfs       f0, 0x78(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x78(r1)

	.loc_0x14C:
	  bl        0x1634B0
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x94(r1)
	  lis       r0, 0x4330
	  lfs       f3, -0x6F5C(r2)
	  addi      r6, r1, 0x2C
	  stw       r0, 0x90(r1)
	  lfs       f2, -0x6F60(r2)
	  addi      r5, r1, 0x28
	  lfd       f1, 0x90(r1)
	  addi      r4, r1, 0x24
	  lfs       f0, -0x6F50(r2)
	  fsubs     f4, f1, f4
	  lfs       f1, -0x6F48(r2)
	  addi      r3, r1, 0x54
	  fdivs     f3, f4, f3
	  fmuls     f2, f2, f3
	  fsubs     f0, f2, f0
	  fmuls     f0, f1, f0
	  fmuls     f2, f29, f0
	  fmuls     f1, f30, f0
	  fmuls     f0, f31, f0
	  stfs      f2, 0x2C(r1)
	  stfs      f1, 0x28(r1)
	  stfs      f0, 0x24(r1)
	  bl        -0x7DB0C
	  lfs       f1, 0x70(r1)
	  lfs       f0, 0x54(r1)
	  lfs       f3, 0x74(r1)
	  lfs       f2, 0x58(r1)
	  fadds     f0, f1, f0
	  lfs       f4, 0x78(r1)
	  lfs       f1, 0x5C(r1)
	  fadds     f2, f3, f2
	  stfs      f0, 0x70(r1)
	  fadds     f0, f4, f1
	  stfs      f2, 0x74(r1)
	  stfs      f0, 0x78(r1)
	  lfs       f1, 0x70(r1)
	  lfs       f0, 0x74(r1)
	  lfs       f2, 0x78(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA703C
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x23C
	  lfs       f0, 0x70(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x70(r1)
	  lfs       f0, 0x74(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x74(r1)
	  lfs       f0, 0x78(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x78(r1)

	.loc_0x23C:
	  lwz       r3, 0x70(r1)
	  mr        r4, r30
	  lwz       r0, 0x74(r1)
	  li        r5, 0x6D
	  stw       r3, 0x24(r31)
	  stw       r0, 0x28(r31)
	  lwz       r0, 0x78(r1)
	  stw       r0, 0x2C(r31)
	  lwz       r3, 0xC(r31)
	  bl        -0x2A720

	.loc_0x264:
	  lwz       r0, 0xBC(r1)
	  lfd       f31, 0xB0(r1)
	  lfd       f30, 0xA8(r1)
	  lfd       f29, 0xA0(r1)
	  lwz       r31, 0x9C(r1)
	  lwz       r30, 0x98(r1)
	  addi      r1, r1, 0xB8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B4CFC
 * Size:	00085C
 */
int ActKinoko::exeBoid()
{
	Creature* target = mTarget.getPtr();
	if (!target || !target->isAlive()) {
		return ACTOUT_Fail;
	}

	if (qdist2(mPiki->mNavi->mPosition.x, mPiki->mNavi->mPosition.z, mPiki->mPosition.x, mPiki->mPosition.z) < 120.0f) {
		initAttack();
		return ACTOUT_Continue;
	}

	mStateTimer -= gsys->getFrameTime();
	if (mStateTimer < 0.0f) {
		initBoid();
	}

	Iterator iter(&mPiki->mSearchBuffer);
	int boidCount = 0;
	Vector3f boidPos(0.0f, 0.0f, 0.0f);
	Vector3f boidVel(0.0f, 0.0f, 0.0f);
	Vector3f closestPartnerDir(0.0f, 0.0f, 0.0f);
	bool isClosePartner = false;
	f32 minDist         = 50.0f;

	CI_LOOP(iter)
	{
		Creature* obj = *iter;
		if (obj->mObjType == OBJTYPE_Piki) {
			Piki* piki = static_cast<Piki*>(obj);
			if (piki != mPiki && piki->isKinoko()) {
				f32 dist = qdist2(piki->mPosition.x, piki->mPosition.z, mPiki->mPosition.x, mPiki->mPosition.z);
				if (dist < minDist) {
					minDist           = dist;
					closestPartnerDir = mPiki->mPosition - piki->mPosition;
					isClosePartner    = true;
				}

				boidPos = boidPos + piki->mPosition;
				boidVel = boidVel + piki->mVelocity;
				boidCount++;
			}
		}
	}

	if (boidCount > 0) {
		closestPartnerDir.normalise();
		boidPos.multiply(1.0f / f32(boidCount));
		boidVel.multiply(1.0f / f32(boidCount));
		boidVel.normalise();
		Vector3f boidDir = boidPos - mPiki->mPosition;
		Vector3f offset(sinf(mPiki->mFaceDirection), 0.0f, cosf(mPiki->mFaceDirection));
		boidDir.normalise();
		Vector3f moveDir;
		if (isClosePartner) {
			moveDir = offset * 0.01f + closestPartnerDir * 0.99f;
		} else {
			moveDir = offset * 0.4f + boidDir * 0.5f + mTargetDirection * 0.1f;
		}

		moveDir.normalise();
		mPiki->setSpeed(0.3f, moveDir);

	} else {
		mPiki->setSpeed(0.3f, mTargetDirection);
	}

	Vector3f newMoveDir = target->mPosition - mPiki->mPosition;
	if (!(newMoveDir.normalise() < 100.0f)) {
		mPiki->setSpeed(0.5f, newMoveDir);
	}

	return ACTOUT_Continue;

	u32 badCompiler[4];
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x2D8(r1)
	  stfd      f31, 0x2D0(r1)
	  stfd      f30, 0x2C8(r1)
	  stfd      f29, 0x2C0(r1)
	  stfd      f28, 0x2B8(r1)
	  stfd      f27, 0x2B0(r1)
	  stfd      f26, 0x2A8(r1)
	  stfd      f25, 0x2A0(r1)
	  stfd      f24, 0x298(r1)
	  stfd      f23, 0x290(r1)
	  stfd      f22, 0x288(r1)
	  stmw      r25, 0x26C(r1)
	  mr        r31, r3
	  lwz       r30, 0x18(r3)
	  cmplwi    r30, 0
	  addi      r3, r30, 0
	  beq-      .loc_0x64
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x88(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x6C

	.loc_0x64:
	  li        r3, 0x1
	  b         .loc_0x820

	.loc_0x6C:
	  lwz       r3, 0xC(r31)
	  lwz       r4, 0x504(r3)
	  lfs       f3, 0x94(r3)
	  lfs       f1, 0x94(r4)
	  lfs       f2, 0x9C(r4)
	  lfs       f4, 0x9C(r3)
	  bl        -0x7C758
	  lfs       f0, -0x6F38(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0xA4
	  li        r0, 0x1
	  stw       r0, 0x1C(r31)
	  li        r3, 0
	  b         .loc_0x820

	.loc_0xA4:
	  lwz       r3, 0x2DEC(r13)
	  lfs       f1, 0x20(r31)
	  lfs       f0, 0x28C(r3)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x20(r31)
	  lfs       f1, 0x20(r31)
	  lfs       f0, -0x6F78(r2)
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x338
	  li        r0, 0
	  stw       r0, 0x1C(r31)
	  lwz       r29, 0x18(r31)
	  cmplwi    r29, 0
	  beq-      .loc_0x338
	  bl        0x163298
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x264(r1)
	  lis       r0, 0x4330
	  lfs       f3, -0x6F5C(r2)
	  addi      r6, r1, 0xB0
	  stw       r0, 0x260(r1)
	  lfs       f2, -0x6F60(r2)
	  addi      r5, r1, 0xAC
	  lfd       f1, 0x260(r1)
	  addi      r4, r1, 0xA8
	  lfs       f0, -0x6F54(r2)
	  fsubs     f4, f1, f4
	  lfs       f1, -0x6F58(r2)
	  addi      r3, r1, 0x178
	  fdivs     f3, f4, f3
	  fmuls     f2, f2, f3
	  fmuls     f0, f0, f2
	  fadds     f0, f1, f0
	  stfs      f0, 0x20(r31)
	  lwz       r7, 0xC(r31)
	  lfs       f1, 0x9C(r29)
	  addi      r7, r7, 0x94
	  lfs       f0, 0x8(r7)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xB0(r1)
	  lfs       f1, 0x98(r29)
	  lfs       f0, 0x4(r7)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xAC(r1)
	  lfs       f1, 0x94(r29)
	  lfs       f0, 0x0(r7)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xA8(r1)
	  bl        -0x7DD48
	  lfs       f27, 0x178(r1)
	  lfs       f28, 0x17C(r1)
	  fmuls     f1, f27, f27
	  lfs       f29, 0x180(r1)
	  fmuls     f0, f28, f28
	  fmuls     f2, f29, f29
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA7248
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x1A8
	  fdivs     f27, f27, f1
	  fdivs     f28, f28, f1
	  fdivs     f29, f29, f1

	.loc_0x1A8:
	  stfs      f29, 0x16C(r1)
	  fneg      f0, f27
	  lfs       f1, -0x4C00(r13)
	  stfs      f1, 0x170(r1)
	  stfs      f0, 0x174(r1)
	  bl        0x1631B8
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x264(r1)
	  lis       r0, 0x4330
	  lfs       f2, -0x6F5C(r2)
	  stw       r0, 0x260(r1)
	  lfs       f1, -0x6F60(r2)
	  lfd       f3, 0x260(r1)
	  lfs       f0, -0x6F50(r2)
	  fsubs     f3, f3, f4
	  fdivs     f2, f3, f2
	  fmuls     f1, f1, f2
	  fcmpo     cr0, f1, f0
	  ble-      .loc_0x220
	  lfs       f0, 0x16C(r1)
	  lfs       f1, -0x6F4C(r2)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0x170(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x174(r1)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x174(r1)

	.loc_0x220:
	  bl        0x163154
	  xoris     r0, r3, 0x8000
	  lfd       f4, -0x6F40(r2)
	  stw       r0, 0x264(r1)
	  lis       r0, 0x4330
	  lfs       f3, -0x6F5C(r2)
	  addi      r6, r1, 0x84
	  stw       r0, 0x260(r1)
	  lfs       f2, -0x6F60(r2)
	  addi      r5, r1, 0x80
	  lfd       f1, 0x260(r1)
	  addi      r4, r1, 0x7C
	  lfs       f0, -0x6F50(r2)
	  fsubs     f4, f1, f4
	  lfs       f1, -0x6F48(r2)
	  addi      r3, r1, 0x188
	  fdivs     f3, f4, f3
	  fmuls     f2, f2, f3
	  fsubs     f0, f2, f0
	  fmuls     f0, f1, f0
	  fmuls     f2, f29, f0
	  fmuls     f1, f28, f0
	  fmuls     f0, f27, f0
	  stfs      f2, 0x84(r1)
	  stfs      f1, 0x80(r1)
	  stfs      f0, 0x7C(r1)
	  bl        -0x7DE68
	  lfs       f1, 0x16C(r1)
	  lfs       f0, 0x188(r1)
	  lfs       f3, 0x170(r1)
	  lfs       f2, 0x18C(r1)
	  fadds     f0, f1, f0
	  lfs       f4, 0x174(r1)
	  lfs       f1, 0x190(r1)
	  fadds     f2, f3, f2
	  stfs      f0, 0x16C(r1)
	  fadds     f0, f4, f1
	  stfs      f2, 0x170(r1)
	  stfs      f0, 0x174(r1)
	  lfs       f1, 0x16C(r1)
	  lfs       f0, 0x170(r1)
	  lfs       f2, 0x174(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA7398
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x310
	  lfs       f0, 0x16C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0x170(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x174(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x174(r1)

	.loc_0x310:
	  lwz       r3, 0x16C(r1)
	  mr        r4, r29
	  lwz       r0, 0x170(r1)
	  li        r5, 0x6D
	  stw       r3, 0x24(r31)
	  stw       r0, 0x28(r31)
	  lwz       r0, 0x174(r1)
	  stw       r0, 0x2C(r31)
	  lwz       r3, 0xC(r31)
	  bl        -0x2AA7C

	.loc_0x338:
	  lwz       r3, 0xC(r31)
	  li        r28, 0
	  lfs       f27, -0x4BFC(r13)
	  li        r27, 0
	  addi      r29, r3, 0x1B8
	  addi      r3, r29, 0
	  lfs       f28, -0x4BF8(r13)
	  lwz       r12, 0x0(r29)
	  lfs       f29, -0x4BF4(r13)
	  lwz       r12, 0xC(r12)
	  lfs       f30, -0x4BF0(r13)
	  mtlr      r12
	  lfs       f31, -0x4BEC(r13)
	  lfs       f26, -0x4BE8(r13)
	  lfs       f25, -0x4BE4(r13)
	  lfs       f24, -0x4BE0(r13)
	  lfs       f23, -0x4BDC(r13)
	  lfs       f22, -0x6F74(r2)
	  blrl
	  mr        r26, r3
	  b         .loc_0x4A0

	.loc_0x38C:
	  cmpwi     r26, -0x1
	  bne-      .loc_0x3B0
	  mr        r3, r29
	  lwz       r12, 0x0(r29)
	  li        r4, 0
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  b         .loc_0x3C8

	.loc_0x3B0:
	  mr        r3, r29
	  lwz       r12, 0x0(r29)
	  mr        r4, r26
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl

	.loc_0x3C8:
	  lwz       r0, 0x6C(r3)
	  cmpwi     r0, 0
	  bne-      .loc_0x484
	  lwz       r0, 0xC(r31)
	  addi      r25, r3, 0
	  cmplw     r3, r0
	  beq-      .loc_0x484
	  mr        r3, r25
	  lwz       r12, 0x0(r25)
	  lwz       r12, 0x120(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x484
	  lwz       r3, 0xC(r31)
	  lfs       f1, 0x94(r25)
	  lfs       f2, 0x9C(r25)
	  lfs       f3, 0x94(r3)
	  lfs       f4, 0x9C(r3)
	  bl        -0x7CAE8
	  fcmpo     cr0, f1, f22
	  bge-      .loc_0x450
	  lwz       r3, 0xC(r31)
	  fmr       f22, f1
	  lfsu      f1, 0x94(r3)
	  li        r27, 0x1
	  lfs       f0, 0x94(r25)
	  lfs       f3, 0x4(r3)
	  fsubs     f25, f1, f0
	  lfs       f2, 0x98(r25)
	  lfs       f1, 0x8(r3)
	  lfs       f0, 0x9C(r25)
	  fsubs     f24, f3, f2
	  fsubs     f23, f1, f0

	.loc_0x450:
	  lfs       f1, 0x94(r25)
	  addi      r28, r28, 0x1
	  lfs       f0, 0x98(r25)
	  lfs       f3, 0x9C(r25)
	  fadds     f27, f27, f1
	  lfs       f2, 0x70(r25)
	  fadds     f28, f28, f0
	  lfs       f1, 0x74(r25)
	  lfs       f0, 0x78(r25)
	  fadds     f29, f29, f3
	  fadds     f30, f30, f2
	  fadds     f31, f31, f1
	  fadds     f26, f26, f0

	.loc_0x484:
	  mr        r3, r29
	  lwz       r12, 0x0(r29)
	  mr        r4, r26
	  lwz       r12, 0x10(r12)
	  mtlr      r12
	  blrl
	  mr        r26, r3

	.loc_0x4A0:
	  mr        r3, r29
	  lwz       r12, 0x0(r29)
	  mr        r4, r26
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x4C8
	  li        r0, 0x1
	  b         .loc_0x4F4

	.loc_0x4C8:
	  mr        r3, r29
	  lwz       r12, 0x0(r29)
	  mr        r4, r26
	  lwz       r12, 0x8(r12)
	  mtlr      r12
	  blrl
	  cmplwi    r3, 0
	  bne-      .loc_0x4F0
	  li        r0, 0x1
	  b         .loc_0x4F4

	.loc_0x4F0:
	  li        r0, 0

	.loc_0x4F4:
	  rlwinm.   r0,r0,0,24,31
	  beq+      .loc_0x38C
	  cmpwi     r28, 0
	  ble-      .loc_0x768
	  fmuls     f1, f25, f25
	  fmuls     f0, f24, f24
	  fmuls     f2, f23, f23
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA75D4
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x534
	  fdivs     f25, f25, f1
	  fdivs     f24, f24, f1
	  fdivs     f23, f23, f1

	.loc_0x534:
	  xoris     r0, r28, 0x8000
	  lfd       f1, -0x6F40(r2)
	  stw       r0, 0x264(r1)
	  lis       r0, 0x4330
	  lfs       f2, -0x6F60(r2)
	  stw       r0, 0x260(r1)
	  lfd       f0, 0x260(r1)
	  fsubs     f0, f0, f1
	  fdivs     f3, f2, f0
	  fmuls     f30, f30, f3
	  fmuls     f31, f31, f3
	  fmuls     f26, f26, f3
	  fmuls     f1, f30, f30
	  fmuls     f0, f31, f31
	  fmuls     f2, f26, f26
	  fmuls     f27, f27, f3
	  fadds     f0, f1, f0
	  fmuls     f28, f28, f3
	  fmuls     f29, f29, f3
	  fadds     f1, f2, f0
	  bl        -0xA7640
	  lwz       r4, 0xC(r31)
	  lfs       f3, 0x94(r4)
	  lfs       f2, 0x98(r4)
	  fsubs     f26, f27, f3
	  lfs       f0, 0x9C(r4)
	  fsubs     f27, f28, f2
	  lfs       f1, 0xA0(r4)
	  fsubs     f28, f29, f0
	  bl        0x1668B0
	  lwz       r3, 0xC(r31)
	  fmr       f30, f1
	  lfs       f1, 0xA0(r3)
	  bl        0x166A34
	  fmuls     f2, f26, f26
	  lfs       f22, -0x4BD8(r13)
	  fmuls     f0, f27, f27
	  fmuls     f3, f28, f28
	  fmr       f31, f1
	  fadds     f0, f2, f0
	  fadds     f1, f3, f0
	  bl        -0xA7694
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x5F4
	  fdivs     f26, f26, f1
	  fdivs     f27, f27, f1
	  fdivs     f28, f28, f1

	.loc_0x5F4:
	  lfs       f0, -0x6F78(r2)
	  rlwinm.   r0,r27,0,24,31
	  stfs      f0, 0x210(r1)
	  stfs      f0, 0x20C(r1)
	  stfs      f0, 0x208(r1)
	  beq-      .loc_0x648
	  lfs       f4, -0x4BD0(r13)
	  lfs       f5, -0x4BD4(r13)
	  fmuls     f2, f25, f4
	  fmuls     f3, f31, f5
	  fmuls     f1, f22, f5
	  fmuls     f0, f24, f4
	  fadds     f2, f3, f2
	  fmuls     f3, f23, f4
	  fmuls     f4, f30, f5
	  fadds     f1, f1, f0
	  stfs      f2, 0x208(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x20C(r1)
	  stfs      f0, 0x210(r1)
	  b         .loc_0x700

	.loc_0x648:
	  lfs       f0, -0x4BC8(r13)
	  addi      r6, r1, 0x9C
	  lfs       f5, 0x2C(r31)
	  addi      r5, r1, 0x98
	  lfs       f6, -0x4BC4(r13)
	  lfs       f4, 0x28(r31)
	  fmuls     f2, f28, f0
	  lfs       f3, 0x24(r31)
	  fmuls     f1, f27, f0
	  fmuls     f0, f26, f0
	  fmuls     f29, f5, f6
	  fmuls     f28, f4, f6
	  stfs      f2, 0x9C(r1)
	  fmuls     f27, f3, f6
	  stfs      f1, 0x98(r1)
	  addi      r4, r1, 0x94
	  stfs      f0, 0x94(r1)
	  addi      r3, r1, 0x1B0
	  bl        -0x7E270
	  lfs       f0, -0x4BCC(r13)
	  addi      r6, r1, 0x90
	  addi      r5, r1, 0x8C
	  fmuls     f2, f30, f0
	  addi      r4, r1, 0x88
	  fmuls     f1, f22, f0
	  addi      r3, r1, 0x1BC
	  fmuls     f0, f31, f0
	  stfs      f2, 0x90(r1)
	  stfs      f1, 0x8C(r1)
	  stfs      f0, 0x88(r1)
	  bl        -0x7E2A0
	  lfs       f2, 0x1BC(r1)
	  lfs       f0, 0x1B0(r1)
	  lfs       f1, 0x1C0(r1)
	  fadds     f2, f2, f0
	  lfs       f0, 0x1B4(r1)
	  lfs       f3, 0x1C4(r1)
	  fadds     f0, f1, f0
	  lfs       f1, 0x1B8(r1)
	  fadds     f2, f2, f27
	  fadds     f3, f3, f1
	  fadds     f1, f0, f28
	  stfs      f2, 0x208(r1)
	  fadds     f0, f3, f29
	  stfs      f1, 0x20C(r1)
	  stfs      f0, 0x210(r1)

	.loc_0x700:
	  lfs       f1, 0x208(r1)
	  lfs       f0, 0x20C(r1)
	  fmuls     f1, f1, f1
	  lfs       f2, 0x210(r1)
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA77DC
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x754
	  lfs       f0, 0x208(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x208(r1)
	  lfs       f0, 0x20C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x20C(r1)
	  lfs       f0, 0x210(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x210(r1)

	.loc_0x754:
	  lwz       r3, 0xC(r31)
	  addi      r4, r1, 0x208
	  lfs       f1, -0x6F34(r2)
	  bl        0x1697C
	  b         .loc_0x778

	.loc_0x768:
	  lwz       r3, 0xC(r31)
	  addi      r4, r31, 0x24
	  lfs       f1, -0x6F34(r2)
	  bl        0x16968

	.loc_0x778:
	  lwz       r3, 0xC(r31)
	  lfsu      f0, 0x94(r3)
	  lfs       f1, 0x94(r30)
	  lfs       f3, 0x98(r30)
	  lfs       f2, 0x4(r3)
	  fsubs     f0, f1, f0
	  lfs       f4, 0x9C(r30)
	  lfs       f1, 0x8(r3)
	  fsubs     f2, f3, f2
	  stfs      f0, 0x1FC(r1)
	  fsubs     f0, f4, f1
	  stfs      f2, 0x200(r1)
	  stfs      f0, 0x204(r1)
	  lfs       f1, 0x1FC(r1)
	  lfs       f0, 0x200(r1)
	  lfs       f2, 0x204(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0xA7888
	  lfs       f0, -0x6F78(r2)
	  fcmpu     cr0, f0, f1
	  beq-      .loc_0x800
	  lfs       f0, 0x1FC(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x1FC(r1)
	  lfs       f0, 0x200(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x200(r1)
	  lfs       f0, 0x204(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x204(r1)

	.loc_0x800:
	  lfs       f0, -0x6F30(r2)
	  fcmpo     cr0, f1, f0
	  blt-      .loc_0x81C
	  lwz       r3, 0xC(r31)
	  addi      r4, r1, 0x1FC
	  lfs       f1, -0x6F50(r2)
	  bl        0x168C4

	.loc_0x81C:
	  li        r3, 0

	.loc_0x820:
	  lmw       r25, 0x26C(r1)
	  lwz       r0, 0x2DC(r1)
	  lfd       f31, 0x2D0(r1)
	  lfd       f30, 0x2C8(r1)
	  lfd       f29, 0x2C0(r1)
	  lfd       f28, 0x2B8(r1)
	  lfd       f27, 0x2B0(r1)
	  lfd       f26, 0x2A8(r1)
	  lfd       f25, 0x2A0(r1)
	  lfd       f24, 0x298(r1)
	  lfd       f23, 0x290(r1)
	  lfd       f22, 0x288(r1)
	  addi      r1, r1, 0x2D8
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	800B5558
 * Size:	000098
 */
void ActKinoko::animationKeyUpdated(PaniAnimKeyEvent& event)
{
	switch (event.mEventType) {
	case KEY_Action0:
		if (mState == STATE_Stick) {
			Navi* navi = naviMgr->getNavi();
			if (!navi) {
				ERROR("kinoko no navi!\n");
			}
			PRINT("navi=%x", navi);
			InteractSuck suck(mPiki, 0.5f);
			if (navi->stimulate(suck)) {
				SeSystem::playPlayerSe(SE_KINOKOPIKI_ATTACK);
			}
		}
		break;
	}

	u32 badCompiler[2];
}

/*
 * --INFO--
 * Address:	800B55F0
 * Size:	000004
 */
void ActKinoko::cleanup()
{
}
