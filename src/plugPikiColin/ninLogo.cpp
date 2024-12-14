#include "NinLogoSection.h"
#include "NinLogoSetupSection.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
static void _Error(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F0
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80061250
 * Size:	000180
 */
void NinLogoSection::init()
{
	Node::init("<NinLogoSection>");
	gsys->mTimerState = TS_Off;
	add(new NinLogoSetupSection());
}

/*
 * --INFO--
 * Address:	800614C0
 * Size:	000214
 */
void NinLogoSetupSection::draw(Graphics& gfx)
{

	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x1A8(r1)
	  stmw      r27, 0x194(r1)
	  li        r27, 0
	  mr        r31, r4
	  mr        r30, r3
	  mr        r3, r31
	  lwz       r5, 0x310(r4)
	  lwz       r0, 0x30C(r4)
	  addi      r4, r1, 0x3C
	  stw       r27, 0x3C(r1)
	  stw       r27, 0x40(r1)
	  stw       r0, 0x44(r1)
	  stw       r5, 0x48(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0x48(r12)
	  mtlr      r12
	  blrl
	  lwz       r5, 0x310(r31)
	  addi      r4, r1, 0x2C
	  lwz       r0, 0x30C(r31)
	  mr        r3, r31
	  stw       r27, 0x2C(r1)
	  stw       r27, 0x30(r1)
	  stw       r0, 0x34(r1)
	  stw       r5, 0x38(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0x50(r12)
	  mtlr      r12
	  blrl
	  stb       r27, 0x28(r1)
	  addi      r4, r1, 0x28
	  addi      r3, r31, 0
	  stb       r27, 0x29(r1)
	  stb       r27, 0x2A(r1)
	  stb       r27, 0x2B(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xB4(r12)
	  mtlr      r12
	  blrl
	  mr        r3, r31
	  lwz       r12, 0x3B4(r31)
	  li        r4, 0x3
	  li        r5, 0
	  lwz       r12, 0x38(r12)
	  mtlr      r12
	  blrl
	  lwz       r6, 0x310(r31)
	  addi      r5, r1, 0x18
	  lwz       r0, 0x30C(r31)
	  mr        r3, r31
	  addi      r4, r1, 0x14C
	  stw       r27, 0x18(r1)
	  stw       r27, 0x1C(r1)
	  stw       r0, 0x20(r1)
	  stw       r6, 0x24(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0x40(r12)
	  mtlr      r12
	  blrl
	  li        r28, 0xFF
	  stb       r28, 0x14(r1)
	  li        r29, 0x40
	  addi      r4, r1, 0x14
	  stb       r28, 0x15(r1)
	  mr        r3, r31
	  li        r5, 0x1
	  stb       r29, 0x16(r1)
	  stb       r28, 0x17(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  stb       r28, 0x10(r1)
	  addi      r4, r1, 0x10
	  addi      r3, r31, 0
	  stb       r27, 0x11(r1)
	  stb       r29, 0x12(r1)
	  stb       r28, 0x13(r1)
	  lwz       r12, 0x3B4(r31)
	  lwz       r12, 0xAC(r12)
	  mtlr      r12
	  blrl
	  lwz       r27, 0x2C(r30)
	  cmplwi    r27, 0
	  beq-      .loc_0x1D0
	  lwz       r0, 0x3C(r27)
	  cmpwi     r0, 0
	  beq-      .loc_0x1BC
	  lwz       r28, 0x20(r27)
	  lwz       r0, 0x3C(r28)
	  cmpwi     r0, 0
	  beq-      .loc_0x1AC
	  lwz       r29, 0x20(r28)
	  lwz       r0, 0x3C(r29)
	  cmpwi     r0, 0
	  beq-      .loc_0x19C
	  lwz       r5, 0x20(r29)
	  mr        r3, r30
	  lfs       f1, -0x78C0(r2)
	  mr        r4, r31
	  bl        .loc_0x214

	.loc_0x19C:
	  lfs       f1, -0x78BC(r2)
	  addi      r3, r29, 0
	  addi      r4, r31, 0
	  bl        -0x3258

	.loc_0x1AC:
	  lfs       f1, -0x78B8(r2)
	  addi      r3, r28, 0
	  addi      r4, r31, 0
	  bl        -0x3268

	.loc_0x1BC:
	  lfs       f1, -0x78C8(r2)
	  addi      r3, r27, 0
	  addi      r4, r31, 0
	  bl        -0x3278
	  b         .loc_0x1E4

	.loc_0x1D0:
	  lwz       r3, 0x2EF8(r13)
	  cmplwi    r3, 0
	  beq-      .loc_0x1E4
	  mr        r4, r31
	  bl        0x17912C

	.loc_0x1E4:
	  lis       r3, 0x803A
	  subi      r3, r3, 0x2848
	  lwz       r6, 0x310(r3)
	  addi      r4, r31, 0
	  lfs       f1, 0x314(r3)
	  li        r5, 0
	  bl        -0x100F4
	  lmw       r27, 0x194(r1)
	  lwz       r0, 0x1AC(r1)
	  addi      r1, r1, 0x1A8
	  mtlr      r0
	  blr

	.loc_0x214:
	*/
}

/*
 * --INFO--
 * Address:	800616D4
 * Size:	0000EC
 */
void NinLogoSetupSection::drawMenu(Graphics&, Menu*, f32)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  stfd      f31, 0x30(r1)
	  fmr       f31, f1
	  stmw      r27, 0x1C(r1)
	  mr        r28, r5
	  addi      r27, r4, 0
	  lwz       r0, 0x3C(r5)
	  cmpwi     r0, 0
	  beq-      .loc_0xC4
	  lwz       r31, 0x20(r28)
	  lwz       r0, 0x3C(r31)
	  cmpwi     r0, 0
	  beq-      .loc_0xB0
	  lwz       r30, 0x20(r31)
	  lwz       r0, 0x3C(r30)
	  cmpwi     r0, 0
	  beq-      .loc_0x98
	  lwz       r29, 0x20(r30)
	  lwz       r0, 0x3C(r29)
	  cmpwi     r0, 0
	  beq-      .loc_0x7C
	  lfs       f1, -0x78B8(r2)
	  mr        r4, r27
	  lwz       r5, 0x20(r29)
	  fmuls     f0, f1, f31
	  fmuls     f0, f1, f0
	  fmuls     f0, f1, f0
	  fmuls     f1, f1, f0
	  bl        .loc_0x0

	.loc_0x7C:
	  lfs       f1, -0x78B8(r2)
	  addi      r3, r29, 0
	  addi      r4, r27, 0
	  fmuls     f0, f1, f31
	  fmuls     f0, f1, f0
	  fmuls     f1, f1, f0
	  bl        -0x3358

	.loc_0x98:
	  lfs       f1, -0x78B8(r2)
	  addi      r3, r30, 0
	  addi      r4, r27, 0
	  fmuls     f0, f1, f31
	  fmuls     f1, f1, f0
	  bl        -0x3370

	.loc_0xB0:
	  lfs       f0, -0x78B8(r2)
	  addi      r3, r31, 0
	  addi      r4, r27, 0
	  fmuls     f1, f0, f31
	  bl        -0x3384

	.loc_0xC4:
	  fmr       f1, f31
	  addi      r3, r28, 0
	  addi      r4, r27, 0
	  bl        -0x3394
	  lmw       r27, 0x1C(r1)
	  lwz       r0, 0x3C(r1)
	  lfd       f31, 0x30(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}
