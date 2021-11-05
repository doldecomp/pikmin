.include "macros.inc"

.section .text, "ax"  # 0x80005560 - 0x80221F60
/* 800EB3D0 000E8330  38 00 00 01 */	li r0, 1
/* 800EB3D4 000E8334  3B 83 00 00 */	addi r28, r3, 0
/* 800EB3D8 000E8338  98 0D 30 6F */	stb r0, containerExitMode__7PikiMgr@sda21(r13)
/* 800EB3DC 000E833C  80 6D 30 68 */	lwz r3, pikiMgr@sda21(r13)
/* 800EB3E0 000E8340  81 83 00 00 */	lwz r12, 0(r3)
/* 800EB3E4 000E8344  81 8C 00 78 */	lwz r12, 0x78(r12)
/* 800EB3E8 000E8348  7D 88 03 A6 */	mtlr r12
/* 800EB3EC 000E834C  4E 80 00 21 */	blrl 
/* 800EB3F0 000E8350  38 00 00 00 */	li r0, 0
/* 800EB3F4 000E8354  7C 7E 1B 79 */	or. r30, r3, r3
/* 800EB3F8 000E8358  98 0D 30 6F */	stb r0, containerExitMode__7PikiMgr@sda21(r13)
/* 800EB3FC 000E835C  40 82 00 0C */	bne lbl_800EB408
/* 800EB400 000E8360  38 60 00 00 */	li r3, 0
/* 800EB404 000E8364  48 00 01 94 */	b lbl_800EB598
lbl_800EB408:
/* 800EB408 000E8368  80 6D 31 20 */	lwz r3, naviMgr@sda21(r13)
/* 800EB40C 000E836C  48 02 BF B9 */	bl getNavi__7NaviMgrFv
/* 800EB410 000E8370  38 83 00 00 */	addi r4, r3, 0
/* 800EB414 000E8374  38 7E 00 00 */	addi r3, r30, 0
/* 800EB418 000E8378  4B FE 0C 2D */	bl init__4PikiFP4Navi
/* 800EB41C 000E837C  7F C3 F3 78 */	mr r3, r30
/* 800EB420 000E8380  81 9E 00 00 */	lwz r12, 0(r30)
/* 800EB424 000E8384  38 9C 00 04 */	addi r4, r28, 4
/* 800EB428 000E8388  81 8C 00 2C */	lwz r12, 0x2c(r12)
/* 800EB42C 000E838C  7D 88 03 A6 */	mtlr r12
/* 800EB430 000E8390  4E 80 00 21 */	blrl 
/* 800EB434 000E8394  A0 1D 04 28 */	lhz r0, 0x428(r29)
/* 800EB438 000E8398  3C 60 80 3D */	lis r3, pikiInfMgr@ha
/* 800EB43C 000E839C  38 63 1D F0 */	addi r3, r3, pikiInfMgr@l
/* 800EB440 000E83A0  1C 00 00 0C */	mulli r0, r0, 0xc
/* 800EB444 000E83A4  7C 63 02 14 */	add r3, r3, r0
/* 800EB448 000E83A8  80 03 00 08 */	lwz r0, 8(r3)
/* 800EB44C 000E83AC  2C 00 00 00 */	cmpwi r0, 0
/* 800EB450 000E83B0  40 81 00 0C */	ble lbl_800EB45C
/* 800EB454 000E83B4  3B 80 00 02 */	li r28, 2
/* 800EB458 000E83B8  48 00 00 1C */	b lbl_800EB474
lbl_800EB45C:
/* 800EB45C 000E83BC  80 03 00 04 */	lwz r0, 4(r3)
/* 800EB460 000E83C0  2C 00 00 00 */	cmpwi r0, 0
/* 800EB464 000E83C4  40 81 00 0C */	ble lbl_800EB470
/* 800EB468 000E83C8  3B 80 00 01 */	li r28, 1
/* 800EB46C 000E83CC  48 00 00 08 */	b lbl_800EB474
lbl_800EB470:
/* 800EB470 000E83D0  3B 80 00 00 */	li r28, 0
lbl_800EB474:
/* 800EB474 000E83D4  7F C3 F3 78 */	mr r3, r30
/* 800EB478 000E83D8  81 9E 00 00 */	lwz r12, 0(r30)
/* 800EB47C 000E83DC  7F 84 E3 78 */	mr r4, r28
/* 800EB480 000E83E0  81 8C 01 30 */	lwz r12, 0x130(r12)
/* 800EB484 000E83E4  7D 88 03 A6 */	mtlr r12
/* 800EB488 000E83E8  4E 80 00 21 */	blrl 
/* 800EB48C 000E83EC  7F C3 F3 78 */	mr r3, r30
/* 800EB490 000E83F0  A0 9D 04 28 */	lhz r4, 0x428(r29)
/* 800EB494 000E83F4  4B FD E3 E5 */	bl initColor__4PikiFi
/* 800EB498 000E83F8  3C 60 80 3D */	lis r3, pikiInfMgr@ha
/* 800EB49C 000E83FC  38 63 1D F0 */	addi r3, r3, pikiInfMgr@l
/* 800EB4A0 000E8400  38 9E 00 00 */	addi r4, r30, 0
/* 800EB4A4 000E8404  4B FD A3 91 */	bl decPiki__10PikiInfMgrFP4Piki
/* 800EB4A8 000E8408  C0 0D CB 84 */	lfs f0, lbl_803E18A4@sda21(r13)
/* 800EB4AC 000E840C  38 9E 00 00 */	addi r4, r30, 0
/* 800EB4B0 000E8410  38 A0 00 00 */	li r5, 0
/* 800EB4B4 000E8414  D0 1E 00 7C */	stfs f0, 0x7c(r30)
/* 800EB4B8 000E8418  C0 0D CB 88 */	lfs f0, lbl_803E18A8@sda21(r13)
/* 800EB4BC 000E841C  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800EB4C0 000E8420  C0 0D CB 8C */	lfs f0, lbl_803E18AC@sda21(r13)
/* 800EB4C4 000E8424  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 800EB4C8 000E8428  80 7E 04 90 */	lwz r3, 0x490(r30)
/* 800EB4CC 000E842C  81 83 00 00 */	lwz r12, 0(r3)
/* 800EB4D0 000E8430  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 800EB4D4 000E8434  7D 88 03 A6 */	mtlr r12
/* 800EB4D8 000E8438  4E 80 00 21 */	blrl 
/* 800EB4DC 000E843C  57 E0 18 38 */	slwi r0, r31, 3
/* 800EB4E0 000E8440  C0 22 9A 40 */	lfs f1, lbl_803E9C40@sda21(r2)
/* 800EB4E4 000E8444  7C 7D 02 14 */	add r3, r29, r0
/* 800EB4E8 000E8448  80 83 04 48 */	lwz r4, 0x448(r3)
/* 800EB4EC 000E844C  7F C3 F3 78 */	mr r3, r30
/* 800EB4F0 000E8450  4B FA 55 D9 */	bl startRope__8CreatureFP12RopeCreaturef
/* 800EB4F4 000E8454  38 7E 00 00 */	addi r3, r30, 0
/* 800EB4F8 000E8458  38 80 00 0C */	li r4, 0xc
/* 800EB4FC 000E845C  38 A0 00 00 */	li r5, 0
/* 800EB500 000E8460  4B FE 1C CD */	bl changeMode__4PikiFiP4Navi
/* 800EB504 000E8464  57 80 10 3A */	slwi r0, r28, 2
/* 800EB508 000E8468  7C DD 02 14 */	add r6, r29, r0
/* 800EB50C 000E846C  80 A6 04 2C */	lwz r5, 0x42c(r6)
/* 800EB510 000E8470  3C 80 80 3D */	lis r4, containerPikis__8GameStat@ha
/* 800EB514 000E8474  3C 60 80 3D */	lis r3, workPikis__8GameStat@ha
/* 800EB518 000E8478  38 05 FF FF */	addi r0, r5, -1
/* 800EB51C 000E847C  90 06 04 2C */	stw r0, 0x42c(r6)
/* 800EB520 000E8480  38 84 1E A0 */	addi r4, r4, containerPikis__8GameStat@l
/* 800EB524 000E8484  38 03 1E 88 */	addi r0, r3, workPikis__8GameStat@l
/* 800EB528 000E8488  A0 7E 05 10 */	lhz r3, 0x510(r30)
/* 800EB52C 000E848C  54 63 10 3A */	slwi r3, r3, 2
/* 800EB530 000E8490  7C 84 1A 14 */	add r4, r4, r3
/* 800EB534 000E8494  80 64 00 00 */	lwz r3, 0(r4)
/* 800EB538 000E8498  38 63 FF FF */	addi r3, r3, -1
/* 800EB53C 000E849C  90 64 00 00 */	stw r3, 0(r4)
/* 800EB540 000E84A0  A0 7E 05 10 */	lhz r3, 0x510(r30)
/* 800EB544 000E84A4  54 63 10 3A */	slwi r3, r3, 2
/* 800EB548 000E84A8  7C 80 1A 14 */	add r4, r0, r3
/* 800EB54C 000E84AC  80 64 00 00 */	lwz r3, 0(r4)
/* 800EB550 000E84B0  38 03 00 01 */	addi r0, r3, 1
/* 800EB554 000E84B4  90 04 00 00 */	stw r0, 0(r4)
/* 800EB558 000E84B8  48 02 70 09 */	bl update__8GameStatFv
/* 800EB55C 000E84BC  38 7D 00 00 */	addi r3, r29, 0
/* 800EB560 000E84C0  38 9D 00 00 */	addi r4, r29, 0
/* 800EB564 000E84C4  38 A0 00 D3 */	li r5, 0xd3
/* 800EB568 000E84C8  4B F9 F0 4D */	bl playEventSound__8CreatureFP8Creaturei
/* 800EB56C 000E84CC  80 9D 04 34 */	lwz r4, 0x434(r29)
/* 800EB570 000E84D0  80 1D 04 30 */	lwz r0, 0x430(r29)
/* 800EB574 000E84D4  80 7D 04 2C */	lwz r3, 0x42c(r29)
/* 800EB578 000E84D8  7C 00 22 14 */	add r0, r0, r4
/* 800EB57C 000E84DC  7C 03 02 15 */	add. r0, r3, r0
/* 800EB580 000E84E0  40 82 00 14 */	bne lbl_800EB594
/* 800EB584 000E84E4  80 7D 02 E8 */	lwz r3, 0x2e8(r29)
/* 800EB588 000E84E8  38 9D 00 00 */	addi r4, r29, 0
/* 800EB58C 000E84EC  38 A0 00 00 */	li r5, 0
/* 800EB590 000E84F0  4B F9 21 C9 */	bl start__8SimpleAIFP10AICreaturei
lbl_800EB594:
/* 800EB594 000E84F4  7F C3 F3 78 */	mr r3, r30
lbl_800EB598:
/* 800EB598 000E84F8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800EB59C 000E84FC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800EB5A0 000E8500  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800EB5A4 000E8504  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800EB5A8 000E8508  83 81 00 30 */	lwz r28, 0x30(r1)
/* 800EB5AC 000E850C  38 21 00 40 */	addi r1, r1, 0x40
/* 800EB5B0 000E8510  7C 08 03 A6 */	mtlr r0
/* 800EB5B4 000E8514  4E 80 00 20 */	blr 

