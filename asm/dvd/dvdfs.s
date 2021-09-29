.include "macros.inc"

.global __DVDFSInit
__DVDFSInit:
/* 801FEF80 001FBEE0  3C 60 80 00 */	lis r3, 0x80000038@ha
/* 801FEF84 001FBEE4  90 6D 32 98 */	stw r3, BootInfo_1@sda21(r13)
/* 801FEF88 001FBEE8  80 03 00 38 */	lwz r0, 0x80000038@l(r3)
/* 801FEF8C 001FBEEC  90 0D 32 9C */	stw r0, FstStart@sda21(r13)
/* 801FEF90 001FBEF0  80 6D 32 9C */	lwz r3, FstStart@sda21(r13)
/* 801FEF94 001FBEF4  28 03 00 00 */	cmplwi r3, 0
/* 801FEF98 001FBEF8  4D 82 00 20 */	beqlr 
/* 801FEF9C 001FBEFC  80 03 00 08 */	lwz r0, 8(r3)
/* 801FEFA0 001FBF00  90 0D 32 A4 */	stw r0, MaxEntryNum@sda21(r13)
/* 801FEFA4 001FBF04  80 0D 32 A4 */	lwz r0, MaxEntryNum@sda21(r13)
/* 801FEFA8 001FBF08  1C 00 00 0C */	mulli r0, r0, 0xc
/* 801FEFAC 001FBF0C  7C 03 02 14 */	add r0, r3, r0
/* 801FEFB0 001FBF10  90 0D 32 A0 */	stw r0, FstStringStart@sda21(r13)
/* 801FEFB4 001FBF14  4E 80 00 20 */	blr 

