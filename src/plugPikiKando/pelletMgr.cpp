#include "Pellet.h"
#include "PelletView.h"
#include "PelletState.h"
#include "StateMachine.h"
#include "Interactions.h"
#include "MapMgr.h"
#include "Stickers.h"
#include "PlayerState.h"
#include "UtEffect.h"
#include "KMath.h"
#include "RadarInfo.h"
#include "SoundMgr.h"
#include "AIPerf.h"
#include "teki.h"
#include "Font.h"
#include "Graphics.h"
#include "EffectMgr.h"
#include "DebugLog.h"
#include "zen/Math.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F0
 */
DEFINE_PRINT(nullptr);

bool SmartTurnOver;

static u32 _ufoIDTable[] = {
	'ust1', 'ust2', 'ust3', 'ust4', 'ust5', 'uf01', 'uf02', 'uf03', 'uf04', 'uf05', 'uf06', 'uf07', 'uf08', 'uf09', 'uf10', 'uf11',
	'un01', 'un02', 'un03', 'un04', 'un05', 'un06', 'un07', 'un08', 'un09', 'un10', 'un11', 'un12', 'un13', 'un14', 'udef',
};

/*
 * --INFO--
 * Address:	80094B14
 * Size:	000044
 */
int PelletMgr::getUfoIndexFromID(u32 ufoID)
{
	int i;
	for (i = 0;; i++) {
		if (_ufoIDTable[i] == 'udef') {
			return -1;
		}

		if (_ufoIDTable[i] == ufoID) {
			return i;
		}
	}

	return i;
}

/*
 * --INFO--
 * Address:	80094B58
 * Size:	000018
 */
u32 PelletMgr::getUfoIDFromIndex(int idx)
{
	if (idx >= 30) {
		ERROR("N MECK!\n");
	}
	return _ufoIDTable[idx];
}

/*
 * --INFO--
 * Address:	80094B70
 * Size:	000390
 */
PelletConfig::PelletConfig()
    : mPelletName(this, String("new", 0), String("", 0), String("", 0), "x99", nullptr)
    , mPelletType(this, PELTYPE_Blue, 0, 0, "p00", nullptr)
    , mPelletColor(this, PELCOLOR_NULL, 0, 0, "p09", nullptr)
    , mCarryMinPikis(this, 1, 0, 0, "p01", nullptr)
    , mCarryMaxPikis(this, 1, 0, 0, "p02", nullptr)
    , mUseDynamicMotion(this, 0, 0, 0, "p03", nullptr)
    , _A0(this, 10.0f, 0.0f, 0.0f, "p04", nullptr)
    , _B0(this, 4.0f, 0.0f, 0.0f, "p05", nullptr)
    , _C0(this, 4, 0, 0, "p08", nullptr)
    , mMatchingOnyonSeeds(this, 1, 0, 0, "p06", nullptr)
    , mNonMatchingOnyonSeeds(this, 1, 0, 0, "p07", nullptr)
    , mPelletScale(this, 1.0f, 0.0f, 0.0f, "p10", nullptr)
    , mCarryInfoHeight(this, 30.0f, 0.0f, 0.0f, "p11", nullptr)
    , mAnimSoundID(this, 6, 0, 0, "p12", nullptr)
    , mBounceSoundID(this, 0xFFFFFFFF, 0, 0, "p13", nullptr)
{
	mModelId.setID('none');
	_38.setID('none');
	mPelletId.setID('none');
	initCore("pelletConfig");
	mUfoPartIndex = -1;
}

/*
 * --INFO--
 * Address:	80094F00
 * Size:	000074
 */
void PelletConfig::read(RandomAccessStream& input)
{
	Parameters::read(input);
	mModelId.read(input);
	mPelletId.read(input);
	_38.read(input);
	mUfoPartIndex = input.readInt();
}

// see PelletBounceSoundID in Pellet.h
static u32 bounceSounds[] = {
	SE_PELLET_BOUND,   SE_UFOPARTS_BOUND, SE_UFOPARTS_SPRING, SE_UFOPARTS_MONEYBOX, SE_UFOPARTS_BOUND, SE_UFOPARTS_BOUND,
	SE_UFOPARTS_BOUND, SE_UFOPARTS_BOUND, SE_UFOPARTS_BOUND,  SE_UFOPARTS_BOUND,    SE_UFOPARTS_BOUND, SE_UFOPARTS_BOUND,
};

NumberPel numberPellets[13] = {
	{ PELCOLOR_Blue, NUMPEL_OnePellet, 'pb01' },   { PELCOLOR_Blue, NUMPEL_FivePellet, 'pb05' },
	{ PELCOLOR_Blue, NUMPEL_TenPellet, 'pb10' },   { PELCOLOR_Blue, NUMPEL_TwentyPellet, 'pb20' },
	{ PELCOLOR_Red, NUMPEL_OnePellet, 'pr01' },    { PELCOLOR_Red, NUMPEL_FivePellet, 'pr05' },
	{ PELCOLOR_Red, NUMPEL_TenPellet, 'pr10' },    { PELCOLOR_Red, NUMPEL_TwentyPellet, 'pr20' },
	{ PELCOLOR_Yellow, NUMPEL_OnePellet, 'py01' }, { PELCOLOR_Yellow, NUMPEL_FivePellet, 'py05' },
	{ PELCOLOR_Yellow, NUMPEL_TenPellet, 'py10' }, { PELCOLOR_Yellow, NUMPEL_TwentyPellet, 'py20' },
	{ PELCOLOR_NULL, NUMPEL_NULL, 'ujaa' },
};

/*
 * --INFO--
 * Address:	80094F74
 * Size:	0001C8
 */
void PelletView::becomePellet(u32 id, Vector3f& pos, f32 direction)
{
	if (mPellet) {
		PRINT("becomePellet twice **\n");
		return;
	}

	Pellet* pellet = pelletMgr->newPellet(id, this);
	if (!pellet) {
		return;
	}

	f32 minY = mapMgr->getMinY(pos.x, pos.z, true);
	f32 maxY = mapMgr->getMaxY(pos.x, pos.z, true);

	if (zen::Abs(pos.y - maxY) < zen::Abs(pos.y - minY)) {
		pos.y = maxY;
	} else {
		pos.y = minY;
	}

	pellet->init(pos);
	pellet->mFaceDirection = direction;
	pellet->mRotationQuat.fromEuler(Vector3f(0.0f, direction, 0.0f));
	pellet->mRotation.set(0.0f, direction, 0.0f);
	pellet->mVelocity.set(0.0f, 0.0f, 0.0f);
	pellet->mTargetVelocity.set(0.0f, 0.0f, 0.0f);
	pellet->mAngularMomentum.set(0.0f, 0.0f, 0.0f);
	pellet->mAngularVelocity.set(0.0f, 0.0f, 0.0f);
	pellet->mVolatileVelocity.set(0.0f, 0.0f, 0.0f);
	pellet->_B0.set(0.0f, 0.0f, 0.0f);
	pellet->startAI(0);
	pellet->useRealDynamics();

	mPellet = pellet;
}

