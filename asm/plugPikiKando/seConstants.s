.include "macros.inc"

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 800E2738 000DF698  80 19 00 28 */	lwz r0, 0x28(r25)
/* 800E273C 000DF69C  38 80 00 00 */	li r4, 0
/* 800E2740 000DF6A0  80 79 00 38 */	lwz r3, 0x38(r25)
/* 800E2744 000DF6A4  7C 00 D9 D6 */	mullw r0, r0, r27
/* 800E2748 000DF6A8  7F E3 02 14 */	add r31, r3, r0
/* 800E274C 000DF6AC  80 1F 00 6C */	lwz r0, 0x6c(r31)
/* 800E2750 000DF6B0  2C 00 00 00 */	cmpwi r0, 0
/* 800E2754 000DF6B4  41 82 00 0C */	beq lbl_800E2760
/* 800E2758 000DF6B8  2C 00 00 36 */	cmpwi r0, 0x36
/* 800E275C 000DF6BC  40 82 00 08 */	bne lbl_800E2764
lbl_800E2760:
/* 800E2760 000DF6C0  38 80 00 01 */	li r4, 1
lbl_800E2764:
/* 800E2764 000DF6C4  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 800E2768 000DF6C8  40 82 00 20 */	bne lbl_800E2788
/* 800E276C 000DF6CC  38 7F 00 40 */	addi r3, r31, 0x40
/* 800E2770 000DF6D0  4B FB 1A 21 */	bl aiCulling__8FastGridFv
/* 800E2774 000DF6D4  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E2778 000DF6D8  41 82 00 10 */	beq lbl_800E2788
/* 800E277C 000DF6DC  80 1F 00 C8 */	lwz r0, 0xc8(r31)
/* 800E2780 000DF6E0  54 00 03 19 */	rlwinm. r0, r0, 0, 0xc, 0xc
/* 800E2784 000DF6E4  40 82 01 FC */	bne lbl_800E2980
lbl_800E2788:
/* 800E2788 000DF6E8  3B 5B 00 01 */	addi r26, r27, 1
/* 800E278C 000DF6EC  57 5E 10 3A */	slwi r30, r26, 2
/* 800E2790 000DF6F0  48 00 01 E4 */	b lbl_800E2974
lbl_800E2794:
/* 800E2794 000DF6F4  80 79 00 3C */	lwz r3, 0x3c(r25)
/* 800E2798 000DF6F8  7C 03 F0 2E */	lwzx r0, r3, r30
/* 800E279C 000DF6FC  2C 00 00 00 */	cmpwi r0, 0
/* 800E27A0 000DF700  41 80 01 CC */	blt lbl_800E296C
/* 800E27A4 000DF704  80 79 00 28 */	lwz r3, 0x28(r25)
/* 800E27A8 000DF708  88 0D 2F AC */	lbz r0, useUpdateMgr__6AIPerf@sda21(r13)
/* 800E27AC 000DF70C  7C 63 D1 D6 */	mullw r3, r3, r26
/* 800E27B0 000DF710  80 99 00 38 */	lwz r4, 0x38(r25)
/* 800E27B4 000DF714  28 00 00 00 */	cmplwi r0, 0
/* 800E27B8 000DF718  7F 84 1A 14 */	add r28, r4, r3
/* 800E27BC 000DF71C  41 82 00 24 */	beq lbl_800E27E0
/* 800E27C0 000DF720  38 7F 01 68 */	addi r3, r31, 0x168
/* 800E27C4 000DF724  4B FC 2C 95 */	bl updatable__13UpdateContextFv
/* 800E27C8 000DF728  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E27CC 000DF72C  40 82 00 14 */	bne lbl_800E27E0
/* 800E27D0 000DF730  38 7C 01 68 */	addi r3, r28, 0x168
/* 800E27D4 000DF734  4B FC 2C 85 */	bl updatable__13UpdateContextFv
/* 800E27D8 000DF738  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E27DC 000DF73C  41 82 01 90 */	beq lbl_800E296C
lbl_800E27E0:
/* 800E27E0 000DF740  80 1C 00 6C */	lwz r0, 0x6c(r28)
/* 800E27E4 000DF744  38 60 00 00 */	li r3, 0
/* 800E27E8 000DF748  2C 00 00 00 */	cmpwi r0, 0
/* 800E27EC 000DF74C  41 82 00 0C */	beq lbl_800E27F8
/* 800E27F0 000DF750  2C 00 00 36 */	cmpwi r0, 0x36
/* 800E27F4 000DF754  40 82 00 08 */	bne lbl_800E27FC
lbl_800E27F8:
/* 800E27F8 000DF758  38 60 00 01 */	li r3, 1
lbl_800E27FC:
/* 800E27FC 000DF75C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E2800 000DF760  40 82 00 20 */	bne lbl_800E2820
/* 800E2804 000DF764  38 7C 00 40 */	addi r3, r28, 0x40
/* 800E2808 000DF768  4B FB 19 89 */	bl aiCulling__8FastGridFv
/* 800E280C 000DF76C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E2810 000DF770  41 82 00 10 */	beq lbl_800E2820
/* 800E2814 000DF774  80 1C 00 C8 */	lwz r0, 0xc8(r28)
/* 800E2818 000DF778  54 00 03 19 */	rlwinm. r0, r0, 0, 0xc, 0xc
/* 800E281C 000DF77C  40 82 01 50 */	bne lbl_800E296C
lbl_800E2820:
/* 800E2820 000DF780  80 0D A0 F0 */	lwz r0, useGrid__6AIPerf@sda21(r13)
/* 800E2824 000DF784  2C 00 00 00 */	cmpwi r0, 0
/* 800E2828 000DF788  41 82 00 48 */	beq lbl_800E2870
/* 800E282C 000DF78C  7F 83 E3 78 */	mr r3, r28
/* 800E2830 000DF790  81 9C 00 00 */	lwz r12, 0(r28)
/* 800E2834 000DF794  81 8C 00 64 */	lwz r12, 0x64(r12)
/* 800E2838 000DF798  7D 88 03 A6 */	mtlr r12
/* 800E283C 000DF79C  4E 80 00 21 */	blrl 
/* 800E2840 000DF7A0  7F E3 FB 78 */	mr r3, r31
/* 800E2844 000DF7A4  FF A0 08 90 */	fmr f29, f1
/* 800E2848 000DF7A8  81 9F 00 00 */	lwz r12, 0(r31)
/* 800E284C 000DF7AC  81 8C 00 64 */	lwz r12, 0x64(r12)
/* 800E2850 000DF7B0  7D 88 03 A6 */	mtlr r12
/* 800E2854 000DF7B4  4E 80 00 21 */	blrl 
/* 800E2858 000DF7B8  EC 21 E8 2A */	fadds f1, f1, f29
/* 800E285C 000DF7BC  38 7F 00 40 */	addi r3, r31, 0x40
/* 800E2860 000DF7C0  38 9C 00 40 */	addi r4, r28, 0x40
/* 800E2864 000DF7C4  4B FB 1B 8D */	bl doCulling__8FastGridFRC8FastGridf
/* 800E2868 000DF7C8  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 800E286C 000DF7CC  40 82 01 00 */	bne lbl_800E296C
lbl_800E2870:
/* 800E2870 000DF7D0  38 7F 00 00 */	addi r3, r31, 0
/* 800E2874 000DF7D4  38 9C 00 00 */	addi r4, r28, 0
/* 800E2878 000DF7D8  4B FA 91 B9 */	bl centreDist__FP8CreatureP8Creature
/* 800E287C 000DF7DC  7F 83 E3 78 */	mr r3, r28
/* 800E2880 000DF7E0  FF A0 08 90 */	fmr f29, f1
/* 800E2884 000DF7E4  81 9C 00 00 */	lwz r12, 0(r28)
/* 800E2888 000DF7E8  81 8C 00 64 */	lwz r12, 0x64(r12)
/* 800E288C 000DF7EC  7D 88 03 A6 */	mtlr r12

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 801F8868 001F57C8  54 84 07 B8 */	rlwinm r4, r4, 0, 0x1e, 0x1c
/* 801F886C 001F57CC  38 63 68 00 */	addi r3, r3, 0xCC006800@l
/* 801F8870 001F57D0  90 9E 00 0C */	stw r4, 0xc(r30)
/* 801F8874 001F57D4  7C 63 02 14 */	add r3, r3, r0
/* 801F8878 001F57D8  83 A3 00 00 */	lwz r29, 0(r3)
/* 801F887C 001F57DC  73 A0 04 05 */	andi. r0, r29, 0x405
/* 801F8880 001F57E0  90 03 00 00 */	stw r0, 0(r3)
/* 801F8884 001F57E4  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 801F8888 001F57E8  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 801F888C 001F57EC  41 82 00 30 */	beq lbl_801F88BC
/* 801F8890 001F57F0  2C 1F 00 01 */	cmpwi r31, 1
/* 801F8894 001F57F4  41 82 00 20 */	beq lbl_801F88B4
/* 801F8898 001F57F8  40 80 00 24 */	bge lbl_801F88BC
/* 801F889C 001F57FC  2C 1F 00 00 */	cmpwi r31, 0
/* 801F88A0 001F5800  40 80 00 08 */	bge lbl_801F88A8
/* 801F88A4 001F5804  48 00 00 18 */	b lbl_801F88BC
lbl_801F88A8:
/* 801F88A8 001F5808  3C 60 00 10 */	lis r3, 0x10
/* 801F88AC 001F580C  48 00 0A F9 */	bl __OSUnmaskInterrupts
/* 801F88B0 001F5810  48 00 00 0C */	b lbl_801F88BC
lbl_801F88B4:
/* 801F88B4 001F5814  3C 60 00 02 */	lis r3, 2
/* 801F88B8 001F5818  48 00 0A ED */	bl __OSUnmaskInterrupts
lbl_801F88BC:
/* 801F88BC 001F581C  7F 83 E3 78 */	mr r3, r28
/* 801F88C0 001F5820  48 00 06 E5 */	bl OSRestoreInterrupts
/* 801F88C4 001F5824  2C 1F 00 02 */	cmpwi r31, 2
/* 801F88C8 001F5828  41 82 00 2C */	beq lbl_801F88F4
/* 801F88CC 001F582C  57 A0 06 31 */	rlwinm. r0, r29, 0, 0x18, 0x18
/* 801F88D0 001F5830  41 82 00 24 */	beq lbl_801F88F4
/* 801F88D4 001F5834  7F E3 FB 78 */	mr r3, r31
/* 801F88D8 001F5838  4B FF FA 9D */	bl EXIProbe
/* 801F88DC 001F583C  2C 03 00 00 */	cmpwi r3, 0
/* 801F88E0 001F5840  41 82 00 0C */	beq lbl_801F88EC
/* 801F88E4 001F5844  38 60 00 01 */	li r3, 1
/* 801F88E8 001F5848  48 00 00 10 */	b lbl_801F88F8
lbl_801F88EC:
/* 801F88EC 001F584C  38 60 00 00 */	li r3, 0
/* 801F88F0 001F5850  48 00 00 08 */	b lbl_801F88F8
lbl_801F88F4:
/* 801F88F4 001F5854  38 60 00 01 */	li r3, 1
lbl_801F88F8:
/* 801F88F8 001F5858  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801F88FC 001F585C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801F8900 001F5860  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801F8904 001F5864  7C 08 03 A6 */	mtlr r0
/* 801F8908 001F5868  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801F890C 001F586C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 801F8910 001F5870  38 21 00 20 */	addi r1, r1, 0x20
/* 801F8914 001F5874  4E 80 00 20 */	blr 