.global DVDConvertPathToEntrynum
DVDConvertPathToEntrynum:
/* 801FEFB8 001FBF18  7C 08 02 A6 */	mflr r0
/* 801FEFBC 001FBF1C  90 01 00 04 */	stw r0, 4(r1)
/* 801FEFC0 001FBF20  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 801FEFC4 001FBF24  BE 81 00 18 */	stmw r20, 0x18(r1)
/* 801FEFC8 001FBF28  7C 77 1B 78 */	mr r23, r3
/* 801FEFCC 001FBF2C  3C 60 80 2F */	lis r3, lbl_802E8460@ha
/* 801FEFD0 001FBF30  3B 37 00 00 */	addi r25, r23, 0
/* 801FEFD4 001FBF34  3B E3 84 60 */	addi r31, r3, lbl_802E8460@l
/* 801FEFD8 001FBF38  83 8D 32 A8 */	lwz r28, currentDirectory@sda21(r13)
lbl_801FEFDC:
/* 801FEFDC 001FBF3C  88 17 00 00 */	lbz r0, 0(r23)
/* 801FEFE0 001FBF40  28 00 00 00 */	cmplwi r0, 0
/* 801FEFE4 001FBF44  40 82 00 0C */	bne lbl_801FEFF0
/* 801FEFE8 001FBF48  7F 83 E3 78 */	mr r3, r28
/* 801FEFEC 001FBF4C  48 00 02 98 */	b lbl_801FF284
lbl_801FEFF0:
/* 801FEFF0 001FBF50  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FEFF4 001FBF54  40 82 00 10 */	bne lbl_801FF004
/* 801FEFF8 001FBF58  3B 80 00 00 */	li r28, 0
/* 801FEFFC 001FBF5C  3A F7 00 01 */	addi r23, r23, 1
/* 801FF000 001FBF60  4B FF FF DC */	b lbl_801FEFDC
lbl_801FF004:
/* 801FF004 001FBF64  28 00 00 2E */	cmplwi r0, 0x2e
/* 801FF008 001FBF68  40 82 00 70 */	bne lbl_801FF078
/* 801FF00C 001FBF6C  88 17 00 01 */	lbz r0, 1(r23)
/* 801FF010 001FBF70  28 00 00 2E */	cmplwi r0, 0x2e
/* 801FF014 001FBF74  40 82 00 44 */	bne lbl_801FF058
/* 801FF018 001FBF78  88 17 00 02 */	lbz r0, 2(r23)
/* 801FF01C 001FBF7C  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FF020 001FBF80  40 82 00 1C */	bne lbl_801FF03C
/* 801FF024 001FBF84  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 801FF028 001FBF88  80 8D 32 9C */	lwz r4, FstStart@sda21(r13)
/* 801FF02C 001FBF8C  38 03 00 04 */	addi r0, r3, 4
/* 801FF030 001FBF90  7F 84 00 2E */	lwzx r28, r4, r0
/* 801FF034 001FBF94  3A F7 00 03 */	addi r23, r23, 3
/* 801FF038 001FBF98  4B FF FF A4 */	b lbl_801FEFDC
lbl_801FF03C:
/* 801FF03C 001FBF9C  28 00 00 00 */	cmplwi r0, 0
/* 801FF040 001FBFA0  40 82 00 38 */	bne lbl_801FF078
/* 801FF044 001FBFA4  1C 1C 00 0C */	mulli r0, r28, 0xc
/* 801FF048 001FBFA8  80 6D 32 9C */	lwz r3, FstStart@sda21(r13)
/* 801FF04C 001FBFAC  7C 63 02 14 */	add r3, r3, r0
/* 801FF050 001FBFB0  80 63 00 04 */	lwz r3, 4(r3)
/* 801FF054 001FBFB4  48 00 02 30 */	b lbl_801FF284
lbl_801FF058:
/* 801FF058 001FBFB8  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FF05C 001FBFBC  40 82 00 0C */	bne lbl_801FF068
/* 801FF060 001FBFC0  3A F7 00 02 */	addi r23, r23, 2
/* 801FF064 001FBFC4  4B FF FF 78 */	b lbl_801FEFDC
lbl_801FF068:
/* 801FF068 001FBFC8  28 00 00 00 */	cmplwi r0, 0
/* 801FF06C 001FBFCC  40 82 00 0C */	bne lbl_801FF078
/* 801FF070 001FBFD0  7F 83 E3 78 */	mr r3, r28
/* 801FF074 001FBFD4  48 00 02 10 */	b lbl_801FF284
lbl_801FF078:
/* 801FF078 001FBFD8  80 0D 32 AC */	lwz r0, __DVDLongFileNameFlag@sda21(r13)
/* 801FF07C 001FBFDC  28 00 00 00 */	cmplwi r0, 0
/* 801FF080 001FBFE0  40 82 00 A4 */	bne lbl_801FF124
/* 801FF084 001FBFE4  3A 97 00 00 */	addi r20, r23, 0
/* 801FF088 001FBFE8  38 80 00 00 */	li r4, 0
/* 801FF08C 001FBFEC  38 60 00 00 */	li r3, 0
/* 801FF090 001FBFF0  48 00 00 44 */	b lbl_801FF0D4
lbl_801FF094:
/* 801FF094 001FBFF4  28 00 00 2E */	cmplwi r0, 0x2e
/* 801FF098 001FBFF8  40 82 00 2C */	bne lbl_801FF0C4
/* 801FF09C 001FBFFC  7C 17 A0 50 */	subf r0, r23, r20
/* 801FF0A0 001FC000  2C 00 00 08 */	cmpwi r0, 8
/* 801FF0A4 001FC004  41 81 00 0C */	bgt lbl_801FF0B0
/* 801FF0A8 001FC008  2C 04 00 01 */	cmpwi r4, 1
/* 801FF0AC 001FC00C  40 82 00 0C */	bne lbl_801FF0B8
lbl_801FF0B0:
/* 801FF0B0 001FC010  38 60 00 01 */	li r3, 1
/* 801FF0B4 001FC014  48 00 00 34 */	b lbl_801FF0E8
lbl_801FF0B8:
/* 801FF0B8 001FC018  3B 14 00 01 */	addi r24, r20, 1
/* 801FF0BC 001FC01C  38 80 00 01 */	li r4, 1
/* 801FF0C0 001FC020  48 00 00 10 */	b lbl_801FF0D0
lbl_801FF0C4:
/* 801FF0C4 001FC024  28 00 00 20 */	cmplwi r0, 0x20
/* 801FF0C8 001FC028  40 82 00 08 */	bne lbl_801FF0D0
/* 801FF0CC 001FC02C  38 60 00 01 */	li r3, 1
lbl_801FF0D0:
/* 801FF0D0 001FC030  3A 94 00 01 */	addi r20, r20, 1
lbl_801FF0D4:
/* 801FF0D4 001FC034  88 14 00 00 */	lbz r0, 0(r20)
/* 801FF0D8 001FC038  28 00 00 00 */	cmplwi r0, 0
/* 801FF0DC 001FC03C  41 82 00 0C */	beq lbl_801FF0E8
/* 801FF0E0 001FC040  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FF0E4 001FC044  40 82 FF B0 */	bne lbl_801FF094
lbl_801FF0E8:
/* 801FF0E8 001FC048  2C 04 00 01 */	cmpwi r4, 1
/* 801FF0EC 001FC04C  40 82 00 14 */	bne lbl_801FF100
/* 801FF0F0 001FC050  7C 18 A0 50 */	subf r0, r24, r20
/* 801FF0F4 001FC054  2C 00 00 03 */	cmpwi r0, 3
/* 801FF0F8 001FC058  40 81 00 08 */	ble lbl_801FF100
/* 801FF0FC 001FC05C  38 60 00 01 */	li r3, 1
lbl_801FF100:
/* 801FF100 001FC060  2C 03 00 00 */	cmpwi r3, 0
/* 801FF104 001FC064  41 82 00 40 */	beq lbl_801FF144
/* 801FF108 001FC068  38 BF 00 00 */	addi r5, r31, 0
/* 801FF10C 001FC06C  4C C6 31 82 */	crclr 6
/* 801FF110 001FC070  38 D9 00 00 */	addi r6, r25, 0
/* 801FF114 001FC074  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF118 001FC078  38 80 01 75 */	li r4, 0x175
/* 801FF11C 001FC07C  4B FF 87 F5 */	bl OSPanic
/* 801FF120 001FC080  48 00 00 24 */	b lbl_801FF144
lbl_801FF124:
/* 801FF124 001FC084  7E F4 BB 78 */	mr r20, r23
/* 801FF128 001FC088  48 00 00 08 */	b lbl_801FF130
lbl_801FF12C:
/* 801FF12C 001FC08C  3A 94 00 01 */	addi r20, r20, 1
lbl_801FF130:
/* 801FF130 001FC090  88 14 00 00 */	lbz r0, 0(r20)
/* 801FF134 001FC094  28 00 00 00 */	cmplwi r0, 0
/* 801FF138 001FC098  41 82 00 0C */	beq lbl_801FF144
/* 801FF13C 001FC09C  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FF140 001FC0A0  40 82 FF EC */	bne lbl_801FF12C
lbl_801FF144:
/* 801FF144 001FC0A4  88 14 00 00 */	lbz r0, 0(r20)
/* 801FF148 001FC0A8  28 00 00 00 */	cmplwi r0, 0
/* 801FF14C 001FC0AC  40 82 00 0C */	bne lbl_801FF158
/* 801FF150 001FC0B0  3B C0 00 00 */	li r30, 0
/* 801FF154 001FC0B4  48 00 00 08 */	b lbl_801FF15C
lbl_801FF158:
/* 801FF158 001FC0B8  3B C0 00 01 */	li r30, 1
lbl_801FF15C:
/* 801FF15C 001FC0BC  1F BC 00 0C */	mulli r29, r28, 0xc
/* 801FF160 001FC0C0  7F 77 A0 50 */	subf r27, r23, r20
/* 801FF164 001FC0C4  3B 5C 00 01 */	addi r26, r28, 1
/* 801FF168 001FC0C8  48 00 00 E0 */	b lbl_801FF248
lbl_801FF16C:
/* 801FF16C 001FC0CC  1F 9A 00 0C */	mulli r28, r26, 0xc
/* 801FF170 001FC0D0  7C 83 E0 2E */	lwzx r4, r3, r28
/* 801FF174 001FC0D4  54 80 00 0F */	rlwinm. r0, r4, 0, 0, 7
/* 801FF178 001FC0D8  40 82 00 0C */	bne lbl_801FF184
/* 801FF17C 001FC0DC  38 00 00 00 */	li r0, 0
/* 801FF180 001FC0E0  48 00 00 08 */	b lbl_801FF188
lbl_801FF184:
/* 801FF184 001FC0E4  38 00 00 01 */	li r0, 1
lbl_801FF188:
/* 801FF188 001FC0E8  2C 00 00 00 */	cmpwi r0, 0
/* 801FF18C 001FC0EC  40 82 00 0C */	bne lbl_801FF198
/* 801FF190 001FC0F0  2C 1E 00 01 */	cmpwi r30, 1
/* 801FF194 001FC0F4  41 82 00 7C */	beq lbl_801FF210
lbl_801FF198:
/* 801FF198 001FC0F8  80 6D 32 A0 */	lwz r3, FstStringStart@sda21(r13)
/* 801FF19C 001FC0FC  54 80 02 3E */	clrlwi r0, r4, 8
/* 801FF1A0 001FC100  3A B7 00 00 */	addi r21, r23, 0
/* 801FF1A4 001FC104  7E 83 02 14 */	add r20, r3, r0
/* 801FF1A8 001FC108  48 00 00 34 */	b lbl_801FF1DC
lbl_801FF1AC:
/* 801FF1AC 001FC10C  88 74 00 00 */	lbz r3, 0(r20)
/* 801FF1B0 001FC110  3A 94 00 01 */	addi r20, r20, 1
/* 801FF1B4 001FC114  48 01 6C 29 */	bl tolower
/* 801FF1B8 001FC118  88 15 00 00 */	lbz r0, 0(r21)
/* 801FF1BC 001FC11C  3A C3 00 00 */	addi r22, r3, 0
/* 801FF1C0 001FC120  3A B5 00 01 */	addi r21, r21, 1
/* 801FF1C4 001FC124  7C 03 03 78 */	mr r3, r0
/* 801FF1C8 001FC128  48 01 6C 15 */	bl tolower
/* 801FF1CC 001FC12C  7C 03 B0 00 */	cmpw r3, r22
/* 801FF1D0 001FC130  41 82 00 0C */	beq lbl_801FF1DC
/* 801FF1D4 001FC134  38 00 00 00 */	li r0, 0
/* 801FF1D8 001FC138  48 00 00 30 */	b lbl_801FF208
lbl_801FF1DC:
/* 801FF1DC 001FC13C  88 14 00 00 */	lbz r0, 0(r20)
/* 801FF1E0 001FC140  28 00 00 00 */	cmplwi r0, 0
/* 801FF1E4 001FC144  40 82 FF C8 */	bne lbl_801FF1AC
/* 801FF1E8 001FC148  88 15 00 00 */	lbz r0, 0(r21)
/* 801FF1EC 001FC14C  28 00 00 2F */	cmplwi r0, 0x2f
/* 801FF1F0 001FC150  41 82 00 0C */	beq lbl_801FF1FC
/* 801FF1F4 001FC154  28 00 00 00 */	cmplwi r0, 0
/* 801FF1F8 001FC158  40 82 00 0C */	bne lbl_801FF204
lbl_801FF1FC:
/* 801FF1FC 001FC15C  38 00 00 01 */	li r0, 1
/* 801FF200 001FC160  48 00 00 08 */	b lbl_801FF208
lbl_801FF204:
/* 801FF204 001FC164  38 00 00 00 */	li r0, 0
lbl_801FF208:
/* 801FF208 001FC168  2C 00 00 01 */	cmpwi r0, 1
/* 801FF20C 001FC16C  41 82 00 58 */	beq lbl_801FF264
lbl_801FF210:
/* 801FF210 001FC170  80 0D 32 9C */	lwz r0, FstStart@sda21(r13)
/* 801FF214 001FC174  7C 60 E2 14 */	add r3, r0, r28
/* 801FF218 001FC178  80 03 00 00 */	lwz r0, 0(r3)
/* 801FF21C 001FC17C  54 00 00 0F */	rlwinm. r0, r0, 0, 0, 7
/* 801FF220 001FC180  40 82 00 0C */	bne lbl_801FF22C
/* 801FF224 001FC184  38 00 00 00 */	li r0, 0
/* 801FF228 001FC188  48 00 00 08 */	b lbl_801FF230
lbl_801FF22C:
/* 801FF22C 001FC18C  38 00 00 01 */	li r0, 1
lbl_801FF230:
/* 801FF230 001FC190  2C 00 00 00 */	cmpwi r0, 0
/* 801FF234 001FC194  41 82 00 0C */	beq lbl_801FF240
/* 801FF238 001FC198  80 03 00 08 */	lwz r0, 8(r3)
/* 801FF23C 001FC19C  48 00 00 08 */	b lbl_801FF244
lbl_801FF240:
/* 801FF240 001FC1A0  38 1A 00 01 */	addi r0, r26, 1
lbl_801FF244:
/* 801FF244 001FC1A4  7C 1A 03 78 */	mr r26, r0
lbl_801FF248:
/* 801FF248 001FC1A8  80 6D 32 9C */	lwz r3, FstStart@sda21(r13)
/* 801FF24C 001FC1AC  38 03 00 08 */	addi r0, r3, 8
/* 801FF250 001FC1B0  7C 1D 00 2E */	lwzx r0, r29, r0
/* 801FF254 001FC1B4  7C 1A 00 40 */	cmplw r26, r0
/* 801FF258 001FC1B8  41 80 FF 14 */	blt lbl_801FF16C
/* 801FF25C 001FC1BC  38 60 FF FF */	li r3, -1
/* 801FF260 001FC1C0  48 00 00 24 */	b lbl_801FF284
lbl_801FF264:
/* 801FF264 001FC1C4  2C 1E 00 00 */	cmpwi r30, 0
/* 801FF268 001FC1C8  40 82 00 0C */	bne lbl_801FF274
/* 801FF26C 001FC1CC  7F 43 D3 78 */	mr r3, r26
/* 801FF270 001FC1D0  48 00 00 14 */	b lbl_801FF284
lbl_801FF274:
/* 801FF274 001FC1D4  7E FB BA 14 */	add r23, r27, r23
/* 801FF278 001FC1D8  3B 9A 00 00 */	addi r28, r26, 0
/* 801FF27C 001FC1DC  3A F7 00 01 */	addi r23, r23, 1
/* 801FF280 001FC1E0  4B FF FD 5C */	b lbl_801FEFDC
lbl_801FF284:
/* 801FF284 001FC1E4  BA 81 00 18 */	lmw r20, 0x18(r1)
/* 801FF288 001FC1E8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 801FF28C 001FC1EC  38 21 00 48 */	addi r1, r1, 0x48
/* 801FF290 001FC1F0  7C 08 03 A6 */	mtlr r0
/* 801FF294 001FC1F4  4E 80 00 20 */	blr 