.global needShadow__8GoalItemFv
needShadow__8GoalItemFv:
/* 800EB5B8 000E8518  38 60 00 00 */	li r3, 0
/* 800EB5BC 000E851C  4E 80 00 20 */	blr 

.global __ct__8GoalItemFP12CreaturePropP15ItemShapeObjectP15ItemShapeObjectP15ItemShapeObjectP8SimpleAI
__ct__8GoalItemFP12CreaturePropP15ItemShapeObjectP15ItemShapeObjectP15ItemShapeObjectP8SimpleAI:
/* 800EB5C0 000E8520  7C 08 02 A6 */	mflr r0
/* 800EB5C4 000E8524  90 01 00 04 */	stw r0, 4(r1)
/* 800EB5C8 000E8528  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800EB5CC 000E852C  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 800EB5D0 000E8530  3B 65 00 00 */	addi r27, r5, 0
/* 800EB5D4 000E8534  3B 86 00 00 */	addi r28, r6, 0
/* 800EB5D8 000E8538  38 A4 00 00 */	addi r5, r4, 0
/* 800EB5DC 000E853C  3B E3 00 00 */	addi r31, r3, 0
/* 800EB5E0 000E8540  3B A7 00 00 */	addi r29, r7, 0
/* 800EB5E4 000E8544  3B C8 00 00 */	addi r30, r8, 0
/* 800EB5E8 000E8548  38 80 00 10 */	li r4, 0x10
/* 800EB5EC 000E854C  38 C0 00 00 */	li r6, 0
/* 800EB5F0 000E8550  48 00 A2 BD */	bl __ct__12ItemCreatureFiP12CreaturePropP5Shape
/* 800EB5F4 000E8554  3C 60 80 2C */	lis r3, __vt__8Suckable@ha
/* 800EB5F8 000E8558  38 63 C1 80 */	addi r3, r3, __vt__8Suckable@l
/* 800EB5FC 000E855C  90 7F 00 00 */	stw r3, 0(r31)
/* 800EB600 000E8560  38 03 01 14 */	addi r0, r3, 0x114
/* 800EB604 000E8564  3C 60 80 2B */	lis r3, "__vt__Q23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"@ha
/* 800EB608 000E8568  90 1F 02 B8 */	stw r0, 0x2b8(r31)
/* 800EB60C 000E856C  38 03 05 F4 */	addi r0, r3, "__vt__Q23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"@l
/* 800EB610 000E8570  3C 60 80 2C */	lis r3, __vt__8GoalItem@ha
/* 800EB614 000E8574  90 1F 03 C8 */	stw r0, 0x3c8(r31)
/* 800EB618 000E8578  38 63 CB 8C */	addi r3, r3, __vt__8GoalItem@l
/* 800EB61C 000E857C  38 83 01 14 */	addi r4, r3, 0x114
/* 800EB620 000E8580  90 7F 00 00 */	stw r3, 0(r31)
/* 800EB624 000E8584  38 03 01 74 */	addi r0, r3, 0x174
/* 800EB628 000E8588  38 7F 04 5C */	addi r3, r31, 0x45c
/* 800EB62C 000E858C  90 9F 02 B8 */	stw r4, 0x2b8(r31)
/* 800EB630 000E8590  90 1F 03 C8 */	stw r0, 0x3c8(r31)
/* 800EB634 000E8594  C0 02 9A 3C */	lfs f0, lbl_803E9C3C@sda21(r2)
/* 800EB638 000E8598  D0 1F 04 04 */	stfs f0, 0x404(r31)
/* 800EB63C 000E859C  D0 1F 04 00 */	stfs f0, 0x400(r31)
/* 800EB640 000E85A0  D0 1F 03 FC */	stfs f0, 0x3fc(r31)
/* 800EB644 000E85A4  D0 1F 04 24 */	stfs f0, 0x424(r31)
/* 800EB648 000E85A8  D0 1F 04 20 */	stfs f0, 0x420(r31)
/* 800EB64C 000E85AC  D0 1F 04 1C */	stfs f0, 0x41c(r31)
/* 800EB650 000E85B0  4B FB 86 0D */	bl __ct__9SeContextFv
/* 800EB654 000E85B4  38 00 00 00 */	li r0, 0
/* 800EB658 000E85B8  90 1F 04 84 */	stw r0, 0x484(r31)
/* 800EB65C 000E85BC  38 60 00 14 */	li r3, 0x14
/* 800EB660 000E85C0  90 1F 04 88 */	stw r0, 0x488(r31)
/* 800EB664 000E85C4  90 1F 04 8C */	stw r0, 0x48c(r31)
/* 800EB668 000E85C8  90 1F 04 90 */	stw r0, 0x490(r31)
/* 800EB66C 000E85CC  B0 1F 04 28 */	sth r0, 0x428(r31)
/* 800EB670 000E85D0  90 1F 03 C0 */	stw r0, 0x3c0(r31)
/* 800EB674 000E85D4  93 7F 04 38 */	stw r27, 0x438(r31)
/* 800EB678 000E85D8  93 9F 04 3C */	stw r28, 0x43c(r31)
/* 800EB67C 000E85DC  93 BF 04 40 */	stw r29, 0x440(r31)
/* 800EB680 000E85E0  80 1F 04 38 */	lwz r0, 0x438(r31)
/* 800EB684 000E85E4  90 1F 03 C0 */	stw r0, 0x3c0(r31)
/* 800EB688 000E85E8  93 DF 02 E8 */	stw r30, 0x2e8(r31)
/* 800EB68C 000E85EC  4B F5 B9 79 */	bl alloc__6SystemFUl
/* 800EB690 000E85F0  3B C3 00 00 */	addi r30, r3, 0
/* 800EB694 000E85F4  7F C3 F3 79 */	or. r3, r30, r30
/* 800EB698 000E85F8  41 82 00 0C */	beq lbl_800EB6A4
/* 800EB69C 000E85FC  38 80 00 0F */	li r4, 0xf
/* 800EB6A0 000E8600  4B F9 D5 91 */	bl __ct__8CollInfoFi
lbl_800EB6A4:
/* 800EB6A4 000E8604  93 DF 02 20 */	stw r30, 0x220(r31)
/* 800EB6A8 000E8608  38 00 00 00 */	li r0, 0
/* 800EB6AC 000E860C  38 7F 00 00 */	addi r3, r31, 0
/* 800EB6B0 000E8610  90 1F 03 E0 */	stw r0, 0x3e0(r31)
/* 800EB6B4 000E8614  90 1F 03 DC */	stw r0, 0x3dc(r31)
/* 800EB6B8 000E8618  90 1F 03 E8 */	stw r0, 0x3e8(r31)
/* 800EB6BC 000E861C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800EB6C0 000E8620  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 800EB6C4 000E8624  38 21 00 38 */	addi r1, r1, 0x38
/* 800EB6C8 000E8628  7C 08 03 A6 */	mtlr r0
/* 800EB6CC 000E862C  4E 80 00 20 */	blr 