.global EXIIntrruptHandler
EXIIntrruptHandler:
/* 801F8918 001F5878  7C 08 02 A6 */	mflr r0
/* 801F891C 001F587C  7C 65 07 34 */	extsh r5, r3
/* 801F8920 001F5880  90 01 00 04 */	stw r0, 4(r1)
/* 801F8924 001F5884  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 801F8928 001F5888  38 05 FF F7 */	addi r0, r5, -9
/* 801F892C 001F588C  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 801F8930 001F5890  94 21 FF F8 */	stwu r1, -8(r1)
/* 801F8934 001F5894  7C 63 00 96 */	mulhw r3, r3, r0
/* 801F8938 001F5898  54 60 0F FE */	srwi r0, r3, 0x1f
/* 801F893C 001F589C  7C 63 02 14 */	add r3, r3, r0
/* 801F8940 001F58A0  3C A0 CC 00 */	lis r5, 0xCC006800@ha
/* 801F8944 001F58A4  39 05 68 00 */	addi r8, r5, 0xCC006800@l
/* 801F8948 001F58A8  1C 03 00 14 */	mulli r0, r3, 0x14
/* 801F894C 001F58AC  7D 08 02 14 */	add r8, r8, r0
/* 801F8950 001F58B0  80 E8 00 00 */	lwz r7, 0(r8)
/* 801F8954 001F58B4  1C C3 00 38 */	mulli r6, r3, 0x38
/* 801F8958 001F58B8  70 E7 07 F5 */	andi. r7, r7, 0x7f5
/* 801F895C 001F58BC  3C A0 80 3D */	lis r5, Ecb@ha
/* 801F8960 001F58C0  38 05 23 F0 */	addi r0, r5, Ecb@l
/* 801F8964 001F58C4  60 E7 00 02 */	ori r7, r7, 2
/* 801F8968 001F58C8  90 E8 00 00 */	stw r7, 0(r8)
/* 801F896C 001F58CC  7C A0 32 14 */	add r5, r0, r6
/* 801F8970 001F58D0  80 05 00 00 */	lwz r0, 0(r5)
/* 801F8974 001F58D4  28 00 00 00 */	cmplwi r0, 0
/* 801F8978 001F58D8  7C 0C 03 78 */	mr r12, r0
/* 801F897C 001F58DC  41 82 00 0C */	beq lbl_801F8988
/* 801F8980 001F58E0  7D 88 03 A6 */	mtlr r12
/* 801F8984 001F58E4  4E 80 00 21 */	blrl 
lbl_801F8988:
/* 801F8988 001F58E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801F898C 001F58EC  38 21 00 08 */	addi r1, r1, 8
/* 801F8990 001F58F0  7C 08 03 A6 */	mtlr r0
/* 801F8994 001F58F4  4E 80 00 20 */	blr 

