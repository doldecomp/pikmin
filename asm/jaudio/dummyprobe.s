.include "macros.inc"

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 800056A0 00002600  7C C3 33 78 */	mr r3, r6
lbl_800056A4:
/* 800056A4 00002604  38 21 00 28 */	addi r1, r1, 0x28
/* 800056A8 00002608  4E 80 00 20 */	blr 
/* 800056AC 0000260C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800056B0 00002610  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800056B4 00002614  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800056B8 00002618  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 800056BC 0000261C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global Nas_HeapInit__FP6ALHeapPUcl
Nas_HeapInit__FP6ALHeapPUcl:
/* 800056C0 00002620  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800056C4 00002624  28 04 00 00 */	cmplwi r4, 0
/* 800056C8 00002628  38 C0 00 00 */	li r6, 0
/* 800056CC 0000262C  90 61 00 08 */	stw r3, 8(r1)
/* 800056D0 00002630  80 E1 00 08 */	lwz r7, 8(r1)
/* 800056D4 00002634  90 C7 00 0C */	stw r6, 0xc(r7)
/* 800056D8 00002638  40 82 00 14 */	bne lbl_800056EC
/* 800056DC 0000263C  90 C7 00 08 */	stw r6, 8(r7)

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 800371D8 00034138  3B 07 8B C4 */	addi r24, r7, __vt__10RoutePoint@l
/* 800371DC 0003413C  3B FC 00 58 */	addi r31, r28, 0x58
/* 800371E0 00034140  3B DC 00 5C */	addi r30, r28, 0x5c
/* 800371E4 00034144  C3 A2 83 78 */	lfs f29, lbl_803E8578@sda21(r2)
/* 800371E8 00034148  C3 C2 83 7C */	lfs f30, lbl_803E857C@sda21(r2)
/* 800371EC 0003414C  C3 E2 83 80 */	lfs f31, lbl_803E8580@sda21(r2)
/* 800371F0 00034150  48 00 03 18 */	b lbl_80037508
lbl_800371F4:
/* 800371F4 00034154  38 7D 00 00 */	addi r3, r29, 0
/* 800371F8 00034158  38 80 00 01 */	li r4, 1
/* 800371FC 0003415C  48 00 9E B5 */	bl getToken__9CmdStreamFb
/* 80037200 00034160  38 7D 00 00 */	addi r3, r29, 0
/* 80037204 00034164  38 8D 85 78 */	addi r4, r13, lbl_803DD298@sda21
/* 80037208 00034168  48 00 A1 CD */	bl isToken__9CmdStreamFPc
/* 8003720C 0003416C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80037210 00034170  41 82 00 44 */	beq lbl_80037254
/* 80037214 00034174  38 7D 00 00 */	addi r3, r29, 0

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 8021C544 002194A4  7C 08 03 A6 */	mtlr r0
/* 8021C548 002194A8  4E 80 00 20 */	blr 

.global TRKGetFreeBuffer
TRKGetFreeBuffer:
/* 8021C54C 002194AC  7C 08 02 A6 */	mflr r0
/* 8021C550 002194B0  90 01 00 04 */	stw r0, 4(r1)
/* 8021C554 002194B4  38 00 00 00 */	li r0, 0
/* 8021C558 002194B8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8021C55C 002194BC  BF 61 00 0C */	stmw r27, 0xc(r1)
/* 8021C560 002194C0  3B 84 00 00 */	addi r28, r4, 0
/* 8021C564 002194C4  3B 63 00 00 */	addi r27, r3, 0
/* 8021C568 002194C8  3B E0 03 00 */	li r31, 0x300
/* 8021C56C 002194CC  3B C0 00 00 */	li r30, 0
/* 8021C570 002194D0  90 04 00 00 */	stw r0, 0(r4)
/* 8021C574 002194D4  48 00 00 54 */	b lbl_8021C5C8
lbl_8021C578:
/* 8021C578 002194D8  7F C3 F3 78 */	mr r3, r30
/* 8021C57C 002194DC  48 00 00 6D */	bl TRKGetBuffer
/* 8021C580 002194E0  7C 7D 1B 78 */	mr r29, r3

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 80214188 002110E8  7F E3 FB 78 */	mr r3, r31
/* 8021418C 002110EC  4B FF AB D9 */	bl GXSetCPUFifo
/* 80214190 002110F0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80214194 002110F4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80214198 002110F8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8021419C 002110FC  7C 08 03 A6 */	mtlr r0
/* 802141A0 00211100  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802141A4 00211104  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802141A8 00211108  38 21 00 20 */	addi r1, r1, 0x20
/* 802141AC 0021110C  4E 80 00 20 */	blr 

