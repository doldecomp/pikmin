.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global GXSetTevIndirect
GXSetTevIndirect:
/* 80212BC8 0020FB28  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80212BCC 0020FB2C  54 84 07 B6 */	rlwinm r4, r4, 0, 0x1e, 0x1b
/* 80212BD0 0020FB30  54 A0 10 3A */	slwi r0, r5, 2
/* 80212BD4 0020FB34  7C 80 03 78 */	or r0, r4, r0
/* 80212BD8 0020FB38  81 61 00 34 */	lwz r11, 0x34(r1)
/* 80212BDC 0020FB3C  54 05 07 30 */	rlwinm r5, r0, 0, 0x1c, 0x18
/* 80212BE0 0020FB40  89 81 00 33 */	lbz r12, 0x33(r1)
/* 80212BE4 0020FB44  54 C0 20 36 */	slwi r0, r6, 4
/* 80212BE8 0020FB48  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212BEC 0020FB4C  7C A0 03 78 */	or r0, r5, r0
/* 80212BF0 0020FB50  54 05 06 6C */	rlwinm r5, r0, 0, 0x19, 0x16
/* 80212BF4 0020FB54  55 60 38 30 */	slwi r0, r11, 7
/* 80212BF8 0020FB58  7C A0 03 78 */	or r0, r5, r0
/* 80212BFC 0020FB5C  54 05 05 E4 */	rlwinm r5, r0, 0, 0x17, 0x12
/* 80212C00 0020FB60  54 E0 48 2C */	slwi r0, r7, 9
/* 80212C04 0020FB64  7C A0 03 78 */	or r0, r5, r0
/* 80212C08 0020FB68  54 05 04 DE */	rlwinm r5, r0, 0, 0x13, 0xf
/* 80212C0C 0020FB6C  55 00 68 24 */	slwi r0, r8, 0xd
/* 80212C10 0020FB70  7C A0 03 78 */	or r0, r5, r0
/* 80212C14 0020FB74  38 A3 00 10 */	addi r5, r3, 0x10
/* 80212C18 0020FB78  54 03 04 18 */	rlwinm r3, r0, 0, 0x10, 0xc
/* 80212C1C 0020FB7C  55 20 80 1E */	slwi r0, r9, 0x10
/* 80212C20 0020FB80  7C 60 03 78 */	or r0, r3, r0
/* 80212C24 0020FB84  54 03 03 56 */	rlwinm r3, r0, 0, 0xd, 0xb
/* 80212C28 0020FB88  55 80 98 18 */	slwi r0, r12, 0x13
/* 80212C2C 0020FB8C  7C 60 03 78 */	or r0, r3, r0
/* 80212C30 0020FB90  54 03 03 14 */	rlwinm r3, r0, 0, 0xc, 0xa
/* 80212C34 0020FB94  55 40 A1 16 */	rlwinm r0, r10, 0x14, 4, 0xb
/* 80212C38 0020FB98  7C 66 03 78 */	or r6, r3, r0
/* 80212C3C 0020FB9C  38 00 00 61 */	li r0, 0x61
/* 80212C40 0020FBA0  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 80212C44 0020FBA4  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 80212C48 0020FBA8  54 A0 C0 0E */	slwi r0, r5, 0x18
/* 80212C4C 0020FBAC  50 C0 02 3E */	rlwimi r0, r6, 0, 8, 0x1f
/* 80212C50 0020FBB0  90 03 80 00 */	stw r0, 0xCC008000@l(r3)
/* 80212C54 0020FBB4  38 00 00 01 */	li r0, 1
/* 80212C58 0020FBB8  38 21 00 28 */	addi r1, r1, 0x28
/* 80212C5C 0020FBBC  B0 04 00 02 */	sth r0, 2(r4)
/* 80212C60 0020FBC0  4E 80 00 20 */	blr 