.global TCIntrruptHandler
TCIntrruptHandler:
/* 801F8998 001F58F8  7C 08 02 A6 */	mflr r0
/* 801F899C 001F58FC  7C 66 07 34 */	extsh r6, r3
/* 801F89A0 001F5900  90 01 00 04 */	stw r0, 4(r1)
/* 801F89A4 001F5904  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 801F89A8 001F5908  38 06 FF F6 */	addi r0, r6, -10
/* 801F89AC 001F590C  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 801F89B0 001F5910  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801F89B4 001F5914  7C 63 00 96 */	mulhw r3, r3, r0
/* 801F89B8 001F5918  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 801F89BC 001F591C  93 C1 00 28 */	stw r30, 0x28(r1)

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
  .4byte 0x7365436f
  .4byte 0x6e737461
  .4byte 0x6e74732e
  .4byte 0x63707000
  .4byte 0x7365436f
  .4byte 0x6e737461
  .4byte 0x6e740000
.global lbl_802B1D2C
lbl_802B1D2C:
	.4byte 0x736F756E
	.4byte 0x642E6269
	.4byte 0x6E000000
	.4byte 0x5061726D
	.4byte 0x3C666C6F
	.4byte 0x61743E00
	.4byte 0x42617365
	.4byte 0x5061726D
	.4byte 0x00000000
	.4byte 0x803DFA44
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x5365436F
	.4byte 0x6E737461
	.4byte 0x6E740000
	.4byte 0x436F7265
	.4byte 0x4E6F6465
	.4byte 0x00000000
	.4byte 0x803DFA54
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x803DFA54
	.4byte 0x00000000
	.4byte 0x803DFA5C
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x803DFA54
	.4byte 0x00000000
	.4byte 0x803DFA5C
	.4byte 0x00000000
	.4byte 0x803DFA6C
	.4byte 0x00000000
	.4byte 0x00000000
