.include "macros.inc"
.section .text, "ax"  # 0x80005560 - 0x80221F60
.global TRKHandleRequestEvent
TRKHandleRequestEvent:
/* 8021BF4C 00218EAC  7C 08 02 A6 */	mflr r0
/* 8021BF50 00218EB0  90 01 00 04 */	stw r0, 4(r1)
/* 8021BF54 00218EB4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8021BF58 00218EB8  80 63 00 08 */	lwz r3, 8(r3)
/* 8021BF5C 00218EBC  48 00 06 8D */	bl TRKGetBuffer
/* 8021BF60 00218EC0  48 00 0F 95 */	bl TRKDispatchMessage
/* 8021BF64 00218EC4  38 21 00 08 */	addi r1, r1, 8
/* 8021BF68 00218EC8  80 01 00 04 */	lwz r0, 4(r1)
/* 8021BF6C 00218ECC  7C 08 03 A6 */	mtlr r0
/* 8021BF70 00218ED0  4E 80 00 20 */	blr 

.global TRKHandleSupportEvent
TRKHandleSupportEvent:
/* 8021BF74 00218ED4  7C 08 02 A6 */	mflr r0
/* 8021BF78 00218ED8  90 01 00 04 */	stw r0, 4(r1)
/* 8021BF7C 00218EDC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8021BF80 00218EE0  48 00 3A 4D */	bl TRKTargetSupportRequest
/* 8021BF84 00218EE4  38 21 00 08 */	addi r1, r1, 8
/* 8021BF88 00218EE8  80 01 00 04 */	lwz r0, 4(r1)
/* 8021BF8C 00218EEC  7C 08 03 A6 */	mtlr r0
/* 8021BF90 00218EF0  4E 80 00 20 */	blr 

.global TRKIdle
TRKIdle:
/* 8021BF94 00218EF4  7C 08 02 A6 */	mflr r0
/* 8021BF98 00218EF8  90 01 00 04 */	stw r0, 4(r1)
/* 8021BF9C 00218EFC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8021BFA0 00218F00  48 00 3B 59 */	bl TRKTargetStopped
/* 8021BFA4 00218F04  2C 03 00 00 */	cmpwi r3, 0
/* 8021BFA8 00218F08  40 82 00 08 */	bne lbl_8021BFB0
/* 8021BFAC 00218F0C  48 00 48 0D */	bl TRKTargetContinue
lbl_8021BFB0:
/* 8021BFB0 00218F10  38 21 00 08 */	addi r1, r1, 8
/* 8021BFB4 00218F14  80 01 00 04 */	lwz r0, 4(r1)
/* 8021BFB8 00218F18  7C 08 03 A6 */	mtlr r0
/* 8021BFBC 00218F1C  4E 80 00 20 */	blr 