.global GXSetIndTexCoordScale
GXSetIndTexCoordScale:
/* 80212C64 0020FBC4  2C 03 00 02 */	cmpwi r3, 2
/* 80212C68 0020FBC8  41 82 00 F4 */	beq lbl_80212D5C
/* 80212C6C 0020FBCC  40 80 00 14 */	bge lbl_80212C80
/* 80212C70 0020FBD0  2C 03 00 00 */	cmpwi r3, 0
/* 80212C74 0020FBD4  41 82 00 18 */	beq lbl_80212C8C
/* 80212C78 0020FBD8  40 80 00 7C */	bge lbl_80212CF4
/* 80212C7C 0020FBDC  48 00 01 AC */	b lbl_80212E28
lbl_80212C80:
/* 80212C80 0020FBE0  2C 03 00 04 */	cmpwi r3, 4
/* 80212C84 0020FBE4  40 80 01 A4 */	bge lbl_80212E28
/* 80212C88 0020FBE8  48 00 01 3C */	b lbl_80212DC4
lbl_80212C8C:
/* 80212C8C 0020FBEC  80 CD 2A 68 */	lwz r6, gx@sda21(r13)
/* 80212C90 0020FBF0  54 A3 20 36 */	slwi r3, r5, 4
/* 80212C94 0020FBF4  38 00 00 61 */	li r0, 0x61
/* 80212C98 0020FBF8  38 E6 01 28 */	addi r7, r6, 0x128
/* 80212C9C 0020FBFC  80 C6 01 28 */	lwz r6, 0x128(r6)
/* 80212CA0 0020FC00  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80212CA4 0020FC04  54 C6 00 36 */	rlwinm r6, r6, 0, 0, 0x1b
/* 80212CA8 0020FC08  7C C4 23 78 */	or r4, r6, r4
/* 80212CAC 0020FC0C  90 87 00 00 */	stw r4, 0(r7)
/* 80212CB0 0020FC10  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212CB4 0020FC14  38 C4 01 28 */	addi r6, r4, 0x128
/* 80212CB8 0020FC18  80 84 01 28 */	lwz r4, 0x128(r4)
/* 80212CBC 0020FC1C  54 84 07 2E */	rlwinm r4, r4, 0, 0x1c, 0x17
/* 80212CC0 0020FC20  7C 83 1B 78 */	or r3, r4, r3
/* 80212CC4 0020FC24  90 66 00 00 */	stw r3, 0(r6)
/* 80212CC8 0020FC28  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212CCC 0020FC2C  38 83 01 28 */	addi r4, r3, 0x128
/* 80212CD0 0020FC30  80 63 01 28 */	lwz r3, 0x128(r3)
/* 80212CD4 0020FC34  54 63 02 3E */	clrlwi r3, r3, 8
/* 80212CD8 0020FC38  64 63 25 00 */	oris r3, r3, 0x2500
/* 80212CDC 0020FC3C  90 64 00 00 */	stw r3, 0(r4)
/* 80212CE0 0020FC40  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80212CE4 0020FC44  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212CE8 0020FC48  80 03 01 28 */	lwz r0, 0x128(r3)
/* 80212CEC 0020FC4C  90 05 80 00 */	stw r0, 0xCC008000@l(r5)
/* 80212CF0 0020FC50  48 00 01 38 */	b lbl_80212E28
lbl_80212CF4:
/* 80212CF4 0020FC54  80 ED 2A 68 */	lwz r7, gx@sda21(r13)
/* 80212CF8 0020FC58  54 A3 60 26 */	slwi r3, r5, 0xc
/* 80212CFC 0020FC5C  84 A7 01 28 */	lwzu r5, 0x128(r7)
/* 80212D00 0020FC60  54 86 40 2E */	slwi r6, r4, 8
/* 80212D04 0020FC64  38 00 00 61 */	li r0, 0x61
/* 80212D08 0020FC68  54 A5 06 26 */	rlwinm r5, r5, 0, 0x18, 0x13
/* 80212D0C 0020FC6C  7C A5 33 78 */	or r5, r5, r6
/* 80212D10 0020FC70  90 A7 00 00 */	stw r5, 0(r7)
/* 80212D14 0020FC74  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80212D18 0020FC78  80 AD 2A 68 */	lwz r5, gx@sda21(r13)
/* 80212D1C 0020FC7C  38 C5 01 28 */	addi r6, r5, 0x128
/* 80212D20 0020FC80  80 A5 01 28 */	lwz r5, 0x128(r5)
/* 80212D24 0020FC84  54 A5 05 1E */	rlwinm r5, r5, 0, 0x14, 0xf
/* 80212D28 0020FC88  7C A3 1B 78 */	or r3, r5, r3
/* 80212D2C 0020FC8C  90 66 00 00 */	stw r3, 0(r6)
/* 80212D30 0020FC90  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212D34 0020FC94  38 A3 01 28 */	addi r5, r3, 0x128
/* 80212D38 0020FC98  80 63 01 28 */	lwz r3, 0x128(r3)
/* 80212D3C 0020FC9C  54 63 02 3E */	clrlwi r3, r3, 8
/* 80212D40 0020FCA0  64 63 25 00 */	oris r3, r3, 0x2500
/* 80212D44 0020FCA4  90 65 00 00 */	stw r3, 0(r5)
/* 80212D48 0020FCA8  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80212D4C 0020FCAC  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212D50 0020FCB0  80 03 01 28 */	lwz r0, 0x128(r3)
/* 80212D54 0020FCB4  90 04 80 00 */	stw r0, 0xCC008000@l(r4)
/* 80212D58 0020FCB8  48 00 00 D0 */	b lbl_80212E28
lbl_80212D5C:
/* 80212D5C 0020FCBC  80 CD 2A 68 */	lwz r6, gx@sda21(r13)
/* 80212D60 0020FCC0  54 A3 20 36 */	slwi r3, r5, 4
/* 80212D64 0020FCC4  38 00 00 61 */	li r0, 0x61
/* 80212D68 0020FCC8  38 E6 01 2C */	addi r7, r6, 0x12c
/* 80212D6C 0020FCCC  80 C6 01 2C */	lwz r6, 0x12c(r6)
/* 80212D70 0020FCD0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80212D74 0020FCD4  54 C6 00 36 */	rlwinm r6, r6, 0, 0, 0x1b
/* 80212D78 0020FCD8  7C C4 23 78 */	or r4, r6, r4
/* 80212D7C 0020FCDC  90 87 00 00 */	stw r4, 0(r7)
/* 80212D80 0020FCE0  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212D84 0020FCE4  38 C4 01 2C */	addi r6, r4, 0x12c
/* 80212D88 0020FCE8  80 84 01 2C */	lwz r4, 0x12c(r4)
/* 80212D8C 0020FCEC  54 84 07 2E */	rlwinm r4, r4, 0, 0x1c, 0x17
/* 80212D90 0020FCF0  7C 83 1B 78 */	or r3, r4, r3
/* 80212D94 0020FCF4  90 66 00 00 */	stw r3, 0(r6)
/* 80212D98 0020FCF8  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212D9C 0020FCFC  38 83 01 2C */	addi r4, r3, 0x12c
/* 80212DA0 0020FD00  80 63 01 2C */	lwz r3, 0x12c(r3)
/* 80212DA4 0020FD04  54 63 02 3E */	clrlwi r3, r3, 8
/* 80212DA8 0020FD08  64 63 26 00 */	oris r3, r3, 0x2600
/* 80212DAC 0020FD0C  90 64 00 00 */	stw r3, 0(r4)
/* 80212DB0 0020FD10  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80212DB4 0020FD14  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212DB8 0020FD18  80 03 01 2C */	lwz r0, 0x12c(r3)
/* 80212DBC 0020FD1C  90 05 80 00 */	stw r0, 0xCC008000@l(r5)
/* 80212DC0 0020FD20  48 00 00 68 */	b lbl_80212E28
lbl_80212DC4:
/* 80212DC4 0020FD24  80 ED 2A 68 */	lwz r7, gx@sda21(r13)
/* 80212DC8 0020FD28  54 A3 60 26 */	slwi r3, r5, 0xc
/* 80212DCC 0020FD2C  84 A7 01 2C */	lwzu r5, 0x12c(r7)
/* 80212DD0 0020FD30  54 86 40 2E */	slwi r6, r4, 8
/* 80212DD4 0020FD34  38 00 00 61 */	li r0, 0x61
/* 80212DD8 0020FD38  54 A5 06 26 */	rlwinm r5, r5, 0, 0x18, 0x13
/* 80212DDC 0020FD3C  7C A5 33 78 */	or r5, r5, r6
/* 80212DE0 0020FD40  90 A7 00 00 */	stw r5, 0(r7)
/* 80212DE4 0020FD44  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80212DE8 0020FD48  80 AD 2A 68 */	lwz r5, gx@sda21(r13)
/* 80212DEC 0020FD4C  38 C5 01 2C */	addi r6, r5, 0x12c
/* 80212DF0 0020FD50  80 A5 01 2C */	lwz r5, 0x12c(r5)
/* 80212DF4 0020FD54  54 A5 05 1E */	rlwinm r5, r5, 0, 0x14, 0xf
/* 80212DF8 0020FD58  7C A3 1B 78 */	or r3, r5, r3
/* 80212DFC 0020FD5C  90 66 00 00 */	stw r3, 0(r6)
/* 80212E00 0020FD60  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212E04 0020FD64  38 A3 01 2C */	addi r5, r3, 0x12c
/* 80212E08 0020FD68  80 63 01 2C */	lwz r3, 0x12c(r3)
/* 80212E0C 0020FD6C  54 63 02 3E */	clrlwi r3, r3, 8
/* 80212E10 0020FD70  64 63 26 00 */	oris r3, r3, 0x2600
/* 80212E14 0020FD74  90 65 00 00 */	stw r3, 0(r5)
/* 80212E18 0020FD78  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80212E1C 0020FD7C  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212E20 0020FD80  80 03 01 2C */	lwz r0, 0x12c(r3)
/* 80212E24 0020FD84  90 04 80 00 */	stw r0, 0xCC008000@l(r4)
lbl_80212E28:
/* 80212E28 0020FD88  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212E2C 0020FD8C  38 00 00 01 */	li r0, 1
/* 80212E30 0020FD90  B0 03 00 02 */	sth r0, 2(r3)
/* 80212E34 0020FD94  4E 80 00 20 */	blr 

