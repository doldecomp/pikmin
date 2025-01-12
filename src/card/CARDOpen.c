#include "Dolphin/card.h"

/*
 * --INFO--
 * Address:	8020BA80
 * Size:	000068
 */
BOOL __CARDCompareFileName(CARDDir* entry, const char* fileName)
{
	char* entName;
	char c1;
	char c2;
	int n;

	entName = (char*)entry->fileName;
	n       = CARD_FILENAME_MAX;
	while (0 <= --n) {
		if ((c1 = *entName++) != (c2 = *fileName++)) {
			return FALSE;
		} else if (c2 == '\0') {
			return TRUE;
		}
	}

	if (*fileName == '\0') {
		return TRUE;
	}

	return FALSE;
}

/*
 * --INFO--
 * Address:	8020BAE8
 * Size:	00008C
 */
s32 __CARDAccess(CARDDir* entry)
{
	if (entry->gameName[0] == 0xFF) {
		return CARD_RESULT_NOFILE;
	}

	if (__CARDDiskID == &__CARDDiskNone
	    || (memcmp(entry->gameName, __CARDDiskID->gameName, 4) == 0 && memcmp(entry->company, __CARDDiskID->company, 2) == 0)) {
		return CARD_RESULT_READY;
	}

	return CARD_RESULT_NOPERM;
}

/*
 * --INFO--
 * Address:	8020BB74
 * Size:	000030
 */
s32 __CARDIsPublic(CARDDir* ent)
{
	if (ent->gameName[0] == 0xFF) {
		return CARD_RESULT_NOFILE;
	}
	if (ent->permission & CARD_ATTR_PUBLIC) {
		return CARD_RESULT_READY;
	}
	return CARD_RESULT_NOPERM;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000148
 */
s32 __CARDGetFileNo(CARDControl* card, char* fileName, s32* outFileNo)
{
	CARDDirectoryBlock* dir;
	CARDDir* entry;
	s32 fileNo;
	s32 result;

	if (!card->attached) {
		return CARD_RESULT_NOCARD;
	}

	dir = __CARDGetDirBlock(card);
	for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
		entry  = &dir->entries[fileNo];
		result = __CARDAccess(entry);
		if (result < 0) {
			continue;
		}
		if (__CARDCompareFileName(entry, fileName)) {
			*outFileNo = fileNo;
			return CARD_RESULT_READY;
		}
	}

	return CARD_RESULT_NOFILE;
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8020BBA4
 * Size:	000174
 */
s32 CARDFastOpen(s32 channel, s32 fileNo, CARDFileInfo* fileInfo)
{
	CARDControl* card;
	s32 result;
	CARDDirectoryBlock* dir;
	CARDDir* ent;

	if (fileNo < 0 || fileNo >= CARD_MAX_FILE) {
		return CARD_RESULT_FATAL_ERROR;
	}

	fileInfo->chan = -1;
	result         = __CARDGetControlBlock(channel, &card);
	if (result < 0) {
		return result;
	}

	dir    = __CARDGetDirBlock(card);
	ent    = &dir->entries[fileNo];
	result = __CARDAccess(ent);
	if (result == CARD_RESULT_NOPERM) {
		result = __CARDIsPublic(ent);
	}
	if (result >= 0) {
		if (!CARDIsValidBlockNo(card, ent->startBlock)) {
			result = CARD_RESULT_BROKEN;
		} else {
			fileInfo->chan   = channel;
			fileInfo->fileNo = fileNo;
			fileInfo->offset = 0;
			fileInfo->iBlock = ent->startBlock;
		}
	}
	return __CARDPutControlBlock(card, result);
}

/*
 * --INFO--
 * Address:	8020BD18
 * Size:	000174
 */
s32 CARDOpen(s32 chan, char* fileName, CARDFileInfo* fileInfo)
{
	CARDControl* card;
	CARDDirectoryBlock* dir;
	CARDDir* ent;
	s32 result;
	s32 fileNo;

	fileInfo->chan = -1;
	result         = __CARDGetControlBlock(chan, &card);
	if (result < 0) {
		return result;
	}
	result = __CARDGetFileNo(card, fileName, &fileNo);
	if (0 <= result) {
		dir = __CARDGetDirBlock(card);
		ent = &dir->entries[fileNo];
		if (!CARDIsValidBlockNo(card, ent->startBlock)) {
			result = CARD_RESULT_BROKEN;
		} else {
			fileInfo->chan   = chan;
			fileInfo->fileNo = fileNo;
			fileInfo->offset = 0;
			fileInfo->iBlock = ent->startBlock;
		}
	}
	return __CARDPutControlBlock(card, result);
}

/*
 * --INFO--
 * Address:	8020BE8C
 * Size:	000054
 */
s32 CARDClose(CARDFileInfo* fileInfo)
{
	CARDControl* card;
	s32 result;

	result = __CARDGetControlBlock(fileInfo->chan, &card);
	if (result < 0) {
		return result;
	}

	fileInfo->chan = -1;
	return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

/*
 * --INFO--
 * Address:	8020BEE0
 * Size:	000008
 */
BOOL __CARDIsOpened(CARDControl* card, s32 fileNo)
{
	return FALSE;
}