.global ignoreAtari__8GoalItemFP8Creature
ignoreAtari__8GoalItemFP8Creature:
/* 800EB6D0 000E8630  80 04 00 6C */	lwz r0, 0x6c(r4)
/* 800EB6D4 000E8634  2C 00 00 0C */	cmpwi r0, 0xc
/* 800EB6D8 000E8638  40 82 00 0C */	bne lbl_800EB6E4
/* 800EB6DC 000E863C  38 60 00 01 */	li r3, 1
/* 800EB6E0 000E8640  4E 80 00 20 */	blr 
lbl_800EB6E4:
/* 800EB6E4 000E8644  38 60 00 00 */	li r3, 0
/* 800EB6E8 000E8648  4E 80 00 20 */	blr 

.global setColorType__8GoalItemFi
setColorType__8GoalItemFi:
/* 800EB6EC 000E864C  7C 08 02 A6 */	mflr r0
/* 800EB6F0 000E8650  38 A0 00 00 */	li r5, 0
/* 800EB6F4 000E8654  90 01 00 04 */	stw r0, 4(r1)
/* 800EB6F8 000E8658  54 80 10 3A */	slwi r0, r4, 2
/* 800EB6FC 000E865C  94 21 FF F8 */	stwu r1, -8(r1)
/* 800EB700 000E8660  B0 83 04 28 */	sth r4, 0x428(r3)
/* 800EB704 000E8664  7C 83 02 14 */	add r4, r3, r0
/* 800EB708 000E8668  80 04 04 38 */	lwz r0, 0x438(r4)
/* 800EB70C 000E866C  38 83 04 84 */	addi r4, r3, 0x484
/* 800EB710 000E8670  90 03 03 C0 */	stw r0, 0x3c0(r3)
/* 800EB714 000E8674  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 800EB718 000E8678  80 63 00 00 */	lwz r3, 0(r3)
/* 800EB71C 000E867C  4B F4 42 11 */	bl makeInstance__9BaseShapeFR17ShapeDynMaterialsi
/* 800EB720 000E8680  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800EB724 000E8684  38 21 00 08 */	addi r1, r1, 8
/* 800EB728 000E8688  7C 08 03 A6 */	mtlr r0
/* 800EB72C 000E868C  4E 80 00 20 */	blr 

