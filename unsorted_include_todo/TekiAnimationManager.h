#ifndef _TEKIANIMATIONMANAGER_H
#define _TEKIANIMATIONMANAGER_H

/**
 * .obj __vt__20TekiAnimationManager, global
 * .4byte __RTTI__20TekiAnimationManager
 * .4byte 0
 * .4byte getAgeNodeType__5ANodeFv
 * .4byte read__20TekiAnimationManagerFR18RandomAccessStream
 * .4byte update__4NodeFv
 * .4byte draw__4NodeFR8Graphics
 * .4byte render__4NodeFR8Graphics
 * .4byte concat__4NodeFv
 * .4byte concat__4NodeFR3VQS
 * .4byte concat__4NodeFR3SRT
 * .4byte concat__4NodeFR8Matrix4f
 * .4byte getModelMatrix__4NodeFv
 */

struct ANode {
	virtual void getAgeNodeType(); // _08 (weak)
};

struct Node {
	virtual void _08() = 0;                 // _08
	virtual void read(RandomAccessStream&); // _0C
	virtual void update();                  // _10
	virtual void draw(Graphics&);           // _14
	virtual void render(Graphics&);         // _18
	virtual void concat();                  // _1C (weak)
	virtual void concat(VQS&);              // _20 (weak)
	virtual void concat(SRT&);              // _24 (weak)
	virtual void concat(Matrix4f&);         // _28 (weak)
	virtual void getModelMatrix();          // _2C (weak)
};

/**
 * @brief TODO
 */
struct TekiAnimationManager : public ANode, public Node {
	virtual void read(RandomAccessStream&); // _0C

	TekiAnimationManager(TekiMgr*);
};

#endif
