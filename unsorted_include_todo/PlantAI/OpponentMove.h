#ifndef _PLANTAI_OPPONENTMOVE_H
#define _PLANTAI_OPPONENTMOVE_H

/**
 * .obj __vt__Q27PlantAI12OpponentMove, global
 * .4byte __RTTI__Q27PlantAI12OpponentMove
 * .4byte 0
 * .4byte getAgeNodeType__5ANodeFv
 * .4byte read__8CoreNodeFR18RandomAccessStream
 * .4byte satisfy__Q27PlantAI12OpponentMoveFP10AICreature
 */

struct ANode {
	virtual void getAgeNodeType(); // _08 (weak)
};

struct CoreNode {
	virtual void _08() = 0;                 // _08
	virtual void read(RandomAccessStream&); // _0C (weak)
};

namespace PlantAI {
/**
 * @brief TODO
 */
struct OpponentMove : public ANode, public CoreNode {
	virtual void satisfy(AICreature*); // _10
};
} // namespace PlantAI

#endif