.global TRKNubMainLoop
TRKNubMainLoop:
/* 8021BFC0 00218F20  7C 08 02 A6 */	mflr r0
/* 8021BFC4 00218F24  3C 60 80 3D */	lis r3, gTRKInputPendingPtr@ha
/* 8021BFC8 00218F28  90 01 00 04 */	stw r0, 4(r1)
/* 8021BFCC 00218F2C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8021BFD0 00218F30  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8021BFD4 00218F34  3B E3 5C E4 */	addi r31, r3, gTRKInputPendingPtr@l
/* 8021BFD8 00218F38  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8021BFDC 00218F3C  3B C0 00 00 */	li r30, 0
/* 8021BFE0 00218F40  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8021BFE4 00218F44  3B A0 00 00 */	li r29, 0
/* 8021BFE8 00218F48  48 00 00 A8 */	b lbl_8021C090
lbl_8021BFEC:
/* 8021BFEC 00218F4C  38 61 00 08 */	addi r3, r1, 8
/* 8021BFF0 00218F50  48 00 01 45 */	bl TRKGetNextEvent
/* 8021BFF4 00218F54  2C 03 00 00 */	cmpwi r3, 0
/* 8021BFF8 00218F58  41 82 00 6C */	beq lbl_8021C064
/* 8021BFFC 00218F5C  88 01 00 08 */	lbz r0, 8(r1)
/* 8021C000 00218F60  3B A0 00 00 */	li r29, 0
/* 8021C004 00218F64  2C 00 00 02 */	cmpwi r0, 2
/* 8021C008 00218F68  41 82 00 28 */	beq lbl_8021C030
/* 8021C00C 00218F6C  40 80 00 14 */	bge lbl_8021C020
/* 8021C010 00218F70  2C 00 00 00 */	cmpwi r0, 0
/* 8021C014 00218F74  41 82 00 44 */	beq lbl_8021C058
/* 8021C018 00218F78  40 80 00 24 */	bge lbl_8021C03C
/* 8021C01C 00218F7C  48 00 00 3C */	b lbl_8021C058
lbl_8021C020:
/* 8021C020 00218F80  2C 00 00 05 */	cmpwi r0, 5
/* 8021C024 00218F84  41 82 00 2C */	beq lbl_8021C050
/* 8021C028 00218F88  40 80 00 30 */	bge lbl_8021C058
/* 8021C02C 00218F8C  48 00 00 18 */	b lbl_8021C044
lbl_8021C030:
/* 8021C030 00218F90  38 61 00 08 */	addi r3, r1, 8
/* 8021C034 00218F94  4B FF FF 19 */	bl TRKHandleRequestEvent
/* 8021C038 00218F98  48 00 00 20 */	b lbl_8021C058
lbl_8021C03C:
/* 8021C03C 00218F9C  3B C0 00 01 */	li r30, 1
/* 8021C040 00218FA0  48 00 00 18 */	b lbl_8021C058
lbl_8021C044:
/* 8021C044 00218FA4  38 61 00 08 */	addi r3, r1, 8
/* 8021C048 00218FA8  48 00 35 D5 */	bl TRKTargetInterrupt
/* 8021C04C 00218FAC  48 00 00 0C */	b lbl_8021C058
lbl_8021C050:
/* 8021C050 00218FB0  38 61 00 08 */	addi r3, r1, 8
/* 8021C054 00218FB4  4B FF FF 21 */	bl TRKHandleSupportEvent
lbl_8021C058:
/* 8021C058 00218FB8  38 61 00 08 */	addi r3, r1, 8
/* 8021C05C 00218FBC  48 00 02 91 */	bl TRKDestructEvent
/* 8021C060 00218FC0  48 00 00 30 */	b lbl_8021C090
lbl_8021C064:
/* 8021C064 00218FC4  2C 1D 00 00 */	cmpwi r29, 0
/* 8021C068 00218FC8  41 82 00 14 */	beq lbl_8021C07C
/* 8021C06C 00218FCC  80 7F 00 00 */	lwz r3, 0(r31)
/* 8021C070 00218FD0  88 03 00 00 */	lbz r0, 0(r3)
/* 8021C074 00218FD4  28 00 00 00 */	cmplwi r0, 0
/* 8021C078 00218FD8  41 82 00 10 */	beq lbl_8021C088
lbl_8021C07C:
/* 8021C07C 00218FDC  3B A0 00 01 */	li r29, 1
/* 8021C080 00218FE0  48 00 0D 65 */	bl TRKGetInput
/* 8021C084 00218FE4  48 00 00 0C */	b lbl_8021C090
lbl_8021C088:
/* 8021C088 00218FE8  4B FF FF 0D */	bl TRKIdle
/* 8021C08C 00218FEC  3B A0 00 00 */	li r29, 0
lbl_8021C090:
/* 8021C090 00218FF0  2C 1E 00 00 */	cmpwi r30, 0
/* 8021C094 00218FF4  41 82 FF 58 */	beq lbl_8021BFEC
/* 8021C098 00218FF8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8021C09C 00218FFC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8021C0A0 00219000  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8021C0A4 00219004  38 21 00 20 */	addi r1, r1, 0x20
/* 8021C0A8 00219008  80 01 00 04 */	lwz r0, 4(r1)
/* 8021C0AC 0021900C  7C 08 03 A6 */	mtlr r0
/* 8021C0B0 00219010  4E 80 00 20 */	blr 