/*
 * --INFO--
 * Address:	8009513C
 * Size:	000270
 */
Pellet::Pellet()
{
	_450 = true;
	mSpawnPosition.set(0.0f, 0.0f, 0.0f);
	mSeContext = new SeContext();
	mSeContext->setContext(this, 2);
	mRippleEffect   = new RippleEffect();
	mPelletView     = nullptr;
	mPikiCarrier    = nullptr;
	mShapeObject    = nullptr;
	mConfig         = nullptr;
	mMotionSpeed    = 0.0f;
	mObjType        = OBJTYPE_Pellet;
	mCollInfo       = nullptr;
	mPelletCollInfo = new CollInfo(6);
	mCurrentState   = nullptr;
	mStateMachine   = new PelletStateMachine();
	mStateMachine->init(this);
	mSearchBuffer.init(mSearchData, 4);
	mCollisionRadius = 4.0f;
	mCarryDirection.set(0.0f, 0.0f, 0.0f);
	setTrySound(false);
}

/*
 * --INFO--
 * Address:	800953AC
 * Size:	00003C
 */
bool Pellet::isUfoPartsID(u32 partsID)
{
	ID32 id(partsID);
	return id.match('u***', '*');
}

/*
 * --INFO--
 * Address:	800953E8
 * Size:	000090
 */
void Pellet::startWaterEffect()
{
	EffectParm unused(&mPosition); // lol.
	EffectParm parm(mPosition);
	unused._24 = 2.0f; // this is so dumb
	UtEffectMgr::cast(17, parm);
}

/*
 * --INFO--
 * Address:	80095478
 * Size:	000030
 */
void Pellet::finishWaterEffect()
{
	mRippleEffect->kill();
}

/*
 * --INFO--
 * Address:	800954A8
 * Size:	000090
 */
void Pellet::doKill()
{
	setTrySound(false);
	mIsAlive = 0;
	if (mPelletView) {
		static_cast<PelletView*>(mPelletView)->viewKill();
		mPelletView = nullptr;
	}
	mSeContext->releaseEvent();
	DualCreature::doKill();
	pelletMgr->kill(this);
	mLifeGauge.countOff();
}

/*
 * --INFO--
 * Address:	80095538
 * Size:	00001C
 */
