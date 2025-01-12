#ifndef _WIN_H
#define _WIN_H

#include "types.h"
#include "Colour.h"
#include "CoreNode.h"

struct Graphics;
struct RectArea;
struct Texture;
struct Vector2i;

/**
 * @brief TODO
 *
 * @warning This is meant to inherit CoreNode according to RTTI. However, it doesn't seem to have a vtable? Unsure what its deal is.
 */
struct GmWin : public CoreNode {

	/**
	 * @brief TODO
	 */
	struct CloseListener {
		virtual void onCloseWindow(); // _08

		// _00 = VTBL?
		// TODO: members
	};

	GmWin(); // unused/inlined

	virtual void open();                                                      // _10
	virtual void close();                                                     // _14
	virtual void update();                                                    // _18 unused/inlined
	virtual void doRender(Graphics&);                                         // _1C unused/inlined
	virtual void render(Graphics&);                                           // _20
	virtual void printStart(Graphics&);                                       // _24
	virtual void print(Graphics&, int, int, char*);                           // _28
	virtual void printcentre(Graphics&, int, char*);                          // _2C
	virtual void printleft(Graphics&, int, char*);                            // _30
	virtual void printright(Graphics&, int, char*);                           // _34
	virtual void texture(Graphics&, Texture*, int, int, int, int, RectArea);  // _38
	virtual void texturecentre(Graphics&, Texture*, int, int, int, RectArea); // _3C
	virtual void textureleft(Graphics&, Texture*, int, int, int, RectArea);   // _40
	virtual void textureright(Graphics&, Texture*, int, int, int, RectArea);  // _44

	void placeCentre();
	void setRect(int, int);   // unused/inlined
	void moveHome(Vector2i&); // unused/inlined

	// _00     = VTBL
	// _00-_14 = CoreNode
	CloseListener* mCloseListener; // _14
	int mWidth;                    // _18
	int mHeight;                   // _1C
	int mPosX;                     // _20
	int mPosY;                     // _24
	int mStatus;                   // _28
	int _2C;                       // _2C
	int _30;                       // _30
	int _34;                       // _34
	Colour mColourA;               // _38
	Colour mAuxColourA;            // _3C
	Colour mColourB;               // _40
	Colour mAuxColourB;            // _44
};

/**
 * @brief TODO
 */
struct ContainerWin {

	/**
	 * @brief TODO
	 */
	struct Listener {
		virtual void informWin(int) = 0; // _08

		// _00 = VTBL
	};

	// unused/inlined:
	void doRender(Graphics&);
	void setWin(int, int, Listener*);
	void update();
	void open();
	void close();

	// TODO: members
};

/**
 * @brief TODO
 */
struct ResultWin {
	// unused/inlined:
	void doRender(Graphics&);
	void update();

	// TODO: members
};

/**
 * @brief TODO
 */
struct GmWinMgr {
	GmWinMgr();

	void addWindow(GmWin*);
	void update();
	void render(Graphics&);
	void getWindow(u32);

	// TODO: members
};

#endif