.global startTakeoff__8GoalItemFv
startTakeoff__8GoalItemFv:
/* 800EB730 000E8690  7C 08 02 A6 */	mflr r0
/* 800EB734 000E8694  90 01 00 04 */	stw r0, 4(r1)
/* 800EB738 000E8698  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800EB73C 000E869C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800EB740 000E86A0  7C 7F 1B 78 */	mr r31, r3
/* 800EB744 000E86A4  81 9F 00 00 */	lwz r12, 0(r31)
/* 800EB748 000E86A8  C0 22 9A 64 */	lfs f1, lbl_803E9C64@sda21(r2)
/* 800EB74C 000E86AC  81 8C 01 4C */	lwz r12, 0x14c(r12)
/* 800EB750 000E86B0  7D 88 03 A6 */	mtlr r12
/* 800EB754 000E86B4  4E 80 00 21 */	blrl 
/* 800EB758 000E86B8  7F E3 FB 78 */	mr r3, r31
/* 800EB75C 000E86BC  A0 9F 04 28 */	lhz r4, 0x428(r31)
/* 800EB760 000E86C0  81 9F 00 00 */	lwz r12, 0(r31)
/* 800EB764 000E86C4  38 84 00 06 */	addi r4, r4, 6
/* 800EB768 000E86C8  81 8C 01 30 */	lwz r12, 0x130(r12)
/* 800EB76C 000E86CC  7D 88 03 A6 */	mtlr r12
/* 800EB770 000E86D0  4E 80 00 21 */	blrl 
/* 800EB774 000E86D4  38 60 00 08 */	li r3, 8
/* 800EB778 000E86D8  20 03 00 0A */	subfic r0, r3, 0xa
/* 800EB77C 000E86DC  2C 03 00 0A */	cmpwi r3, 0xa
/* 800EB780 000E86E0  7C 09 03 A6 */	mtctr r0
/* 800EB784 000E86E4  40 80 00 08 */	bge lbl_800EB78C
lbl_800EB788:
/* 800EB788 000E86E8  42 00 00 00 */	bdnz lbl_800EB788
lbl_800EB78C:
/* 800EB78C 000E86EC  80 1F 00 C8 */	lwz r0, 0xc8(r31)
/* 800EB790 000E86F0  60 00 08 00 */	ori r0, r0, 0x800
/* 800EB794 000E86F4  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 800EB798 000E86F8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800EB79C 000E86FC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800EB7A0 000E8700  38 21 00 18 */	addi r1, r1, 0x18
/* 800EB7A4 000E8704  7C 08 03 A6 */	mtlr r0
/* 800EB7A8 000E8708  4E 80 00 20 */	blr 

