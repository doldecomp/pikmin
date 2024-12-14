#include "Generator.h"
#include "DynSimulator.h"
#include "DynObject.h"
#include "sysNew.h"

MapMgr* GenObjectMapObject::mapMgr;

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
static void _Error(char* fmt, ...)
{
	OSPanic(__FILE__, __LINE__, fmt, "genMapObject");
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8005D0E8
 * Size:	000040
 */
static GenObject* makeObjectMapObject() { return new GenObjectMapObject; }

/*
 * --INFO--
 * Address:	8005D128
 * Size:	000068
 */
GenObjectMapObject::GenObjectMapObject()
    : GenObject('mobj', "create MAP OBJECT")
{
	_18 = 0;
}

/*
 * --INFO--
 * Address:	8005D190
 * Size:	000090
 */
void GenObjectMapObject::initialise(MapMgr* mgr)
{
	mapMgr                 = mgr;
	GenObjectFactory* fact = GenObjectFactory::factory;
	if (fact->mSpawnerCount >= fact->mMaxSpawners) {
		return;
	}

	fact->mSpawnerInfo[fact->mSpawnerCount].mID          = 'mobj';
	fact->mSpawnerInfo[fact->mSpawnerCount].mGenFunction = &makeObjectMapObject;
	fact->mSpawnerInfo[fact->mSpawnerCount].mName        = "create MAP OBJECT";
	fact->mSpawnerInfo[fact->mSpawnerCount].mVersion     = 'v0.0';

	fact->mSpawnerCount++;
}

/*
 * --INFO--
 * Address:	8005D220
 * Size:	000040
 */
void GenObjectMapObject::doRead(RandomAccessStream& input) { _18 = input.readInt(); }

/*
 * --INFO--
 * Address:	8005D260
 * Size:	000004
 */
void GenObjectMapObject::render(Graphics&, Generator*) { }

/*
 * --INFO--
 * Address:	8005D264
 * Size:	000008
 */
void* GenObjectMapObject::birth(BirthInfo&)
{
	if (false) {
		return new DynObjBridge();
	}
	return nullptr;
}

// I hate these, but things will NOT spawn in the correct order without them.
static DynObjBody* fakeFunc() { return new DynObjBody(); }

static DynObjBridge* fakeFunc2() { return new DynObjBridge(); }
