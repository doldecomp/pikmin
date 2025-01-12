#include "Generator.h"
#include "sysNew.h"
#include "TekiPersonality.h"
#include "TekiParameters.h"
#include "Dolphin/os.h"
#include "teki.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
static void _Error(char* fmt, ...)
{
	OSPanic(__FILE__, __LINE__, fmt, "敵を発生"); // 'spawn enemies'
	                                              // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F0
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8011B2CC
 * Size:	000040
 */
static GenObject* makeObjectTeki()
{
	return new GenObjectTeki();
}

/*
 * --INFO--
 * Address:	8011B30C
 * Size:	000088
 */
void GenObjectTeki::initialise()
{
	GenObjectFactory::factory->registerMember('teki', &makeObjectTeki, "敵を発生", 10);
}

/*
 * --INFO--
 * Address:	8011B394
 * Size:	00008C
 */
GenObjectTeki::GenObjectTeki()
    : GenObject('teki', "敵を生む") // 'create enemies'
{
	mTekiType    = TEKI_Frog;
	mPersonality = new TekiPersonality();
}

/*
 * --INFO--
 * Address:	8011B420
 * Size:	000094
 */
void GenObjectTeki::doRead(RandomAccessStream& input)
{
	if (mVersion <= 8) {
		mTekiType = input.readInt();
	} else {
		mTekiType = (u8)input.readByte();
	}

	mPersonality->read(input, mVersion);
}

/*
 * --INFO--
 * Address:	8011B4B4
 * Size:	000068
 */
void GenObjectTeki::doWrite(RandomAccessStream& output)
{
	output.writeByte((char)mTekiType);
	mPersonality->write(output);
}

/*
 * --INFO--
 * Address:	8011B51C
 * Size:	000070
 */
void GenObjectTeki::updateUseList(Generator*, int)
{
	if (mTekiType < TEKI_START || mTekiType >= TEKI_TypeCount) {
		return;
	}

	tekiMgr->mUsingType[mTekiType] = true;

	if (!tekiMgr->mTekiParams[mTekiType]) {
		return;
	}

	int tekiType = tekiMgr->mTekiParams[mTekiType]->getI(TPI_SpawnType);
	if (tekiType >= TEKI_START && tekiType < TEKI_TypeCount) {
		tekiMgr->mUsingType[tekiType] = true;
	}
}

/*
 * --INFO--
 * Address:	8011B58C
 * Size:	000120
 */
Creature* GenObjectTeki::birth(BirthInfo& info)
{
	// TODO: work out the right inlines for this
	u32 badCompiler;
	u32 badCompiler2;
	u32 badCompiler3;

	Teki* teki = tekiMgr->newTeki(mTekiType);
	if (!teki) {
		return nullptr;
	}

	mPersonality->mPosition.set(info.mPosition);
	mPersonality->mScale.set(info.mScale);
	mPersonality->mFaceDirection = info.mRotation.y;
	teki->mPersonality->input(*mPersonality);
	teki->reset();
	teki->startAI(0);
	teki->mRotation = info.mRotation;
	if (info.mGenerator->mGenType->_28()) {
		teki->setCreatureFlag(CF_Unk16);
	}

	teki->mRebirthDay = info.mGenerator->mGenType->_18();
	return teki;
}