.global startLand__8GoalItemFv
startLand__8GoalItemFv:
/* 800EB7AC 000E870C  7C 08 02 A6 */	mflr r0
/* 800EB7B0 000E8710  90 01 00 04 */	stw r0, 4(r1)
/* 800EB7B4 000E8714  38 00 00 00 */	li r0, 0
/* 800EB7B8 000E8718  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800EB7BC 000E871C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800EB7C0 000E8720  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800EB7C4 000E8724  3B C3 00 00 */	addi r30, r3, 0
/* 800EB7C8 000E8728  98 03 03 CC */	stb r0, 0x3cc(r3)
/* 800EB7CC 000E872C  81 9E 00 00 */	lwz r12, 0(r30)
/* 800EB7D0 000E8730  A0 9E 04 28 */	lhz r4, 0x428(r30)
/* 800EB7D4 000E8734  81 8C 01 30 */	lwz r12, 0x130(r12)
/* 800EB7D8 000E8738  38 84 00 09 */	addi r4, r4, 9
/* 800EB7DC 000E873C  7D 88 03 A6 */	mtlr r12
/* 800EB7E0 000E8740  4E 80 00 21 */	blrl 
/* 800EB7E4 000E8744  7F C3 F3 78 */	mr r3, r30
/* 800EB7E8 000E8748  C0 22 9A 64 */	lfs f1, lbl_803E9C64@sda21(r2)
/* 800EB7EC 000E874C  81 9E 00 00 */	lwz r12, 0(r30)
/* 800EB7F0 000E8750  81 8C 01 4C */	lwz r12, 0x14c(r12)
/* 800EB7F4 000E8754  7D 88 03 A6 */	mtlr r12
/* 800EB7F8 000E8758  4E 80 00 21 */	blrl 
/* 800EB7FC 000E875C  80 BE 04 0C */	lwz r5, 0x40c(r30)
/* 800EB800 000E8760  38 00 00 01 */	li r0, 1
/* 800EB804 000E8764  80 85 00 14 */	lwz r4, 0x14(r5)
/* 800EB808 000E8768  80 65 00 18 */	lwz r3, 0x18(r5)
/* 800EB80C 000E876C  90 9E 03 FC */	stw r4, 0x3fc(r30)
/* 800EB810 000E8770  90 7E 04 00 */	stw r3, 0x400(r30)
/* 800EB814 000E8774  80 65 00 1C */	lwz r3, 0x1c(r5)
/* 800EB818 000E8778  90 7E 04 04 */	stw r3, 0x404(r30)
/* 800EB81C 000E877C  98 1E 03 E4 */	stb r0, 0x3e4(r30)
/* 800EB820 000E8780  80 1E 03 E8 */	lwz r0, 0x3e8(r30)
/* 800EB824 000E8784  28 00 00 00 */	cmplwi r0, 0
/* 800EB828 000E8788  40 82 00 48 */	bne lbl_800EB870
/* 800EB82C 000E878C  3C 80 70 69 */	lis r4, 0x70696B69@ha
/* 800EB830 000E8790  80 7E 02 20 */	lwz r3, 0x220(r30)
/* 800EB834 000E8794  38 84 6B 69 */	addi r4, r4, 0x70696B69@l
/* 800EB838 000E8798  4B F9 DE D9 */	bl getSphere__8CollInfoFUl
/* 800EB83C 000E879C  7C 7F 1B 78 */	mr r31, r3
/* 800EB840 000E87A0  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 800EB844 000E87A4  38 BF 00 04 */	addi r5, r31, 4
/* 800EB848 000E87A8  38 80 01 28 */	li r4, 0x128
/* 800EB84C 000E87AC  38 C0 00 00 */	li r6, 0
/* 800EB850 000E87B0  38 E0 00 00 */	li r7, 0
/* 800EB854 000E87B4  48 0B 12 E5 */	bl "create__9EffectMgrFQ29EffectMgr12effTypeTableR8Vector3fPQ23zen37CallBack1<PQ23zen17particleGenerator>PQ23zen58CallBack2<PQ23zen17particleGenerator,PQ23zen11particleMdl>"
/* 800EB858 000E87B8  90 7E 03 E8 */	stw r3, 0x3e8(r30)
/* 800EB85C 000E87BC  80 7E 03 E8 */	lwz r3, 0x3e8(r30)
/* 800EB860 000E87C0  28 03 00 00 */	cmplwi r3, 0
/* 800EB864 000E87C4  41 82 00 0C */	beq lbl_800EB870
/* 800EB868 000E87C8  38 1F 00 04 */	addi r0, r31, 4
/* 800EB86C 000E87CC  90 03 00 18 */	stw r0, 0x18(r3)
lbl_800EB870:
/* 800EB870 000E87D0  38 7E 00 00 */	addi r3, r30, 0
/* 800EB874 000E87D4  38 80 00 01 */	li r4, 1
/* 800EB878 000E87D8  4B FF F8 C1 */	bl setFlightLight__8GoalItemFb
/* 800EB87C 000E87DC  80 7E 04 0C */	lwz r3, 0x40c(r30)
/* 800EB880 000E87E0  C0 0D CB 90 */	lfs f0, lbl_803E18B0@sda21(r13)
/* 800EB884 000E87E4  D4 03 00 14 */	stfsu f0, 0x14(r3)
/* 800EB888 000E87E8  C0 0D CB 94 */	lfs f0, lbl_803E18B4@sda21(r13)
/* 800EB88C 000E87EC  D0 03 00 04 */	stfs f0, 4(r3)
/* 800EB890 000E87F0  C0 0D CB 98 */	lfs f0, lbl_803E18B8@sda21(r13)
/* 800EB894 000E87F4  D0 03 00 08 */	stfs f0, 8(r3)
/* 800EB898 000E87F8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800EB89C 000E87FC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800EB8A0 000E8800  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800EB8A4 000E8804  38 21 00 28 */	addi r1, r1, 0x28
/* 800EB8A8 000E8808  7C 08 03 A6 */	mtlr r0
/* 800EB8AC 000E880C  4E 80 00 20 */	blr 

.global startConeShrink__8GoalItemFv
startConeShrink__8GoalItemFv:
/* 800EB8B0 000E8810  38 00 00 01 */	li r0, 1
/* 800EB8B4 000E8814  98 03 03 F6 */	stb r0, 0x3f6(r3)
/* 800EB8B8 000E8818  C0 02 9A 68 */	lfs f0, lbl_803E9C68@sda21(r2)
/* 800EB8BC 000E881C  D0 03 03 F8 */	stfs f0, 0x3f8(r3)
/* 800EB8C0 000E8820  80 A3 04 0C */	lwz r5, 0x40c(r3)
/* 800EB8C4 000E8824  80 85 00 14 */	lwz r4, 0x14(r5)
/* 800EB8C8 000E8828  80 05 00 18 */	lwz r0, 0x18(r5)
/* 800EB8CC 000E882C  90 83 03 FC */	stw r4, 0x3fc(r3)
/* 800EB8D0 000E8830  90 03 04 00 */	stw r0, 0x400(r3)
/* 800EB8D4 000E8834  80 05 00 1C */	lwz r0, 0x1c(r5)
/* 800EB8D8 000E8838  90 03 04 04 */	stw r0, 0x404(r3)
/* 800EB8DC 000E883C  4E 80 00 20 */	blr 