.global DVDFastOpen
DVDFastOpen:
/* 801FF298 001FC1F8  2C 03 00 00 */	cmpwi r3, 0
/* 801FF29C 001FC1FC  41 80 00 38 */	blt lbl_801FF2D4
/* 801FF2A0 001FC200  80 0D 32 A4 */	lwz r0, MaxEntryNum@sda21(r13)
/* 801FF2A4 001FC204  7C 03 00 40 */	cmplw r3, r0
/* 801FF2A8 001FC208  40 80 00 2C */	bge lbl_801FF2D4
/* 801FF2AC 001FC20C  1C C3 00 0C */	mulli r6, r3, 0xc
/* 801FF2B0 001FC210  80 6D 32 9C */	lwz r3, FstStart@sda21(r13)
/* 801FF2B4 001FC214  7C 03 30 2E */	lwzx r0, r3, r6
/* 801FF2B8 001FC218  54 00 00 0F */	rlwinm. r0, r0, 0, 0, 7
/* 801FF2BC 001FC21C  40 82 00 0C */	bne lbl_801FF2C8
/* 801FF2C0 001FC220  38 00 00 00 */	li r0, 0
/* 801FF2C4 001FC224  48 00 00 08 */	b lbl_801FF2CC
lbl_801FF2C8:
/* 801FF2C8 001FC228  38 00 00 01 */	li r0, 1
lbl_801FF2CC:
/* 801FF2CC 001FC22C  2C 00 00 00 */	cmpwi r0, 0
/* 801FF2D0 001FC230  41 82 00 0C */	beq lbl_801FF2DC
lbl_801FF2D4:
/* 801FF2D4 001FC234  38 60 00 00 */	li r3, 0
/* 801FF2D8 001FC238  4E 80 00 20 */	blr 
lbl_801FF2DC:
/* 801FF2DC 001FC23C  7C 63 32 14 */	add r3, r3, r6
/* 801FF2E0 001FC240  80 A3 00 04 */	lwz r5, 4(r3)
/* 801FF2E4 001FC244  38 00 00 00 */	li r0, 0
/* 801FF2E8 001FC248  38 60 00 01 */	li r3, 1
/* 801FF2EC 001FC24C  90 A4 00 30 */	stw r5, 0x30(r4)
/* 801FF2F0 001FC250  80 AD 32 9C */	lwz r5, FstStart@sda21(r13)
/* 801FF2F4 001FC254  7C A5 32 14 */	add r5, r5, r6
/* 801FF2F8 001FC258  80 A5 00 08 */	lwz r5, 8(r5)
/* 801FF2FC 001FC25C  90 A4 00 34 */	stw r5, 0x34(r4)
/* 801FF300 001FC260  90 04 00 38 */	stw r0, 0x38(r4)
/* 801FF304 001FC264  90 04 00 0C */	stw r0, 0xc(r4)
/* 801FF308 001FC268  4E 80 00 20 */	blr 

