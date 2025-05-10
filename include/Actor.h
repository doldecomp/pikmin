#ifndef _ACTOR_H
#define _ACTOR_H

#include "types.h"
#include "ObjectMgr.h"
#include "AICreature.h"
#include "Graphics.h"
#include "MapMgr.h"
#include "Piki.h"

struct SimpleAI;

/**
 * @brief TODO
 *
 * @note Fun fact: The vtable for this does spawn, but then gets stripped :')
 */
struct Actor : public AICreature {
	Actor(); // unused/inlined

	void setType(int, PikiShapeObject*, CreatureProp*, SimpleAI*);

	// unused/inlined:
	virtual void startAI(int);              // _34
	virtual void refresh(struct Graphics&); // _EC
	virtual void update();                  // _E0
	virtual void doAnimation();             // _108
	virtual void doAI();                    // _104
	virtual void doKill();                  // _10C
	virtual void startMotion(int);          // _130
	virtual void startMotion(int, f32);     // _13C
	virtual void finishMotion();            // _134
	virtual void finishMotion(f32);         // _138

	// _00      = VTBL
	// _00-_304 = AICreature
	PaniPikiAnimMgr mPikiAnimMgr; // _304
	PikiShapeObject* mPikiShape;  // _3B0
};

/**
 * @brief TODO
 *
 * @note This also spawns a vtable but it gets stripped.
 */
struct ActorMgr : public MonoObjectMgr {
	ActorMgr(MapMgr*); // unused/inlined

	virtual ~ActorMgr();              // _48
	virtual Creature* createObject(); // _80

	Actor* newActor(int);

	// _00     = VTBL
	// _08     = VTBL
	// _00-_3C = MonoObjectMgr
	PaniMotionTable* mMotionTable;        // _3C
	PikiShapeObject** mShapeObjectList;   // _40
	CreatureProp** mCreaturePropertyList; // _44
	SimpleAI** mAiManagerList;            // _48
};

extern ActorMgr* actorMgr;

#endif