.global startConeEmit__8GoalItemFv
startConeEmit__8GoalItemFv:
/* 800EB8E0 000E8840  38 00 00 01 */	li r0, 1
/* 800EB8E4 000E8844  98 03 04 08 */	stb r0, 0x408(r3)
/* 800EB8E8 000E8848  C0 02 9A 3C */	lfs f0, lbl_803E9C3C@sda21(r2)
/* 800EB8EC 000E884C  D0 03 03 F8 */	stfs f0, 0x3f8(r3)
/* 800EB8F0 000E8850  4E 80 00 20 */	blr 

.global startAI__8GoalItemFi
startAI__8GoalItemFi:
/* 800EB8F4 000E8854  7C 08 02 A6 */	mflr r0
/* 800EB8F8 000E8858  38 80 00 00 */	li r4, 0
/* 800EB8FC 000E885C  90 01 00 04 */	stw r0, 4(r1)
/* 800EB900 000E8860  38 00 00 01 */	li r0, 1
/* 800EB904 000E8864  94 21 FF 30 */	stwu r1, -0xd0(r1)
/* 800EB908 000E8868  DB E1 00 C8 */	stfd f31, 0xc8(r1)
/* 800EB90C 000E886C  DB C1 00 C0 */	stfd f30, 0xc0(r1)
/* 800EB910 000E8870  DB A1 00 B8 */	stfd f29, 0xb8(r1)
/* 800EB914 000E8874  DB 81 00 B0 */	stfd f28, 0xb0(r1)
/* 800EB918 000E8878  BF 21 00 94 */	stmw r25, 0x94(r1)
/* 800EB91C 000E887C  3B E3 00 00 */	addi r31, r3, 0
/* 800EB920 000E8880  3B C0 00 00 */	li r30, 0
/* 800EB924 000E8884  98 03 03 F4 */	stb r0, 0x3f4(r3)
/* 800EB928 000E8888  93 DF 03 DC */	stw r30, 0x3dc(r31)
/* 800EB92C 000E888C  93 DF 03 E0 */	stw r30, 0x3e0(r31)
/* 800EB930 000E8890  4B FF F6 39 */	bl setSpotActive__8GoalItemFb
/* 800EB934 000E8894  9B DF 03 E4 */	stb r30, 0x3e4(r31)
/* 800EB938 000E8898  80 9F 03 E8 */	lwz r4, 0x3e8(r31)
/* 800EB93C 000E889C  28 04 00 00 */	cmplwi r4, 0
/* 800EB940 000E88A0  41 82 00 18 */	beq lbl_800EB958
/* 800EB944 000E88A4  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 800EB948 000E88A8  38 A0 00 00 */	li r5, 0
/* 800EB94C 000E88AC  38 63 00 14 */	addi r3, r3, 0x14
/* 800EB950 000E88B0  48 0B 5C 75 */	bl killGenerator__Q23zen15particleManagerFPQ23zen17particleGeneratorb
/* 800EB954 000E88B4  93 DF 03 E8 */	stw r30, 0x3e8(r31)
lbl_800EB958:
/* 800EB958 000E88B8  3B C0 00 00 */	li r30, 0
/* 800EB95C 000E88BC  9B DF 03 F5 */	stb r30, 0x3f5(r31)
/* 800EB960 000E88C0  38 1F 04 5C */	addi r0, r31, 0x45c
/* 800EB964 000E88C4  38 9F 00 00 */	addi r4, r31, 0
/* 800EB968 000E88C8  9B DF 03 F6 */	stb r30, 0x3f6(r31)
/* 800EB96C 000E88CC  38 A0 00 03 */	li r5, 3
/* 800EB970 000E88D0  9B DF 04 08 */	stb r30, 0x408(r31)
/* 800EB974 000E88D4  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 800EB978 000E88D8  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800EB97C 000E88DC  4B FB 83 B9 */	bl setContext__9SeContextFP8Creaturei
/* 800EB980 000E88E0  93 DF 04 34 */	stw r30, 0x434(r31)
/* 800EB984 000E88E4  38 A0 00 00 */	li r5, 0
/* 800EB988 000E88E8  38 C0 00 00 */	li r6, 0
/* 800EB98C 000E88EC  93 DF 04 30 */	stw r30, 0x430(r31)
/* 800EB990 000E88F0  93 DF 04 2C */	stw r30, 0x42c(r31)
/* 800EB994 000E88F4  80 9F 03 C0 */	lwz r4, 0x3c0(r31)
/* 800EB998 000E88F8  80 7F 02 20 */	lwz r3, 0x220(r31)
/* 800EB99C 000E88FC  80 84 00 00 */	lwz r4, 0(r4)
/* 800EB9A0 000E8900  4B F9 E1 C5 */	bl initInfo__8CollInfoFP5ShapeP8CollPartPUl
/* 800EB9A4 000E8904  3C 80 74 65 */	lis r4, 0x74657374@ha
/* 800EB9A8 000E8908  80 6D 30 2C */	lwz r3, routeMgr@sda21(r13)
/* 800EB9AC 000E890C  38 84 73 74 */	addi r4, r4, 0x74657374@l
/* 800EB9B0 000E8910  38 BF 00 94 */	addi r5, r31, 0x94
/* 800EB9B4 000E8914  38 C0 00 00 */	li r6, 0
/* 800EB9B8 000E8918  4B FB 57 31 */	bl findNearestWayPoint__8RouteMgrFUlR8Vector3fb
/* 800EB9BC 000E891C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 800EB9C0 000E8920  38 E1 00 60 */	addi r7, r1, 0x60
/* 800EB9C4 000E8924  38 C1 00 6C */	addi r6, r1, 0x6c
/* 800EB9C8 000E8928  7C 00 07 34 */	extsh r0, r0
/* 800EB9CC 000E892C  B0 1F 04 2A */	sth r0, 0x42a(r31)
/* 800EB9D0 000E8930  38 BF 00 94 */	addi r5, r31, 0x94
/* 800EB9D4 000E8934  C0 2D CB 5C */	lfs f1, lbl_803E187C@sda21(r13)
/* 800EB9D8 000E8938  C0 0D CB 50 */	lfs f0, lbl_803E1870@sda21(r13)
/* 800EB9DC 000E893C  D0 21 00 60 */	stfs f1, 0x60(r1)
/* 800EB9E0 000E8940  C0 2D CB 60 */	lfs f1, lbl_803E1880@sda21(r13)
/* 800EB9E4 000E8944  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 800EB9E8 000E8948  C0 0D CB 54 */	lfs f0, lbl_803E1874@sda21(r13)
/* 800EB9EC 000E894C  D0 21 00 64 */	stfs f1, 0x64(r1)
/* 800EB9F0 000E8950  C0 2D CB 64 */	lfs f1, lbl_803E1884@sda21(r13)
/* 800EB9F4 000E8954  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 800EB9F8 000E8958  C0 0D CB 58 */	lfs f0, lbl_803E1878@sda21(r13)
/* 800EB9FC 000E895C  D0 21 00 68 */	stfs f1, 0x68(r1)
/* 800EBA00 000E8960  80 6D 31 80 */	lwz r3, effectMgr@sda21(r13)
/* 800EBA04 000E8964  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 800EBA08 000E8968  A0 9F 04 28 */	lhz r4, 0x428(r31)
/* 800EBA0C 000E896C  48 0B 11 B1 */	bl create__9EffectMgrFQ29EffectMgr14modelTypeTableR8Vector3fR8Vector3fR8Vector3f
/* 800EBA10 000E8970  90 7F 04 0C */	stw r3, 0x40c(r31)
/* 800EBA14 000E8974  3B 60 00 00 */	li r27, 0
/* 800EBA18 000E8978  3C 60 80 2C */	lis r3, leg_ids_1@ha
/* 800EBA1C 000E897C  C0 02 9A 40 */	lfs f0, lbl_803E9C40@sda21(r2)
/* 800EBA20 000E8980  57 64 10 3A */	slwi r4, r27, 2
/* 800EBA24 000E8984  38 03 C8 74 */	addi r0, r3, leg_ids_1@l
/* 800EBA28 000E8988  D0 1F 00 7C */	stfs f0, 0x7c(r31)
/* 800EBA2C 000E898C  7F 80 22 14 */	add r28, r0, r4
/* 800EBA30 000E8990  3B BF 00 00 */	addi r29, r31, 0
/* 800EBA34 000E8994  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800EBA38 000E8998  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800EBA3C 000E899C  93 DF 02 D0 */	stw r30, 0x2d0(r31)
/* 800EBA40 000E89A0  93 DF 02 D4 */	stw r30, 0x2d4(r31)
/* 800EBA44 000E89A4  C3 C2 9A 3C */	lfs f30, lbl_803E9C3C@sda21(r2)
/* 800EBA48 000E89A8  CB E2 9A 70 */	lfd f31, "@1956_2"@sda21(r2)
/* 800EBA4C 000E89AC  CB A2 9A 78 */	lfd f29, "@1957_1"@sda21(r2)
lbl_800EBA50:
/* 800EBA50 000E89B0  80 7F 02 20 */	lwz r3, 0x220(r31)
/* 800EBA54 000E89B4  3B 5D 04 44 */	addi r26, r29, 0x444
/* 800EBA58 000E89B8  80 9C 00 00 */	lwz r4, 0(r28)
/* 800EBA5C 000E89BC  4B F9 DC B5 */	bl getSphere__8CollInfoFUl
/* 800EBA60 000E89C0  7C 79 1B 78 */	mr r25, r3
/* 800EBA64 000E89C4  4B F9 C3 61 */	bl getChild__8CollPartFv
/* 800EBA68 000E89C8  C0 79 00 08 */	lfs f3, 8(r25)
/* 800EBA6C 000E89CC  7C 7E 1B 78 */	mr r30, r3
/* 800EBA70 000E89D0  C0 43 00 08 */	lfs f2, 8(r3)
/* 800EBA74 000E89D4  C0 39 00 04 */	lfs f1, 4(r25)
/* 800EBA78 000E89D8  C0 03 00 04 */	lfs f0, 4(r3)
/* 800EBA7C 000E89DC  EC 63 10 28 */	fsubs f3, f3, f2
/* 800EBA80 000E89E0  C0 59 00 0C */	lfs f2, 0xc(r25)
/* 800EBA84 000E89E4  EC 81 00 28 */	fsubs f4, f1, f0
/* 800EBA88 000E89E8  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 800EBA8C 000E89EC  EC 03 00 F2 */	fmuls f0, f3, f3
/* 800EBA90 000E89F0  EC 42 08 28 */	fsubs f2, f2, f1
/* 800EBA94 000E89F4  EC 24 01 32 */	fmuls f1, f4, f4
/* 800EBA98 000E89F8  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800EBA9C 000E89FC  EC 01 00 2A */	fadds f0, f1, f0
/* 800EBAA0 000E8A00  EF 82 00 2A */	fadds f28, f2, f0
/* 800EBAA4 000E8A04  FC 1C F0 40 */	fcmpo cr0, f28, f30
/* 800EBAA8 000E8A08  40 81 00 54 */	ble lbl_800EBAFC
/* 800EBAAC 000E8A0C  FC 20 E0 34 */	frsqrte f1, f28
/* 800EBAB0 000E8A10  FC 01 00 72 */	fmul f0, f1, f1
/* 800EBAB4 000E8A14  FC 3F 00 72 */	fmul f1, f31, f1
/* 800EBAB8 000E8A18  FC 1C 00 32 */	fmul f0, f28, f0
/* 800EBABC 000E8A1C  FC 1D 00 28 */	fsub f0, f29, f0
/* 800EBAC0 000E8A20  FC 21 00 32 */	fmul f1, f1, f0
/* 800EBAC4 000E8A24  FC 01 00 72 */	fmul f0, f1, f1
/* 800EBAC8 000E8A28  FC 3F 00 72 */	fmul f1, f31, f1
/* 800EBACC 000E8A2C  FC 1C 00 32 */	fmul f0, f28, f0
/* 800EBAD0 000E8A30  FC 1D 00 28 */	fsub f0, f29, f0

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
  .4byte 0x6169426f
  .4byte 0x752e6370
  .4byte 0x70000000
  .4byte 0x52656365
  .4byte 0x69766572
  .4byte 0x3c50696b
  .4byte 0x693e0000
  .4byte 0x803dfe88
  .4byte 0
  .4byte 0
  .4byte 0x803dfe88
  .4byte 0
  .4byte 0x803dfe98
  .4byte 0
  .4byte 0