.global DVDOpen
DVDOpen:
/* 801FF30C 001FC26C  7C 08 02 A6 */	mflr r0
/* 801FF310 001FC270  90 01 00 04 */	stw r0, 4(r1)
/* 801FF314 001FC274  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 801FF318 001FC278  93 E1 00 94 */	stw r31, 0x94(r1)
/* 801FF31C 001FC27C  3B E4 00 00 */	addi r31, r4, 0
/* 801FF320 001FC280  93 C1 00 90 */	stw r30, 0x90(r1)
/* 801FF324 001FC284  3B C3 00 00 */	addi r30, r3, 0
/* 801FF328 001FC288  4B FF FC 91 */	bl DVDConvertPathToEntrynum
/* 801FF32C 001FC28C  2C 03 00 00 */	cmpwi r3, 0
/* 801FF330 001FC290  40 80 00 30 */	bge lbl_801FF360
/* 801FF334 001FC294  38 61 00 10 */	addi r3, r1, 0x10
/* 801FF338 001FC298  38 80 00 80 */	li r4, 0x80
/* 801FF33C 001FC29C  48 00 02 1D */	bl DVDGetCurrentDir
/* 801FF340 001FC2A0  3C 60 80 2F */	lis r3, lbl_802E8528@ha
/* 801FF344 001FC2A4  4C C6 31 82 */	crclr 6
/* 801FF348 001FC2A8  38 63 85 28 */	addi r3, r3, lbl_802E8528@l
/* 801FF34C 001FC2AC  38 9E 00 00 */	addi r4, r30, 0
/* 801FF350 001FC2B0  38 A1 00 10 */	addi r5, r1, 0x10
/* 801FF354 001FC2B4  4B FF 85 3D */	bl OSReport
/* 801FF358 001FC2B8  38 60 00 00 */	li r3, 0
/* 801FF35C 001FC2BC  48 00 00 60 */	b lbl_801FF3BC
lbl_801FF360:
/* 801FF360 001FC2C0  1C A3 00 0C */	mulli r5, r3, 0xc
/* 801FF364 001FC2C4  80 6D 32 9C */	lwz r3, FstStart@sda21(r13)
/* 801FF368 001FC2C8  7C 03 28 2E */	lwzx r0, r3, r5
/* 801FF36C 001FC2CC  54 00 00 0F */	rlwinm. r0, r0, 0, 0, 7
/* 801FF370 001FC2D0  40 82 00 0C */	bne lbl_801FF37C
/* 801FF374 001FC2D4  38 00 00 00 */	li r0, 0
/* 801FF378 001FC2D8  48 00 00 08 */	b lbl_801FF380
lbl_801FF37C:
/* 801FF37C 001FC2DC  38 00 00 01 */	li r0, 1
lbl_801FF380:
/* 801FF380 001FC2E0  2C 00 00 00 */	cmpwi r0, 0
/* 801FF384 001FC2E4  41 82 00 0C */	beq lbl_801FF390
/* 801FF388 001FC2E8  38 60 00 00 */	li r3, 0
/* 801FF38C 001FC2EC  48 00 00 30 */	b lbl_801FF3BC
lbl_801FF390:
/* 801FF390 001FC2F0  7C 63 2A 14 */	add r3, r3, r5
/* 801FF394 001FC2F4  80 83 00 04 */	lwz r4, 4(r3)
/* 801FF398 001FC2F8  38 00 00 00 */	li r0, 0
/* 801FF39C 001FC2FC  38 60 00 01 */	li r3, 1
/* 801FF3A0 001FC300  90 9F 00 30 */	stw r4, 0x30(r31)
/* 801FF3A4 001FC304  80 8D 32 9C */	lwz r4, FstStart@sda21(r13)
/* 801FF3A8 001FC308  7C 84 2A 14 */	add r4, r4, r5
/* 801FF3AC 001FC30C  80 84 00 08 */	lwz r4, 8(r4)
/* 801FF3B0 001FC310  90 9F 00 34 */	stw r4, 0x34(r31)
/* 801FF3B4 001FC314  90 1F 00 38 */	stw r0, 0x38(r31)
/* 801FF3B8 001FC318  90 1F 00 0C */	stw r0, 0xc(r31)
lbl_801FF3BC:
/* 801FF3BC 001FC31C  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 801FF3C0 001FC320  83 E1 00 94 */	lwz r31, 0x94(r1)
/* 801FF3C4 001FC324  83 C1 00 90 */	lwz r30, 0x90(r1)
/* 801FF3C8 001FC328  7C 08 03 A6 */	mtlr r0
/* 801FF3CC 001FC32C  38 21 00 98 */	addi r1, r1, 0x98
/* 801FF3D0 001FC330  4E 80 00 20 */	blr 

.global DVDClose
DVDClose:
/* 801FF3D4 001FC334  7C 08 02 A6 */	mflr r0
/* 801FF3D8 001FC338  90 01 00 04 */	stw r0, 4(r1)
/* 801FF3DC 001FC33C  94 21 FF F8 */	stwu r1, -8(r1)
/* 801FF3E0 001FC340  48 00 28 4D */	bl DVDCancel
/* 801FF3E4 001FC344  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801FF3E8 001FC348  38 60 00 01 */	li r3, 1
/* 801FF3EC 001FC34C  38 21 00 08 */	addi r1, r1, 8
/* 801FF3F0 001FC350  7C 08 03 A6 */	mtlr r0
/* 801FF3F4 001FC354  4E 80 00 20 */	blr 

