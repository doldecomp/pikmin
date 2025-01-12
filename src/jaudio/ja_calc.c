#include "types.h"
#include "std/Math.h"
#include "jaudio/calc.h"
#include "Dolphin/math.h"
#include "stl/math.h"

static f32 SINTABLE[257];

/*
 * --INFO--
 * Address:	8000DC20
 * Size:	000020
 */
f32 sqrtf2(f32 x)
{
	return std::sqrtf(x);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
void cosf2(f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000DCC0
 * Size:	000024
 */
f32 atanf2(f32 x, f32 y)
{
	return atan2(x, y);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
void sinf2(f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000DD00
 * Size:	000088
 */
void Jac_InitSinTable()
{
	for (u32 i = 0; i < 257; i++) {
		SINTABLE[i] = sinf(HALF_PI * f32(i) * 0.00390625f);
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x38(r1)
	  addi      r11, r1, 0x38
	  bl        0x207150
	  stmw      r28, 0x10(r1)
	  lis       r3, 0x8031
	  lfs       f29, -0x7F48(r2)
	  lfd       f30, -0x7F40(r2)
	  subi      r30, r3, 0x2520
	  lfs       f31, -0x7F44(r2)
	  li        r28, 0
	  li        r31, 0
	  lis       r29, 0x4330

	.loc_0x38:
	  stw       r28, 0xC(r1)
	  stw       r29, 0x8(r1)
	  lfd       f0, 0x8(r1)
	  fsubs     f0, f0, f30
	  fmuls     f0, f29, f0
	  fmuls     f1, f0, f31
	  bl        0x20DF98
	  addi      r28, r28, 0x1
	  add       r3, r30, r31
	  cmplwi    r28, 0x101
	  stfs      f1, 0x0(r3)
	  addi      r31, r31, 0x4
	  blt+      .loc_0x38
	  lwz       r0, 0x3C(r1)
	  addi      r11, r1, 0x38
	  bl        0x207138
	  lmw       r28, 0x10(r1)
	  addi      r1, r1, 0x38
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address:	8000DDA0
 * Size:	000034
 */
f32 sinf3(f32 x)
{
	return SINTABLE[int(256.0f * x)];
}