.global GXSetNumIndStages
GXSetNumIndStages:
/* 80212E38 0020FD98  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212E3C 0020FD9C  54 60 82 1E */	rlwinm r0, r3, 0x10, 8, 0xf
/* 80212E40 0020FDA0  84 64 02 04 */	lwzu r3, 0x204(r4)
/* 80212E44 0020FDA4  54 63 04 18 */	rlwinm r3, r3, 0, 0x10, 0xc
/* 80212E48 0020FDA8  7C 60 03 78 */	or r0, r3, r0
/* 80212E4C 0020FDAC  90 04 00 00 */	stw r0, 0(r4)
/* 80212E50 0020FDB0  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212E54 0020FDB4  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 80212E58 0020FDB8  60 00 00 06 */	ori r0, r0, 6
/* 80212E5C 0020FDBC  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 80212E60 0020FDC0  4E 80 00 20 */	blr 

.global GXSetTevDirect
GXSetTevDirect:
/* 80212E64 0020FDC4  7C 08 02 A6 */	mflr r0
/* 80212E68 0020FDC8  38 80 00 00 */	li r4, 0
/* 80212E6C 0020FDCC  90 01 00 04 */	stw r0, 4(r1)
/* 80212E70 0020FDD0  38 00 00 00 */	li r0, 0
/* 80212E74 0020FDD4  38 A0 00 00 */	li r5, 0
/* 80212E78 0020FDD8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80212E7C 0020FDDC  38 C0 00 00 */	li r6, 0
/* 80212E80 0020FDE0  38 E0 00 00 */	li r7, 0
/* 80212E84 0020FDE4  90 01 00 08 */	stw r0, 8(r1)
/* 80212E88 0020FDE8  39 00 00 00 */	li r8, 0
/* 80212E8C 0020FDEC  39 20 00 00 */	li r9, 0
/* 80212E90 0020FDF0  90 01 00 0C */	stw r0, 0xc(r1)
/* 80212E94 0020FDF4  39 40 00 00 */	li r10, 0
/* 80212E98 0020FDF8  4B FF FD 31 */	bl GXSetTevIndirect
/* 80212E9C 0020FDFC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80212EA0 0020FE00  38 21 00 18 */	addi r1, r1, 0x18
/* 80212EA4 0020FE04  7C 08 03 A6 */	mtlr r0
/* 80212EA8 0020FE08  4E 80 00 20 */	blr 