.global entryToPath
entryToPath:
/* 801FF3F8 001FC358  7C 08 02 A6 */	mflr r0
/* 801FF3FC 001FC35C  28 03 00 00 */	cmplwi r3, 0
/* 801FF400 001FC360  90 01 00 04 */	stw r0, 4(r1)
/* 801FF404 001FC364  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801FF408 001FC368  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 801FF40C 001FC36C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 801FF410 001FC370  3B C5 00 00 */	addi r30, r5, 0
/* 801FF414 001FC374  93 A1 00 24 */	stw r29, 0x24(r1)
/* 801FF418 001FC378  3B A4 00 00 */	addi r29, r4, 0
/* 801FF41C 001FC37C  93 81 00 20 */	stw r28, 0x20(r1)
/* 801FF420 001FC380  40 82 00 0C */	bne lbl_801FF42C
/* 801FF424 001FC384  38 60 00 00 */	li r3, 0
/* 801FF428 001FC388  48 00 01 10 */	b lbl_801FF538
lbl_801FF42C:
/* 801FF42C 001FC38C  80 8D 32 9C */	lwz r4, FstStart@sda21(r13)
/* 801FF430 001FC390  1C 63 00 0C */	mulli r3, r3, 0xc
/* 801FF434 001FC394  80 CD 32 A0 */	lwz r6, FstStringStart@sda21(r13)
/* 801FF438 001FC398  38 A4 00 04 */	addi r5, r4, 4
/* 801FF43C 001FC39C  7C 04 18 2E */	lwzx r0, r4, r3
/* 801FF440 001FC3A0  7C 65 18 2E */	lwzx r3, r5, r3
/* 801FF444 001FC3A4  54 00 02 3E */	clrlwi r0, r0, 8
/* 801FF448 001FC3A8  28 03 00 00 */	cmplwi r3, 0
/* 801FF44C 001FC3AC  7F E6 02 14 */	add r31, r6, r0
/* 801FF450 001FC3B0  40 82 00 0C */	bne lbl_801FF45C
/* 801FF454 001FC3B4  38 60 00 00 */	li r3, 0
/* 801FF458 001FC3B8  48 00 00 80 */	b lbl_801FF4D8
lbl_801FF45C:
/* 801FF45C 001FC3BC  1C 63 00 0C */	mulli r3, r3, 0xc
/* 801FF460 001FC3C0  7C 04 18 2E */	lwzx r0, r4, r3
/* 801FF464 001FC3C4  7F A4 EB 78 */	mr r4, r29
/* 801FF468 001FC3C8  7C 65 18 2E */	lwzx r3, r5, r3
/* 801FF46C 001FC3CC  38 BE 00 00 */	addi r5, r30, 0
/* 801FF470 001FC3D0  54 00 02 3E */	clrlwi r0, r0, 8
/* 801FF474 001FC3D4  7F 86 02 14 */	add r28, r6, r0
/* 801FF478 001FC3D8  4B FF FF 81 */	bl entryToPath
/* 801FF47C 001FC3DC  7C 03 F0 40 */	cmplw r3, r30
/* 801FF480 001FC3E0  40 82 00 08 */	bne lbl_801FF488
/* 801FF484 001FC3E4  48 00 00 54 */	b lbl_801FF4D8
lbl_801FF488:
/* 801FF488 001FC3E8  38 03 00 00 */	addi r0, r3, 0
/* 801FF48C 001FC3EC  38 63 00 01 */	addi r3, r3, 1
/* 801FF490 001FC3F0  38 80 00 2F */	li r4, 0x2f
/* 801FF494 001FC3F4  7C C3 F0 50 */	subf r6, r3, r30
/* 801FF498 001FC3F8  7C 9D 01 AE */	stbx r4, r29, r0
/* 801FF49C 001FC3FC  38 86 00 00 */	addi r4, r6, 0
/* 801FF4A0 001FC400  7C BD 1A 14 */	add r5, r29, r3
/* 801FF4A4 001FC404  48 00 00 18 */	b lbl_801FF4BC
lbl_801FF4A8:
/* 801FF4A8 001FC408  88 1C 00 00 */	lbz r0, 0(r28)
/* 801FF4AC 001FC40C  3B 9C 00 01 */	addi r28, r28, 1
/* 801FF4B0 001FC410  38 84 FF FF */	addi r4, r4, -1
/* 801FF4B4 001FC414  98 05 00 00 */	stb r0, 0(r5)
/* 801FF4B8 001FC418  38 A5 00 01 */	addi r5, r5, 1
lbl_801FF4BC:
/* 801FF4BC 001FC41C  28 04 00 00 */	cmplwi r4, 0
/* 801FF4C0 001FC420  41 82 00 10 */	beq lbl_801FF4D0
/* 801FF4C4 001FC424  88 1C 00 00 */	lbz r0, 0(r28)
/* 801FF4C8 001FC428  28 00 00 00 */	cmplwi r0, 0
/* 801FF4CC 001FC42C  40 82 FF DC */	bne lbl_801FF4A8
lbl_801FF4D0:
/* 801FF4D0 001FC430  7C 04 30 50 */	subf r0, r4, r6
/* 801FF4D4 001FC434  7C 63 02 14 */	add r3, r3, r0
lbl_801FF4D8:
/* 801FF4D8 001FC438  7C 03 F0 40 */	cmplw r3, r30
/* 801FF4DC 001FC43C  40 82 00 08 */	bne lbl_801FF4E4
/* 801FF4E0 001FC440  48 00 00 58 */	b lbl_801FF538
lbl_801FF4E4:
/* 801FF4E4 001FC444  38 03 00 00 */	addi r0, r3, 0
/* 801FF4E8 001FC448  38 63 00 01 */	addi r3, r3, 1
/* 801FF4EC 001FC44C  38 80 00 2F */	li r4, 0x2f
/* 801FF4F0 001FC450  7C E3 F0 50 */	subf r7, r3, r30
/* 801FF4F4 001FC454  7C 9D 01 AE */	stbx r4, r29, r0
/* 801FF4F8 001FC458  38 DF 00 00 */	addi r6, r31, 0
/* 801FF4FC 001FC45C  38 87 00 00 */	addi r4, r7, 0
/* 801FF500 001FC460  7C BD 1A 14 */	add r5, r29, r3
/* 801FF504 001FC464  48 00 00 18 */	b lbl_801FF51C
lbl_801FF508:
/* 801FF508 001FC468  88 06 00 00 */	lbz r0, 0(r6)
/* 801FF50C 001FC46C  38 C6 00 01 */	addi r6, r6, 1
/* 801FF510 001FC470  38 84 FF FF */	addi r4, r4, -1
/* 801FF514 001FC474  98 05 00 00 */	stb r0, 0(r5)
/* 801FF518 001FC478  38 A5 00 01 */	addi r5, r5, 1
lbl_801FF51C:
/* 801FF51C 001FC47C  28 04 00 00 */	cmplwi r4, 0
/* 801FF520 001FC480  41 82 00 10 */	beq lbl_801FF530
/* 801FF524 001FC484  88 06 00 00 */	lbz r0, 0(r6)
/* 801FF528 001FC488  28 00 00 00 */	cmplwi r0, 0
/* 801FF52C 001FC48C  40 82 FF DC */	bne lbl_801FF508
lbl_801FF530:
/* 801FF530 001FC490  7C 04 38 50 */	subf r0, r4, r7
/* 801FF534 001FC494  7C 63 02 14 */	add r3, r3, r0
lbl_801FF538:
/* 801FF538 001FC498  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801FF53C 001FC49C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 801FF540 001FC4A0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 801FF544 001FC4A4  7C 08 03 A6 */	mtlr r0
/* 801FF548 001FC4A8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 801FF54C 001FC4AC  83 81 00 20 */	lwz r28, 0x20(r1)
/* 801FF550 001FC4B0  38 21 00 30 */	addi r1, r1, 0x30
/* 801FF554 001FC4B4  4E 80 00 20 */	blr 

