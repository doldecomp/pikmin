#include "jaudio/centcalc.h"

#include "jaudio/tables.h"

// TODO: This is probably some curve that can be expressed in better terms than a bunch of constant values copied from the DOL.
#define KEY_TABLE_LENGTH (64)
static f32 KEY_TABLE[KEY_TABLE_LENGTH] = {
	1.0000000, 1.0009100, 1.0018210, 1.0027330, 1.0036449, 1.0045590, 1.0054730, 1.0063879, 1.0073040, 1.0082200, 1.0091380,
	1.0100560, 1.0109750, 1.0118960, 1.0128160, 1.0137380, 1.0146610, 1.0155840, 1.0165080, 1.0174330, 1.0183589, 1.0192860,
	1.0202140, 1.0211420, 1.0220710, 1.0230020, 1.0239330, 1.0248640, 1.0257970, 1.0267310, 1.0276650, 1.0286000, 1.0295360,
	1.0304730, 1.0314110, 1.0323499, 1.0332890, 1.0342300, 1.0351710, 1.0361130, 1.0370560, 1.0380000, 1.0389440, 1.0398900,
	1.0408360, 1.0417830, 1.0427310, 1.0436800, 1.0446300, 1.0455810, 1.0465320, 1.0474850, 1.0484380, 1.0493920, 1.0503470,
	1.0513030, 1.0522600, 1.0532170, 1.0541760, 1.0551350, 1.0560950, 1.0570560, 1.0580180, 1.0589809,
};

/*
 * --INFO--
 * Address:	80014BC0
 * Size:	0000CC
 */
f32 Jam_PitchToCent(f32 param_1, f32 param_2)
{
	u32 badCompiler;
	f32 fVar1;
	f32 fVar2;
	s16 sVar3;

	fVar1 = 4.0f * param_1 * param_2;
	sVar3 = fVar1;
	fVar2 = fVar1 - sVar3;
	if (fVar1 < 0.0f && fVar2 != 0.0f) {
		fVar2 += 1.0f;
		sVar3 -= 1;
	}
	if (fVar2 >= 1.0f) {
		fVar2 -= 1.0f;
		sVar3 += 1;
	}
	return C5BASE_PITCHTABLE[sVar3 + 60] * (KEY_TABLE)[(u16)(fVar2 * 64.0f)];
}