int Pellet::getState()
{
	if (mCurrentState) {
		return mCurrentState->getID();
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80095554
 * Size:	000038
 */
bool Pellet::ignoreAtari(Creature* creature)
{
	if (creature->getStickObject() == this) {
		return true;
	}

	if (mPelletView && creature == mPelletView) {
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	8009558C
 * Size:	000008
 */
bool Pellet::isAlive()
{
	return mIsAlive;
}

/*
 * --INFO--
 * Address:	80095594
 * Size:	000048
 */
bool Pellet::isAtari()
{
	int state = getState();
	if (state == 2) {
		return false;
	}
	if (state == 3 || state == 1) {
		return false;
	}
	return true;
}

/*
 * --INFO--
 * Address:	800955DC
 * Size:	000050
 */
bool Pellet::isVisible()
{
	int state = getState();
	if (!mIsAlive) {
		return false;
	}

	if (state == 1 || state == 2 || state == 4) {
		return false;
	}
	return true;
}

/*
 * --INFO--
 * Address:	8009562C
 * Size:	000080
 */
void Pellet::setTrySound(bool doSetOn)
{
	if (!doSetOn) {
		mIsPlayTrySound = false;
		stopEventSound(this, SE_LIFT_TRY);

	} else if (!mIsPlayTrySound && getPickOffset() == 0.0f) {
		playEventSound(this, SE_LIFT_TRY);
		mIsPlayTrySound = true;
	}
}

/*
 * --INFO--
 * Address:	800956AC
 * Size:	0003A0
 */
void Pellet::startPick()
{
	if (!playerState->mDemoFlags.isFlag(DEMOFLAG_Unk9)) {
		playerState->mDemoFlags.setFlagOnly(DEMOFLAG_Unk9);
	}

	setTrySound(false);
	disableFixPos();
	resetCreatureFlag(CF_IsPositionFixed);
	disableFriction();
	startCarryMotion(30.0f);

	if (!mPelletView) {
		if (isMotionFlag(2)) {
			mAnimator.startMotion(PaniMotionInfo(0), PaniMotionInfo(3, this));
		} else {
			mAnimator.startMotion(PaniMotionInfo(0));
		}
	}

	f32 offset = 8.0f;
	if (mPelletView) {
		offset = 4.0f;
	} else {
		offset = offset / mScale.y;
	}

	f32 dir = 1.0f;
	if (!isFrontFace()) {
		dir = -1.0f;
	}

	enablePickOffset(offset);

	Stickers stuckList(this);
	Iterator iter(&stuckList);
	bool isOnlyPiki = true;
	CI_LOOP(iter)
	{
		Creature* stuck = *iter;
		if (stuck->isTeki()) {
			isOnlyPiki = false;
		}

		stuck->mAttachPosition.y -= offset * dir;
	}

	if (!isOnlyPiki) {
		disablePickOffset();
		CI_LOOP(iter)
		{
			(*iter)->mAttachPosition.y += offset * dir;
		}
	}

	f32 minY = mapMgr->getMinY(mPosition.x, mPosition.z, true);
	if (minY > mPosition.y) {
		PRINT("************* START PICK YABAI !!!\n");
	}
	if (!isRealDynamics()) {
		mPosition.y += offset;
	}
}

/*
 * --INFO--
 * Address:	80095A4C
 * Size:	000080
 */
void Pellet::finishPick()
{
	mCarrierCounter = 0;
	enableFixPos();
	stopEventSound(this, SE_LIFT_MOVE);
	stopEventSound(this, SE_LIFT_TRY);
	enableFriction();
	finishMotion();
	disablePickOffset();
	mCarryState = 0;
}

/*
 * --INFO--
 * Address:	80095ACC
 * Size:	0000B8
 */
void Pellet::startGoal()
{
	finishPick();
	mStateMachine->transit(this, 1);
	mPikiCarrier = 0;
	mCarryDirection.set(0.0f, 0.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	80095C3C
 * Size:	00016C
 */
void Pellet::doCarry(Creature* carryingPiki, Vector3f& direction, u16 carrierCount)
{
	if (mCarryState == 1) {
		mTransitionTimer -= gsys->getFrameTime();
		if (mTransitionTimer <= 0.0f) {
			mCarryState = 2;
		}

		mCarryDirection = direction * 0.5f;
		return;
	}

	if (mPikiCarrier && mPikiCarrier->mObjType != carryingPiki->mObjType) {
		if (mCarryState == 0) {
			mCarryState      = 1;
			mTransitionTimer = 3.5f;
			return;
		}

		if (mPikiCarrier->getStickObject() == this && mCarrierCount > carrierCount) {
			PRINT("%s win\n", ObjType::getName(mPikiCarrier->mObjType));
			return;
		}

		mCarryDirection = direction;
		mPikiCarrier    = carryingPiki;
		mCarrierCount   = carrierCount;
		PRINT("%s win\n", ObjType::getName(mPikiCarrier->mObjType));
		mCarryState      = 1;
		mTransitionTimer = 3.5f;

		return;
	}

	mCarryDirection = direction;
	mPikiCarrier    = carryingPiki;
	mCarrierCount   = carrierCount;
}

/*
 * --INFO--
 * Address:	80095DA8
 * Size:	000108
 */
f32 Pellet::getBottomRadius()
{
	if (mPelletView) {
		return static_cast<PelletView*>(mPelletView)->viewGetBottomRadius();
	}

	bool hasCentPart = false;
	if (mCollInfo && mCollInfo->hasInfo() && mCollInfo->getSphere('cent')) {
		hasCentPart = true;
	}

	if (!hasCentPart) {
		if (!mPelletView) {
			PRINT("PELLE IS %s (view=%x)\n", mConfig->mPelletName.mValue.mString, mPelletView);
			PRINT("*** NO VIEW NO CENT :: SIZE 10\n");
			static int count = 0;
			count++;
			if (count > 10) {
				if (isAlive()) {
					ERROR("okasii!\n");
				}

				ERROR("who called me ?\n");
			}
			return 10.0f;
		}

		PRINT("PELLE IS %s (view=%x)\n", mConfig->mPelletName.mValue.mString, mPelletView);
		PRINT("if view is creature, the name is %s\n", ObjType::getName(static_cast<Creature*>(mPelletView)->mObjType));
		ERROR("BottomRadius Loop\n");
	}

	return getCentreSize();
}

/*
 * --INFO--
 * Address:	80095EB0
 * Size:	00001C
 */
Vector3f Pellet::getCentre()
{
	return mPosition;
}

/*
 * --INFO--
 * Address:	80095ECC
 * Size:	000048
 */
f32 Pellet::getCylinderHeight()
{
	if (mPelletView) {
		return static_cast<PelletView*>(mPelletView)->viewGetHeight();
	}
	return mConfig->mCarryInfoHeight();
}

/*
 * --INFO--
 * Address:	80095F14
 * Size:	000078
 */
f32 Pellet::getSize()
{
	if (mPelletView) {
		Vector3f viewScale(static_cast<PelletView*>(mPelletView)->viewGetScale());
		return viewScale.x * static_cast<PelletView*>(mPelletView)->viewGetBottomRadius();
	}
	return getBottomRadius();
}

/*
 * --INFO--
 * Address:	80095FA8
 * Size:	000008
 */
f32 Pellet::getiMass()
{
	return 0.0f;
}

/*
 * --INFO--
 * Address:	80095FB0
 * Size:	0000E4
 */
bool Pellet::startStickTeki(Creature* teki, f32 p2)
{
	Vector3f toEnemy = getCentre();
	toEnemy          = teki->getCentre() - toEnemy;
	f32 angle        = atan2f(toEnemy.x, toEnemy.z);
	mStuckAngle      = roundAng(angle - mFaceDirection);

	teki->startStickObject(this, nullptr, -2, p2);
	if (teki->getStickObject() != this) {
		return false;
	}

	startPick();
	return true;
}

/*
 * --INFO--
 * Address:	80096094
 * Size:	000094
 */
void Pellet::endStickTeki(Creature* teki)
{
	finishPick();
	teki->endStickObject();
}

/*
 * --INFO--
 * Address:	80096128
 * Size:	000174
 */
bool Pellet::winnable(int tekiStrength)
{
	if (mConfig->mModelId.match('NAVI', '*')) {
		// breadbugs aren't allowed to yoink sleeping captains.
		return false;
	}

	Stickers stuckList(this);
	Iterator iter(&stuckList);
	int pikiCount = 0;
	CI_LOOP(iter)
	{
		if ((*iter)->isPiki()) {
			pikiCount++;
		}
	}

	if (tekiStrength > pikiCount) {
		// not enough pikis - get dragged to the nest losers!
		return true;
	}

	// get boot scooted to the onyon bread boi
	return false;
}

/*
 * --INFO--
 * Address:	8009629C
 * Size:	000068
 */
bool Pellet::stickSlot(int slotID)
{
	if (slotID != -1 && !isSlotFlag(slotID)) {
		// valid, empty slot - fill it.
		setSlotFlag(slotID);
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	80096304
 * Size:	00005C
 */
void Pellet::stickOffSlot(int slotID)
{
	if (slotID != -1 && isSlotFlag(slotID)) {
		// valid, filled slot - reset it.
		resetSlotFlag(slotID);
	}
}

/*
 * --INFO--
 * Address:	80096360
 * Size:	00006C
 */
int Pellet::getMinFreeSlotIndex()
{
	for (int i = 0; i < mConfig->mCarryMaxPikis(); i++) {
		if (!isSlotFlag(i)) {
			return i;
		}
	}

	return -1;
}

/*
 * --INFO--
 * Address:	800963CC
 * Size:	000160
 */
int Pellet::getNearestFreeSlotIndex(Vector3f& pos)
{
	f32 minDist    = 12800.0f;
	int nearestIdx = -1;
	for (int i = 0; i < mConfig->mCarryMaxPikis(); i++) {
		if (!isSlotFlag(i)) {
			// free slot, how far away is it
			Vector3f slotSep = getSlotGlobalPos(i, 0.0f) - pos;
			f32 slotDist     = slotSep.length();
			if (slotDist < minDist) {
				minDist    = slotDist;
				nearestIdx = i;
			}
		}
	}

	return nearestIdx;
}

/*
 * --INFO--
 * Address:	8009652C
 * Size:	0000D8
 */
int Pellet::getRandomFreeSlotIndex()
{
	int maxCarryNum = mConfig->mCarryMaxPikis();
	int randIdx     = System::getRand(1.0f) * maxCarryNum;
	int idDist      = 128;
	int outIdx      = -1;
	for (int i = 0; i < maxCarryNum; i++) {
		if (!isSlotFlag(i)) {
			// there are like 50 abs inlines, you could've just used one kando.
			int slotidDist = (i - randIdx > 0) ? i - randIdx : -(i - randIdx);
			// looking for "nearest" free slot to our randomly picked slot ID
			if (slotidDist < idDist) {
				idDist = slotidDist;
				outIdx = i;
			}
		}
	}

	return outIdx;
}

/*
 * --INFO--
 * Address:	80096604
 * Size:	0001A0
 */
Vector3f Pellet::getSlotLocalPos(int slotID, f32 offset)
{
	f32 grabAngle;
	if (slotID == -2) {
		grabAngle = mStuckAngle;
	} else {
		grabAngle = (TAU / mConfig->mCarryMaxPikis()) * slotID;
	}

	f32 grabRadius;
	f32 pickupHeight = mPickOffset;
	if (!mPelletView) {
		grabRadius = getBottomRadius() + offset;
		grabRadius /= mScale.x;
	} else {
		grabRadius = getBottomRadius() + offset;
	}

	Vector3f localPos;
	if (SmartTurnOver) {
		f32 y = pickupHeight;
		if (getGroundFlag() != 0x55) {
			y = getCylinderHeight() - pickupHeight;
		}
		localPos.set(grabRadius * sinf(grabAngle), y, grabRadius * cosf(grabAngle));

	} else if (isFrontFace()) {
		localPos.set(grabRadius * sinf(grabAngle), pickupHeight, grabRadius * cosf(grabAngle));

	} else {
		f32 y = getCylinderHeight() - pickupHeight;
		localPos.set(grabRadius * sinf(grabAngle), y, grabRadius * cosf(grabAngle));
	}

	return localPos;
}

/*
 * --INFO--
 * Address:	800967A4
 * Size:	000078
 */
Vector3f Pellet::getSlotGlobalPos(int slotID, f32 offset)
{
	Vector3f globalPos = getSlotLocalPos(slotID, offset);
	globalPos.multMatrix(mWorldMtx);
	return globalPos;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
void Pellet::initSlotFlags()
{
	mSlotFlags[0] = mSlotFlags[1] = mSlotFlags[2] = 0;
}

/*
 * --INFO--
 * Address:	8009681C
 * Size:	000034
 */
void Pellet::setSlotFlag(int slotID)
{
	if (slotID != -2) {
		// 32 flags per slot, so get correct slot (>> 5 == divide by 32 + drop remainder)
		mSlotFlags[slotID >> 5] |= (1 << (slotID - 32 * (slotID >> 5)));
	}
}

/*
 * --INFO--
 * Address:	80096850
 * Size:	000034
 */
void Pellet::resetSlotFlag(int slotID)
{
	if (slotID != -2) {
		// 32 flags per slot, so get correct slot (>> 5 == divide by 32 + drop remainder)
		mSlotFlags[slotID >> 5] &= ~(1 << (slotID - 32 * (slotID >> 5)));
	}
}

/*
 * --INFO--
 * Address:	80096884
 * Size:	000044
 */
bool Pellet::isSlotFlag(int slotID)
{
	if (slotID == -2) {
		return false;
	}

	return (mSlotFlags[slotID >> 5] & (1 << (slotID - 32 * (slotID >> 5)))) != 0;
}

/*
 * --INFO--
 * Address:	800968C8
 * Size:	0000E0
 */
void Pellet::initPellet(PelletShapeObject* shapeObj, PelletConfig* config)
{
	mCarrierCounter = 0;
	mMotionFlag     = 1;
	mShapeObject    = shapeObj;
	if (shapeObj->isMotionFlag(2)) {
		setMotionFlag(2);
		if (!isMotionFlag(2)) {
			ERROR("WHYYYYYYYYYYY\n"); // same kando
		}
	}

	mConfig   = config;
	mCollInfo = mPelletCollInfo;
	mCollInfo->initInfo(mShapeObject->mShape, nullptr, nullptr);
	f32 scale = config->mPelletScale();
	mScale.set(scale, scale, scale);
	if (config->mPelletColor() != PELCOLOR_NULL || isUfoParts()) {
		mShapeObject->mShape->makeInstance(mShapeDynMaterials, 0);
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void Pellet::initPellet(PelletView* view, PelletConfig* config)
{
	mCarrierCounter = 0;
	mMotionFlag     = 1;
	mPelletView     = view;
	mConfig         = config;
	mScale.set(view->viewGetScale());
	mShapeObject = nullptr;
	mCollInfo    = nullptr;
}

/*
 * --INFO--
 * Address:	800969A8
 * Size:	000044
 */
void Pellet::startCarryMotion(f32 speed)
{
	mMotionSpeed = speed;
	if (mPelletView) {
		static_cast<PelletView*>(mPelletView)->viewStartTrembleMotion(mMotionSpeed);
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void Pellet::stopMotion()
{
	if (mPelletView) {
		static_cast<PelletView*>(mPelletView)->viewSetMotionSpeed(0.0f);
	} else {
		mMotionSpeed = 0.0f;
	}
}

/*
 * --INFO--
 * Address:	800969F4
 * Size:	000064
 */
void Pellet::finishMotion()
{
	if (mPelletView) {
		static_cast<PelletView*>(mPelletView)->viewFinishMotion();
	} else {
		mAnimator.finishMotion(&PaniMotionInfo(-1), nullptr);
	}
}

/*
 * --INFO--
 * Address:	80096A5C
 * Size:	000098
 */
void Pellet::init(Vector3f& pos)
{
	Creature::init(pos);
	if (mShapeObject) {
		mAnimator.init(&mShapeObject->mAnimatorA, &mShapeObject->mAnimatorB, mShapeObject->mAnimMgr, pelletMgr->mUfoMotionTable);
	}
	initSlotFlags();
	enableFriction();
	if (mConfig->mUseDynamicMotion()) {
		setDynamicsSimpleFixed(false);
	} else {
		setDynamicsSimpleFixed(true);
	}

	mCarryState = 0;
}

/*
 * --INFO--
 * Address:	80096AF4
 * Size:	000034
 */
bool Pellet::isFree()
{
	// mSlotFlags needs to be int for resetSlotFlags, this seems to be the easier fix
	if ((u32)(mSlotFlags[0]) == 0 && (u32)(mSlotFlags[1]) == 0 && (u32)(mSlotFlags[2]) == 0) {
		return true;
	}
	return false;
}

/*
 * --INFO--
 * Address:	80096B28
 * Size:	000248
 */
void Pellet::doLoad(RandomAccessStream& input)
{
	_450                  = input.readByte();
	mSpawnPosition.x      = input.readFloat();
	mSpawnPosition.y      = input.readFloat();
	mSpawnPosition.z      = input.readFloat();
	Vector3f displacement = mSpawnPosition - mPosition;
	if (displacement.length() < 40.0f) {
		PRINT("UFO PARTS DIDN'T MOVE!\n");
		mPosition = mSpawnPosition;
	} else if (isNan(mPosition.x) || isNan(mPosition.y) || isNan(mPosition.z)) {
		// this isn't in the DLL, funnily enough
		mPosition = mSpawnPosition;
	} else {
		PRINT("PARTS MOVED !!! (%.1f %.1f %.1f)\n", displacement.x, displacement.y, displacement.z);
		mPosition = routeMgr->getSafePosition('test', mPosition);
	}

	mPosition.y = mapMgr->getMinY(mPosition.x, mPosition.z, true);
	PRINT("ufo parts %s : (%.1f %.1f %.1f)", mConfig->mModelId.mStringID, mPosition.x, mPosition.y, mPosition.z);
	disableFixPos();
	enableFixPos();
	mStateMachine->transit(this, 5);
}

/*
 * --INFO--
 * Address:	80096D70
 * Size:	000078
 */
void Pellet::animationKeyUpdated(PaniAnimKeyEvent& event)
{
	if (isMotionFlag(2) && event.mEventType == KEY_LoopEnd && isUfoParts() && mConfig->mAnimSoundID() >= 0) {
		playEventSound(this, mConfig->mAnimSoundID() + SE_UFOPARTS_SOUNDTYPE);
	}
}

/*
 * --INFO--
 * Address:	80096DE8
 * Size:	000094
 */
void Pellet::doSave(RandomAccessStream& output)
{
	output.writeByte(_450);
	output.writeFloat(mSpawnPosition.x);
	output.writeFloat(mSpawnPosition.y);
	output.writeFloat(mSpawnPosition.z);
}

/*
 * --INFO--
 * Address:	80096E7C
 * Size:	0003B8
 */
void Pellet::startAI(int stateID)
{
	mRotationQuat.fromEuler(Vector3f(0.0f, mFaceDirection, 0.0f));
	mRotation.set(0.0f, mFaceDirection, 0.0f);
	mLastPosition = mPosition;
	enableFixPos();
	if (_450) {
		mSpawnPosition = mPosition;
	}

	setTrySound(false);
	if (isUfoParts() && mConfig->mAnimSoundID() >= 0) {
		playEventSound(this, mConfig->mAnimSoundID() + SE_UFOPARTS_SOUNDTYPE);
	}

	mIsAlive = true;
	if (isUfoParts()) {
		radarInfo->attachParts(this);
	}

	mTargetGoal     = nullptr;
	mStuckMouthPart = 0;
	mPikiCarrier    = nullptr;

	bool check = false;
	if (mMotionFlag == 3) {
		check = true;
	}

	if (!mPelletView) {
		if (isMotionFlag(2)) {
			mAnimator.startMotion(PaniMotionInfo(0), PaniMotionInfo(3, this));
			check = false;
		} else {
			mAnimator.startMotion(PaniMotionInfo(0));
		}
	} else {
		startCarryMotion(0.0f);
	}

	if (check) {
		PRINT("view=%x isMotionFlag() = %s\n", mPelletView, isCreatureFlag(CF_GravityEnabled) ? "true" : "false");
		ERROR("DAME DESU YO !\n"); // 'no you can't!'
	}

	if (mPelletView || stateID == 1) {
		mStateMachine->transit(this, 0);
	} else {
		mStateMachine->transit(this, 2);
	}

	stopMotion();
	int color;
	int type;
	if (pelletMgr->decomposeNumberPellet(mConfig->mModelId.mId, color, type)) {
		f32 heights[4] = {
			3.3f,
			7.0f,
			13.0f,
			18.0f,
		};
		EffectMgr::effTypeTable effects[4] = {
			EffectMgr::EFF_Empl_01,
			EffectMgr::EFF_Empl_05,
			EffectMgr::EFF_Empl_10,
			EffectMgr::EFF_Empl_20,
		};
		Vector3f pos(mPosition);
		pos.y += heights[type];
		mCurrentPelletHeight   = heights[type];
		mCurrentPelletPosition = pos;

		zen::particleGenerator* ptclGen = effectMgr->create(effects[type], pos, nullptr, nullptr);
		if (ptclGen) {
			ptclGen->setEmitPosPtr(&mCurrentPelletPosition);
			_4A0 = 90;
		} else {
			_4A0 = 0;
		}
	} else {
		_4A0 = 0;
	}

	mIsAIActive = true;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void Pellet::startAppear()
{
	mTargetGoal  = nullptr;
	mPikiCarrier = nullptr;
	if (!mPelletView) {
		mAnimator.startMotion(PaniMotionInfo(0));
		mMotionSpeed = 30.0f;
	}
	mStateMachine->transit(this, 2);
}

/*
 * --INFO--
 * Address:	80097234
 * Size:	000060
 */
void Pellet::doAnimation()
{
	if (mShapeObject) {
		mAnimator.updateAnimation(mMotionSpeed, 30.0f);
	}

	if (mPelletView) {
		static_cast<PelletView*>(mPelletView)->viewDoAnimation();
	}
}

/*
 * --INFO--
 * Address:	80097298
 * Size:	000088
 */
void Pellet::refresh(Graphics& gfx)
{
	int state = getState();
	if (state == 3 && !pelletMgr->isMovieFlag(1)) {
		return;
	}

	if (state == 0 && mPickOffset != 0.0f && !pelletMgr->isMovieFlag(2)) {
		return;
	}

	if (pelletMgr->isMovieFlag(4)) {
		DualCreature::refresh(gfx);
	}
}

/*
 * --INFO--
 * Address:	80097320
 * Size:	000088
 */
void Pellet::postUpdate(int p1, f32 p2)
{
	int state = getState();
	if (state == 3 && !pelletMgr->isMovieFlag(1)) {
		return;
	}

	if (state == 0 && mPickOffset != 0.0f && !pelletMgr->isMovieFlag(2)) {
		return;
	}

	if (pelletMgr->isMovieFlag(4)) {
		DualCreature::postUpdate(p1, p2);
	}
}

/*
 * --INFO--
 * Address:	800973A8
 * Size:	00094C
 */
void Pellet::update()
{
	mLastPosition   = mPosition;
	bool isOnGround = onGround();
	if (isOnGround && !mIsAIActive && mConfig->mBounceSoundID() != -1) {
		playEventSound(this, bounceSounds[mConfig->mBounceSoundID()]);
		if (getY() < 0.12f) {
			PRINT("*** PELLET FLICK PIKIS !!!\n");
			InteractFlick flick(this, 100.0f, 0.0f, FLICK_BACKWARDS_ANGLE);
			interactStickers(this, flick, nullptr);
		}
	}

	mIsAIActive = isOnGround;
	int state   = getState();

	if (state == 3 && !(pelletMgr->mMovieFlags & 1)) {
		mVolatileVelocity.set(0.0f, 0.0f, 0.0f);
		return;
	}

	if (state == 0 && mPickOffset != 0.0f && !pelletMgr->isMovieFlag(2)) {
		mVolatileVelocity.set(0.0f, 0.0f, 0.0f);
		return;
	}

	if (!pelletMgr->isMovieFlag(4)) {
		mVolatileVelocity.set(0.0f, 0.0f, 0.0f);
		return;
	}

	if (_4A0) {
		_4A0--;
		mCurrentPelletPosition = mPosition;
		mCurrentPelletPosition.y += mCurrentPelletHeight;
	}

	Stickers stuckList(this);
	Iterator iter(&stuckList);
	int carryCount = 0;
	CI_LOOP(iter)
	{
		Creature* piki = *iter;
		if (piki && piki->isPiki()) {
			carryCount++;
		}
	}

	mCarrierCounter      = carryCount;
	f32 height           = getCylinderHeight();
	mLifeGauge.mPosition = mPosition;
	mLifeGauge.mPosition.y += height + 5.0f;
	mCollisionRadius = height * 0.5f;

	if (mPickOffset != 0.0f) {
		bool isFinishPick = false;
		if (!mStickListHead) {
			isFinishPick = true;
			PRINT("NO-STICKER- FINISH PICK\n");
		} else if (mPikiCarrier && mPikiCarrier->isPiki()) {
			Stickers stuckList2(this);
			Iterator iter2(&stuckList2);
			int carryCount2 = 0;
			CI_LOOP(iter2)
			{
				Creature* piki = *iter2;
				if (piki && piki->isPiki()) {
					carryCount2++;
				}
			}

			mCarrierCounter = carryCount2;
			if (carryCount2 < mConfig->mCarryMinPikis()) {
				isFinishPick = true;
				PRINT("SHONINZU- FINISH PICK!\n");
			}
		}

		if (isFinishPick) {
			mPikiCarrier = nullptr;
			finishPick();
			return;
		}
	}

	if (mPikiCarrier) {
		if (!mStickListHead) {
			mPikiCarrier = nullptr;
			finishPick();
			return;
		}

		if (onGround()) {
			mVelocity.x = mCarryDirection.x;
			mVelocity.z = mCarryDirection.z;
			mVelocity.y += mCarryDirection.y;
		}

		if (mapMgr->getMinY(mPosition.x, mPosition.z, true) > mPosition.y) {
			PRINT("** YABAI YO!\n");
		}

		bool isTekiAttached    = false;
		Creature* attachedTeki = nullptr;
		if (mPikiCarrier->isPiki()) {
			Stickers stuckList3(this);
			Iterator iter3(&stuckList3);
			u32 badCompiler;
			bool isOnlyPiki = true;
			CI_LOOP(iter3)
			{
				Creature* stuck = *iter3;
				if (stuck->isTeki()) {
					isOnlyPiki   = false;
					attachedTeki = stuck;
					break;
				}
			}

			if (!isOnlyPiki) {
				isTekiAttached = true;
			}

			if (isOnlyPiki && mCarrierCounter == 0) {
				stopEventSound(this, SE_LIFT_MOVE);
				stopEventSound(this, SE_LIFT_TRY);
			}
		}

		f32 targetAngle;
		if (isTekiAttached) {
			Vector3f tekiDir = mPosition - attachedTeki->mPosition;
			targetAngle      = atan2f(tekiDir.x, tekiDir.z);
		} else {
			Vector3f targetDir = mPikiCarrier->mPosition - mPosition;
			targetAngle        = atan2f(targetDir.x, targetDir.z);
		}

		f32 angle = angDist(atan2f(mVelocity.x, mVelocity.z), targetAngle);
		if (zen::Abs(angle) > PI / 20.0f) {
			f32 val = ((6.0f / getBottomRadius()) * 0.7f);
			rotateY(gsys->getFrameTime() * angle * val);
		}
	} else if (mFloorTri) {
		f32 rate    = 3.0f * gsys->getFrameTime();
		mVelocity.x = mVelocity.x - mVelocity.x * rate;
		mVelocity.z = mVelocity.z - mVelocity.z * rate;
	}

	// removed nan check here
	mStateMachine->exec(this);
	// removed nan check here
	DualCreature::update();
	// removed nan check here

	if (mFloorTri && isDynFlag(1)) {
		mVelocity = mVelocity - mVelocity * 2.0f * gsys->getFrameTime();
	}
}

/*
 * --INFO--
 * Address:	80097D34
 * Size:	000050
 */
void Pellet::bounceCallback()
{
	MsgBounce msg(Vector3f(0.0f, 1.0f, 0.0f));
	sendMsg(&msg);
}

/*
 * --INFO--
 * Address:	80097D84
 * Size:	000020
 */
void Pellet::collisionCallback(CollEvent& event)
{
	if (isCreatureFlag(CF_AllowFixPosition) && isCreatureFlag(CF_IsPositionFixed)) {
		resetCreatureFlag(CF_IsPositionFixed);
	}
}

/*
 * --INFO--
 * Address:	80097DA4
 * Size:	000074
 */
bool Pellet::stimulate(Interaction& interaction)
{
	if (interaction.actCommon(this)) {
		return interaction.actPellet(this);
	}
	return false;
}

/*
 * --INFO--
 * Address:	80097E18
 * Size:	0002F8
 */
void Pellet::doRender(Graphics& gfx, Matrix4f& mtx)
{
	if (mStuckMouthPart) {
		Matrix4f jointMtx = mStuckMouthPart->getJointMatrix();
		Matrix4f transformMtx;
		f32 scale = 1.0f / reinterpret_cast<Vector3f*>(&jointMtx)->length();
		transformMtx.makeSRT(Vector3f(scale, scale, scale), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f));
		mPosition = mStuckMouthPart->mCentre;
		jointMtx.multiplyTo(transformMtx, mtx);
	}

	if (mPelletView) {
		if (aiCullable()) {
			static_cast<PelletView*>(mPelletView)->viewDraw(gfx, mtx);
		}
		return;
	}

	gfx.useMatrix(Matrix4f::ident, 0);
	mAnimator.updateContext();

	if (mConfig->mPelletColor() != PELCOLOR_NULL) {
		f32 val = mConfig->mPelletColor();
		mShapeDynMaterials.animate(&val);
	} else if (isUfoParts()) {
		mShapeDynMaterials.animate(nullptr);
	}

	mShapeObject->mShape->updateAnim(gfx, mtx, nullptr);
	if (mCollInfo) {
		mCollInfo->updateInfo(gfx, false);
	}

	if (aiCullable()) {
		mShapeObject->mShape->drawshape(gfx, *gfx.mCamera, &mShapeDynMaterials);
	}
}

/*
 * --INFO--
 * Address:	80098110
 * Size:	0001BC
 */
void Pellet::doCreateColls(Graphics& gfx)
{
	u32 badCompiler[2]; // this is ACTUALLY from unused temps according to the DLL

	mMass              = 0.0f;
	f32 rad            = getBottomRadius();
	f32 firstPtclSize  = 0.75f;
	f32 secondPtclSize = 0.0f;
	int collNum        = mConfig->_C0();

	if (mPelletView) {
		rad *= static_cast<PelletView*>(mPelletView)->viewGetScale().x;
	}

	for (int i = 0; i < collNum; i++) {
		f32 angle = (TAU / collNum) * i;
		Vector3f ptclPos(rad * cosf(angle), 0.0f, rad * sinf(angle));
		addParticle(firstPtclSize, ptclPos);

		ptclPos.set(rad * cosf(angle), 0.0f, rad * sinf(angle));

		ptclPos.y += (mPelletView) ? getCylinderHeight() : getCylinderHeight() * mConfig->mPelletScale();
		addParticle(secondPtclSize, ptclPos);
	}
}

/*
 * --INFO--
 * Address:	800982CC
 * Size:	000064
 */
bool InteractSwallow::actPellet(Pellet* pellet)
{
	if (pellet->getState() == 3) {
		return false;
	}
	pellet->mStuckMouthPart = mMouthPart;
	pellet->startStickMouth(mOwner, mMouthPart);
	return true;
}

/*
 * --INFO--
 * Address:	80098330
 * Size:	000148
 */
bool InteractKill::actPellet(Pellet* pellet)
{
	if (pellet->mStuckMouthPart) {
		Stickers stuckList(pellet);
		Iterator iter(&stuckList);
		CI_LOOP(iter)
		{
			(*iter)->kill(false);
			iter.dec();
		}
	}
	pellet->kill(false);
	return true;
}

/*
 * --INFO--
 * Address:	80098478
 * Size:	000058
 */
bool PelletMgr::decomposeNumberPellet(u32 id, int& color, int& type)
{
	for (int i = 0; i < 20; i++) {
		if (id == numberPellets[i].mPelletID) {
			color = numberPellets[i].mPelletColor;
			type  = numberPellets[i].mPelletType;
			return true;
		}
	}
	return false;
}

/*
 * --INFO--
 * Address:	800984D0
 * Size:	000068
 */
void PelletMgr::registerUfoParts()
{
	PRINT("BEGIN\n");
	FOREACH_NODE(CoreNode, mConfigList.mChild, node)
	{
		PelletConfig* config = static_cast<PelletConfig*>(node);
		if (config->mPelletType() == PELTYPE_UfoPart) {
			playerState->registerUfoParts(config->mUfoPartIndex, config->mModelId.mId, config->mPelletId.mId);
		}
	}
}

/*
 * --INFO--
 * Address:	80098538
 * Size:	000078
 */
Pellet* PelletMgr::newNumberPellet(int color, int type)
{
	NumberPel* num = numberPellets;
	u32 id         = 0;
	for (num; num->mPelletColor != PELCOLOR_NULL; num++) {
		if (color == num->mPelletColor && type == num->mPelletType) {
			id = num->mPelletID;
			break;
		}
	}

	if (id) {
		return newPellet(id, nullptr);
	}

	PRINT("color(%d) size(%d) is not valid!\n", color, type);
	return nullptr;
}

/*
 * --INFO--
 * Address:	800985B0
 * Size:	000154
 */
Pellet* PelletMgr::newPellet(u32 pelletID, PelletView* view)
{
	PelletConfig* config = getConfig(pelletID);
	if (!config) {
		return nullptr;
	}

	if (config->mModelId.match('tk**', '*') && !view) {
		PRINT("** newPellet( %s, 0 ) ! teki : use becomepellet!\n", config->mModelId.mStringID);
		PRINT("** newPellet( %s, 0 ) ! teki : use becomepellet!\n", config->mModelId.mStringID);
		ERROR("nakata!");
	}

	if (view) {
		if (config) {
			Pellet* pellet = static_cast<Pellet*>(birth());
			if (pellet) {
				pellet->initPellet(view, config);
			}
			return pellet;
		}
	} else {
		PelletShapeObject* obj = getShapeObject(pelletID);
		PRINT("pellet birth *******\n");
		ID32 pelID(pelletID);
		pelID.print();

		if (config && obj) {
			Pellet* pellet = static_cast<Pellet*>(birth());
			if (pellet) {
				pellet->initPellet(obj, config);
			}
			PRINT("init pellet done ***\n");
			return pellet;
		}
	}

	return nullptr;
}

/*
 * --INFO--
 * Address:	80098704
 * Size:	000094
 */
PelletShapeObject* PelletMgr::getShapeObject(u32 pelletID)
{
	PelletConfig* config = getConfig(pelletID);
	if (!config) {
		return nullptr;
	}

	FOREACH_NODE(CoreNode, mAnimInfoList.mChild, node)
	{
		PelletAnimInfo* info = static_cast<PelletAnimInfo*>(node);
		if (info->mID.mId == config->mPelletId.mId) {
			return info->mPelletShapeObject;
		}
	}

	PRINT("no PelletShapeObject for %s\n", ID32(pelletID).mStringID);
	return nullptr;
}

/*
 * --INFO--
 * Address:	80098798
 * Size:	000054
 */
Creature* PelletMgr::createObject()
{
	Pellet* pellet = new Pellet();
	pellet->mProps = mPelletProps;
	return pellet;
}

/*
 * --INFO--
 * Address:	800987EC
 * Size:	000254
 */
PelletMgr::PelletMgr(MapMgr* mgr)
{
	mUfoMotionTable = PaniPelletAnimator::createMotionTable();
	mAnimInfoList.initCore("");
	mAnimInfoNum = 0;
	mPelletProps = new PelletProp();
	mConfigNum   = 0;
	mReadStage   = 0;
	load("parms/", "pelMgr.bin", 1);
	create(96);
	mMovieFlags = PELMOVIE_Unk1 | PELMOVIE_Unk2 | PELMOVIE_Unk3;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
bool PelletMgr::useShape(u32 pelletID)
{
	FOREACH_NODE(UseNode, mUseList.mChild, node)
	{
		if (node->mPelletID == pelletID) {
			return true;
		}
	}
	return false;
}

/*
 * --INFO--
 * Address:	80098B04
 * Size:	0000F0
 */
void PelletMgr::addUseList(u32 pelletID)
{
	if (!useShape(pelletID)) {
		UseNode* newNode   = new UseNode();
		newNode->mPelletID = pelletID;
		mUseList.add(newNode);
	}
}

/*
 * --INFO--
 * Address:	80098BF4
 * Size:	000054
 */
void PelletMgr::initShapeInfos()
{
	mReadStage = 1;
	load("objects/", "pelAnim.bin", 1);
	createShapeObjects();
}

/*
 * --INFO--
 * Address:	80098C48
 * Size:	000040
 */
int PelletMgr::getConfigIndex(u32 pelletID)
{
	int idx = 0;
	FOREACH_NODE(CoreNode, mConfigList.mChild, node)
	{
		PelletConfig* config = static_cast<PelletConfig*>(node);
		if (config->mModelId.mId == pelletID) {
			return idx;
		}
		idx++;
	}
	return -1;
}

/*
 * --INFO--
 * Address:	80098C88
 * Size:	00009C
 */
PelletConfig* PelletMgr::getConfigFromIdx(int idx)
{
	if (idx < 0 || idx >= mConfigNum) {
		return nullptr;
	}

	CoreNode* config = mConfigList.mChild;
	for (int i = 0; i < idx; i++) {
		config = config->mNext;
	}
	return static_cast<PelletConfig*>(config);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
ID32 PelletMgr::getConfigIdAt(int idx)
{

	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80098D24
 * Size:	000038
 */
PelletConfig* PelletMgr::getConfig(u32 pelletID)
{
	FOREACH_NODE(CoreNode, mConfigList.mChild, node)
	{
		PelletConfig* config = static_cast<PelletConfig*>(node);
		if (config->mModelId.mId == pelletID) {
			return config;
		}
	}

	return nullptr;
}

/*
 * --INFO--
 * Address:	80098D5C
 * Size:	000044
 */
void PelletMgr::read(RandomAccessStream& input)
{
	switch (mReadStage) {
	case 0:
		readConfigs(input);
		break;
	case 1:
		readAnimInfos(input);
		break;
	}
}

/*
 * --INFO--
 * Address:	80098DA0
 * Size:	0000BC
 */
void PelletMgr::readConfigs(RandomAccessStream& input)
{
	mConfigNum = input.readInt();

	for (int i = 0; i < mConfigNum; i++) {
		PelletConfig* config = new PelletConfig();
		config->read(input);
		mConfigList.add(config);
	}
}

/*
 * --INFO--
 * Address:	80098E5C
 * Size:	0000BC
 */
void PelletMgr::readAnimInfos(RandomAccessStream& input)
{
	mAnimInfoNum = input.readInt();

	for (int i = 0; i < mAnimInfoNum; i++) {
		PelletAnimInfo* info = new PelletAnimInfo();
		info->read(input);
		mAnimInfoList.add(info);
	}
}

/*
 * --INFO--
 * Address:	80098F18
 * Size:	0000D4
 */
void PelletMgr::initTekiNakaParts()
{
	FOREACH_NODE(CoreNode, mAnimInfoList.mChild, node)
	{
		PelletAnimInfo* info = static_cast<PelletAnimInfo*>(node);
		if (useShape(info->mID.mId) && !info->mPelletShapeObject && info->mID.match('un**', '*')) {
			PRINT("*** NAKA PARTS (%s)\n", info->mID.mStringID);
			if (info->createShapeObject()) {
				PRINT("NAKA (%s) create done !\n", info->mID.mStringID);
			} else {
				ERROR("failed to create NAKA SHAPEOBJECT\n");
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80098FEC
 * Size:	0000DC
 */
void PelletMgr::createShapeObjects()
{
	FOREACH_NODE(CoreNode, mAnimInfoList.mChild, node)
	{
		PelletAnimInfo* info = static_cast<PelletAnimInfo*>(node);
		bool doCreate        = false;
		switch (info->mCreationType) {
		case 0:
			doCreate = true;
			break;
		case 1:
			doCreate = useShape(info->mID.mId);
			break;
		case 2:
			doCreate = tekiMgr->mUsingType[info->mTekiType];
			break;
		case 3:
			PRINT("NOT YET\n");
			break;
		}

		if (doCreate) {
			if (!info->createShapeObject()) {
				PRINT("FAILED TO CREATE SHAPEOBJECT for %s\n", info->mID.mStringID);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	800990C8
 * Size:	000210
 */
void PelletMgr::refresh(Graphics& gfx)
{
	MonoObjectMgr::refresh(gfx);
	Iterator iter(this);
	CI_LOOP(iter)
	{
		Pellet* pellet = static_cast<Pellet*>(*iter);
		if (AIPerf::kandoOnly) {
			gfx.setColour(Colour(0, 255, 0, 255), true);
			char buf[16];
			if (pellet->isFrontFace()) {
				sprintf(buf, "front");
			} else {
				sprintf(buf, "back");
			}

			Vector3f pos(pellet->mPosition);
			pos.y += pellet->getCylinderHeight();
			pos.multMatrix(gfx.mCamera->mLookAtMtx);
			int val = -(gsys->mConsFont->stringWidth(buf) / 2);
			gfx.perspPrintf(gsys->mConsFont, pos, val, 0, buf);
		}
	}
}

/*
 * --INFO--
 * Address:	800992D8
 * Size:	000004
 */
void PelletMgr::refresh2d(Graphics&)
{
}

PelletMgr* pelletMgr;