.global DVDGetCurrentDir
DVDGetCurrentDir:
/* 801FF558 001FC4B8  7C 08 02 A6 */	mflr r0
/* 801FF55C 001FC4BC  90 01 00 04 */	stw r0, 4(r1)
/* 801FF560 001FC4C0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801FF564 001FC4C4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801FF568 001FC4C8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801FF56C 001FC4CC  3B C4 00 00 */	addi r30, r4, 0
/* 801FF570 001FC4D0  38 BE 00 00 */	addi r5, r30, 0
/* 801FF574 001FC4D4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801FF578 001FC4D8  3B A3 00 00 */	addi r29, r3, 0
/* 801FF57C 001FC4DC  38 9D 00 00 */	addi r4, r29, 0
/* 801FF580 001FC4E0  83 ED 32 A8 */	lwz r31, currentDirectory@sda21(r13)
/* 801FF584 001FC4E4  38 7F 00 00 */	addi r3, r31, 0
/* 801FF588 001FC4E8  4B FF FE 71 */	bl entryToPath
/* 801FF58C 001FC4EC  7C 03 F0 40 */	cmplw r3, r30
/* 801FF590 001FC4F0  40 82 00 14 */	bne lbl_801FF5A4
/* 801FF594 001FC4F4  38 00 00 00 */	li r0, 0
/* 801FF598 001FC4F8  7C 7D F2 14 */	add r3, r29, r30
/* 801FF59C 001FC4FC  98 03 FF FF */	stb r0, -1(r3)
/* 801FF5A0 001FC500  48 00 00 5C */	b lbl_801FF5FC
lbl_801FF5A4:
/* 801FF5A4 001FC504  1C 1F 00 0C */	mulli r0, r31, 0xc
/* 801FF5A8 001FC508  80 8D 32 9C */	lwz r4, FstStart@sda21(r13)
/* 801FF5AC 001FC50C  7C 04 00 2E */	lwzx r0, r4, r0
/* 801FF5B0 001FC510  54 00 00 0F */	rlwinm. r0, r0, 0, 0, 7
/* 801FF5B4 001FC514  40 82 00 0C */	bne lbl_801FF5C0
/* 801FF5B8 001FC518  38 00 00 00 */	li r0, 0
/* 801FF5BC 001FC51C  48 00 00 08 */	b lbl_801FF5C4
lbl_801FF5C0:
/* 801FF5C0 001FC520  38 00 00 01 */	li r0, 1
lbl_801FF5C4:
/* 801FF5C4 001FC524  2C 00 00 00 */	cmpwi r0, 0
/* 801FF5C8 001FC528  41 82 00 28 */	beq lbl_801FF5F0
/* 801FF5CC 001FC52C  38 1E FF FF */	addi r0, r30, -1
/* 801FF5D0 001FC530  7C 03 00 40 */	cmplw r3, r0
/* 801FF5D4 001FC534  40 82 00 10 */	bne lbl_801FF5E4
/* 801FF5D8 001FC538  38 00 00 00 */	li r0, 0
/* 801FF5DC 001FC53C  7C 1D 19 AE */	stbx r0, r29, r3
/* 801FF5E0 001FC540  48 00 00 1C */	b lbl_801FF5FC
lbl_801FF5E4:
/* 801FF5E4 001FC544  38 00 00 2F */	li r0, 0x2f
/* 801FF5E8 001FC548  7C 1D 19 AE */	stbx r0, r29, r3
/* 801FF5EC 001FC54C  38 63 00 01 */	addi r3, r3, 1
lbl_801FF5F0:
/* 801FF5F0 001FC550  38 00 00 00 */	li r0, 0
/* 801FF5F4 001FC554  7C 1D 19 AE */	stbx r0, r29, r3
/* 801FF5F8 001FC558  38 00 00 01 */	li r0, 1
lbl_801FF5FC:
/* 801FF5FC 001FC55C  7C 03 03 78 */	mr r3, r0
/* 801FF600 001FC560  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801FF604 001FC564  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801FF608 001FC568  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801FF60C 001FC56C  7C 08 03 A6 */	mtlr r0
/* 801FF610 001FC570  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801FF614 001FC574  38 21 00 20 */	addi r1, r1, 0x20
/* 801FF618 001FC578  4E 80 00 20 */	blr 

.global DVDReadAsyncPrio
DVDReadAsyncPrio:
/* 801FF61C 001FC57C  7C 08 02 A6 */	mflr r0
/* 801FF620 001FC580  90 01 00 04 */	stw r0, 4(r1)
/* 801FF624 001FC584  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801FF628 001FC588  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 801FF62C 001FC58C  7C DD 33 79 */	or. r29, r6, r6
/* 801FF630 001FC590  3B 43 00 00 */	addi r26, r3, 0
/* 801FF634 001FC594  3B 64 00 00 */	addi r27, r4, 0
/* 801FF638 001FC598  3B 85 00 00 */	addi r28, r5, 0
/* 801FF63C 001FC59C  3B C7 00 00 */	addi r30, r7, 0
/* 801FF640 001FC5A0  3B E8 00 00 */	addi r31, r8, 0
/* 801FF644 001FC5A4  41 80 00 10 */	blt lbl_801FF654
/* 801FF648 001FC5A8  80 1A 00 34 */	lwz r0, 0x34(r26)
/* 801FF64C 001FC5AC  7C 1D 00 40 */	cmplw r29, r0
/* 801FF650 001FC5B0  41 80 00 1C */	blt lbl_801FF66C
lbl_801FF654:
/* 801FF654 001FC5B4  3C 60 80 2F */	lis r3, lbl_802E8560@ha
/* 801FF658 001FC5B8  4C C6 31 82 */	crclr 6
/* 801FF65C 001FC5BC  38 A3 85 60 */	addi r5, r3, lbl_802E8560@l
/* 801FF660 001FC5C0  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF664 001FC5C4  38 80 02 DF */	li r4, 0x2df
/* 801FF668 001FC5C8  4B FF 82 A9 */	bl OSPanic
lbl_801FF66C:
/* 801FF66C 001FC5CC  7C 9D E2 15 */	add. r4, r29, r28
/* 801FF670 001FC5D0  41 80 00 14 */	blt lbl_801FF684
/* 801FF674 001FC5D4  80 7A 00 34 */	lwz r3, 0x34(r26)
/* 801FF678 001FC5D8  38 03 00 20 */	addi r0, r3, 0x20
/* 801FF67C 001FC5DC  7C 04 00 40 */	cmplw r4, r0
/* 801FF680 001FC5E0  41 80 00 1C */	blt lbl_801FF69C
lbl_801FF684:
/* 801FF684 001FC5E4  3C 60 80 2F */	lis r3, lbl_802E8560@ha
/* 801FF688 001FC5E8  4C C6 31 82 */	crclr 6
/* 801FF68C 001FC5EC  38 A3 85 60 */	addi r5, r3, lbl_802E8560@l
/* 801FF690 001FC5F0  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF694 001FC5F4  38 80 02 E5 */	li r4, 0x2e5
/* 801FF698 001FC5F8  4B FF 82 79 */	bl OSPanic
lbl_801FF69C:
/* 801FF69C 001FC5FC  93 DA 00 38 */	stw r30, 0x38(r26)
/* 801FF6A0 001FC600  3C 60 80 20 */	lis r3, cbForReadAsync@ha
/* 801FF6A4 001FC604  38 E3 F6 DC */	addi r7, r3, cbForReadAsync@l
/* 801FF6A8 001FC608  80 1A 00 30 */	lwz r0, 0x30(r26)
/* 801FF6AC 001FC60C  38 7A 00 00 */	addi r3, r26, 0
/* 801FF6B0 001FC610  38 9B 00 00 */	addi r4, r27, 0
/* 801FF6B4 001FC614  38 BC 00 00 */	addi r5, r28, 0
/* 801FF6B8 001FC618  39 1F 00 00 */	addi r8, r31, 0
/* 801FF6BC 001FC61C  7C C0 EA 14 */	add r6, r0, r29
/* 801FF6C0 001FC620  48 00 1E 01 */	bl DVDReadAbsAsyncPrio
/* 801FF6C4 001FC624  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 801FF6C8 001FC628  38 60 00 01 */	li r3, 1
/* 801FF6CC 001FC62C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801FF6D0 001FC630  38 21 00 38 */	addi r1, r1, 0x38
/* 801FF6D4 001FC634  7C 08 03 A6 */	mtlr r0
/* 801FF6D8 001FC638  4E 80 00 20 */	blr 

