#ifndef _INTERACTPRESS_H
#define _INTERACTPRESS_H

/**
 * .obj __vt__13InteractPress, global
 * .4byte __RTTI__13InteractPress
 * .4byte 0
 * .4byte actCommon__11InteractionFP8Creature
 * .4byte actPiki__13InteractPressFP4Piki
 * .4byte actTeki__13InteractPressFP4Teki
 * .4byte actNavi__13InteractPressFP4Navi
 * .4byte actBoss__11InteractionFP4Boss
 * .4byte actPellet__11InteractionFP6Pellet
 * .4byte actHinderRock__11InteractionFP10HinderRock
 * .4byte actBridge__11InteractionFP6Bridge
 * .4byte actItem__11InteractionFP12ItemCreature
*/

struct Interaction {
	virtual void actCommon(Creature *);        // _08
	virtual void actPiki(Piki *);              // _0C
	virtual void actTeki(Teki *);              // _10
	virtual void actNavi(Navi *);              // _14
	virtual void actBoss(Boss *);              // _18
	virtual void actPellet(Pellet *);          // _1C
	virtual void actHinderRock(HinderRock *);  // _20
	virtual void actBridge(Bridge *);          // _24
	virtual void actItem(ItemCreature *);      // _28
};

/**
 * @brief TODO
 */
struct InteractPress : public Interaction {
	virtual void actPiki(Piki *);  // _0C
	virtual void actTeki(Teki *);  // _10
	virtual void actNavi(Navi *);  // _14

};

#endif