.global __vt__6ActBou
__vt__6ActBou:
  .4byte __RTTI__6ActBou
  .4byte 0
  .4byte "procMsg__15Receiver<4Piki>FP4PikiP3Msg"
  .4byte "procBounceMsg__15Receiver<4Piki>FP4PikiP9MsgBounce"
  .4byte "procStickMsg__15Receiver<4Piki>FP4PikiP8MsgStick"
  .4byte "procHangMsg__15Receiver<4Piki>FP4PikiP7MsgHang"
  .4byte "procTargetMsg__15Receiver<4Piki>FP4PikiP9MsgTarget"
  .4byte procCollideMsg__6ActBouFP4PikiP10MsgCollide
  .4byte "procAnimMsg__15Receiver<4Piki>FP4PikiP7MsgAnim"
  .4byte "procDamageMsg__15Receiver<4Piki>FP4PikiP9MsgDamage"
  .4byte "procWallMsg__15Receiver<4Piki>FP4PikiP7MsgWall"
  .4byte "procOffWallMsg__15Receiver<4Piki>FP4PikiP10MsgOffWall"
  .4byte "procUserMsg__15Receiver<4Piki>FP4PikiP7MsgUser"
  .4byte "procGroundMsg__15Receiver<4Piki>FP4PikiP9MsgGround"
  .4byte defaultInitialiser__6ActionFv
  .4byte dump__6ActionFv
  .4byte draw__6ActionFR8Graphics
  .4byte __dt__6ActBouFv
  .4byte init__6ActBouFP8Creature
  .4byte exec__6ActBouFv
  .4byte cleanup__6ActBouFv
  .4byte resume__6ActionFv
  .4byte restart__6ActionFv
  .4byte resumable__6ActionFv
  .4byte getInfo__6ActionFPc
  .4byte 0x800a7908
  .4byte 0x800a7930
  .4byte 0x800a7944
  .4byte 0x800a7958
  .4byte 0x800a796c
  .4byte 0x800a7980
  .4byte 0x800a7994
  .4byte 0x800a79a8
  .4byte 0x800a791c
  .4byte 0x800a79d0
  .4byte 0x800a79bc
  .4byte 0

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.global __RTTI__13ActBoreSelect
__RTTI__13ActBoreSelect:
  .4byte 0x802b5884
  .4byte 0x802b5894
