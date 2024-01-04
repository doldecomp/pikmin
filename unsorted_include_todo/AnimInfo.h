#ifndef _ANIMINFO_H
#define _ANIMINFO_H

/**
 * .obj __vt__8AnimInfo, weak
 * .4byte __RTTI__8AnimInfo
 * .4byte 0
 * .4byte getAgeNodeType__5ANodeFv
 * .4byte read__8CoreNodeFR18RandomAccessStream
 */

struct ANode {
	virtual void getAgeNodeType(); // _08 (weak)
};

struct CoreNode {
	virtual void _08() = 0;                 // _08
	virtual void read(RandomAccessStream&); // _0C (weak)
};

/**
 * @brief TODO
 */
struct AnimInfo : public ANode, public CoreNode {

	void checkAnimData();
};

#endif