.global cbForReadAsync
cbForReadAsync:
/* 801FF6DC 001FC63C  7C 08 02 A6 */	mflr r0
/* 801FF6E0 001FC640  90 01 00 04 */	stw r0, 4(r1)
/* 801FF6E4 001FC644  94 21 FF F8 */	stwu r1, -8(r1)
/* 801FF6E8 001FC648  81 84 00 38 */	lwz r12, 0x38(r4)
/* 801FF6EC 001FC64C  28 0C 00 00 */	cmplwi r12, 0
/* 801FF6F0 001FC650  41 82 00 0C */	beq lbl_801FF6FC
/* 801FF6F4 001FC654  7D 88 03 A6 */	mtlr r12
/* 801FF6F8 001FC658  4E 80 00 21 */	blrl 
lbl_801FF6FC:
/* 801FF6FC 001FC65C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801FF700 001FC660  38 21 00 08 */	addi r1, r1, 8
/* 801FF704 001FC664  7C 08 03 A6 */	mtlr r0
/* 801FF708 001FC668  4E 80 00 20 */	blr 

.global DVDReadPrio
DVDReadPrio:
/* 801FF70C 001FC66C  7C 08 02 A6 */	mflr r0
/* 801FF710 001FC670  90 01 00 04 */	stw r0, 4(r1)
/* 801FF714 001FC674  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801FF718 001FC678  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 801FF71C 001FC67C  7C DD 33 79 */	or. r29, r6, r6
/* 801FF720 001FC680  3B E3 00 00 */	addi r31, r3, 0
/* 801FF724 001FC684  3B 64 00 00 */	addi r27, r4, 0
/* 801FF728 001FC688  3B 85 00 00 */	addi r28, r5, 0
/* 801FF72C 001FC68C  3B C7 00 00 */	addi r30, r7, 0
/* 801FF730 001FC690  41 80 00 10 */	blt lbl_801FF740
/* 801FF734 001FC694  80 1F 00 34 */	lwz r0, 0x34(r31)
/* 801FF738 001FC698  7C 1D 00 40 */	cmplw r29, r0
/* 801FF73C 001FC69C  41 80 00 1C */	blt lbl_801FF758
lbl_801FF740:
/* 801FF740 001FC6A0  3C 60 80 2F */	lis r3, lbl_802E8594@ha
/* 801FF744 001FC6A4  4C C6 31 82 */	crclr 6
/* 801FF748 001FC6A8  38 A3 85 94 */	addi r5, r3, lbl_802E8594@l
/* 801FF74C 001FC6AC  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF750 001FC6B0  38 80 03 25 */	li r4, 0x325
/* 801FF754 001FC6B4  4B FF 81 BD */	bl OSPanic
lbl_801FF758:
/* 801FF758 001FC6B8  7C 9D E2 15 */	add. r4, r29, r28
/* 801FF75C 001FC6BC  41 80 00 14 */	blt lbl_801FF770
/* 801FF760 001FC6C0  80 7F 00 34 */	lwz r3, 0x34(r31)
/* 801FF764 001FC6C4  38 03 00 20 */	addi r0, r3, 0x20
/* 801FF768 001FC6C8  7C 04 00 40 */	cmplw r4, r0
/* 801FF76C 001FC6CC  41 80 00 1C */	blt lbl_801FF788
lbl_801FF770:
/* 801FF770 001FC6D0  3C 60 80 2F */	lis r3, lbl_802E8594@ha
/* 801FF774 001FC6D4  4C C6 31 82 */	crclr 6
/* 801FF778 001FC6D8  38 A3 85 94 */	addi r5, r3, lbl_802E8594@l
/* 801FF77C 001FC6DC  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF780 001FC6E0  38 80 03 2B */	li r4, 0x32b
/* 801FF784 001FC6E4  4B FF 81 8D */	bl OSPanic
lbl_801FF788:
/* 801FF788 001FC6E8  80 1F 00 30 */	lwz r0, 0x30(r31)
/* 801FF78C 001FC6EC  3C 80 80 20 */	lis r4, cbForReadSync@ha
/* 801FF790 001FC6F0  38 E4 F8 24 */	addi r7, r4, cbForReadSync@l
/* 801FF794 001FC6F4  38 7F 00 00 */	addi r3, r31, 0
/* 801FF798 001FC6F8  38 9B 00 00 */	addi r4, r27, 0
/* 801FF79C 001FC6FC  38 BC 00 00 */	addi r5, r28, 0
/* 801FF7A0 001FC700  39 1E 00 00 */	addi r8, r30, 0
/* 801FF7A4 001FC704  7C C0 EA 14 */	add r6, r0, r29
/* 801FF7A8 001FC708  48 00 1D 19 */	bl DVDReadAbsAsyncPrio
/* 801FF7AC 001FC70C  2C 03 00 00 */	cmpwi r3, 0
/* 801FF7B0 001FC710  40 82 00 0C */	bne lbl_801FF7BC
/* 801FF7B4 001FC714  38 60 FF FF */	li r3, -1
/* 801FF7B8 001FC718  48 00 00 58 */	b lbl_801FF810
lbl_801FF7BC:
/* 801FF7BC 001FC71C  4B FF 97 C1 */	bl OSDisableInterrupts
/* 801FF7C0 001FC720  7C 7E 1B 78 */	mr r30, r3
lbl_801FF7C4:
/* 801FF7C4 001FC724  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 801FF7C8 001FC728  2C 00 00 00 */	cmpwi r0, 0
/* 801FF7CC 001FC72C  40 82 00 0C */	bne lbl_801FF7D8
/* 801FF7D0 001FC730  83 FF 00 20 */	lwz r31, 0x20(r31)
/* 801FF7D4 001FC734  48 00 00 30 */	b lbl_801FF804
lbl_801FF7D8:
/* 801FF7D8 001FC738  2C 00 FF FF */	cmpwi r0, -1
/* 801FF7DC 001FC73C  40 82 00 0C */	bne lbl_801FF7E8
/* 801FF7E0 001FC740  3B E0 FF FF */	li r31, -1
/* 801FF7E4 001FC744  48 00 00 20 */	b lbl_801FF804
lbl_801FF7E8:
/* 801FF7E8 001FC748  2C 00 00 0A */	cmpwi r0, 0xa
/* 801FF7EC 001FC74C  40 82 00 0C */	bne lbl_801FF7F8
/* 801FF7F0 001FC750  3B E0 FF FD */	li r31, -3
/* 801FF7F4 001FC754  48 00 00 10 */	b lbl_801FF804
lbl_801FF7F8:
/* 801FF7F8 001FC758  38 6D 32 B0 */	addi r3, r13, __DVDThreadQueue@sda21
/* 801FF7FC 001FC75C  4B FF D1 C1 */	bl OSSleepThread
/* 801FF800 001FC760  4B FF FF C4 */	b lbl_801FF7C4
lbl_801FF804:
/* 801FF804 001FC764  7F C3 F3 78 */	mr r3, r30
/* 801FF808 001FC768  4B FF 97 9D */	bl OSRestoreInterrupts
/* 801FF80C 001FC76C  7F E3 FB 78 */	mr r3, r31
lbl_801FF810:
/* 801FF810 001FC770  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 801FF814 001FC774  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801FF818 001FC778  38 21 00 38 */	addi r1, r1, 0x38
/* 801FF81C 001FC77C  7C 08 03 A6 */	mtlr r0
/* 801FF820 001FC780  4E 80 00 20 */	blr 

