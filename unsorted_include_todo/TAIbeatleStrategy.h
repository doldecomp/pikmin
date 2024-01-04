#ifndef _TAIBEATLESTRATEGY_H
#define _TAIBEATLESTRATEGY_H

/**
 * .obj __vt__17TAIbeatleStrategy, global
 * .4byte __RTTI__17TAIbeatleStrategy
 * .4byte 0
 * .4byte start__11YaiStrategyFR4Teki
 * .4byte act__17TAIbeatleStrategyFR4Teki
 * .4byte eventPerformed__11YaiStrategyFR9TekiEvent
 * .4byte createEffect__12TekiStrategyFR4Tekii
 * .4byte draw__11YaiStrategyFR4TekiR8Graphics
 * .4byte drawDebugInfo__12TekiStrategyFR4TekiR8Graphics
 * .4byte interact__17TAIbeatleStrategyFR4TekiR18TekiInteractionKey
 * .4byte spawnCorpseParts__12TekiStrategyFR4Teki
 */

struct YaiStrategy {
	virtual void start(Teki&);               // _08
	virtual void act(Teki&);                 // _0C
	virtual void eventPerformed(TekiEvent&); // _10
	virtual void _14() = 0;                  // _14
	virtual void draw(Teki&, Graphics&);     // _18
};

struct TekiStrategy {
	virtual void _08() = 0;                            // _08
	virtual void act(Teki&);                           // _0C
	virtual void _10() = 0;                            // _10
	virtual void createEffect(Teki&, int);             // _14
	virtual void _18() = 0;                            // _18
	virtual void drawDebugInfo(Teki&, Graphics&);      // _1C
	virtual void interact(Teki&, TekiInteractionKey&); // _20
	virtual void spawnCorpseParts(Teki&);              // _24
};

/**
 * @brief TODO
 */
struct TAIbeatleStrategy : public YaiStrategy, public TekiStrategy {
	virtual void act(Teki&);                           // _0C
	virtual void interact(Teki&, TekiInteractionKey&); // _20
};

#endif