.global __GXUpdateBPMask
__GXUpdateBPMask:
/* 80212EAC 0020FE0C  80 6D 2A 68 */	lwz r3, gx@sda21(r13)
/* 80212EB0 0020FE10  38 C0 00 00 */	li r6, 0
/* 80212EB4 0020FE14  38 80 00 00 */	li r4, 0
/* 80212EB8 0020FE18  80 03 02 04 */	lwz r0, 0x204(r3)
/* 80212EBC 0020FE1C  54 00 87 7E */	rlwinm r0, r0, 0x10, 0x1d, 0x1f
/* 80212EC0 0020FE20  28 00 00 00 */	cmplwi r0, 0
/* 80212EC4 0020FE24  7C 09 03 A6 */	mtctr r0
/* 80212EC8 0020FE28  40 81 00 6C */	ble lbl_80212F34
lbl_80212ECC:
/* 80212ECC 0020FE2C  2C 04 00 02 */	cmpwi r4, 2
/* 80212ED0 0020FE30  41 82 00 3C */	beq lbl_80212F0C
/* 80212ED4 0020FE34  40 80 00 14 */	bge lbl_80212EE8
/* 80212ED8 0020FE38  2C 04 00 00 */	cmpwi r4, 0
/* 80212EDC 0020FE3C  41 82 00 18 */	beq lbl_80212EF4
/* 80212EE0 0020FE40  40 80 00 20 */	bge lbl_80212F00
/* 80212EE4 0020FE44  48 00 00 3C */	b lbl_80212F20
lbl_80212EE8:
/* 80212EE8 0020FE48  2C 04 00 04 */	cmpwi r4, 4
/* 80212EEC 0020FE4C  40 80 00 34 */	bge lbl_80212F20
/* 80212EF0 0020FE50  48 00 00 28 */	b lbl_80212F18
lbl_80212EF4:
/* 80212EF4 0020FE54  80 03 01 20 */	lwz r0, 0x120(r3)
/* 80212EF8 0020FE58  54 05 07 7E */	clrlwi r5, r0, 0x1d
/* 80212EFC 0020FE5C  48 00 00 24 */	b lbl_80212F20
lbl_80212F00:
/* 80212F00 0020FE60  80 03 01 20 */	lwz r0, 0x120(r3)
/* 80212F04 0020FE64  54 05 D7 7E */	rlwinm r5, r0, 0x1a, 0x1d, 0x1f
/* 80212F08 0020FE68  48 00 00 18 */	b lbl_80212F20
lbl_80212F0C:
/* 80212F0C 0020FE6C  80 03 01 20 */	lwz r0, 0x120(r3)
/* 80212F10 0020FE70  54 05 A7 7E */	rlwinm r5, r0, 0x14, 0x1d, 0x1f
/* 80212F14 0020FE74  48 00 00 0C */	b lbl_80212F20
lbl_80212F18:
/* 80212F18 0020FE78  80 03 01 20 */	lwz r0, 0x120(r3)
/* 80212F1C 0020FE7C  54 05 77 7E */	rlwinm r5, r0, 0xe, 0x1d, 0x1f
lbl_80212F20:
/* 80212F20 0020FE80  38 00 00 01 */	li r0, 1
/* 80212F24 0020FE84  7C 00 28 30 */	slw r0, r0, r5
/* 80212F28 0020FE88  7C C6 03 78 */	or r6, r6, r0
/* 80212F2C 0020FE8C  38 84 00 01 */	addi r4, r4, 1
/* 80212F30 0020FE90  42 00 FF 9C */	bdnz lbl_80212ECC
lbl_80212F34:
/* 80212F34 0020FE94  38 83 01 24 */	addi r4, r3, 0x124
/* 80212F38 0020FE98  80 63 01 24 */	lwz r3, 0x124(r3)
/* 80212F3C 0020FE9C  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80212F40 0020FEA0  7C 00 30 40 */	cmplw r0, r6
/* 80212F44 0020FEA4  4D 82 00 20 */	beqlr 
/* 80212F48 0020FEA8  54 60 00 2E */	rlwinm r0, r3, 0, 0, 0x17
/* 80212F4C 0020FEAC  7C 00 33 78 */	or r0, r0, r6
/* 80212F50 0020FEB0  90 04 00 00 */	stw r0, 0(r4)
/* 80212F54 0020FEB4  38 00 00 61 */	li r0, 0x61
/* 80212F58 0020FEB8  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80212F5C 0020FEBC  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80212F60 0020FEC0  38 00 00 01 */	li r0, 1
/* 80212F64 0020FEC4  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212F68 0020FEC8  80 64 01 24 */	lwz r3, 0x124(r4)
/* 80212F6C 0020FECC  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80212F70 0020FED0  B0 04 00 02 */	sth r0, 2(r4)
/* 80212F74 0020FED4  4E 80 00 20 */	blr 

.global __GXFlushTextureState
__GXFlushTextureState:
/* 80212F78 0020FED8  38 00 00 61 */	li r0, 0x61
/* 80212F7C 0020FEDC  80 8D 2A 68 */	lwz r4, gx@sda21(r13)
/* 80212F80 0020FEE0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80212F84 0020FEE4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80212F88 0020FEE8  38 00 00 01 */	li r0, 1
/* 80212F8C 0020FEEC  80 64 01 24 */	lwz r3, 0x124(r4)
/* 80212F90 0020FEF0  90 65 80 00 */	stw r3, 0xCC008000@l(r5)
/* 80212F94 0020FEF4  B0 04 00 02 */	sth r0, 2(r4)
/* 80212F98 0020FEF8  4E 80 00 20 */	blr 