.global cbForReadSync
cbForReadSync:
/* 801FF824 001FC784  7C 08 02 A6 */	mflr r0
/* 801FF828 001FC788  38 6D 32 B0 */	addi r3, r13, __DVDThreadQueue@sda21
/* 801FF82C 001FC78C  90 01 00 04 */	stw r0, 4(r1)
/* 801FF830 001FC790  94 21 FF F8 */	stwu r1, -8(r1)
/* 801FF834 001FC794  4B FF D2 75 */	bl OSWakeupThread
/* 801FF838 001FC798  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801FF83C 001FC79C  38 21 00 08 */	addi r1, r1, 8
/* 801FF840 001FC7A0  7C 08 03 A6 */	mtlr r0
/* 801FF844 001FC7A4  4E 80 00 20 */	blr 

.global DVDPrepareStreamAsync
DVDPrepareStreamAsync:
/* 801FF848 001FC7A8  7C 08 02 A6 */	mflr r0
/* 801FF84C 001FC7AC  90 01 00 04 */	stw r0, 4(r1)
/* 801FF850 001FC7B0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801FF854 001FC7B4  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 801FF858 001FC7B8  3B A5 00 00 */	addi r29, r5, 0
/* 801FF85C 001FC7BC  7C 7B 1B 78 */	mr r27, r3
/* 801FF860 001FC7C0  3B 84 00 00 */	addi r28, r4, 0
/* 801FF864 001FC7C4  3B C6 00 00 */	addi r30, r6, 0
/* 801FF868 001FC7C8  80 E3 00 30 */	lwz r7, 0x30(r3)
/* 801FF86C 001FC7CC  3C 60 80 2F */	lis r3, lbl_802E8460@ha
/* 801FF870 001FC7D0  3B E3 84 60 */	addi r31, r3, lbl_802E8460@l
/* 801FF874 001FC7D4  7C 07 EA 14 */	add r0, r7, r29
/* 801FF878 001FC7D8  54 00 04 7F */	clrlwi. r0, r0, 0x11
/* 801FF87C 001FC7DC  41 82 00 20 */	beq lbl_801FF89C
/* 801FF880 001FC7E0  38 C7 00 00 */	addi r6, r7, 0
/* 801FF884 001FC7E4  4C C6 31 82 */	crclr 6
/* 801FF888 001FC7E8  38 FD 00 00 */	addi r7, r29, 0
/* 801FF88C 001FC7EC  38 BF 01 8C */	addi r5, r31, 0x18c
/* 801FF890 001FC7F0  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF894 001FC7F4  38 80 04 7E */	li r4, 0x47e
/* 801FF898 001FC7F8  4B FF 80 79 */	bl OSPanic
lbl_801FF89C:
/* 801FF89C 001FC7FC  28 1C 00 00 */	cmplwi r28, 0
/* 801FF8A0 001FC800  40 82 00 0C */	bne lbl_801FF8AC
/* 801FF8A4 001FC804  80 1B 00 34 */	lwz r0, 0x34(r27)
/* 801FF8A8 001FC808  7F 9D 00 50 */	subf r28, r29, r0
lbl_801FF8AC:
/* 801FF8AC 001FC80C  57 80 04 7F */	clrlwi. r0, r28, 0x11
/* 801FF8B0 001FC810  41 82 00 1C */	beq lbl_801FF8CC
/* 801FF8B4 001FC814  38 DC 00 00 */	addi r6, r28, 0
/* 801FF8B8 001FC818  4C C6 31 82 */	crclr 6
/* 801FF8BC 001FC81C  38 BF 01 F4 */	addi r5, r31, 0x1f4
/* 801FF8C0 001FC820  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF8C4 001FC824  38 80 04 88 */	li r4, 0x488
/* 801FF8C8 001FC828  4B FF 80 49 */	bl OSPanic
lbl_801FF8CC:
/* 801FF8CC 001FC82C  80 7B 00 34 */	lwz r3, 0x34(r27)
/* 801FF8D0 001FC830  7C 1D 18 40 */	cmplw r29, r3
/* 801FF8D4 001FC834  40 80 00 10 */	bge lbl_801FF8E4
/* 801FF8D8 001FC838  7C 1D E2 14 */	add r0, r29, r28
/* 801FF8DC 001FC83C  7C 00 18 40 */	cmplw r0, r3
/* 801FF8E0 001FC840  40 81 00 20 */	ble lbl_801FF900
lbl_801FF8E4:
/* 801FF8E4 001FC844  38 DD 00 00 */	addi r6, r29, 0
/* 801FF8E8 001FC848  4C C6 31 82 */	crclr 6
/* 801FF8EC 001FC84C  38 FC 00 00 */	addi r7, r28, 0
/* 801FF8F0 001FC850  38 BF 02 4C */	addi r5, r31, 0x24c
/* 801FF8F4 001FC854  38 6D 2A 10 */	addi r3, r13, lbl_803E7730@sda21
/* 801FF8F8 001FC858  38 80 04 90 */	li r4, 0x490
/* 801FF8FC 001FC85C  4B FF 80 15 */	bl OSPanic
lbl_801FF900:
/* 801FF900 001FC860  93 DB 00 38 */	stw r30, 0x38(r27)
/* 801FF904 001FC864  3C 60 80 20 */	lis r3, cbForPrepareStreamAsync@ha
/* 801FF908 001FC868  38 C3 F9 34 */	addi r6, r3, cbForPrepareStreamAsync@l
/* 801FF90C 001FC86C  80 1B 00 30 */	lwz r0, 0x30(r27)
/* 801FF910 001FC870  38 7B 00 00 */	addi r3, r27, 0
/* 801FF914 001FC874  38 9C 00 00 */	addi r4, r28, 0
/* 801FF918 001FC878  7C A0 EA 14 */	add r5, r0, r29
/* 801FF91C 001FC87C  48 00 1E 25 */	bl DVDPrepareStreamAbsAsync
/* 801FF920 001FC880  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 801FF924 001FC884  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801FF928 001FC888  38 21 00 38 */	addi r1, r1, 0x38
/* 801FF92C 001FC88C  7C 08 03 A6 */	mtlr r0
/* 801FF930 001FC890  4E 80 00 20 */	blr 

.global cbForPrepareStreamAsync
cbForPrepareStreamAsync:
/* 801FF934 001FC894  7C 08 02 A6 */	mflr r0
/* 801FF938 001FC898  90 01 00 04 */	stw r0, 4(r1)
/* 801FF93C 001FC89C  94 21 FF F8 */	stwu r1, -8(r1)
/* 801FF940 001FC8A0  81 84 00 38 */	lwz r12, 0x38(r4)
/* 801FF944 001FC8A4  28 0C 00 00 */	cmplwi r12, 0
/* 801FF948 001FC8A8  41 82 00 0C */	beq lbl_801FF954
/* 801FF94C 001FC8AC  7D 88 03 A6 */	mtlr r12
/* 801FF950 001FC8B0  4E 80 00 21 */	blrl 
lbl_801FF954:
/* 801FF954 001FC8B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801FF958 001FC8B8  38 21 00 08 */	addi r1, r1, 8
/* 801FF95C 001FC8BC  7C 08 03 A6 */	mtlr r0
/* 801FF960 001FC8C0  4E 80 00 20 */	blr 