.global __vt__10SeConstant
__vt__10SeConstant:
  .4byte __RTTI__10SeConstant
  .4byte 0
  .4byte getAgeNodeType__5ANodeFv
  .4byte read__10SeConstantFR18RandomAccessStream
  .4byte update__4NodeFv
  .4byte draw__4NodeFR8Graphics
  .4byte render__4NodeFR8Graphics
  .4byte concat__4NodeFv
  .4byte concat__4NodeFR3VQS
  .4byte concat__4NodeFR3SRT
  .4byte concat__4NodeFR8Matrix4f
  .4byte getModelMatrix__4NodeFv
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0
  .4byte 0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
  .4byte 0x802b1c1c
.global __RTTI__5SeWin
__RTTI__5SeWin:
  .4byte 0x803df9cc
  .4byte 0x802b1c30
  .4byte 0x53654d67
  .4byte 0x72000000
  .4byte 0x4e6f6465
  .4byte 0
  .4byte 0x803dfa0c
  .4byte 0x802b1c94
.global __RTTI__5SeMgr
__RTTI__5SeMgr:
  .4byte 0x803dfa04
  .4byte 0x802b1ca8
  .4byte 0
.global lbl_803DFA28
lbl_803DFA28:
	.4byte 0x3C4E6F64
	.4byte 0x653E0000
.global lbl_803DFA30
lbl_803DFA30:
	.4byte 0x70303000
.global lbl_803DFA34
lbl_803DFA34:
	.4byte 0x70303100
.global lbl_803DFA38
lbl_803DFA38:
	.4byte 0x70303200
.global lbl_803DFA3C
lbl_803DFA3C:
	.4byte 0x7061726D
	.4byte 0x732F0000
	.4byte 0x802B1D44
	.4byte 0x00000000
	.4byte 0x414E6F64

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803EA594
lbl_803EA594:
	.4byte 0x41A00000
.global lbl_803EA598
lbl_803EA598:
	.4byte 0x3E99999A
.global lbl_803EA59C
lbl_803EA59C:
	.4byte 0x3DCCCCCD
.global lbl_803EA5A0
lbl_803EA5A0:
	.4byte 0x42700000

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803EBC6C
lbl_803EBC6C:
	.4byte 0x46FFFE00
.global lbl_803EBC70
lbl_803EBC70:
	.4byte 0x3F59999A
.global lbl_803EBC74
lbl_803EBC74:
	.4byte 0x3F000000
.global "@3136"
"@3136":
	.4byte 0x43300000