.global __RTTI__13ActFreeSelect
__RTTI__13ActFreeSelect:
  .4byte 0x802b590c
  .4byte 0x802b591c
  .4byte 0x802b5a20
  .4byte 0
  .4byte 0x41637469
  .4byte 0x6f6e0000
  .4byte 0x803dfe48
  .4byte 0x802b5a30
.global __RTTI__9ActBoMake
__RTTI__9ActBoMake:
  .4byte 0x802b5a14
  .4byte 0x802b5a3c
.global lbl_803DFE60
lbl_803DFE60:
	.4byte 0x426F7500
.global lbl_803DFE64
lbl_803DFE64:
	.4byte 0x00000000
.global lbl_803DFE68
lbl_803DFE68:
	.4byte 0x00000000
.global lbl_803DFE6C
lbl_803DFE6C:
	.4byte 0x00000000
.global lbl_803DFE70
lbl_803DFE70:
	.4byte 0x00000000
.global lbl_803DFE74
lbl_803DFE74:
	.4byte 0x00000000

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803EA74C
lbl_803EA74C:
	.4byte 0x40A00000
.global lbl_803EA750
lbl_803EA750:
	.4byte 0x41C80000
.global lbl_803EA754
lbl_803EA754:
	.4byte 0x42180000
.global lbl_803EA758
lbl_803EA758:
	.4byte 0x43C80000
.global lbl_803EA75C
lbl_803EA75C:
	.4byte 0x42480000
.global lbl_803EA760
lbl_803EA760:
	.4byte 0x42200000
.global lbl_803EA764
lbl_803EA764:
	.4byte 0x420C0000
.global lbl_803EA768
lbl_803EA768:
	.4byte 0x40800000
.global lbl_803EA76C
lbl_803EA76C:
	.4byte 0x41880000
.global lbl_803EA770
lbl_803EA770:
	.4byte 0x41200000

.section .sdata2, "a"  # 0x803E8200 - 0x803EC840
.global lbl_803EBE24
lbl_803EBE24:
	.4byte 0x3F333333
.global lbl_803EBE28
lbl_803EBE28:
	.4byte 0x3E800000
.global lbl_803EBE2C
lbl_803EBE2C:
	.4byte 0x40000000
.global lbl_803EBE30
lbl_803EBE30:
	.4byte 0x3E19999A
.global lbl_803EBE34
lbl_803EBE34:
	.4byte 0x3DCCCCCD
.global lbl_803EBE38
lbl_803EBE38:
	.4byte 0x00000000
.global lbl_803EBE3C
lbl_803EBE3C:
	.4byte 0x44960000
.global lbl_803EBE40
lbl_803EBE40:
	.4byte 0x41200000
.global lbl_803EBE44
lbl_803EBE44:
	.4byte 0x41300000
.global lbl_803EBE48
lbl_803EBE48:
	.4byte 0x42C80000
