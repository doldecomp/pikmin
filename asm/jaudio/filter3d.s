.include "macros.inc"

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 8001BC00 00018B60  4B FE FF 21 */	bl DSP_FlushChannel__FUc
/* 8001BC04 00018B64  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8001BC08 00018B68  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8001BC0C 00018B6C  38 21 00 18 */	addi r1, r1, 0x18
/* 8001BC10 00018B70  7C 08 03 A6 */	mtlr r0
/* 8001BC14 00018B74  4E 80 00 20 */	blr 
/* 8001BC18 00018B78  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */
/* 8001BC1C 00018B7C  00 00 00 00 */	.4byte 0x00000000  /* unknown instruction */

.global Play_DirectPCM__FP6dspch_PsUsUl
Play_DirectPCM__FP6dspch_PsUsUl:
/* 8001BC20 00018B80  7C 08 02 A6 */	mflr r0
/* 8001BC24 00018B84  90 01 00 04 */	stw r0, 4(r1)
/* 8001BC28 00018B88  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8001BC2C 00018B8C  BF 81 00 18 */	stmw r28, 0x18(r1)
/* 8001BC30 00018B90  3B 83 00 00 */	addi r28, r3, 0
/* 8001BC34 00018B94  3B A4 00 00 */	addi r29, r4, 0
/* 8001BC38 00018B98  3B C5 00 00 */	addi r30, r5, 0
/* 8001BC3C 00018B9C  3B E6 00 00 */	addi r31, r6, 0
/* 8001BC40 00018BA0  88 63 00 00 */	lbz r3, 0(r3)
/* 8001BC44 00018BA4  4B FE F9 1D */	bl GetDspHandle__FUc
/* 8001BC48 00018BA8  93 A3 01 18 */	stw r29, 0x118(r3)
/* 8001BC4C 00018BAC  38 00 00 00 */	li r0, 0
/* 8001BC50 00018BB0  38 A0 00 21 */	li r5, 0x21
/* 8001BC54 00018BB4  38 80 00 00 */	li r4, 0
/* 8001BC58 00018BB8  B0 03 01 02 */	sth r0, 0x102(r3)
/* 8001BC5C 00018BBC  57 C0 80 1E */	slwi r0, r30, 0x10
/* 8001BC60 00018BC0  B0 A3 01 00 */	sth r5, 0x100(r3)
/* 8001BC64 00018BC4  93 E3 00 74 */	stw r31, 0x74(r3)
/* 8001BC68 00018BC8  93 A3 01 10 */	stw r29, 0x110(r3)
/* 8001BC6C 00018BCC  90 03 01 14 */	stw r0, 0x114(r3)
/* 8001BC70 00018BD0  88 7C 00 00 */	lbz r3, 0(r28)
/* 8001BC74 00018BD4  4B FE F9 6D */	bl DSP_SetMixerInitDelayMax__FUcUc
/* 8001BC78 00018BD8  3B E0 00 00 */	li r31, 0
lbl_8001BC7C:
/* 8001BC7C 00018BDC  28 1F 00 02 */	cmplwi r31, 2

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 8005A794 000576F4  90 1F 00 04 */	stw r0, 4(r31)
/* 8005A798 000576F8  7F E4 FB 78 */	mr r4, r31
/* 8005A79C 000576FC  80 7E 00 34 */	lwz r3, 0x34(r30)
/* 8005A7A0 00057700  81 83 00 04 */	lwz r12, 4(r3)
/* 8005A7A4 00057704  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8005A7A8 00057708  7D 88 03 A6 */	mtlr r12
/* 8005A7AC 0005770C  4E 80 00 21 */	blrl 
/* 8005A7B0 00057710  80 DF 03 10 */	lwz r6, 0x310(r31)
/* 8005A7B4 00057714  38 A1 01 28 */	addi r5, r1, 0x128
/* 8005A7B8 00057718  80 1F 03 0C */	lwz r0, 0x30c(r31)
/* 8005A7BC 0005771C  7F E3 FB 78 */	mr r3, r31
/* 8005A7C0 00057720  38 81 00 C4 */	addi r4, r1, 0xc4
/* 8005A7C4 00057724  93 41 01 28 */	stw r26, 0x128(r1)
/* 8005A7C8 00057728  93 41 01 2C */	stw r26, 0x12c(r1)
/* 8005A7CC 0005772C  90 01 01 30 */	stw r0, 0x130(r1)
/* 8005A7D0 00057730  90 C1 01 34 */	stw r6, 0x134(r1)
/* 8005A7D4 00057734  81 9F 03 B4 */	lwz r12, 0x3b4(r31)
/* 8005A7D8 00057738  81 8C 00 40 */	lwz r12, 0x40(r12)
/* 8005A7DC 0005773C  7D 88 03 A6 */	mtlr r12
/* 8005A7E0 00057740  4E 80 00 21 */	blrl 
/* 8005A7E4 00057744  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 8005A7E8 00057748  28 00 00 00 */	cmplwi r0, 0
/* 8005A7EC 0005774C  40 82 00 1C */	bne lbl_8005A808
/* 8005A7F0 00057750  80 6D 2E 84 */	lwz r3, menuWindow@sda21(r13)
/* 8005A7F4 00057754  28 03 00 00 */	cmplwi r3, 0
/* 8005A7F8 00057758  41 82 00 10 */	beq lbl_8005A808
/* 8005A7FC 0005775C  7F E4 FB 78 */	mr r4, r31
/* 8005A800 00057760  48 13 89 CD */	bl draw__Q23zen12ogScrMenuMgrFR8Graphics
/* 8005A804 00057764  98 6D 2E 80 */	stb r3, menuOn@sda21(r13)
lbl_8005A808:
/* 8005A808 00057768  80 DF 03 10 */	lwz r6, 0x310(r31)
/* 8005A80C 0005776C  3B 40 00 00 */	li r26, 0
/* 8005A810 00057770  80 1F 03 0C */	lwz r0, 0x30c(r31)

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 801708C4 0016D824  80 6D 2F 6C */	lwz r3, playerState@sda21(r13)
/* 801708C8 0016D828  38 80 00 31 */	li r4, 0x31
/* 801708CC 0016D82C  38 63 00 70 */	addi r3, r3, 0x70
/* 801708D0 0016D830  4B F1 31 31 */	bl setOn__11ResultFlagsFi
/* 801708D4 0016D834  48 00 24 2C */	b lbl_80172D00
lbl_801708D8:
/* 801708D8 0016D838  7F E3 FB 78 */	mr r3, r31
/* 801708DC 0016D83C  4B FF E0 F1 */	bl attackTransit__6KingAiFv
/* 801708E0 0016D840  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 801708E4 0016D844  41 82 00 90 */	beq lbl_80170974
/* 801708E8 0016D848  80 7F 00 04 */	lwz r3, 4(r31)
/* 801708EC 0016D84C  38 80 00 05 */	li r4, 5
/* 801708F0 0016D850  38 00 00 00 */	li r0, 0
/* 801708F4 0016D854  90 83 02 E8 */	stw r4, 0x2e8(r3)
/* 801708F8 0016D858  38 BF 00 00 */	addi r5, r31, 0
/* 801708FC 0016D85C  38 61 0A 28 */	addi r3, r1, 0xa28
/* 80170900 0016D860  80 DF 00 04 */	lwz r6, 4(r31)
/* 80170904 0016D864  38 80 00 08 */	li r4, 8
/* 80170908 0016D868  98 06 02 BD */	stb r0, 0x2bd(r6)
/* 8017090C 0016D86C  80 DF 00 04 */	lwz r6, 4(r31)
/* 80170910 0016D870  90 06 02 EC */	stw r0, 0x2ec(r6)
/* 80170914 0016D874  98 1F 00 09 */	stb r0, 9(r31)
/* 80170918 0016D878  90 1F 00 1C */	stw r0, 0x1c(r31)
/* 8017091C 0016D87C  4B FA E6 71 */	bl __ct__14PaniMotionInfoFiP19PaniAnimKeyListener
/* 80170920 0016D880  80 BF 00 04 */	lwz r5, 4(r31)
/* 80170924 0016D884  38 83 00 00 */	addi r4, r3, 0
/* 80170928 0016D888  38 65 03 3C */	addi r3, r5, 0x33c
/* 8017092C 0016D88C  4B FA E8 95 */	bl startMotion__12PaniAnimatorFR14PaniMotionInfo
/* 80170930 0016D890  80 7F 00 04 */	lwz r3, 4(r31)
/* 80170934 0016D894  C0 22 AC BC */	lfs f1, lbl_803EAEBC@sda21(r2)
/* 80170938 0016D898  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8017093C 0016D89C  48 00 31 5D */	bl initBlending__8KingBodyFf
/* 80170940 0016D8A0  80 7F 00 04 */	lwz r3, 4(r31)

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803E8520
lbl_803E8520:
	.4byte 0x42800000
.global lbl_803E8524
lbl_803E8524:
	.4byte 0x3A83126F

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
	.4byte 0x00000000
.global "@1704"
"@1704":
	.4byte 0x40080000

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global "@2593"
"@2593":
	.4byte 0x3FE00000
	.4byte 0x00000000

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803E8CC0
lbl_803E8CC0:
	.4byte 0x41A00000
.global lbl_803E8CC4
lbl_803E8CC4:
	.4byte 0x3DCCCCCD

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803EB0E8
lbl_803EB0E8:
	.4byte 0x447A0000
.global lbl_803EB0EC
lbl_803EB0EC:
	.4byte 0x3F000000