.global GXEndDisplayList
GXEndDisplayList:
/* 802141B0 00211110  7C 08 02 A6 */	mflr r0
/* 802141B4 00211114  3C 80 80 3D */	lis r4, DisplayListFifo@ha
/* 802141B8 00211118  90 01 00 04 */	stw r0, 4(r1)
/* 802141BC 0021111C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802141C0 00211120  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802141C4 00211124  3B E4 3B C8 */	addi r31, r4, DisplayListFifo@l

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 800259B4 00022914  EC 01 00 32 */	fmuls f0, f1, f0
/* 800259B8 00022918  EC 02 00 2A */	fadds f0, f2, f0
/* 800259BC 0002291C  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 800259C0 00022920  80 7E 00 04 */	lwz r3, 4(r30)
/* 800259C4 00022924  C8 22 82 30 */	lfd f1, "@613"@sda21(r2)
/* 800259C8 00022928  38 63 FF FF */	addi r3, r3, -1
/* 800259CC 0002292C  C0 5E 00 1C */	lfs f2, 0x1c(r30)
/* 800259D0 00022930  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800259D4 00022934  90 01 00 28 */	stw r0, 0x28(r1)
/* 800259D8 00022938  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800259DC 0002293C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800259E0 00022940  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800259E4 00022944  4C 41 13 82 */	cror 2, 1, 2
/* 800259E8 00022948  40 82 00 0C */	bne lbl_800259F4
/* 800259EC 0002294C  C0 02 82 2C */	lfs f0, lbl_803E842C@sda21(r2)
/* 800259F0 00022950  D0 1E 00 1C */	stfs f0, 0x1c(r30)

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 80044234 00041194  7C 08 39 D6 */	mullw r0, r8, r7
/* 80044238 00041198  7C E6 59 D6 */	mullw r7, r6, r11
/* 8004423C 0004119C  7C C9 51 D6 */	mullw r6, r9, r10
/* 80044240 000411A0  7C 00 28 50 */	subf r0, r0, r5
/* 80044244 000411A4  7C 0A 01 D6 */	mullw r0, r10, r0
/* 80044248 000411A8  7C 86 20 50 */	subf r4, r6, r4
/* 8004424C 000411AC  7C A8 39 D6 */	mullw r5, r8, r7
/* 80044250 000411B0  7C 84 02 14 */	add r4, r4, r0
/* 80044254 000411B4  7C 09 59 D6 */	mullw r0, r9, r11
/* 80044258 000411B8  7C 84 2A 14 */	add r4, r4, r5
/* 8004425C 000411BC  7C 80 22 14 */	add r4, r0, r4
/* 80044260 000411C0  7C 03 20 AE */	lbzx r0, r3, r4
/* 80044264 000411C4  54 03 06 36 */	rlwinm r3, r0, 0, 0x18, 0x1b
/* 80044268 000411C8  4E 80 00 20 */	blr 
lbl_8004426C:
/* 8004426C 000411CC  80 E3 00 10 */	lwz r7, 0x10(r3)
/* 80044270 000411D0  81 43 00 0C */	lwz r10, 0xc(r3)

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 80207F00 00204E60  41 82 00 18 */	beq lbl_80207F18
/* 80207F04 00204E64  93 FE 00 CC */	stw r31, 0xcc(r30)
/* 80207F08 00204E68  7D 88 03 A6 */	mtlr r12
/* 80207F0C 00204E6C  38 7D 00 00 */	addi r3, r29, 0
/* 80207F10 00204E70  38 80 FF FD */	li r4, -3
/* 80207F14 00204E74  4E 80 00 21 */	blrl 
lbl_80207F18:
/* 80207F18 00204E78  81 9E 00 C4 */	lwz r12, 0xc4(r30)
/* 80207F1C 00204E7C  28 0C 00 00 */	cmplwi r12, 0
/* 80207F20 00204E80  41 82 00 28 */	beq lbl_80207F48
/* 80207F24 00204E84  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80207F28 00204E88  2C 00 00 07 */	cmpwi r0, 7
/* 80207F2C 00204E8C  41 80 00 1C */	blt lbl_80207F48
/* 80207F30 00204E90  38 00 00 00 */	li r0, 0
/* 80207F34 00204E94  7D 88 03 A6 */	mtlr r12
/* 80207F38 00204E98  90 1E 00 C4 */	stw r0, 0xc4(r30)
/* 80207F3C 00204E9C  38 7D 00 00 */	addi r3, r29, 0

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 8015A364 001572C4  38 7F 02 14 */	addi r3, r31, 0x214
/* 8015A368 001572C8  C0 02 A9 F8 */	lfs f0, lbl_803EABF8@sda21(r2)
/* 8015A36C 001572CC  38 9F 02 00 */	addi r4, r31, 0x200
/* 8015A370 001572D0  D0 1F 02 10 */	stfs f0, 0x210(r31)
/* 8015A374 001572D4  80 0D FE 54 */	lwz r0, lbl_803E4B74@sda21(r13)
/* 8015A378 001572D8  90 01 01 98 */	stw r0, 0x198(r1)
/* 8015A37C 001572DC  80 01 01 98 */	lwz r0, 0x198(r1)
/* 8015A380 001572E0  90 01 01 84 */	stw r0, 0x184(r1)
/* 8015A384 001572E4  4B F0 46 FD */	bl __ct__8BaseParmFP10Parameters5ayuID
/* 8015A388 001572E8  93 DF 02 1C */	stw r30, 0x21c(r31)
/* 8015A38C 001572EC  38 A1 01 80 */	addi r5, r1, 0x180
/* 8015A390 001572F0  38 7F 02 24 */	addi r3, r31, 0x224
/* 8015A394 001572F4  C0 02 A9 FC */	lfs f0, lbl_803EABFC@sda21(r2)
/* 8015A398 001572F8  38 9F 02 00 */	addi r4, r31, 0x200
/* 8015A39C 001572FC  D0 1F 02 20 */	stfs f0, 0x220(r31)
/* 8015A3A0 00157300  80 0D FE 58 */	lwz r0, lbl_803E4B78@sda21(r13)
