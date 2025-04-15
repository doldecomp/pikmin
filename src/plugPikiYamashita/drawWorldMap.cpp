#include "zen/DrawWorldMap.h"
#include "zen/EffectMgr2D.h"
#include "zen/DrawCommon.h"
#include "P2D/Pane.h"
#include "P2D/TextBox.h"
#include "nlib/Math.h"
#include "DebugLog.h"
#include "sysNew.h"

#define MAX_PARTS_PRACTICE  (2)
#define MAX_PARTS_FOREST    (8)
#define MAX_PARTS_CAVE      (9)
#define MAX_PARTS_YAKUSHIMA (10)
#define MAX_PARTS_LAST      (1)

namespace {
zen::EffectMgr2D* WMeffMgr;

// idk what's going on with these. mapNoScr2Game has to spit out WorldMapName values, which have to equal StageID values
u8 mapNoScr2Game[5] = { WM_Yakushima, WM_Forest, WM_Practice, WM_Cave, WM_Last };
u8 mapNoGame2Scr[5] = { WMSCR_Practice, WMSCR_Forest, WMSCR_Cave, WMSCR_Yakushima, WMSCR_Last };
} // namespace

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR()

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
DEFINE_PRINT("drawWorldMap")

namespace zen {
/**
 * @brief TODO
 *
 * @note Size: 0x28.
 */
struct WorldMapWipe {
	WorldMapWipe() { mWipePane = nullptr; }

	// weak
	void init(P2DScreen* wipeScreen, u32 tag)
	{
		P2DPane* pane = wipeScreen->search(tag, true);
		if (pane->getTypeID() == PANETYPE_Picture) {
			mWipePane = (P2DPicture*)pane;
			_00.set(mWipePane->getPosH() + (mWipePane->getWidth() >> 1), mWipePane->getPosV() + (mWipePane->getHeight() >> 1), 0.0f);
			move(mWipePane->getPosH(), mWipePane->getPosV());

		} else {
			// these are load bearing, take these out and this inlines :')
			PRINT("not picture pane.\n");
			ERROR("not picture pane.\n");
		}
	}

	void move(int x, int y)
	{
		x -= (mWipePane->getWidth() >> 1);
		y -= (mWipePane->getHeight() >> 1);

		_0C.set(mWipePane->getPosH(), mWipePane->getPosV(), 0.0f);
		_18.set(x, y, 0.0f);
	}

	void set(int x, int y)
	{
		x -= (mWipePane->getWidth() >> 1);
		y -= (mWipePane->getHeight() >> 1);
		mWipePane->move(x, y);
		_0C.set(x, y, 0.0f);
		_18.set(x, y, 0.0f);
	}

	void moveDefaultPos() { move(zen::RoundOff(_00.x), zen::RoundOff(_00.y)); }
	void update(f32 t, u8 alpha)
	{
		f32 tComp = 1.0f - t;
		mWipePane->move(zen::RoundOff(_0C.x * tComp + _18.x * t), zen::RoundOff(_0C.y * tComp + _18.y * t));
		mWipePane->setAlpha(alpha);
	}

	void setDefault() { set(zen::RoundOff(_00.x), zen::RoundOff(_00.y)); }

	Vector3f _00;          // _00
	Vector3f _0C;          // _0C
	Vector3f _18;          // _18
	P2DPicture* mWipePane; // _24
};

/**
 * @brief TODO
 *
 * @note Size: 0xB0.
 */
struct WorldMapWipeMgr {
	WorldMapWipeMgr()
	{
		_04       = 0.0f;
		_08       = 1.0f;
		mIsActive = false;
	}

	void init(P2DScreen* wipeScreen)
	{
		mWipes[0].init(wipeScreen, 'wp00');
		mWipes[1].init(wipeScreen, 'wp01');
		mWipes[2].init(wipeScreen, 'wp02');
		mWipes[3].init(wipeScreen, 'wp03');
		init();
	}

	void init()
	{
		_04       = 0.0f;
		_08       = 0.8f;
		mIsActive = false;
	}

	void set(int x, int y)
	{
		for (int i = 0; i < 4; i++) {
			mWipes[i].set(x, y);
		}
		_00 = 0;
	}

	void open(f32 p1)
	{
		_04 = 0.0f;
		_08 = p1;
		for (int i = 0; i < 4; i++) {
			mWipes[i].moveDefaultPos();
		}
		_00       = 2;
		mIsActive = true;
	}

	bool isActive() { return mIsActive; }

	bool update()
	{
		mIsActive = false;
		int state = _00;
		switch (state) {
		case 0:
			break;
		case 1:
		case 2:
			_04 += gsys->getFrameTime();
			if (_04 > _08) {
				_04   = _08;
				state = 0;
			}
			f32 blendFactor;
			u8 alpha;
			if (_00 == 2) {
				blendFactor = (1.0f - NMathF::cos(_04 / _08 * PI)) * 0.5f;
				alpha       = zen::RoundOff(255.0f * (1.0f - blendFactor));
			} else {
				blendFactor = NMathF::sin(_04 / _08 * HALF_PI);
				alpha       = zen::RoundOff(255.0f * blendFactor);
			}

			for (int i = 0; i < 4; i++) {
				mWipes[i].update(blendFactor, alpha);
			}

			_00       = state;
			mIsActive = true;
			break;
		}

		return mIsActive;
	}

	void close(f32 p1, int p2, int p3)
	{
		_04 = 0.0f;
		_08 = p1;
		for (int i = 0; i < 4; i++) {
			mWipes[i].move(p2, p3);
		}
		_00       = 1;
		mIsActive = true;
	}

	void setDefault()
	{
		for (int i = 0; i < 4; i++) {
			mWipes[i].setDefault();
		}
		_00 = 0;
	}

	int _00;                // _00
	f32 _04;                // _04
	f32 _08;                // _08
	WorldMapWipe mWipes[4]; // _0C
	bool mIsActive;         // _AC
};

/**
 * @brief TODO
 *
 * @note Size: 0x3C.
 */
struct WorldMapCursorOnyon {
	WorldMapCursorOnyon()
	{
		mOnyonIcon = nullptr;
		_04.set(0.0f, 0.0f, 0.0f);
		_1C.set(0.0f, 0.0f, 0.0f);
		_34 = zen::Rand(scaleFrameMax);
		mBottomPos.set(0.0f, bottomLengthDefault, 0.0f);
	}

	// weak:
	void init()
	{
		if (mOnyonIcon) {
			mOnyonIcon->setOffset(mOnyonIcon->getWidth() >> 1, mOnyonIcon->getHeight() >> 2);
		} else {
			PRINT("Illegal init WorldMapCursorOnyon Class.\n");
			ERROR("Illegal initialize.");
		}

		_34 = zen::Rand(scaleFrameMax);

		_04.set(0.0f, 0.0f, 0.0f);
		_1C.set(0.0f, 0.0f, 0.0f);
		mBottomPos.set(0.0f, bottomLengthDefault, 0.0f);

		_38 = WMeffMgr->create(EFF2D_MapOnyonSparkle, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
	}
	void update(Vector3f& scale)
	{
		Vector3f vec1 = _10 - _04;
		f32 time      = 60.0f * gsys->getFrameTime();
		f32 len1      = vec1.length();
		if (len1 > 0.000001f) {
			f32 factor = len1 / 300.0f * 10.0f;
			vec1.div(len1);
			if (factor > 15.0f) {
				factor = 15.0f;
			}

			_1C.set(Vector3f(vec1 * factor * time));
			_04.add(_1C);
		}

		mOnyonIcon->move(_04.x, _04.y);
		updateBottomPos();
		_34 += gsys->getFrameTime();
		if (_34 > scaleFrameMax) {
			_34 -= scaleFrameMax;
		}
		f32 angle = _34 / scaleFrameMax;
		mOnyonIcon->setScale(
		    Vector3f(0.9f * scale.x + 0.1f * NMathF::sin(TAU * angle), 0.9f * scale.y - 0.1f * NMathF::sin(TAU * angle), 1.0f));
		if (_38) {
			Vector3f vec2;
			vec2.set(mOnyonIcon->getPosH() + (mOnyonIcon->getWidth() >> 1), mOnyonIcon->getPosV(), 0.0f);
			vec2.y = 480.0f - vec2.y;
			_38->setEmitPos(vec2);
		}
	}

	// DLL:
	void init(P2DScreen* iconScreen, u32 tag, bool hideIcon)
	{
		P2DPane* icon = iconScreen->search(tag, true);
		if (icon->getTypeID() == PANETYPE_Picture) {
			mOnyonIcon = (P2DPicture*)icon;
			if (hideIcon) {
				mOnyonIcon->hide();
			}
		}

		init();
	}
	void show()
	{
		mOnyonIcon->show();
		if (_38) {
			_38->startGen();
		}
	}
	void hide()
	{
		mOnyonIcon->hide();
		if (_38) {
			_38->stopGen();
		}
	}
	void move(f32 x, f32 y) { _10.set(x, y, 0.0f); }
	void set(f32 x, f32 y, f32 scale)
	{
		_04.set(x, y, 0.0f);
		_10.set(x, y, 0.0f);
		mBottomPos.set(x, y + bottomLengthDefault, 0.0f);
		mOnyonIcon->move(_04.x, _04.y);
		mOnyonIcon->setScale(Vector3f(scale, scale, 1.0f));
	}

	void updateBottomPos()
	{
		Vector3f vec1;
		Vector3f vec2;
		vec2.set(mBottomPos.x, mBottomPos.y + 3.0f * gsys->getFrameTime() * 60.0f, mBottomPos.z);
		vec1.set(vec2 - _04);

		f32 len1 = vec1.length();
		if (len1 < 0.000001f) {
			vec1.set(mBottomPos - _04);
			len1 = vec1.length();

			if (len1 < 0.000001f) {
				vec1.set(0.0f, bottomLengthDefault, 0.0f);
				len1 = bottomLengthDefault;
			}
		}

		if (len1 < bottomLengthMin) {
			vec1.multiply(bottomLengthMin / len1);
		} else if (len1 > bottomLengthMax) {
			vec1.multiply(bottomLengthMax / len1);
		}

		vec2.set(_04 + vec1);
		mOnyonIcon->rotateZ(NMathF::atan2(vec1.y, vec1.x) - HALF_PI);
		vec1.normalize();

		vec1.multiply((bottomLengthDefault - len1) * gsys->getFrameTime() * 10.0f);
		mBottomPos.set(vec2);
	}

	static f32 scaleFrameMax;
	static f32 bottomLengthMin;
	static f32 bottomLengthMax;
	static f32 bottomLengthDefault;

	P2DPicture* mOnyonIcon; // _00
	Vector3f _04;           // _04
	Vector3f _10;           // _10
	Vector3f _1C;           // _1C
	Vector3f mBottomPos;    // _28
	f32 _34;                // _34
	particleGenerator* _38; // _38
};

/**
 * @brief TODO
 *
 * @note Size: 0x12C.
 */
struct WorldMapCursorMgr {

	/**
	 * @brief TODO
	 */
	enum ufoStatusFlag {
		UFO_Unk0 = 0,
		UFO_Unk1 = 1,
		UFO_Unk2 = 2,
	};

	WorldMapCursorMgr()
	{
		mRocketIcon = nullptr;
		for (int i = 0; i < 2; i++) {
			_110[i] = 0;
		}

		initParams();
	}

	// weak functions:
	void initParams()
	{
		setLandingFlag(false);
		_35 = 0;
		_38.set(0.0f, 0.0f, 0.0f);
		_00 = 0.0f;
		_0C.set(0.0f, 0.0f, 0.0f);
		_24.set(0.0f, 0.0f, 0.0f);
		mRocketPos.set(0.0f, 0.0f, 0.0f);
		_30 = 0.0f;
		mBlueOnyonPos.set(0.0f, 0.0f, 0.0f);
		mOnyonVelocity.set(0.0f, 0.0f, 0.0f);
		setUfoStatus(UFO_Unk0);
		_128 = 1.0f;
	}

	void setLandingFlag(bool doSet)
	{
		if (doSet) {
			_34 = 1;
			SeSystem::playSysSe(SYSSE_SELECT_DECIDE);

			if (_110[0]) {
				_110[0]->setInitVel(4.0f * _118);
			}
			if (_110[1]) {
				_110[1]->setInitVel(5.0f * _11C);
			}
		} else {
			_34 = 0;
			if (_110[0]) {
				_110[0]->setInitVel(_118);
			}
			if (_110[1]) {
				_110[1]->setInitVel(_11C);
			}
		}
	}
	void init()
	{
		int i;
		if (mRocketIcon) {
			mRocketPos.set(mRocketIcon->getPosH(), mRocketIcon->getPosV(), 0.0f);
			mRocketIcon->setOffset(mRocketIcon->getWidth() >> 1, mRocketIcon->getHeight() >> 1);
			mRocketIcon->setScale(1.0f);
		} else {
			PRINT("Illegal initilize.\n");
			ERROR("Illegal initilize.\n");
		}

		initParams();
		mCursorOnyons[Blue].init();
		mCursorOnyons[Red].init();
		mCursorOnyons[Yellow].init();

		for (i = 0; i < 2; i++) {
			if (_110[i]) {
				_110[0]->forceFinish(); // oops
			}
		}

		_110[0] = WMeffMgr->create(EFF2D_MapRocketFire, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
		_110[0]->invisible();
		_118 = _110[0]->getInitVel();
		_120 = _110[0]->getFreqFrm();

		_110[1] = WMeffMgr->create(EFF2D_MapRocketSmoke, Vector3f(0.0f, 0.0f, 0.0f), nullptr, nullptr);
		_110[1]->invisible();
		_11C = _110[1]->getInitVel();
		_124 = _110[0]->getFreqFrm(); // maybe typo?

		if (playerState) {
			for (i = 0; i < PikiColorCount; i++) {
				if (playerState->displayPikiCount(i)) {
					mCursorOnyons[i].show();
				} else {
					mCursorOnyons[i].hide();
				}
			}
		} else {
			mCursorOnyons[Blue].show();
			mCursorOnyons[Red].show();
			mCursorOnyons[Yellow].show();
		}
	}
	void moveOnyon()
	{
		Vector3f onyonPos[PikiColorCount];
		updateOnyonPos(&onyonPos[Blue], &onyonPos[Red], &onyonPos[Yellow]);
		mCursorOnyons[Blue].move(onyonPos[Blue].x, onyonPos[Blue].y);
		mCursorOnyons[Red].move(onyonPos[Red].x, onyonPos[Red].y);
		mCursorOnyons[Yellow].move(onyonPos[Yellow].x, onyonPos[Yellow].y);
	}
	void updateOnyonPos(Vector3f* bluePos, Vector3f* redPos, Vector3f* yellowPos)
	{
		Vector3f orbitCenter;
		Vector3f newBlueTargetPos;
		Vector3f orbitVec;

		f32 time        = 60.0f * gsys->getFrameTime();
		f32 rocketScale = mRocketIcon->getScale().x;
		orbitCenter.set(mRocketPos.x + ONYON_OFFSET_X, mRocketPos.y + ONYON_OFFSET_Y, mRocketPos.z + ONYON_OFFSET_Z);

		mBlueOnyonPos.add(Vector3f(mOnyonVelocity * time));
		orbitVec.set(mBlueOnyonPos - orbitCenter);
		f32 norm = orbitVec.length();
		if (norm < 0.000001f) {
			orbitVec.set(0.0f, 0.0f, 0.0f);
		} else {
			orbitVec.multiply(ONYON_POS_RADIUS * rocketScale / norm);
		}

		newBlueTargetPos.set(orbitCenter + orbitVec);
		mOnyonVelocity.add(Vector3f(newBlueTargetPos - mBlueOnyonPos));
		mBlueOnyonPos.set(newBlueTargetPos);

		// set blue onyon position (just calculated, reference for others)
		bluePos->set(mBlueOnyonPos.x, mBlueOnyonPos.y, 0.0f);

		// calculate red onyon position (120 degrees rotated from blue)
		f32 cosR = cosf(TAU / 3.0f);
		f32 sinR = sinf(TAU / 3.0f);
		redPos->set(orbitVec.x * cosR + orbitCenter.x - orbitVec.y * sinR, orbitVec.x * sinR + orbitCenter.y + orbitVec.y * cosR, 0.0f);

		// calculate yellow onyon position (240 degrees rotated from blue)
		f32 cosY = cosf(2.0f * TAU / 3.0f);
		f32 sinY = sinf(2.0f * TAU / 3.0f);
		yellowPos->set(orbitVec.x * cosY + orbitCenter.x - orbitVec.y * sinY, orbitVec.x * sinY + orbitCenter.y + orbitVec.y * cosY, 0.0f);
	}
	void stayUfo()
	{
		Vector3f vec1;
		f32 sec = 60.0f * gsys->getFrameTime();
		vec1.set(_0C.x - mRocketPos.x, _0C.y - mRocketPos.y, 0.0f);
		vec1.multiply(0.8f * gsys->getFrameTime());
		_24.add(vec1);
		_24.multiply(0.92f);
		f32 len = _24.length();
		if (len < 0.000001f) {
			_24.set(0.0f, 0.5f, 0.0f);
		} else {
			if (len > 1.0f) {
				_24.multiply(1.0f / len);
			}
			if (len < 0.5f) {
				_24.multiply(0.5f / len);
			}
		}

		mRocketPos.add(_24);

		mRocketIcon->move(zen::RoundOff(mRocketPos.x), zen::RoundOff(mRocketPos.y));
		_30 += calcAddAngle(mRocketIcon->getRotate(), 0.0f, 0.017453292f, sec);
		_30 *= 0.9999f;
		if (_30 > (5.0f * PI / 180.0f)) {
			_30 = (5.0f * PI / 180.0f);
		}
		if (_30 < -(5.0f * PI / 180.0f)) {
			_30 = -(5.0f * PI / 180.0f);
		}

		rotateUfo(zen::correctRad(_30 + mRocketIcon->getRotate()));

		u32 badCompiler;

		PRINT("fake", mRocketIcon ? "fake" : "fake");
		PRINT("fake", mRocketIcon ? "fake" : "fake");
		PRINT("fake", mRocketIcon ? "fake" : "fake");
	}

	bool moveUfo()
	{
		bool res = false;
		Vector3f vec1;
		f32 d;
		f32 sec   = 60.0f * gsys->getFrameTime();
		f32 scale = mRocketIcon->getScale().x;
		f32 a     = 1.0f;

		vec1.set(_0C.x - mRocketPos.x, _0C.y - mRocketPos.y, 0.0f);
		f32 len1 = vec1.length();
		f32 b    = mRocketIcon->getRotate() - HALF_PI;
		b        = zen::correctRad(b);
		f32 c    = NMathF::atan2(vec1.y, vec1.x);
		d        = len1 / 300.0f * 15.0f;
		f32 e;
		if (_34) {
			_00 += gsys->getFrameTime();
			if (len1 < 10.0f) {
				a = 0.0f;
				if (scale == 0.0f) {
					res = true;
				}
			} else {
				a = len1 / 300.0f;
				if (a > 1.0f) {
					a = 1.0f;
				}
			}

			d *= 1.5f;
			e = 20.0f * _00;
			if (e > 180.0f) {
				e = 0.0f;
			}
		} else {
			if (len1 < 20.0f && scale == 1.0f) {
				res = true;
			}
			e = 10.0f;
		}

		b += calcAddAngle(b, c, e * PI / 180.0f, sec);

		rotateUfo(zen::correctRad(b + HALF_PI));

		if (d > 15.0f) {
			d = 15.0f;
		}

		_24.set(d * NMathF::cos(b) * sec, d * NMathF::sin(b) * sec, 0.0f);
		mRocketPos.add(_24);

		// don't let the rocket go more than 100 out of screen bounds (640 x 480)
		if (mRocketPos.x < (0.0f - 100.0f)) {
			mRocketPos.x = (0.0f - 100.0f);
		}
		if (mRocketPos.x > (640.0f + 100.0f)) {
			mRocketPos.x = (640.0f + 100.0f);
		}

		if (mRocketPos.y < (0.0f - 100.0f)) {
			mRocketPos.y = (0.0f - 100.0f);
		}
		if (mRocketPos.y > (480.0f + 100.0f)) {
			mRocketPos.y = (480.0f + 100.0f);
		}

		mRocketIcon->move(zen::RoundOff(mRocketPos.x), zen::RoundOff(mRocketPos.y));

		if (zen::Abs(scale - a) < 0.02f) {
			scale = a;
		} else if (scale < a) {
			scale += 0.02f * sec;
		} else {
			scale -= 0.02f * sec;
		}

		mRocketIcon->setScale(scale);

		u32 badCompiler[2];
		PRINT("fake", mRocketIcon ? "fake" : "fake");
		PRINT("fake", mRocketIcon ? "fake" : "fake");
		PRINT("fake", mRocketIcon ? "fake" : "fake");
		PRINT("fake", mRocketIcon ? "fake" : "fake");
		return res;
	}
	void forceMove()
	{
		if (_35) {
			setUfoStatus(UFO_Unk1);
			_00 = 0.0f;
			_0C.set(_38);
			_35 = false;
			setLandingFlag(true);
		} else {
			PRINT("can't forceMove.\n");
			ERROR("can't forceMove.");
		}
	}
	void effect()
	{
		f32 angle = mRocketIcon->getRotate() - HALF_PI;
		Vector3f vec1;
		vec1.set(mRocketIcon->getPosH() + (mRocketIcon->getWidth() >> 1), mRocketIcon->getPosV() + (mRocketIcon->getHeight() >> 1), 0.0f);
		vec1.add(Vector3f(NMathF::cos(angle) * (-f32(mRocketIcon->getWidth() >> 1) * mRocketIcon->getScale().x),
		                  NMathF::sin(angle) * (-f32(mRocketIcon->getHeight() >> 1) * mRocketIcon->getScale().y), 0.0f));
		vec1.y = 480.0f - vec1.y;

		if (_110[0]) {
			_110[0]->visible();
			_110[0]->setEmitPos(vec1);
			_110[0]->setEmitDir(Vector3f(-NMathF::cos(angle), NMathF::sin(angle), 0.0f));
			_110[0]->setScaleSize(mRocketIcon->getScale().x * 0.5f);
			_110[0]->setFreqFrm(_120 * mRocketIcon->getScale().x * mRocketIcon->getScale().x);
			if (mUfoStatus == UFO_Unk0) {
				_110[0]->setInitVel(_118);
			} else {
				_110[0]->setInitVel(2.0f * _118);
			}
		}

		if (_110[1]) {
			_110[1]->visible();
			_110[1]->setEmitPos(vec1);
			_110[1]->setEmitDir(Vector3f(-NMathF::cos(angle), NMathF::sin(angle), 0.0f));
			_110[1]->setScaleSize(mRocketIcon->getScale().x * 0.7f);
			_110[1]->setFreqFrm(_124 * mRocketIcon->getScale().x * mRocketIcon->getScale().x);
			if (mUfoStatus == UFO_Unk0) {
				_110[1]->setInitVel(_11C * 0.25f);
			} else {
				_110[1]->setInitVel(_11C);
			}
		}
	}

	// DLL:
	void setUfoStatus(ufoStatusFlag status)
	{
		mUfoStatus = status;
		switch (mUfoStatus) {
		case UFO_Unk0:
			_30 = 0.0f;
			break;
		case UFO_Unk1:
			break;
		}
	}

	void init(P2DScreen* iconScreen)
	{
		P2DPane* rocket = iconScreen->search('ri', true);
		if (rocket->getTypeID() == PANETYPE_Picture) {
			mRocketIcon = (P2DPicture*)rocket;
		}

		mCursorOnyons[Blue].init(iconScreen, 'ci_b', false);
		mCursorOnyons[Red].init(iconScreen, 'ci_r', false);
		mCursorOnyons[Yellow].init(iconScreen, 'ci_y', false);
		init();
	}
	void updateOnyons()
	{
		moveOnyon();
		for (int i = 0; i < PikiColorCount; i++) {
			mCursorOnyons[i].update(mRocketIcon->getScale());
		}
	}
	void update()
	{
		switch (mUfoStatus) {
		case UFO_Unk0:
			stayUfo();
			break;

		case UFO_Unk1:
			if (moveUfo()) {
				if (_35) {
					forceMove();
				} else if (_34) {
					setUfoStatus(UFO_Unk2);
				} else {
					setUfoStatus(UFO_Unk0);
				}
			}
			break;
		case UFO_Unk2:
			break;
		}

		updateOnyons();
		effect();
	}

	ufoStatusFlag getStatusFlag() { return mUfoStatus; }

	bool isLanding() { return _34; }
	bool isMoveOK() { return !_35 && !_34; }

	f32 calcAddAngle(f32 p1, f32 p2, f32 p3, f32 p4)
	{
		f32 diff = p2 - p1;
		if (zen::Abs(diff) > p3) {
			f32 x = p3;
			if (zen::Abs(diff) < PI) {
				if (diff < 0.0f) {
					x *= -1.0f;
				}
			} else if (diff > 0.0f) {
				x *= -1.0f;
			}

			return x * p4;
		}

		return diff;
	}

	void rotateUfo(f32 angle) { mRocketIcon->rotateZ(mRocketIcon->getWidth() >> 1, mRocketIcon->getHeight() >> 1, angle); }

	void set(int x, int y, f32 scale)
	{
		mRocketPos.set(x, y, 0.0f);
		_0C.set(x, y, 0.0f);
		mRocketIcon->move(x, y);
		mRocketIcon->setScale(Vector3f(scale, scale, 1.0f));
		setOnyonPos(scale);
	}
	void setOnyonPos(f32 scale)
	{
		Vector3f onyonPos[PikiColorCount];
		updateOnyonPos(&onyonPos[Blue], &onyonPos[Red], &onyonPos[Yellow]);
		mCursorOnyons[Blue].set(onyonPos[Blue].x, onyonPos[Blue].y, scale);
		mCursorOnyons[Red].set(onyonPos[Red].x, onyonPos[Red].y, scale);
		mCursorOnyons[Yellow].set(onyonPos[Yellow].x, onyonPos[Yellow].y, scale);
	}
	void move(int x, int y, bool p3)
	{
		bool check = false;
		if (_35) {
			return;
		}

		if (p3) {
			switch (mUfoStatus) {
			case UFO_Unk0:
				_00   = 0.0f;
				check = true;
				setLandingFlag(true);
				break;
			case UFO_Unk1:
				if (!_34) {
					_35 = true;
					_38.set(x, y, 0.0f);
				}
				break;
			}
		} else if (!_34) {
			check = true;
		}

		if (check) {
			if (!_34 && !_35) {
				SeSystem::playSysSe(SYSSE_SELECT_MOVE);
			}
			setUfoStatus(UFO_Unk1);
			_0C.set(x, y, 0.0f);
		}
	}

	void moveCancel(int x, int y)
	{
		if (_35 || _34) {
			_35 = false;
			setLandingFlag(false);
			setUfoStatus(UFO_Unk1);
			_0C.set(x, y, 0.0f);
			SeSystem::playSysSe(SYSSE_CANCEL);
		}
	}

	// DLL inlines to do:

	static const f32 ONYON_POS_RADIUS;
	static const f32 ONYON_OFFSET_X;
	static const f32 ONYON_OFFSET_Y;
	static const f32 ONYON_OFFSET_Z;

	f32 _00;                                           // _00
	ufoStatusFlag mUfoStatus;                          // _04
	P2DPicture* mRocketIcon;                           // _08
	Vector3f _0C;                                      // _0C
	Vector3f mRocketPos;                               // _18
	Vector3f _24;                                      // _24
	f32 _30;                                           // _30
	bool _34;                                          // _34
	bool _35;                                          // _35
	Vector3f _38;                                      // _38
	WorldMapCursorOnyon mCursorOnyons[PikiColorCount]; // _44, indexed by PikiColor
	Vector3f mBlueOnyonPos;                            // _F8
	Vector3f mOnyonVelocity;                           // _104
	zen::particleGenerator* _110[2];                   // _110
	f32 _118;                                          // _118
	f32 _11C;                                          // _11C
	f32 _120;                                          // _120
	f32 _124;                                          // _124
	f32 _128;                                          // _128
};

/**
 * @brief TODO
 */
struct WorldMapPartsInfoMgr {
	WorldMapPartsInfoMgr()
	{
		mMaxPartCount   = 0;
		mFadedStarIcons = nullptr;
	}

	void setDisplayParts(int max, int curr)
	{
		for (int i = 0; i < mMaxPartCount; i++) {
			if (i < max) {
				if (i < curr) {
					mGlowingStarIcons[i]->show();
					mFadedStarIcons[i]->hide();
				} else {
					mGlowingStarIcons[i]->hide();
					mFadedStarIcons[i]->show();
				}
			} else {
				mGlowingStarIcons[i]->hide();
				mFadedStarIcons[i]->hide();
			}
		}
	}
	void setActiveMapNo(WorldMapName id)
	{
		int curr, max;
		if (id == WM_NULL) {
			max = curr = 0;
		} else if (playerState) {
			switch (id) {
			case WM_Practice:
				max  = MAX_PARTS_PRACTICE;
				curr = playerState->getPartsGetCount(WM_Practice);
				break;
			case WM_Forest:
				max  = MAX_PARTS_FOREST;
				curr = playerState->getPartsGetCount(WM_Forest);
				break;
			case WM_Cave:
				max  = MAX_PARTS_CAVE;
				curr = playerState->getPartsGetCount(WM_Cave);
				break;
			case WM_Yakushima:
				max  = MAX_PARTS_YAKUSHIMA;
				curr = playerState->getPartsGetCount(WM_Yakushima);
				break;
			case WM_Last:
				max  = MAX_PARTS_LAST;
				curr = playerState->getPartsGetCount(WM_Last);
				break;
			default:
				max  = 0;
				curr = 0;
				break;
			}
		} else {
			switch (id) {
			case WM_Practice:
				max  = MAX_PARTS_PRACTICE;
				curr = 1;
				break;
			case WM_Forest:
				max  = MAX_PARTS_FOREST;
				curr = 2;
				break;
			case WM_Cave:
				max  = MAX_PARTS_CAVE;
				curr = 3;
				break;
			case WM_Yakushima:
				max  = MAX_PARTS_YAKUSHIMA;
				curr = 4;
				break;
			case WM_Last:
				max  = MAX_PARTS_LAST;
				curr = 0;
				break;
			default:
				max  = 0;
				curr = 0;
				break;
			}
		}

		setDisplayParts(max, curr);
	}

	// DLL:
	void init(P2DScreen* dataScreen)
	{
		char partStr[8];
		int partCount = 0;
		sprintf(partStr, "pa%02d", 0);
		while (dataScreen->search(P2DPaneLibrary::makeTag(partStr), false)) {
			sprintf(partStr, "pa%02d", ++partCount);
		}

		mMaxPartCount     = partCount;
		mFadedStarIcons   = new P2DPicture*[mMaxPartCount];
		mGlowingStarIcons = new P2DPicture*[mMaxPartCount];

		for (int i = 0; i < mMaxPartCount; i++) {
			sprintf(partStr, "pn%02d", i);
			P2DPane* pane = dataScreen->search(P2DPaneLibrary::makeTag(partStr), true);
			if (pane->getTypeID() == PANETYPE_Picture) {
				mFadedStarIcons[i] = (P2DPicture*)pane;
				mFadedStarIcons[i]->show();
				P2DPaneLibrary::changeParent(mFadedStarIcons[i], P2DPaneLibrary::getParentPane(mFadedStarIcons[i]));
			} else {
				PRINT("not picture pane.\n");
				ERROR("not picture pane.\n");
			}

			sprintf(partStr, "pa%02d", i);
			pane = dataScreen->search(P2DPaneLibrary::makeTag(partStr), true);
			if (pane->getTypeID() == PANETYPE_Picture) {
				mGlowingStarIcons[i] = (P2DPicture*)pane;
				mGlowingStarIcons[i]->show();
				P2DPaneLibrary::changeParent(mGlowingStarIcons[i], P2DPaneLibrary::getParentPane(mGlowingStarIcons[i]));
			} else {
				PRINT("not picture pane.\n");
				ERROR("not picture pane.\n");
			}
		}

		init();
	}
	void init() { }
	void update() { }

	void close() { setActiveMapNo(WM_NULL); }

	int mMaxPartCount;              // _00
	P2DPicture** mFadedStarIcons;   // _04
	P2DPicture** mGlowingStarIcons; // _08
};

/**
 * @brief TODO
 *
 * @note Size: 0x88.
 */
struct WorldMapConfirmMgr {
	/**
	 * @brief TODO
	 */
	enum statusFlag {
		STATUS_Unk0 = 0,
		STATUS_Unk1 = 1,
		STATUS_Unk2 = 2,
		STATUS_Unk3 = 3,
	};

	/**
	 * @brief TODO
	 */
	enum selectFlag {
		SELECT_Unk0 = 0,
		SELECT_Unk1 = 1,
		SELECT_COUNT, // 2
	};

	WorldMapConfirmMgr()
	{
		mConfirmScreen = new DrawScreen("screen/blo/w_ok.blo", nullptr, true, true);

		P2DScreen* confScreen = mConfirmScreen->getScreenPtr();
		confScreen->setOffset(mConfirmScreen->getScreenPtr()->getWidth() >> 1, mConfirmScreen->getScreenPtr()->getHeight() >> 1);
		P2DPane* parent = confScreen->search('pall', true);
		P2DPane* pane   = confScreen->search('se_c', true);
		if (pane->getTypeID() == PANETYPE_TextBox) {
			static_cast<P2DTextBox*>(pane)->getFontColor(_68, _6C);
		} else {
			ERROR("tag<se_c> pane is not text box.\n");
		}

		mMenuItems = new DrawMenuItem[SELECT_COUNT];

		for (int i = 0; i < SELECT_COUNT; i++) {
			char str[8];
			sprintf(str, "he%02d", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			P2DPaneLibrary::changeParent(pane, parent);
			mMenuItems[i].setTextPane(pane, nullptr);

			sprintf(str, "i%02dl", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			if (mMenuItems[i].setIconLPane(pane, parent)) {
				ERROR("pane [%s] is not picture.\n", str);
			}

			sprintf(str, "i%02dr", i);
			pane = confScreen->search(P2DPaneLibrary::makeTag(str), true);
			if (mMenuItems[i].setIconRPane(pane, parent)) {
				ERROR("pane [%s] is not picture.\n", str);
			}
		}

		mLeftSpecCursor.init(confScreen, parent, 'z**l', 10.0f, 100.0f);
		mRightSpecCursor.init(confScreen, parent, 'z**r', 50.0f, 100.0f);
		init();
	}

	void init(statusFlag status)
	{
		mStatus = status;
		mConfirmScreen->getScreenPtr()->move(640, 0);
		mConfirmScreen->getScreenPtr()->setScale(1.0f);
		mConfirmScreen->getScreenPtr()->show();
		_70               = 0.0f;
		mCurrentSelection = SELECT_Unk0;
		mLeftSpecCursor.initPos(mMenuItems[mCurrentSelection].getIconLPosH(), mMenuItems[mCurrentSelection].getIconLPosV());
		mRightSpecCursor.initPos(mMenuItems[mCurrentSelection].getIconRPosH(), mMenuItems[mCurrentSelection].getIconRPosV());

		for (int i = 0; i < SELECT_COUNT; i++) {
			mMenuItems[i].init(i == mCurrentSelection, _68, _6C);
		}
	}

	bool modeOperation(Controller* controller)
	{
		DrawMenuItem* currItem;
		bool res     = false;
		int startSel = mCurrentSelection;
		mCurrentSelection += controller->keyClick(KBBTN_MSTICK_DOWN) - controller->keyClick(KBBTN_MSTICK_UP);
		if (mCurrentSelection < 0) {
			mCurrentSelection = SELECT_Unk1;
		}
		if (mCurrentSelection > 1) {
			mCurrentSelection = SELECT_Unk0;
		}

		currItem = &mMenuItems[mCurrentSelection];
		for (int i = 0; i < 2; i++) {
			mMenuItems[i].update(i == mCurrentSelection, _68, _6C);
		}
		if (startSel != mCurrentSelection) {
			SeSystem::playSysSe(SYSSE_MOVE1);
			mLeftSpecCursor.move(currItem->getIconLPosH(), currItem->getIconLPosV(), 0.5f);
			mRightSpecCursor.move(currItem->getIconRPosH(), currItem->getIconRPosV(), 0.5f);
		}

		if (controller->keyClick(KBBTN_START | KBBTN_A)) {
			SeSystem::playSysSe(SYSSE_DECIDE1);
			res = true;
		}

		if (controller->keyClick(KBBTN_B)) {
			SeSystem::playSysSe(SYSSE_CANCEL);
			mCurrentSelection = SELECT_Unk1;
			res               = true;
		}
		return res;
	}

	// DLL:
	void init() { init(STATUS_Unk0); }

	void draw(Graphics&) { mConfirmScreen->draw(); }

	bool update(Controller* controller)
	{
		switch (mStatus) {
		case STATUS_Unk1:
			_70 += gsys->getFrameTime();
			f32 a;
			if (_70 > 0.25f) {
				_70     = 0.0f;
				a       = 1.0f;
				mStatus = STATUS_Unk2;
			} else {
				a = NMathF::sin(_70 / 0.25f * HALF_PI);
			}

			f32 angle1 = HALF_PI * a;
			_7C.x      = 100.0f * NMathF::cos(angle1);
			_7C.y      = 0.0f;
			_7C.z      = 100.0f * NMathF::sin(angle1) - 100.0f;

			mConfirmScreen->getScreenPtr()->move(zen::RoundOff(_7C.x), zen::RoundOff(_7C.y));
			mConfirmScreen->getScreenPtr()->moveZ(_7C.z);
			mConfirmScreen->getScreenPtr()->rotate(P2DROTATE_Unk1, TAU - (angle1 - HALF_PI));
			break;
		case STATUS_Unk2:
			if (modeOperation(controller)) {
				mStatus = STATUS_Unk3;
				_70     = 0.0f;
			}
			break;
		case STATUS_Unk3:
			_70 += gsys->getFrameTime();
			f32 b;
			if (_70 > 0.25f) {
				_70     = 0.0f;
				b       = 1.0f;
				mStatus = STATUS_Unk0;
				mConfirmScreen->getScreenPtr()->hide();
			} else {
				b = 1.0f - NMathF::cos(_70 / 0.25f * HALF_PI);
			}
			if (mCurrentSelection == SELECT_Unk0) {
				mConfirmScreen->getScreenPtr()->move(0, zen::RoundOff(b * -480.0f));
			} else {
				f32 angle2 = HALF_PI * b + HALF_PI;
				_7C.x      = 100.0f * NMathF::cos(angle2);
				_7C.y      = 0.0f;
				_7C.z      = 100.0f * NMathF::sin(angle2) - 100.0f;

				mConfirmScreen->getScreenPtr()->move(zen::RoundOff(_7C.x), zen::RoundOff(_7C.y));
				mConfirmScreen->getScreenPtr()->moveZ(_7C.z);
				mConfirmScreen->getScreenPtr()->rotate(P2DROTATE_Unk1, TAU - (angle2 - HALF_PI));
			}
			break;
		}

		mConfirmScreen->update();
		mLeftSpecCursor.update();
		mRightSpecCursor.update();
		return mStatus == STATUS_Unk0;
	}
	selectFlag getSelectFlag() { return (selectFlag)mCurrentSelection; }

	void start() { init(STATUS_Unk1); }

	DrawScreen* mConfirmScreen;         // _00
	SpectrumCursorMgr mLeftSpecCursor;  // _04
	SpectrumCursorMgr mRightSpecCursor; // _34
	DrawMenuItem* mMenuItems;           // _64
	Colour _68;                         // _68
	Colour _6C;                         // _6C
	f32 _70;                            // _70
	statusFlag mStatus;                 // _74
	int mCurrentSelection;              // _78, see selectFlag enum
	Vector3f _7C;                       // _7C
};

/**
 * @brief TODO
 *
 * @note Size: 0x138.
 */
struct WorldMapCoursePointMgr {
	WorldMapCoursePointMgr()
	{
		mSelectedPoint = 0;
		mEventFlag     = 0;
		_00            = 0;
	}

	bool modeAppear()
	{
		bool res                   = false;
		WorldMapCoursePoint* point = mCoursePoints;
		for (int i = 0; i < 5; i++) {
			point->update(point == mSelectedPoint);
			if (point->getEventFlag() & 0x1) {
				res = true;
			}
			point++;
		}
		return res;
	}
	bool modeOperation(Controller* controller, bool p2)
	{
		WorldMapCoursePoint* point = mCoursePoints;
		for (int i = 0; i < 5; i++) {
			point->update(point == mSelectedPoint);
			point++;
			u32 badCompiler;
		}
		if (controller) {
			if (p2) {
				keyOperation(controller, KBBTN_MSTICK_UP, WorldMapCoursePoint::LINK_Up);
				keyOperation(controller, KBBTN_MSTICK_DOWN, WorldMapCoursePoint::LINK_Down);
				keyOperation(controller, KBBTN_MSTICK_LEFT, WorldMapCoursePoint::LINK_Left);
				keyOperation(controller, KBBTN_MSTICK_RIGHT, WorldMapCoursePoint::LINK_Right);

				if (controller->keyClick(KBBTN_START | KBBTN_A)) {
					SeSystem::playSysSe(SYSSE_DECIDE1);
					mEventFlag |= 0x10;
				}
			} else if (controller->keyClick(KBBTN_B)) {
				SeSystem::playSysSe(SYSSE_CANCEL);
				mEventFlag |= 0x20;
			}
		}
		return false;
	}

	// DLL:
	void setSelectCourse(WorldMapName gameStageID)
	{
		mSelectedPoint = &mCoursePoints[mapNoGame2Scr[gameStageID]];
		mSelectedPoint->select();
	}

	void init(P2DScreen* pointScreen, P2DScreen* lineScreen, WorldMapName startStageID)
	{
		WorldMapCoursePoint* point;
		mEventFlag = 0;
		if (playerState) {
			point = &mCoursePoints[0];
			point->setPane(pointScreen, 'x_1', 'x_1s', 'po01', lineScreen, 'sli1');
			point->setLink(&mCoursePoints[4], &mCoursePoints[1], nullptr, &mCoursePoints[3]);
			if (playerState->courseOpen(STAGE_Yakushima)) {
				point = &mCoursePoints[1];
				point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
				point->setLink(&mCoursePoints[0], nullptr, nullptr, &mCoursePoints[2]);
			} else {
				point = &mCoursePoints[1];
				point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
				point->setLink(&mCoursePoints[3], nullptr, nullptr, &mCoursePoints[2]);
			}

			point = &mCoursePoints[2];
			point->setPane(pointScreen, 'x_3', 'x_3s', 'po03', lineScreen, 'sli3');
			point->setLink(&mCoursePoints[3], nullptr, &mCoursePoints[1], nullptr);
			if (playerState->courseOpen(STAGE_Yakushima)) {
				point = &mCoursePoints[3];
				point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
				point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[0], nullptr);
			} else {
				point = &mCoursePoints[3];
				point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
				point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[1], nullptr);
			}

			point = &mCoursePoints[4];
			point->setPane(pointScreen, 'x_5', 'x_5s', 'po05', lineScreen, 'sli5');
			point->setLink(nullptr, &mCoursePoints[3], &mCoursePoints[0], nullptr);

		} else {
			point = &mCoursePoints[0];
			point->setPane(pointScreen, 'x_1', 'x_1s', 'po01', lineScreen, 'sli1');
			point->setLink(&mCoursePoints[4], &mCoursePoints[1], nullptr, &mCoursePoints[3]);

			point = &mCoursePoints[1];
			point->setPane(pointScreen, 'x_2', 'x_2s', 'po02', lineScreen, 'sli2');
			point->setLink(&mCoursePoints[0], nullptr, nullptr, &mCoursePoints[2]);

			point = &mCoursePoints[2];
			point->setPane(pointScreen, 'x_3', 'x_3s', 'po03', lineScreen, 'sli3');
			point->setLink(&mCoursePoints[3], nullptr, &mCoursePoints[1], nullptr);

			point = &mCoursePoints[3];
			point->setPane(pointScreen, 'x_4', 'x_4s', 'po04', lineScreen, 'sli4');
			point->setLink(&mCoursePoints[4], &mCoursePoints[2], &mCoursePoints[0], nullptr);

			point = &mCoursePoints[4];
			point->setPane(pointScreen, 'x_5', 'x_5s', 'po05', lineScreen, 'sli5');
			point->setLink(nullptr, &mCoursePoints[3], &mCoursePoints[0], nullptr);
		}

		for (int i = WM_START; i < WM_COUNT; i++) {
			WorldMapName gameStageID = (WorldMapName)mapNoScr2Game[i];
			char onyStr[8];
			sprintf(onyStr, "ony%d", i + 1);
			char chaStr[8];
			sprintf(chaStr, "cha%d", i + 1);

			mCoursePoints[i].setCursorPoint(pointScreen, P2DPaneLibrary::makeTag(onyStr), P2DPaneLibrary::makeTag(chaStr));
			mCoursePoints[i].setNumber(gameStageID);
			mCoursePoints[i].nonSelect();
			mCoursePoints[i].openCourse();
			if (playerState && !playerState->courseOpen(gameStageID)) {
				mCoursePoints[i].closeCourse();
			}
		}

		setSelectCourse(startStageID);
	}

	// might be appear
	void start(WorldMapName id)
	{
		_00 = 0;
		for (int i = 0; i < WM_COUNT; i++) {
			mCoursePoints[i].nonSelect();
		}
		setSelectCourse(id);
	}

	void getLandPos(int* x, int* y)
	{
		P2DPane* landPane = mSelectedPoint->getLandPane();
		*x                = landPane->getPosH();
		*y                = landPane->getPosV();
	}
	void getStayPos(int* x, int* y)
	{
		P2DPane* landPane = mSelectedPoint->getStayPane();
		*x                = landPane->getPosH();
		*y                = landPane->getPosV();
	}

	void appear(WorldMapName id)
	{
		_00 = 1;
		for (int i = 0; i < WM_COUNT; i++) {
			if (mSelectedPoint != &mCoursePoints[i]) {
				mCoursePoints[i].nonSelect();
			} else {
				mCoursePoints[i].select();
			}
		}

		mCoursePoints[mapNoGame2Scr[id]].appear();
	}

	WorldMapName getSelectCourseNumber()
	{
		WorldMapName id = WM_NULL;
		if (mSelectedPoint) {
			id = mSelectedPoint->getNumber();
		}
		return id;
	}

	bool update(Controller* controller, bool p2)
	{
		bool res   = false;
		mEventFlag = 0;
		switch (_00) {
		case 0:
			res = modeOperation(controller, p2);
			break;
		case 1:
			res = modeAppear();
			if (res == true) {
				_00        = 0;
				mEventFlag = 0x40;
			}
			break;
		default:
			PRINT("unknown mode %d \n", _00);
			ERROR("unknown mode %d \n", _00);
			break;
		}
		return res;
	}

	u32 getEventFlag() { return mEventFlag; }

	void createCourseInEffect() { mSelectedPoint->createCourseInEffect(); }

	// DLL inlines to do:
	void keyOperation(Controller* controller, u32 button, WorldMapCoursePoint::linkFlag linkID)
	{
		if (controller->keyClick(button)) {
			WorldMapCoursePoint* linkPoint = mSelectedPoint->getLinkCoursePointPtr(linkID);
			if (linkPoint && linkPoint->getOpenSw()) {
				SeSystem::playSysSe(SYSSE_MOVE1);
				mSelectedPoint->nonSelect();
				mSelectedPoint = linkPoint;
				mSelectedPoint->select();
				mEventFlag |= 0x1;
			}
		}
	}

	int _00;                              // _00
	WorldMapCoursePoint* mSelectedPoint;  // _04
	WorldMapCoursePoint mCoursePoints[5]; // _08
	u32 mEventFlag;                       // _134
};

/**
 * @brief TODO
 */
struct WorldMapMapImageMgr {
	WorldMapMapImageMgr()
	{
		_04 = 2;
		_08 = -1;
		_00 = 0.0f;
		_20 = 0;
		for (int i = 0; i < 5; i++) {
			mMapImagePanes[i] = nullptr;
		}
	}

	// weak:
	void init()
	{
		_04 = 0;
		for (int i = 0; i < 5; i++) {
			if (mMapImagePanes[i]) {
				mMapImagePanes[i]->hide();
				mMapImagePanes[i]->setOffset(mMapImagePanes[i]->getWidth() >> 1, mMapImagePanes[i]->getHeight() >> 1);
			}
		}

		_08 = 0;

		closeMapImage();
	}
	void modeOpen()
	{
		_00 += gsys->getFrameTime();
		f32 a;
		if (_00 > 0.25f) {
			a   = 1.0f;
			_00 = 0.0f;
			if (_20) {
				_04 = 1;
				_20 = 0;
			} else {
				_04 = 0;
			}
		} else {
			a = _00 / 0.25f;
		}
		f32 xScale = a / 0.5f;
		if (xScale > 1.0f) {
			xScale = 1.0f;
		}
		f32 yScale = (a - 0.5f) / 0.5f;
		if (yScale < 0.05f) {
			yScale = 0.05f;
		}
		if (yScale > 1.0f) {
			yScale = 1.0f;
		}
		mMapImagePanes[_08]->setScale(xScale, yScale, 1.0f);
		mMapImagePanes[_08]->show();
	}
	void modeClose()
	{
		_00 += gsys->getFrameTime();
		if (_00 > 0.25f) {
			_00 = 0.25f;
			mMapImagePanes[_08]->hide();
		} else {
			f32 a      = 1.0f - _00 / 0.25f;
			f32 xScale = a / 0.5f;
			if (xScale > 1.0f) {
				xScale = 1.0f;
			}

			f32 yScale = (a - 0.5f) / 0.5f;
			if (yScale < 0.05f) {
				yScale = 0.05f;
			}
			if (yScale > 1.0f) {
				yScale = 1.0f;
			}
			mMapImagePanes[_08]->setScale(xScale, yScale, 1.0f);
			mMapImagePanes[_08]->show();
		}
	}

	// DLL:
	void init(P2DScreen* moniScreen)
	{
		P2DPane* pane1 = moniScreen->search('mi_1', true);
		if (pane1->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[0] = (P2DPicture*)pane1;
		}
		P2DPane* pane2 = moniScreen->search('mi_2', true);
		if (pane2->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[1] = (P2DPicture*)pane2;
		}
		P2DPane* pane3 = moniScreen->search('mi_3', true);
		if (pane3->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[2] = (P2DPicture*)pane3;
		}
		P2DPane* pane4 = moniScreen->search('mi_4', true);
		if (pane4->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[3] = (P2DPicture*)pane4;
		}
		P2DPane* pane5 = moniScreen->search('mi_5', true);
		if (pane5->getTypeID() == PANETYPE_Picture) {
			mMapImagePanes[4] = (P2DPicture*)pane5;
		}

		init();
	}

	void closeMapImage()
	{
		switch (_04) {
		case 0:
			_00 = 0.0f;
			_04 = 1;
			break;
		case 2:
			_20 = 1;
			break;
		}
	}

	void update()
	{
		switch (_04) {
		case 0:
			if (_08 != -1) {
				mMapImagePanes[_08]->show();
				mMapImagePanes[_08]->setScale(1.0f);
			}
			break;
		case 1:
			modeClose();
			break;
		case 2:
			modeOpen();
			break;
		}
	}
	void openMapImage(WorldMapName id)
	{
		if (_04 == 1) {
			_00 = 0.0f;
			_08 = id;
			_04 = 2;
			PRINT("openMapImage %d \n", id);
		}
	}

	f32 _00;                       // _00
	int _04;                       // _04
	int _08;                       // _08
	P2DPicture* mMapImagePanes[5]; // _0C
	u8 _20;                        // _20
};

} // namespace zen

const int zen::WorldMapTitleMgr::OBJ_NUM = 5;

// probably need to move these around later for ordering
f32 zen::WorldMapCursorOnyon::bottomLengthMin     = 10.0f;
f32 zen::WorldMapCursorOnyon::bottomLengthDefault = 15.0f;
f32 zen::WorldMapCursorOnyon::bottomLengthMax     = 20.0f;
f32 zen::WorldMapCursorOnyon::scaleFrameMax       = 0.8f;

const f32 zen::WorldMapCursorMgr::ONYON_POS_RADIUS = 60.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_X   = 0.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_Y   = 20.0f;
const f32 zen::WorldMapCursorMgr::ONYON_OFFSET_Z   = 0.0f;

const int WorldMapCoursePoint::EVENT_NONE          = 0;
const int WorldMapCoursePoint::EVENT_APPEAR_FINISH = 1;

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
zen::DrawWorldMap::~DrawWorldMap()
{
}

/*
 * --INFO--
 * Address:	801DB14C
 * Size:	00246C
 */
zen::DrawWorldMap::DrawWorldMap()
{
	// SET UP EFFECTS MGR
	mEffectMgr2D = new EffectMgr2D(96, 500, 650);
	WMeffMgr     = mEffectMgr2D;

	// SET UP SCREENS
	mWipeScreen  = new DrawScreen("screen/blo/w_wipe.blo", nullptr, true, true);
	mIconScreen  = new DrawScreen("screen/blo/w_icon.blo", nullptr, true, true);
	mTitleScreen = new DrawScreen("screen/blo/w_title.blo", nullptr, true, true);
	mMoniScreen  = new DrawScreen("screen/blo/w_moni.blo", nullptr, true, true);
	mData1Screen = new DrawScreen("screen/blo/w_data1.blo", nullptr, true, true);
	mData2Screen = new DrawScreen("screen/blo/w_data2.blo", nullptr, true, true);
	mPointScreen = new DrawScreen("screen/blo/w_point.blo", nullptr, true, true);
	mLineScreen  = new DrawScreen("screen/blo/w_line.blo", nullptr, true, true);
	mBackScreen  = new DrawScreen("screen/blo/w_back.blo", nullptr, true, true);

	_0C = 0.0f;
	_04 = -1;
	_08 = -1;

	// SET UP COURSE POINTS
	mCoursePointMgr = new WorldMapCoursePointMgr();
	mCoursePointMgr->init(mPointScreen->getScreenPtr(), mLineScreen->getScreenPtr(), WM_START);

	// SET UP WIPES
	mWipeMgr = new WorldMapWipeMgr();
	mWipeMgr->init(mWipeScreen->getScreenPtr());

	// SET UP MAP IMAGES
	mMapImageMgr = new WorldMapMapImageMgr();
	mMapImageMgr->init(mMoniScreen->getScreenPtr());

	// SET UP COUNTERS
	if (playerState) {
		mTotalPartsNum           = playerState->getTotalParts();
		mCurrentPartsNum         = playerState->getCurrParts();
		mTotalPikiCounts[Blue]   = playerState->getTotalPikiCount(Blue);
		mTotalPikiCounts[Red]    = playerState->getTotalPikiCount(Red);
		mTotalPikiCounts[Yellow] = playerState->getTotalPikiCount(Yellow);

	} else {
		PRINT("WARNING! playerState ptr is NULL.\n");
		mTotalPartsNum           = 30;
		mCurrentPartsNum         = 29;
		mTotalPikiCounts[Blue]   = 999;
		mTotalPikiCounts[Red]    = 999;
		mTotalPikiCounts[Yellow] = 999;
	}

	P2DPane* dateCentrePane = mData1Screen->getScreenPtr()->search('dc_c', true);
	P2DPane* dateLeftPane   = mData1Screen->getScreenPtr()->search('dc_l', true);
	P2DPane* dateRightPane  = mData1Screen->getScreenPtr()->search('dc_r', true);

	dateCentrePane->setCallBack(new DrawWorldMapDateCallBack(dateCentrePane, dateLeftPane, dateRightPane));

	// CURRENT PARTS
	P2DPane* currPartsLeftPane = mData1Screen->getScreenPtr()->search('ro_l', true);
	currPartsLeftPane->setCallBack(new NumberPicCallBack<int>(currPartsLeftPane, &mCurrentPartsNum, 10, false));

	P2DPane* currPartsRightPane = mData1Screen->getScreenPtr()->search('ro_r', true);
	currPartsRightPane->setCallBack(new NumberPicCallBack<int>(currPartsRightPane, &mCurrentPartsNum, 1, false));

	// TOTAL PARTS
	P2DPane* totalPartsLeftPane = mData1Screen->getScreenPtr()->search('rt_l', true);
	totalPartsLeftPane->setCallBack(new NumberPicCallBack<int>(totalPartsLeftPane, &mTotalPartsNum, 10, false));

	P2DPane* totalPartsRightPane = mData1Screen->getScreenPtr()->search('rt_r', true);
	totalPartsRightPane->setCallBack(new NumberPicCallBack<int>(totalPartsRightPane, &mTotalPartsNum, 1, false));

	// BLUE PIKIS
	P2DPane* bluePikiLeftPane = mData1Screen->getScreenPtr()->search('bp_l', true);
	bluePikiLeftPane->setCallBack(new NumberPicCallBack<int>(bluePikiLeftPane, &mTotalPikiCounts[Blue], 100, false));

	P2DPane* bluePikiCentrePane = mData1Screen->getScreenPtr()->search('bp_c', true);
	bluePikiCentrePane->setCallBack(new NumberPicCallBack<int>(bluePikiCentrePane, &mTotalPikiCounts[Blue], 10, false));

	P2DPane* bluePikiRightPane = mData1Screen->getScreenPtr()->search('bp_r', true);
	bluePikiRightPane->setCallBack(new NumberPicCallBack<int>(bluePikiRightPane, &mTotalPikiCounts[Blue], 1, false));

	// RED PIKIS
	P2DPane* redPikiLeftPane = mData1Screen->getScreenPtr()->search('rp_l', true);
	redPikiLeftPane->setCallBack(new NumberPicCallBack<int>(redPikiLeftPane, &mTotalPikiCounts[Red], 100, false));

	P2DPane* redPikiCentrePane = mData1Screen->getScreenPtr()->search('rp_c', true);
	redPikiCentrePane->setCallBack(new NumberPicCallBack<int>(redPikiCentrePane, &mTotalPikiCounts[Red], 10, false));

	P2DPane* redPikiRightPane = mData1Screen->getScreenPtr()->search('rp_r', true);
	redPikiRightPane->setCallBack(new NumberPicCallBack<int>(redPikiRightPane, &mTotalPikiCounts[Red], 1, false));

	// YELLOW PIKIS
	P2DPane* yellowPikiLeftPane = mData1Screen->getScreenPtr()->search('yp_l', true);
	yellowPikiLeftPane->setCallBack(new NumberPicCallBack<int>(yellowPikiLeftPane, &mTotalPikiCounts[Yellow], 100, false));

	P2DPane* yellowPikiCentrePane = mData1Screen->getScreenPtr()->search('yp_c', true);
	yellowPikiCentrePane->setCallBack(new NumberPicCallBack<int>(yellowPikiCentrePane, &mTotalPikiCounts[Yellow], 10, false));

	P2DPane* yellowPikiRightPane = mData1Screen->getScreenPtr()->search('yp_r', true);
	yellowPikiRightPane->setCallBack(new NumberPicCallBack<int>(yellowPikiRightPane, &mTotalPikiCounts[Yellow], 1, false));

	mCursorMgr = new WorldMapCursorMgr();
	mCursorMgr->init(mIconScreen->getScreenPtr());

	mTitleMgr = new WorldMapTitleMgr();
	mTitleMgr->init(mTitleScreen->getScreenPtr());

	mPartsInfoMgr = new WorldMapPartsInfoMgr();
	mPartsInfoMgr->init(mData2Screen->getScreenPtr());

	mConfirmMgr = new WorldMapConfirmMgr();

	mShootingStarMgr = new WorldMapShootingStarMgr();

	// I think this has to come from inlines *somehow* but i have so many. so. many.
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	PRINT("fake", mShootingStarMgr ? "fake" : "fake");
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x4B0(r1)
	  stmw      r17, 0x474(r1)
	  addi      r26, r3, 0
	  lis       r3, 0x802E
	  addi      r17, r3, 0x57B0
	  addi      r3, r26, 0x64
	  bl        0xEB8C
	  addi      r3, r26, 0x74
	  bl        -0x4B058
	  li        r3, 0x4C4
	  bl        -0x194178
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x50
	  li        r4, 0x60
	  li        r5, 0x1F4
	  li        r6, 0x28A
	  bl        0xE728

	.loc_0x50:
	  stw       r18, 0x50(r26)
	  li        r3, 0x100
	  lwz       r0, 0x50(r26)
	  stw       r0, 0x31C0(r13)
	  bl        -0x1941A8
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x84
	  addi      r4, r17, 0x24
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BC58

	.loc_0x84:
	  stw       r18, 0x10(r26)
	  li        r3, 0x100
	  bl        -0x1941D4
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0xB0
	  addi      r4, r17, 0x3C
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BC84

	.loc_0xB0:
	  stw       r18, 0x14(r26)
	  li        r3, 0x100
	  bl        -0x194200
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0xDC
	  addi      r4, r17, 0x54
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BCB0

	.loc_0xDC:
	  stw       r18, 0x18(r26)
	  li        r3, 0x100
	  bl        -0x19422C
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x108
	  addi      r4, r17, 0x6C
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BCDC

	.loc_0x108:
	  stw       r18, 0x1C(r26)
	  li        r3, 0x100
	  bl        -0x194258
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x134
	  addi      r4, r17, 0x84
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BD08

	.loc_0x134:
	  stw       r18, 0x20(r26)
	  li        r3, 0x100
	  bl        -0x194284
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x160
	  addi      r4, r17, 0x9C
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BD34

	.loc_0x160:
	  stw       r18, 0x24(r26)
	  li        r3, 0x100
	  bl        -0x1942B0
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x18C
	  addi      r4, r17, 0xB4
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BD60

	.loc_0x18C:
	  stw       r18, 0x28(r26)
	  li        r3, 0x100
	  bl        -0x1942DC
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x1B8
	  addi      r4, r17, 0xCC
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BD8C

	.loc_0x1B8:
	  stw       r18, 0x2C(r26)
	  li        r3, 0x100
	  bl        -0x194308
	  addi      r18, r3, 0
	  mr.       r3, r18
	  beq-      .loc_0x1E4
	  addi      r4, r17, 0xE4
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1BDB8

	.loc_0x1E4:
	  stw       r18, 0x30(r26)
	  li        r0, -0x1
	  li        r3, 0x138
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r26)
	  stw       r0, 0x4(r26)
	  stw       r0, 0x8(r26)
	  bl        -0x194348
	  addi      r18, r3, 0
	  mr.       r5, r18
	  beq-      .loc_0x23C
	  lis       r3, 0x801E
	  subi      r4, r3, 0x1924
	  addi      r3, r5, 0x8
	  li        r5, 0
	  li        r6, 0x3C
	  li        r7, 0x5
	  bl        0x396FC
	  li        r0, 0
	  stw       r0, 0x4(r18)
	  stw       r0, 0x134(r18)
	  stw       r0, 0x0(r18)

	.loc_0x23C:
	  stw       r18, 0x38(r26)
	  li        r23, 0
	  lwz       r4, 0x2C(r26)
	  lwz       r3, 0x28(r26)
	  lwz       r27, 0x38(r26)
	  addi      r28, r4, 0x4
	  addi      r25, r3, 0x4
	  stw       r23, 0x134(r27)
	  lwz       r0, 0x2F6C(r13)
	  cmplwi    r0, 0
	  beq-      .loc_0x460
	  addi      r24, r27, 0x8
	  lis       r22, 0x78
	  lis       r21, 0x785F
	  lis       r20, 0x706F
	  lis       r19, 0x736C
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r22, 0x5F31
	  addi      r6, r21, 0x3173
	  addi      r7, r20, 0x3031
	  addi      r9, r19, 0x6931
	  bl        0x3170
	  addi      r0, r27, 0xF8
	  stw       r0, 0x2C(r24)
	  addi      r29, r27, 0x44
	  addi      r18, r27, 0xBC
	  stw       r29, 0x30(r24)
	  li        r4, 0x3
	  stw       r23, 0x34(r24)
	  stw       r18, 0x38(r24)
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15B8C8
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x304
	  addi      r3, r29, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r22, 0x5F32
	  addi      r6, r21, 0x3273
	  addi      r7, r20, 0x3032
	  addi      r9, r19, 0x6932
	  bl        0x3120
	  stw       r24, 0x2C(r29)
	  addi      r0, r27, 0x80
	  stw       r23, 0x30(r29)
	  stw       r23, 0x34(r29)
	  stw       r0, 0x38(r29)
	  b         .loc_0x338

	.loc_0x304:
	  addi      r3, r29, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r22, 0x5F32
	  addi      r6, r21, 0x3273
	  addi      r7, r20, 0x3032
	  addi      r9, r19, 0x6932
	  bl        0x30E8
	  stw       r18, 0x2C(r29)
	  addi      r0, r27, 0x80
	  stw       r23, 0x30(r29)
	  stw       r23, 0x34(r29)
	  stw       r0, 0x38(r29)

	.loc_0x338:
	  addi      r19, r27, 0x80
	  lis       r29, 0x78
	  lis       r24, 0x785F
	  lis       r23, 0x706F
	  lis       r22, 0x736C
	  addi      r3, r19, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r29, 0x5F33
	  addi      r6, r24, 0x3373
	  addi      r7, r23, 0x3033
	  addi      r9, r22, 0x6933
	  bl        0x30A0
	  addi      r18, r27, 0xBC
	  stw       r18, 0x2C(r19)
	  li        r21, 0
	  addi      r20, r27, 0x44
	  stw       r21, 0x30(r19)
	  li        r4, 0x3
	  stw       r20, 0x34(r19)
	  stw       r21, 0x38(r19)
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15B998
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x3D8
	  addi      r3, r18, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r29, 0x5F34
	  addi      r6, r24, 0x3473
	  addi      r7, r23, 0x3034
	  addi      r9, r22, 0x6934
	  bl        0x3050
	  addi      r0, r27, 0xF8
	  stw       r0, 0x2C(r18)
	  addi      r0, r27, 0x8
	  stw       r19, 0x30(r18)
	  stw       r0, 0x34(r18)
	  stw       r21, 0x38(r18)
	  b         .loc_0x40C

	.loc_0x3D8:
	  addi      r3, r18, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r29, 0x5F34
	  addi      r6, r24, 0x3473
	  addi      r7, r23, 0x3034
	  addi      r9, r22, 0x6934
	  bl        0x3014
	  addi      r0, r27, 0xF8
	  stw       r0, 0x2C(r18)
	  stw       r19, 0x30(r18)
	  stw       r20, 0x34(r18)
	  stw       r21, 0x38(r18)

	.loc_0x40C:
	  addi      r18, r27, 0xF8
	  lis       r5, 0x78
	  lis       r6, 0x785F
	  lis       r7, 0x706F
	  lis       r9, 0x736C
	  addi      r3, r18, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r5, 0x5F35
	  addi      r6, r6, 0x3573
	  addi      r7, r7, 0x3035
	  addi      r9, r9, 0x6935
	  bl        0x2FCC
	  li        r4, 0
	  stw       r4, 0x2C(r18)
	  addi      r3, r27, 0xBC
	  addi      r0, r27, 0x8
	  stw       r3, 0x30(r18)
	  stw       r0, 0x34(r18)
	  stw       r4, 0x38(r18)
	  b         .loc_0x574

	.loc_0x460:
	  addi      r29, r27, 0x8
	  lis       r24, 0x78
	  lis       r31, 0x785F
	  lis       r30, 0x706F
	  lis       r18, 0x736C
	  addi      r3, r29, 0
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  addi      r5, r24, 0x5F31
	  addi      r6, r31, 0x3173
	  addi      r7, r30, 0x3031
	  addi      r9, r18, 0x6931
	  bl        0x2F78
	  addi      r22, r27, 0xF8
	  stw       r22, 0x2C(r29)
	  addi      r19, r27, 0x44
	  addi      r21, r27, 0xBC
	  stw       r19, 0x30(r29)
	  addi      r3, r19, 0
	  addi      r4, r25, 0
	  stw       r23, 0x34(r29)
	  addi      r8, r28, 0
	  addi      r5, r24, 0x5F32
	  stw       r21, 0x38(r29)
	  addi      r6, r31, 0x3273
	  addi      r7, r30, 0x3032
	  addi      r9, r18, 0x6932
	  bl        0x2F3C
	  stw       r29, 0x2C(r19)
	  addi      r20, r27, 0x80
	  addi      r3, r20, 0
	  stw       r23, 0x30(r19)
	  addi      r4, r25, 0
	  addi      r8, r28, 0
	  stw       r23, 0x34(r19)
	  addi      r5, r24, 0x5F33
	  addi      r6, r31, 0x3373
	  stw       r20, 0x38(r19)
	  addi      r7, r30, 0x3033
	  addi      r9, r18, 0x6933
	  bl        0x2F08
	  stw       r21, 0x2C(r20)
	  mr        r3, r21
	  addi      r4, r25, 0
	  stw       r23, 0x30(r20)
	  addi      r8, r28, 0
	  addi      r5, r24, 0x5F34
	  stw       r19, 0x34(r20)
	  addi      r6, r31, 0x3473
	  addi      r7, r30, 0x3034
	  stw       r23, 0x38(r20)
	  addi      r9, r18, 0x6934
	  bl        0x2ED8
	  stw       r22, 0x2C(r21)
	  mr        r3, r22
	  addi      r4, r25, 0
	  stw       r20, 0x30(r21)
	  addi      r8, r28, 0
	  addi      r5, r24, 0x5F35
	  stw       r29, 0x34(r21)
	  addi      r6, r31, 0x3573
	  addi      r7, r30, 0x3035
	  stw       r23, 0x38(r21)
	  addi      r9, r18, 0x6935
	  bl        0x2EA8
	  stw       r23, 0x2C(r22)
	  stw       r21, 0x30(r22)
	  stw       r29, 0x34(r22)
	  stw       r23, 0x38(r22)

	.loc_0x574:
	  addi      r28, r13, 0x2470
	  addi      r18, r28, 0
	  addi      r19, r27, 0
	  li        r22, 0

	.loc_0x584:
	  lbz       r21, 0x0(r18)
	  addi      r3, r1, 0x45C
	  addi      r5, r22, 0x1
	  crclr     6, 0x6
	  addi      r4, r13, 0x2610
	  bl        0x3AEB4
	  addi      r3, r1, 0x464
	  crclr     6, 0x6
	  addi      r5, r22, 0x1
	  addi      r4, r13, 0x2618
	  bl        0x3AEA0
	  lwz       r12, 0x0(r25)
	  mr        r3, r25
	  lbz       r6, 0x465(r1)
	  addi      r20, r19, 0x8
	  lbz       r0, 0x45D(r1)
	  lwz       r12, 0x34(r12)
	  rlwinm    r7,r6,16,0,15
	  lbz       r8, 0x464(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r4, 0x45C(r1)
	  lbz       r5, 0x45E(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r9, 0x466(r1)
	  rlwimi    r0,r5,8,16,23
	  lbz       r6, 0x45F(r1)
	  rlwimi    r7,r8,24,0,7
	  lbz       r10, 0x467(r1)
	  rlwimi    r7,r9,8,16,23
	  or        r4, r6, r0
	  or        r23, r10, r7
	  li        r5, 0x1
	  blrl
	  stw       r3, 0x24(r20)
	  addi      r3, r25, 0
	  addi      r4, r23, 0
	  lwz       r12, 0x0(r25)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  stw       r3, 0x28(r20)
	  stw       r21, 0x18(r19)
	  lbz       r0, 0x14(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x678
	  lwz       r3, 0x14(r20)
	  li        r5, 0x1
	  li        r4, 0
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r5,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x18(r20)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x20(r20)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)

	.loc_0x678:
	  addi      r23, r19, 0x8
	  li        r4, 0x1
	  stb       r4, 0x14(r19)
	  li        r20, 0
	  lwz       r3, 0x1C(r19)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x20(r19)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x24(r19)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x28(r19)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x2F6C(r13)
	  cmplwi    r3, 0
	  beq-      .loc_0x728
	  mr        r4, r21
	  bl        -0x15BCE0
	  rlwinm.   r0,r3,0,24,31
	  bne-      .loc_0x728
	  stb       r20, 0xC(r23)
	  lwz       r3, 0x14(r23)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x18(r23)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x1C(r23)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x20(r23)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r20,7,24,24
	  stb       r0, 0xC(r3)

	.loc_0x728:
	  addi      r22, r22, 0x1
	  cmpwi     r22, 0x5
	  addi      r18, r18, 0x1
	  addi      r19, r19, 0x3C
	  blt+      .loc_0x584
	  lbz       r0, 0x2478(r13)
	  mulli     r3, r0, 0x3C
	  addi      r0, r3, 0x8
	  add       r0, r27, r0
	  stw       r0, 0x4(r27)
	  lwz       r6, 0x4(r27)
	  lbz       r0, 0xC(r6)
	  cmplwi    r0, 0
	  beq-      .loc_0x798
	  lwz       r3, 0x14(r6)
	  li        r5, 0
	  li        r4, 0x1
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r5,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x18(r6)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x20(r6)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)

	.loc_0x798:
	  li        r3, 0xB0
	  bl        -0x1948E4
	  addi      r18, r3, 0
	  mr.       r5, r18
	  beq-      .loc_0x7E0
	  lis       r3, 0x801E
	  subi      r4, r3, 0x1AE0
	  addi      r3, r5, 0xC
	  li        r5, 0
	  li        r6, 0x28
	  li        r7, 0x4
	  bl        0x39160
	  lfs       f0, -0x4188(r2)
	  li        r0, 0
	  stfs      f0, 0x4(r18)
	  lfs       f0, -0x4184(r2)
	  stfs      f0, 0x8(r18)
	  stb       r0, 0xAC(r18)

	.loc_0x7E0:
	  stw       r18, 0x58(r26)
	  lis       r18, 0x7770
	  addi      r5, r18, 0x3030
	  lwz       r3, 0x10(r26)
	  lwz       r19, 0x58(r26)
	  addi      r20, r3, 0x4
	  addi      r4, r20, 0
	  addi      r3, r19, 0xC
	  bl        0x2A70
	  addi      r4, r20, 0
	  addi      r3, r19, 0x34
	  addi      r5, r18, 0x3031
	  bl        0x2A60
	  addi      r4, r20, 0
	  addi      r3, r19, 0x5C
	  addi      r5, r18, 0x3032
	  bl        0x2A50
	  addi      r4, r20, 0
	  addi      r3, r19, 0x84
	  addi      r5, r18, 0x3033
	  bl        0x2A40
	  lfs       f0, -0x4188(r2)
	  li        r18, 0
	  li        r3, 0x24
	  stfs      f0, 0x4(r19)
	  lfs       f0, -0x4180(r2)
	  stfs      f0, 0x8(r19)
	  stb       r18, 0xAC(r19)
	  bl        -0x194998
	  cmplwi    r3, 0
	  beq-      .loc_0x88C
	  li        r0, 0x2
	  stw       r0, 0x4(r3)
	  li        r0, -0x1
	  stw       r0, 0x8(r3)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0x0(r3)
	  stb       r18, 0x20(r3)
	  stw       r18, 0xC(r3)
	  stw       r18, 0x10(r3)
	  stw       r18, 0x14(r3)
	  stw       r18, 0x18(r3)
	  stw       r18, 0x1C(r3)

	.loc_0x88C:
	  stw       r3, 0x54(r26)
	  lis       r3, 0x6D69
	  addi      r4, r3, 0x5F31
	  lwz       r3, 0x1C(r26)
	  li        r5, 0x1
	  lwz       r18, 0x54(r26)
	  addi      r19, r3, 0x4
	  addi      r3, r19, 0
	  lwz       r12, 0x0(r19)
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x8CC
	  stw       r3, 0xC(r18)

	.loc_0x8CC:
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6D69
	  addi      r4, r4, 0x5F32
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x8FC
	  stw       r3, 0x10(r18)

	.loc_0x8FC:
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6D69
	  addi      r4, r4, 0x5F33
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x92C
	  stw       r3, 0x14(r18)

	.loc_0x92C:
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6D69
	  addi      r4, r4, 0x5F34
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x95C
	  stw       r3, 0x18(r18)

	.loc_0x95C:
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6D69
	  addi      r4, r4, 0x5F35
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x98C
	  stw       r3, 0x1C(r18)

	.loc_0x98C:
	  mr        r3, r18
	  bl        0x2828
	  lwz       r3, 0x2F6C(r13)
	  cmplwi    r3, 0
	  beq-      .loc_0x9E8
	  bl        -0x15AE84
	  stw       r3, 0x3C(r26)
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15AE88
	  stw       r3, 0x40(r26)
	  li        r4, 0
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15BEE0
	  stw       r3, 0x44(r26)
	  li        r4, 0x1
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15BEF0
	  stw       r3, 0x48(r26)
	  li        r4, 0x2
	  lwz       r3, 0x2F6C(r13)
	  bl        -0x15BF00
	  stw       r3, 0x4C(r26)
	  b         .loc_0xA08

	.loc_0x9E8:
	  li        r0, 0x1E
	  stw       r0, 0x3C(r26)
	  li        r3, 0x1D
	  li        r0, 0x3E7
	  stw       r3, 0x40(r26)
	  stw       r0, 0x44(r26)
	  stw       r0, 0x48(r26)
	  stw       r0, 0x4C(r26)

	.loc_0xA08:
	  lwz       r3, 0x20(r26)
	  lis       r19, 0x6463
	  lwzu      r12, 0x4(r3)
	  addi      r4, r19, 0x5F63
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  lwz       r4, 0x20(r26)
	  addi      r18, r3, 0
	  li        r5, 0x1
	  lwz       r12, 0x4(r4)
	  addi      r3, r4, 0x4
	  addi      r4, r19, 0x5F6C
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  lwz       r4, 0x20(r26)
	  addi      r20, r3, 0
	  li        r5, 0x1
	  lwz       r12, 0x4(r4)
	  addi      r3, r4, 0x4
	  addi      r4, r19, 0x5F72
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r21, r3, 0
	  li        r3, 0x10
	  bl        -0x194BC0
	  mr.       r19, r3
	  beq-      .loc_0xB04
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  li        r4, 0
	  li        r5, 0x10
	  bl        -0x2B4E8
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1C50C
	  lis       r3, 0x802E
	  addi      r0, r3, 0x5A08
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B4E8
	  addi      r4, r20, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B4F8
	  addi      r4, r21, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B508
	  stw       r18, 0x4(r19)
	  mr        r3, r19
	  stw       r20, 0x8(r19)
	  stw       r21, 0xC(r19)
	  bl        0x2554

	.loc_0xB04:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2B5BC
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x726F
	  addi      r4, r3, 0x5F6C
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x194C84
	  mr.       r19, r3
	  beq-      .loc_0xC4C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B5AC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1C5D0
	  addi      r0, r26, 0x40
	  stw       r0, 0x4(r19)
	  li        r0, 0xA
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0xBF0
	  addi      r3, r19, 0x4
	  bl        -0x5D2B8
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xC1C
	  stw       r0, 0xEC(r18)
	  b         .loc_0xC1C

	.loc_0xBF0:
	  addi      r3, r19, 0x4
	  bl        -0x5D2E8
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xC1C
	  stw       r0, 0xEC(r18)

	.loc_0xC1C:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0xC4C:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2B704
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x726F
	  addi      r4, r3, 0x5F72
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x194DCC
	  mr.       r19, r3
	  beq-      .loc_0xD94
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B6F4
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1C718
	  addi      r0, r26, 0x40
	  stw       r0, 0x4(r19)
	  li        r0, 0x1
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0xD38
	  addi      r3, r19, 0x4
	  bl        -0x5D400
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xD64
	  stw       r0, 0xEC(r18)
	  b         .loc_0xD64

	.loc_0xD38:
	  addi      r3, r19, 0x4
	  bl        -0x5D430
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xD64
	  stw       r0, 0xEC(r18)

	.loc_0xD64:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0xD94:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2B84C
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7274
	  addi      r4, r3, 0x5F6C
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x194F14
	  mr.       r19, r3
	  beq-      .loc_0xEDC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B83C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1C860
	  addi      r0, r26, 0x3C
	  stw       r0, 0x4(r19)
	  li        r0, 0xA
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0xE80
	  addi      r3, r19, 0x4
	  bl        -0x5D548
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xEAC
	  stw       r0, 0xEC(r18)
	  b         .loc_0xEAC

	.loc_0xE80:
	  addi      r3, r19, 0x4
	  bl        -0x5D578
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xEAC
	  stw       r0, 0xEC(r18)

	.loc_0xEAC:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0xEDC:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2B994
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7274
	  addi      r4, r3, 0x5F72
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x19505C
	  mr.       r19, r3
	  beq-      .loc_0x1024
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2B984
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1C9A8
	  addi      r0, r26, 0x3C
	  stw       r0, 0x4(r19)
	  li        r0, 0x1
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0xFC8
	  addi      r3, r19, 0x4
	  bl        -0x5D690
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xFF4
	  stw       r0, 0xEC(r18)
	  b         .loc_0xFF4

	.loc_0xFC8:
	  addi      r3, r19, 0x4
	  bl        -0x5D6C0
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0xFF4
	  stw       r0, 0xEC(r18)

	.loc_0xFF4:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x1024:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2BADC
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x6270
	  addi      r4, r3, 0x5F6C
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x1951A4
	  mr.       r19, r3
	  beq-      .loc_0x116C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2BACC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1CAF0
	  addi      r0, r26, 0x44
	  stw       r0, 0x4(r19)
	  li        r0, 0x64
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1110
	  addi      r3, r19, 0x4
	  bl        -0x5D7D8
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x113C
	  stw       r0, 0xEC(r18)
	  b         .loc_0x113C

	.loc_0x1110:
	  addi      r3, r19, 0x4
	  bl        -0x5D808
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x113C
	  stw       r0, 0xEC(r18)

	.loc_0x113C:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x116C:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2BC24
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x6270
	  addi      r4, r3, 0x5F63
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x1952EC
	  mr.       r19, r3
	  beq-      .loc_0x12B4
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2BC14
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1CC38
	  addi      r0, r26, 0x44
	  stw       r0, 0x4(r19)
	  li        r0, 0xA
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1258
	  addi      r3, r19, 0x4
	  bl        -0x5D920
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1284
	  stw       r0, 0xEC(r18)
	  b         .loc_0x1284

	.loc_0x1258:
	  addi      r3, r19, 0x4
	  bl        -0x5D950
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1284
	  stw       r0, 0xEC(r18)

	.loc_0x1284:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x12B4:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2BD6C
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x6270
	  addi      r4, r3, 0x5F72
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x195434
	  mr.       r19, r3
	  beq-      .loc_0x13FC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2BD5C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1CD80
	  addi      r0, r26, 0x44
	  stw       r0, 0x4(r19)
	  li        r0, 0x1
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x13A0
	  addi      r3, r19, 0x4
	  bl        -0x5DA68
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x13CC
	  stw       r0, 0xEC(r18)
	  b         .loc_0x13CC

	.loc_0x13A0:
	  addi      r3, r19, 0x4
	  bl        -0x5DA98
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x13CC
	  stw       r0, 0xEC(r18)

	.loc_0x13CC:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x13FC:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2BEB4
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7270
	  addi      r4, r3, 0x5F6C
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x19557C
	  mr.       r19, r3
	  beq-      .loc_0x1544
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2BEA4
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1CEC8
	  addi      r0, r26, 0x48
	  stw       r0, 0x4(r19)
	  li        r0, 0x64
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x14E8
	  addi      r3, r19, 0x4
	  bl        -0x5DBB0
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1514
	  stw       r0, 0xEC(r18)
	  b         .loc_0x1514

	.loc_0x14E8:
	  addi      r3, r19, 0x4
	  bl        -0x5DBE0
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1514
	  stw       r0, 0xEC(r18)

	.loc_0x1514:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x1544:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2BFFC
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7270
	  addi      r4, r3, 0x5F63
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x1956C4
	  mr.       r19, r3
	  beq-      .loc_0x168C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2BFEC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1D010
	  addi      r0, r26, 0x48
	  stw       r0, 0x4(r19)
	  li        r0, 0xA
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1630
	  addi      r3, r19, 0x4
	  bl        -0x5DCF8
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x165C
	  stw       r0, 0xEC(r18)
	  b         .loc_0x165C

	.loc_0x1630:
	  addi      r3, r19, 0x4
	  bl        -0x5DD28
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x165C
	  stw       r0, 0xEC(r18)

	.loc_0x165C:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x168C:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2C144
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7270
	  addi      r4, r3, 0x5F72
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x19580C
	  mr.       r19, r3
	  beq-      .loc_0x17D4
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2C134
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1D158
	  addi      r0, r26, 0x48
	  stw       r0, 0x4(r19)
	  li        r0, 0x1
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1778
	  addi      r3, r19, 0x4
	  bl        -0x5DE40
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x17A4
	  stw       r0, 0xEC(r18)
	  b         .loc_0x17A4

	.loc_0x1778:
	  addi      r3, r19, 0x4
	  bl        -0x5DE70
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x17A4
	  stw       r0, 0xEC(r18)

	.loc_0x17A4:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x17D4:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2C28C
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7970
	  addi      r4, r3, 0x5F6C
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x195954
	  mr.       r19, r3
	  beq-      .loc_0x191C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2C27C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1D2A0
	  addi      r0, r26, 0x4C
	  stw       r0, 0x4(r19)
	  li        r0, 0x64
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x18C0
	  addi      r3, r19, 0x4
	  bl        -0x5DF88
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x18EC
	  stw       r0, 0xEC(r18)
	  b         .loc_0x18EC

	.loc_0x18C0:
	  addi      r3, r19, 0x4
	  bl        -0x5DFB8
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x18EC
	  stw       r0, 0xEC(r18)

	.loc_0x18EC:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x191C:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2C3D4
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7970
	  addi      r4, r3, 0x5F63
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x195A9C
	  mr.       r19, r3
	  beq-      .loc_0x1A64
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2C3C4
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1D3E8
	  addi      r0, r26, 0x4C
	  stw       r0, 0x4(r19)
	  li        r0, 0xA
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1A08
	  addi      r3, r19, 0x4
	  bl        -0x5E0D0
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1A34
	  stw       r0, 0xEC(r18)
	  b         .loc_0x1A34

	.loc_0x1A08:
	  addi      r3, r19, 0x4
	  bl        -0x5E100
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1A34
	  stw       r0, 0xEC(r18)

	.loc_0x1A34:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x1A64:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2C51C
	  lwz       r5, 0x20(r26)
	  lis       r3, 0x7970
	  addi      r4, r3, 0x5F72
	  lwz       r12, 0x4(r5)
	  addi      r3, r5, 0x4
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  addi      r18, r3, 0
	  li        r3, 0x1C
	  bl        -0x195BE4
	  mr.       r19, r3
	  beq-      .loc_0x1BAC
	  lis       r3, 0x802D
	  addi      r0, r3, 0x3004
	  stw       r0, 0x0(r19)
	  addi      r4, r18, 0
	  addi      r3, r19, 0x4
	  li        r5, 0x12
	  bl        -0x2C50C
	  lis       r3, 0x802D
	  addi      r0, r3, 0x2FF4
	  stw       r0, 0x0(r19)
	  addi      r3, r19, 0x4
	  bl        -0x1D530
	  addi      r0, r26, 0x4C
	  stw       r0, 0x4(r19)
	  li        r0, 0x1
	  lis       r3, 0x802D
	  stw       r0, 0x8(r19)
	  addi      r0, r3, 0x2FE4
	  li        r4, 0
	  stw       r0, 0x0(r19)
	  stb       r4, 0x18(r19)
	  lwz       r3, 0x4(r19)
	  lwz       r0, 0x0(r3)
	  stw       r0, 0x10(r19)
	  stw       r4, 0x14(r19)
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0xC(r19)
	  lbz       r0, 0x18(r19)
	  cmplwi    r0, 0
	  beq-      .loc_0x1B50
	  addi      r3, r19, 0x4
	  bl        -0x5E218
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2388
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1B7C
	  stw       r0, 0xEC(r18)
	  b         .loc_0x1B7C

	.loc_0x1B50:
	  addi      r3, r19, 0x4
	  bl        -0x5E248
	  lbz       r0, 0xF1(r18)
	  lis       r4, 0x803D
	  rlwinm    r5,r3,2,0,29
	  addi      r3, r4, 0x2360
	  add       r3, r3, r5
	  cmplwi    r0, 0
	  lwz       r0, 0x0(r3)
	  ble-      .loc_0x1B7C
	  stw       r0, 0xEC(r18)

	.loc_0x1B7C:
	  lha       r5, 0x1A(r18)
	  lha       r4, 0x1E(r18)
	  lha       r3, 0x18(r18)
	  lha       r0, 0x1C(r18)
	  sub       r4, r4, r5
	  srawi     r4, r4, 0x1
	  sub       r0, r0, r3
	  srawi     r0, r0, 0x1
	  extsh     r0, r0
	  sth       r0, 0xB8(r18)
	  extsh     r0, r4
	  sth       r0, 0xBA(r18)

	.loc_0x1BAC:
	  addi      r3, r18, 0
	  addi      r4, r19, 0
	  bl        -0x2C664
	  li        r3, 0x12C
	  bl        -0x195D04
	  mr.       r18, r3
	  beq-      .loc_0x1C54
	  lfs       f2, -0x4188(r2)
	  lis       r3, 0x801E
	  subi      r4, r3, 0x1F4C
	  stfs      f2, 0x14(r18)
	  fmr       f1, f2
	  fmr       f0, f2
	  addi      r3, r18, 0x44
	  stfs      f2, 0x10(r18)
	  li        r5, 0
	  stfs      f2, 0xC(r18)
	  li        r6, 0x3C
	  stfs      f2, 0x20(r18)
	  li        r7, 0x3
	  stfs      f2, 0x1C(r18)
	  stfs      f2, 0x18(r18)
	  stfs      f1, 0x2C(r18)
	  stfs      f1, 0x28(r18)
	  stfs      f1, 0x24(r18)
	  stfs      f0, 0x40(r18)
	  stfs      f0, 0x3C(r18)
	  stfs      f0, 0x38(r18)
	  bl        0x37D08
	  lfs       f0, -0x4188(r2)
	  li        r0, 0
	  addi      r3, r18, 0
	  stfs      f0, 0x100(r18)
	  stfs      f0, 0xFC(r18)
	  stfs      f0, 0xF8(r18)
	  stfs      f0, 0x10C(r18)
	  stfs      f0, 0x108(r18)
	  stfs      f0, 0x104(r18)
	  stw       r0, 0x8(r18)
	  stw       r0, 0x110(r18)
	  stw       r0, 0x114(r18)
	  bl        0x1214

	.loc_0x1C54:
	  stw       r18, 0x34(r26)
	  li        r4, 0x7269
	  li        r5, 0x1
	  lwz       r3, 0x14(r26)
	  lwz       r18, 0x34(r26)
	  addi      r19, r3, 0x4
	  addi      r3, r19, 0
	  lwz       r12, 0x0(r19)
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x1C90
	  stw       r3, 0x8(r18)

	.loc_0x1C90:
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6369
	  addi      r4, r4, 0x5F62
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x1CC0
	  stw       r3, 0x44(r18)

	.loc_0x1CC0:
	  addi      r3, r18, 0x44
	  bl        0x1084
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6369
	  addi      r4, r4, 0x5F72
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x1CF8
	  stw       r3, 0x80(r18)

	.loc_0x1CF8:
	  addi      r3, r18, 0x80
	  bl        0x104C
	  mr        r3, r19
	  lwz       r12, 0x0(r19)
	  lis       r4, 0x6369
	  addi      r4, r4, 0x5F79
	  lwz       r12, 0x34(r12)
	  li        r5, 0x1
	  mtlr      r12
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x1D30
	  stw       r3, 0xBC(r18)

	.loc_0x1D30:
	  addi      r3, r18, 0xBC
	  bl        0x1014
	  mr        r3, r18
	  bl        0x8E4
	  li        r3, 0x8
	  bl        -0x195E8C
	  addi      r19, r3, 0
	  mr.       r0, r19
	  beq-      .loc_0x1D88
	  lwz       r18, 0x249C(r13)
	  mulli     r3, r18, 0x28
	  addi      r3, r3, 0x8
	  bl        -0x195EA8
	  lis       r4, 0x801E
	  subi      r4, r4, 0x28C0
	  addi      r7, r18, 0
	  li        r5, 0
	  li        r6, 0x28
	  bl        0x37D64
	  stw       r3, 0x0(r19)
	  li        r0, -0x1
	  stw       r0, 0x4(r19)

	.loc_0x1D88:
	  stw       r19, 0x5C(r26)
	  li        r18, 0
	  mr        r21, r18
	  lwz       r3, 0x18(r26)
	  lwz       r19, 0x5C(r26)
	  lwz       r22, 0x249C(r13)
	  addi      r20, r3, 0x4
	  b         .loc_0x1E50

	.loc_0x1DA8:
	  lbz       r5, 0x0(r28)
	  addi      r3, r1, 0x40C
	  crclr     6, 0x6
	  addi      r4, r13, 0x2620
	  addi      r5, r5, 0x1
	  bl        0x39690
	  lwz       r12, 0x0(r20)
	  mr        r3, r20
	  lbz       r0, 0x40D(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x40C(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x40E(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x40F(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  lwz       r0, 0x0(r19)
	  add       r24, r0, r21
	  stw       r3, 0x4(r24)
	  lwz       r3, 0x4(r24)
	  addi      r3, r3, 0x18
	  bl        -0x24A24
	  lwz       r4, 0x4(r24)
	  addi      r23, r3, 0
	  addi      r3, r4, 0x18
	  bl        -0x24A44
	  srawi     r0, r3, 0x1
	  lwz       r4, 0x4(r24)
	  extsh     r3, r0
	  srawi     r0, r23, 0x1
	  sth       r3, 0xB8(r4)
	  extsh     r0, r0
	  sth       r0, 0xBA(r4)
	  li        r0, 0
	  addi      r21, r21, 0x28
	  stw       r0, 0x0(r24)
	  addi      r18, r18, 0x1
	  addi      r28, r28, 0x1

	.loc_0x1E50:
	  cmpw      r18, r22
	  blt+      .loc_0x1DA8
	  li        r21, 0
	  lwz       r18, 0x249C(r13)
	  addi      r23, r21, 0
	  addi      r20, r21, 0
	  b         .loc_0x1EA4

	.loc_0x1E6C:
	  lwz       r0, 0x0(r19)
	  li        r4, 0x280
	  li        r5, 0x1E0
	  add       r22, r0, r23
	  lwz       r3, 0x4(r22)
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  stw       r20, 0x0(r22)
	  lwz       r3, 0x4(r22)
	  bl        0x748
	  addi      r23, r23, 0x28
	  addi      r21, r21, 0x1

	.loc_0x1EA4:
	  cmpw      r21, r18
	  blt+      .loc_0x1E6C
	  li        r0, -0x1
	  stw       r0, 0x4(r19)
	  li        r3, 0xC
	  bl        -0x196000
	  cmplwi    r3, 0
	  beq-      .loc_0x1ED0
	  li        r0, 0
	  stw       r0, 0x0(r3)
	  stw       r0, 0x4(r3)

	.loc_0x1ED0:
	  stw       r3, 0x60(r26)
	  addi      r3, r1, 0x404
	  crclr     6, 0x6
	  li        r18, 0
	  lwz       r5, 0x24(r26)
	  lwz       r29, 0x60(r26)
	  addi      r4, r13, 0x2628
	  addi      r30, r5, 0x4
	  li        r5, 0
	  bl        0x39558
	  b         .loc_0x1F14

	.loc_0x1EFC:
	  addi      r18, r18, 0x1
	  crclr     6, 0x6
	  addi      r5, r18, 0
	  addi      r3, r1, 0x404
	  addi      r4, r13, 0x2628
	  bl        0x3953C

	.loc_0x1F14:
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x405(r1)
	  li        r5, 0
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x404(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x406(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x407(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  cmplwi    r3, 0
	  bne+      .loc_0x1EFC
	  stw       r18, 0x0(r29)
	  lwz       r0, 0x0(r29)
	  rlwinm    r3,r0,2,0,29
	  bl        -0x1960A8
	  stw       r3, 0x4(r29)
	  lwz       r0, 0x0(r29)
	  rlwinm    r3,r0,2,0,29
	  bl        -0x1960B8
	  li        r18, 0
	  stw       r3, 0x8(r29)
	  mr        r19, r18
	  b         .loc_0x20B4

	.loc_0x1F84:
	  addi      r5, r18, 0
	  crclr     6, 0x6
	  addi      r3, r1, 0x404
	  addi      r4, r13, 0x2630
	  bl        0x394B8
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x405(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x404(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x406(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x407(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x2018
	  lwz       r5, 0x4(r29)
	  li        r4, 0x1
	  stwx      r3, r5, r19
	  lwz       r3, 0x4(r29)
	  lwzx      r3, r3, r19
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x4(r29)
	  lwzx      r3, r3, r19
	  bl        -0x1D63C
	  lwz       r5, 0x4(r29)
	  mr        r4, r3
	  lwzx      r3, r5, r19
	  bl        -0x1D5C0

	.loc_0x2018:
	  addi      r5, r18, 0
	  crclr     6, 0x6
	  addi      r3, r1, 0x404
	  addi      r4, r13, 0x2628
	  bl        0x39424
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x405(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x404(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x406(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x407(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x12
	  bne-      .loc_0x20AC
	  lwz       r5, 0x8(r29)
	  li        r4, 0x1
	  stwx      r3, r5, r19
	  lwz       r3, 0x8(r29)
	  lwzx      r3, r3, r19
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r4,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x8(r29)
	  lwzx      r3, r3, r19
	  bl        -0x1D6D0
	  lwz       r5, 0x8(r29)
	  mr        r4, r3
	  lwzx      r3, r5, r19
	  bl        -0x1D654

	.loc_0x20AC:
	  addi      r19, r19, 0x4
	  addi      r18, r18, 0x1

	.loc_0x20B4:
	  lwz       r0, 0x0(r29)
	  cmpw      r18, r0
	  blt+      .loc_0x1F84
	  li        r3, 0x88
	  bl        -0x19620C
	  addi      r31, r3, 0
	  mr.       r18, r31
	  beq-      .loc_0x242C
	  li        r0, 0
	  stw       r0, 0x4(r31)
	  li        r3, 0x100
	  stw       r0, 0x8(r31)
	  lfs       f6, -0x4184(r2)
	  stfs      f6, 0x10(r31)
	  fmr       f4, f6
	  fmr       f3, f6
	  stfs      f6, 0xC(r31)
	  fmr       f2, f6
	  fmr       f1, f6
	  lfs       f5, -0x4188(r2)
	  stfs      f5, 0x20(r31)
	  fmr       f0, f5
	  stfs      f5, 0x1C(r31)
	  stfs      f5, 0x18(r31)
	  stfs      f5, 0x14(r31)
	  stfs      f6, 0x28(r31)
	  stfs      f6, 0x24(r31)
	  stfs      f4, 0x30(r31)
	  stfs      f4, 0x2C(r31)
	  stw       r0, 0x34(r31)
	  stw       r0, 0x38(r31)
	  stfs      f3, 0x40(r31)
	  stfs      f3, 0x3C(r31)
	  stfs      f5, 0x50(r31)
	  stfs      f5, 0x4C(r31)
	  stfs      f5, 0x48(r31)
	  stfs      f5, 0x44(r31)
	  stfs      f2, 0x58(r31)
	  stfs      f2, 0x54(r31)
	  stfs      f1, 0x60(r31)
	  stfs      f1, 0x5C(r31)
	  stfs      f0, 0x84(r31)
	  stfs      f0, 0x80(r31)
	  stfs      f0, 0x7C(r31)
	  bl        -0x1962AC
	  addi      r19, r3, 0
	  mr.       r3, r19
	  beq-      .loc_0x2188
	  addi      r4, r17, 0xFC
	  li        r5, 0
	  li        r6, 0x1
	  li        r7, 0x1
	  bl        -0x1DD5C

	.loc_0x2188:
	  stw       r19, 0x0(r31)
	  lis       r3, 0x7061
	  addi      r4, r3, 0x6C6C
	  lwz       r3, 0x0(r31)
	  li        r5, 0x1
	  addi      r7, r3, 0x4
	  lha       r3, 0x1C(r3)
	  lha       r0, 0x1C(r7)
	  mr        r30, r7
	  lha       r6, 0x1A(r7)
	  sub       r0, r0, r3
	  lha       r3, 0x1E(r7)
	  srawi     r0, r0, 0x1
	  sub       r6, r3, r6
	  extsh     r3, r0
	  srawi     r0, r6, 0x1
	  sth       r3, 0xB8(r7)
	  extsh     r0, r0
	  sth       r0, 0xBA(r7)
	  mr        r3, r30
	  lwz       r12, 0x0(r30)
	  lwz       r12, 0x34(r12)
	  mtlr      r12
	  blrl
	  lwz       r12, 0x0(r30)
	  lis       r4, 0x7365
	  addi      r29, r3, 0
	  lwz       r12, 0x34(r12)
	  addi      r3, r30, 0
	  addi      r4, r4, 0x5F63
	  mtlr      r12
	  li        r5, 0x1
	  blrl
	  lhz       r0, 0x8(r3)
	  cmplwi    r0, 0x13
	  bne-      .loc_0x2228
	  lwz       r0, 0xF4(r3)
	  stw       r0, 0x68(r31)
	  lwz       r0, 0xF8(r3)
	  stw       r0, 0x6C(r31)

	.loc_0x2228:
	  li        r3, 0x20
	  bl        -0x196374
	  lis       r4, 0x801C
	  lis       r5, 0x801C
	  addi      r4, r4, 0x3C4C
	  addi      r5, r5, 0x3BF8
	  li        r6, 0xC
	  li        r7, 0x2
	  bl        0x37894
	  li        r28, 0
	  stw       r3, 0x64(r31)
	  addi      r27, r28, 0
	  addi      r25, r29, 0

	.loc_0x225C:
	  addi      r5, r28, 0
	  crclr     6, 0x6
	  addi      r3, r1, 0x3FC
	  addi      r4, r13, 0x2638
	  bl        0x391E0
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x3FD(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x3FC(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x3FE(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x3FF(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  addi      r17, r3, 0
	  addi      r4, r29, 0
	  bl        -0x1D85C
	  lwz       r0, 0x64(r31)
	  addi      r4, r17, 0
	  li        r5, 0
	  add       r3, r0, r27
	  lwz       r3, 0x0(r3)
	  bl        -0x1ABEC
	  addi      r5, r28, 0
	  crclr     6, 0x6
	  addi      r3, r1, 0x3FC
	  addi      r4, r13, 0x2640
	  bl        0x39170
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x3FD(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x3FC(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x3FE(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x3FF(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  lhz       r0, 0x8(r3)
	  lwz       r4, 0x64(r31)
	  cmplwi    r0, 0x12
	  add       r6, r4, r27
	  bne-      .loc_0x2350
	  stw       r3, 0x4(r6)
	  li        r5, 0
	  addi      r4, r29, 0
	  lwz       r3, 0x4(r6)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r5,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x4(r6)
	  bl        -0x1D8F8

	.loc_0x2350:
	  addi      r5, r28, 0
	  crclr     6, 0x6
	  addi      r3, r1, 0x3FC
	  addi      r4, r13, 0x2648
	  bl        0x390EC
	  lwz       r12, 0x0(r30)
	  mr        r3, r30
	  lbz       r0, 0x3FD(r1)
	  li        r5, 0x1
	  lwz       r12, 0x34(r12)
	  lbz       r4, 0x3FC(r1)
	  rlwinm    r0,r0,16,0,15
	  lbz       r6, 0x3FE(r1)
	  mtlr      r12
	  rlwimi    r0,r4,24,0,7
	  lbz       r7, 0x3FF(r1)
	  rlwimi    r0,r6,8,16,23
	  or        r4, r7, r0
	  blrl
	  lhz       r0, 0x8(r3)
	  lwz       r4, 0x64(r31)
	  cmplwi    r0, 0x12
	  add       r6, r4, r27
	  bne-      .loc_0x23D4
	  stw       r3, 0x8(r6)
	  li        r5, 0
	  addi      r4, r25, 0
	  lwz       r3, 0x8(r6)
	  lbz       r0, 0xC(r3)
	  rlwimi    r0,r5,7,24,24
	  stb       r0, 0xC(r3)
	  lwz       r3, 0x8(r6)
	  bl        -0x1D97C

	.loc_0x23D4:
	  addi      r28, r28, 0x1
	  cmpwi     r28, 0x2
	  addi      r27, r27, 0xC
	  blt+      .loc_0x225C
	  lis       r17, 0x7A2A
	  lfs       f1, -0x417C(r2)
	  lfs       f2, -0x4178(r2)
	  addi      r4, r30, 0
	  addi      r5, r29, 0
	  addi      r3, r18, 0x4
	  addi      r6, r17, 0x2A6C
	  bl        -0x2910
	  lfs       f1, -0x4174(r2)
	  mr        r4, r30
	  lfs       f2, -0x4178(r2)
	  addi      r5, r29, 0
	  addi      r3, r18, 0x34
	  addi      r6, r17, 0x2A72
	  bl        -0x292C
	  addi      r3, r18, 0
	  li        r4, 0
	  bl        .loc_0x246C

	.loc_0x242C:
	  stw       r31, 0x70(r26)
	  li        r3, 0x8
	  bl        -0x19657C
	  cmplwi    r3, 0
	  beq-      .loc_0x2450
	  lfs       f0, -0x4170(r2)
	  li        r0, 0
	  stfs      f0, 0x0(r3)
	  stb       r0, 0x4(r3)

	.loc_0x2450:
	  stw       r3, 0x364(r26)
	  mr        r3, r26
	  lmw       r17, 0x474(r1)
	  lwz       r0, 0x4B4(r1)
	  addi      r1, r1, 0x4B0
	  mtlr      r0
	  blr

	.loc_0x246C:
	*/
}

/*
 * --INFO--
 * Address:	801DE714
 * Size:	000C14
 */
bool zen::DrawWorldMap::update(Controller* controller)
{
	bool res = false;
	if (_04 != -1) {
		if (_04 == 3) {
			DrawWMPause::returnStatusFlag pauseState = mPause.update(controller);
			if (pauseState != DrawWMPause::RETURN_Unk0) {
				if (pauseState == DrawWMPause::RETURN_Unk2) {
					_04 = -1;
					res = true;
					_08 = 6;
				} else {
					_04 = 2;
				}
			}
		} else if (_04 == 6) {
			if (mSelectDiary.update(controller) == ogDrawSelectDiary::SELECT_NULL) {
				_04 = 7;
				mWipeMgr->set(320, 240);
				mWipeMgr->open(0.5f);
				SeSystem::playSysSe(YMENU_SELECT2);
			}
		} else {
			switch (_04) {
			case 5:
				if (!mWipeMgr->isActive()) {
					_04 = 6;
					mSelectDiary.start();
				}
				mCursorMgr->update();
				updateScreens();
				break;
			case 7:
				if (!mWipeMgr->isActive()) {
					_04 = 2;
				}
				mCursorMgr->update();
				updateScreens();
				break;
			case 0:
				if (modeStart(controller)) {
					if (mStartMode) {
						_04 = 1;
					} else {
						_04 = 2;
					}
				}
				break;
			case 1:
				if (modeAppear(controller)) {
					_04 = 2;
				}
				break;
			case 4:
				if (modeConfirm(controller)) {
					_04 = 2;
				}
				break;
			case 2:
				if (controller->keyClick(KBBTN_START)) {
					mPause.start();
					_04 = 3;
				} else if (controller->keyClick(KBBTN_Y)) {
					if (mCursorMgr->isMoveOK()) {
						mWipeMgr->setDefault();
						mWipeMgr->close(0.5f, 320, 240);
						_04 = 5;
						SeSystem::playSysSe(YMENU_SELECT2);
					}
				} else if (modeOperation(controller)) {
					_04 = 8;
				}
				break;
			case 8:
				if (modeEnd(controller)) {
					_04 = -1;
					res = true;
				}
				break;
			}

			if (mCursorMgr->getStatusFlag() == WorldMapCursorMgr::UFO_Unk0 || mCursorMgr->isLanding()) {
				openMapInfo();
			}

			mEffectMgr2D->update();
			mMapImageMgr->update();
			mWipeMgr->update();
			mTitleMgr->update();
			mPartsInfoMgr->update();
		}
	}

	return res;
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x1D0(r1)
	  stfd      f31, 0x1C8(r1)
	  stfd      f30, 0x1C0(r1)
	  stfd      f29, 0x1B8(r1)
	  stfd      f28, 0x1B0(r1)
	  stmw      r19, 0x17C(r1)
	  mr        r30, r3
	  li        r31, 0
	  lwz       r0, 0x4(r3)
	  cmpwi     r0, -0x1
	  beq-      .loc_0xBEC
	  cmpwi     r0, 0x3
	  bne-      .loc_0x78
	  addi      r3, r30, 0x64
	  bl        0xB6AC
	  cmpwi     r3, 0
	  beq-      .loc_0xBEC
	  cmpwi     r3, 0x2
	  bne-      .loc_0x6C
	  li        r0, -0x1
	  stw       r0, 0x4(r30)
	  li        r0, 0x6
	  li        r31, 0x1
	  stw       r0, 0x8(r30)
	  b         .loc_0xBEC

	.loc_0x6C:
	  li        r0, 0x2
	  stw       r0, 0x4(r30)
	  b         .loc_0xBEC

	.loc_0x78:
	  cmpwi     r0, 0x6
	  bne-      .loc_0x2E4
	  addi      r3, r30, 0x74
	  bl        -0x4DE74
	  cmpwi     r3, -0x1
	  bne-      .loc_0xBEC
	  li        r0, 0x7
	  stw       r0, 0x4(r30)
	  li        r29, 0
	  lis       r20, 0x4330
	  lwz       r21, 0x58(r30)
	  lfd       f29, -0x4168(r2)
	  mr        r22, r21

	.loc_0xAC:
	  lwz       r3, 0x30(r22)
	  addi      r28, r22, 0xC
	  lha       r4, 0x18(r3)
	  lha       r0, 0x1C(r3)
	  lwz       r12, 0x0(r3)
	  sub       r5, r0, r4
	  lha       r4, 0x1A(r3)
	  lha       r0, 0x1E(r3)
	  srawi     r5, r5, 0x1
	  lwz       r12, 0x14(r12)
	  subfic    r23, r5, 0x140
	  sub       r0, r0, r4
	  srawi     r0, r0, 0x1
	  mtlr      r12
	  subfic    r24, r0, 0xF0
	  addi      r4, r23, 0
	  addi      r5, r24, 0
	  blrl
	  xoris     r3, r23, 0x8000
	  stw       r3, 0x174(r1)
	  xoris     r0, r24, 0x8000
	  addi      r29, r29, 0x1
	  stw       r20, 0x170(r1)
	  cmpwi     r29, 0x4
	  addi      r22, r22, 0x28
	  stw       r0, 0x16C(r1)
	  lfd       f0, 0x170(r1)
	  stw       r20, 0x168(r1)
	  fsubs     f2, f0, f29
	  lfd       f0, 0x168(r1)
	  stw       r3, 0x164(r1)
	  fsubs     f1, f0, f29
	  stfs      f2, 0xC(r28)
	  stw       r20, 0x160(r1)
	  stw       r0, 0x15C(r1)
	  lfd       f0, 0x160(r1)
	  stfs      f1, 0x10(r28)
	  fsubs     f1, f0, f29
	  stw       r20, 0x158(r1)
	  lfs       f2, 0x25EC(r13)
	  lfd       f0, 0x158(r1)
	  stfs      f2, 0x14(r28)
	  fsubs     f0, f0, f29
	  stfs      f1, 0x18(r28)
	  stfs      f0, 0x1C(r28)
	  lfs       f0, 0x25F0(r13)
	  stfs      f0, 0x20(r28)
	  blt+      .loc_0xAC
	  li        r29, 0
	  stw       r29, 0x0(r21)
	  addi      r25, r1, 0xF8
	  addi      r24, r1, 0xF4
	  lwz       r30, 0x58(r30)
	  addi      r23, r1, 0x100
	  lfs       f31, -0x4188(r2)
	  addi      r22, r1, 0xFC
	  addi      r21, r30, 0
	  stfs      f31, 0x4(r30)
	  lis       r20, 0x4330
	  lfs       f30, -0x4154(r2)
	  stfs      f30, 0x8(r30)
	  lfd       f29, -0x4168(r2)

	.loc_0x1A4:
	  lfs       f0, 0x10(r21)
	  addi      r28, r21, 0xC
	  fcmpo     cr0, f0, f31
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1C0
	  fadds     f0, f30, f0
	  b         .loc_0x1C4

	.loc_0x1C0:
	  fsubs     f0, f0, f30

	.loc_0x1C4:
	  lfs       f1, 0x0(r28)
	  fctiwz    f0, f0
	  fcmpo     cr0, f1, f31
	  stfd      f0, 0x158(r1)
	  lwz       r26, 0x15C(r1)
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1E8
	  fadds     f0, f30, f1
	  b         .loc_0x1EC

	.loc_0x1E8:
	  fsubs     f0, f1, f30

	.loc_0x1EC:
	  fctiwz    f0, f0
	  lwz       r3, 0x24(r28)
	  addi      r3, r3, 0x18
	  stfd      f0, 0x158(r1)
	  lwz       r27, 0x15C(r1)
	  bl        -0x263F0
	  lwz       r4, 0x24(r28)
	  srawi     r0, r3, 0x1
	  sub       r27, r27, r0
	  addi      r3, r4, 0x18
	  bl        -0x263F4
	  lwz       r5, 0x24(r28)
	  srawi     r3, r3, 0x1
	  addi      r4, r24, 0
	  lha       r0, 0x1A(r5)
	  addi      r5, r25, 0
	  sub       r26, r26, r3
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x164(r1)
	  addi      r3, r28, 0xC
	  addi      r6, r13, 0x25F4
	  stw       r20, 0x160(r1)
	  lfd       f0, 0x160(r1)
	  fsubs     f0, f0, f29
	  stfs      f0, 0xF8(r1)
	  lwz       r7, 0x24(r28)
	  lha       r0, 0x18(r7)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x16C(r1)
	  stw       r20, 0x168(r1)
	  lfd       f0, 0x168(r1)
	  fsubs     f0, f0, f29
	  stfs      f0, 0xF4(r1)
	  bl        -0x1812F8
	  xoris     r3, r26, 0x8000
	  xoris     r0, r27, 0x8000
	  stw       r3, 0x174(r1)
	  mr        r4, r22
	  stw       r0, 0x154(r1)
	  addi      r5, r23, 0
	  addi      r3, r28, 0x18
	  stw       r20, 0x170(r1)
	  addi      r6, r13, 0x25F8
	  stw       r20, 0x150(r1)
	  lfd       f1, 0x170(r1)
	  lfd       f0, 0x150(r1)
	  fsubs     f1, f1, f29
	  fsubs     f0, f0, f29
	  stfs      f1, 0x100(r1)
	  stfs      f0, 0xFC(r1)
	  bl        -0x18133C
	  addi      r29, r29, 0x1
	  cmpwi     r29, 0x4
	  addi      r21, r21, 0x28
	  blt+      .loc_0x1A4
	  li        r0, 0x2
	  stw       r0, 0x0(r30)
	  li        r0, 0x1
	  li        r3, 0x134
	  stb       r0, 0xAC(r30)
	  bl        -0x13967C
	  b         .loc_0xBEC

	.loc_0x2E4:
	  cmplwi    r0, 0x8
	  bgt-      .loc_0x930
	  lis       r3, 0x802E
	  addi      r3, r3, 0x58C0
	  rlwinm    r0,r0,2,0,29
	  lwzx      r0, r3, r0
	  mtctr     r0
	  bctr
	  lwz       r3, 0x58(r30)
	  lbz       r0, 0xAC(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x324
	  li        r0, 0x6
	  stw       r0, 0x4(r30)
	  addi      r3, r30, 0x74
	  bl        -0x4E4E8

	.loc_0x324:
	  lwz       r21, 0x34(r30)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x354
	  bge-      .loc_0x3E4
	  cmpwi     r0, 0
	  bge-      .loc_0x348
	  b         .loc_0x3E4
	  b         .loc_0x3E4

	.loc_0x348:
	  mr        r3, r21
	  bl        0x1F24
	  b         .loc_0x3E4

	.loc_0x354:
	  mr        r3, r21
	  bl        0x1A84
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x3E4
	  lbz       r0, 0x35(r21)
	  cmplwi    r0, 0
	  beq-      .loc_0x37C
	  mr        r3, r21
	  bl        0x1998
	  b         .loc_0x3E4

	.loc_0x37C:
	  lbz       r0, 0x34(r21)
	  cmplwi    r0, 0
	  beq-      .loc_0x3B8
	  li        r0, 0x2
	  stw       r0, 0x4(r21)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x3E4
	  bge-      .loc_0x3E4
	  cmpwi     r0, 0
	  bge-      .loc_0x3AC
	  b         .loc_0x3E4

	.loc_0x3AC:
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0x30(r21)
	  b         .loc_0x3E4

	.loc_0x3B8:
	  li        r0, 0
	  stw       r0, 0x4(r21)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x3E4
	  bge-      .loc_0x3E4
	  cmpwi     r0, 0
	  bge-      .loc_0x3DC
	  b         .loc_0x3E4

	.loc_0x3DC:
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0x30(r21)

	.loc_0x3E4:
	  mr        r3, r21
	  bl        0x15D4
	  li        r20, 0
	  mulli     r0, r20, 0x3C
	  add       r19, r21, r0

	.loc_0x3F8:
	  lwz       r4, 0x8(r21)
	  addi      r3, r19, 0x44
	  addi      r4, r4, 0xC0
	  bl        0xF90
	  addi      r20, r20, 0x1
	  cmpwi     r20, 0x3
	  addi      r19, r19, 0x3C
	  blt+      .loc_0x3F8
	  mr        r3, r21
	  bl        0xC20
	  mr        r3, r30
	  bl        0x87E4
	  b         .loc_0x930
	  lwz       r3, 0x58(r30)
	  lbz       r0, 0xAC(r3)
	  cmplwi    r0, 0
	  bne-      .loc_0x444
	  li        r0, 0x2
	  stw       r0, 0x4(r30)

	.loc_0x444:
	  lwz       r21, 0x34(r30)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x474
	  bge-      .loc_0x504
	  cmpwi     r0, 0
	  bge-      .loc_0x468
	  b         .loc_0x504
	  b         .loc_0x504

	.loc_0x468:
	  mr        r3, r21
	  bl        0x1E04
	  b         .loc_0x504

	.loc_0x474:
	  mr        r3, r21
	  bl        0x1964
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x504
	  lbz       r0, 0x35(r21)
	  cmplwi    r0, 0
	  beq-      .loc_0x49C
	  mr        r3, r21
	  bl        0x1878
	  b         .loc_0x504

	.loc_0x49C:
	  lbz       r0, 0x34(r21)
	  cmplwi    r0, 0
	  beq-      .loc_0x4D8
	  li        r0, 0x2
	  stw       r0, 0x4(r21)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x504
	  bge-      .loc_0x504
	  cmpwi     r0, 0
	  bge-      .loc_0x4CC
	  b         .loc_0x504

	.loc_0x4CC:
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0x30(r21)
	  b         .loc_0x504

	.loc_0x4D8:
	  li        r0, 0
	  stw       r0, 0x4(r21)
	  lwz       r0, 0x4(r21)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x504
	  bge-      .loc_0x504
	  cmpwi     r0, 0
	  bge-      .loc_0x4FC
	  b         .loc_0x504

	.loc_0x4FC:
	  lfs       f0, -0x4188(r2)
	  stfs      f0, 0x30(r21)

	.loc_0x504:
	  mr        r3, r21
	  bl        0x14B4
	  li        r20, 0
	  mulli     r0, r20, 0x3C
	  add       r19, r21, r0

	.loc_0x518:
	  lwz       r4, 0x8(r21)
	  addi      r3, r19, 0x44
	  addi      r4, r4, 0xC0
	  bl        0xE70
	  addi      r20, r20, 0x1
	  cmpwi     r20, 0x3
	  addi      r19, r19, 0x3C
	  blt+      .loc_0x518
	  mr        r3, r21
	  bl        0xB00
	  mr        r3, r30
	  bl        0x86C4
	  b         .loc_0x930
	  mr        r3, r30
	  bl        0x41A8
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  lwz       r0, 0x0(r30)
	  cmpwi     r0, 0
	  beq-      .loc_0x574
	  li        r0, 0x1
	  stw       r0, 0x4(r30)
	  b         .loc_0x930

	.loc_0x574:
	  li        r0, 0x2
	  stw       r0, 0x4(r30)
	  b         .loc_0x930
	  mr        r3, r30
	  bl        0x45F0
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  li        r0, 0x2
	  stw       r0, 0x4(r30)
	  b         .loc_0x930
	  mr        r3, r30
	  bl        0x7D38
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  li        r0, 0x2
	  stw       r0, 0x4(r30)
	  b         .loc_0x930
	  lwz       r3, 0x28(r4)
	  rlwinm.   r0,r3,0,7,7
	  beq-      .loc_0x5D8
	  addi      r3, r30, 0x64
	  bl        0xB0C4
	  li        r0, 0x3
	  stw       r0, 0x4(r30)
	  b         .loc_0x930

	.loc_0x5D8:
	  rlwinm.   r0,r3,0,16,16
	  beq-      .loc_0x8F8
	  lwz       r4, 0x34(r30)
	  li        r3, 0
	  lbz       r0, 0x35(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x604
	  lbz       r0, 0x34(r4)
	  cmplwi    r0, 0
	  bne-      .loc_0x604
	  li        r3, 0x1

	.loc_0x604:
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  lwz       r26, 0x58(r30)
	  addi      r22, r1, 0xE0
	  lfs       f31, -0x4188(r2)
	  addi      r23, r1, 0xDC
	  lfs       f30, -0x4154(r2)
	  lfd       f29, -0x4168(r2)
	  addi      r21, r26, 0
	  addi      r24, r1, 0xE8
	  addi      r25, r1, 0xE4
	  li        r20, 0
	  lis       r28, 0x4330

	.loc_0x638:
	  lfs       f0, 0x10(r21)
	  addi      r19, r21, 0xC
	  fcmpo     cr0, f0, f31
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x654
	  fadds     f0, f30, f0
	  b         .loc_0x658

	.loc_0x654:
	  fsubs     f0, f0, f30

	.loc_0x658:
	  lfs       f1, 0x0(r19)
	  fctiwz    f0, f0
	  fcmpo     cr0, f1, f31
	  stfd      f0, 0x150(r1)
	  lwz       r29, 0x154(r1)
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x67C
	  fadds     f0, f30, f1
	  b         .loc_0x680

	.loc_0x67C:
	  fsubs     f0, f1, f30

	.loc_0x680:
	  fctiwz    f0, f0
	  lwz       r3, 0x24(r19)
	  addi      r3, r3, 0x18
	  stfd      f0, 0x150(r1)
	  lwz       r27, 0x154(r1)
	  bl        -0x26884
	  lwz       r4, 0x24(r19)
	  srawi     r0, r3, 0x1
	  sub       r27, r27, r0
	  addi      r3, r4, 0x18
	  bl        -0x26888
	  srawi     r0, r3, 0x1
	  lwz       r3, 0x24(r19)
	  sub       r29, r29, r0
	  lwz       r12, 0x0(r3)
	  addi      r4, r27, 0
	  addi      r5, r29, 0
	  lwz       r12, 0x14(r12)
	  mtlr      r12
	  blrl
	  xoris     r29, r29, 0x8000
	  xoris     r27, r27, 0x8000
	  stw       r29, 0x15C(r1)
	  mr        r4, r23
	  stw       r27, 0x164(r1)
	  addi      r5, r22, 0
	  addi      r3, r19, 0xC
	  stw       r28, 0x158(r1)
	  addi      r6, r13, 0x25EC
	  stw       r28, 0x160(r1)
	  lfd       f1, 0x158(r1)
	  lfd       f0, 0x160(r1)
	  fsubs     f1, f1, f29
	  fsubs     f0, f0, f29
	  stfs      f1, 0xE0(r1)
	  stfs      f0, 0xDC(r1)
	  bl        -0x181798
	  stw       r29, 0x16C(r1)
	  addi      r4, r25, 0
	  addi      r5, r24, 0
	  stw       r27, 0x174(r1)
	  addi      r3, r19, 0x18
	  addi      r6, r13, 0x25F0
	  stw       r28, 0x168(r1)
	  stw       r28, 0x170(r1)
	  lfd       f1, 0x168(r1)
	  lfd       f0, 0x170(r1)
	  fsubs     f1, f1, f29
	  fsubs     f0, f0, f29
	  stfs      f1, 0xE8(r1)
	  stfs      f0, 0xE4(r1)
	  bl        -0x1817D4
	  addi      r20, r20, 0x1
	  cmpwi     r20, 0x4
	  addi      r21, r21, 0x28
	  blt+      .loc_0x638
	  li        r0, 0
	  stw       r0, 0x0(r26)
	  li        r0, 0x2
	  mtctr     r0
	  lis       r3, 0x4330
	  lwz       r7, 0x58(r30)
	  lfs       f0, -0x4188(r2)
	  mr        r9, r7
	  stfs      f0, 0x4(r7)
	  lfs       f0, -0x4154(r2)
	  stfs      f0, 0x8(r7)
	  lfd       f3, -0x4168(r2)

	.loc_0x790:
	  lwz       r5, 0x30(r9)
	  lha       r0, 0x18(r5)
	  lha       r10, 0x1A(r5)
	  xoris     r0, r0, 0x8000
	  lha       r4, 0x1E(r5)
	  stw       r0, 0x154(r1)
	  xoris     r0, r10, 0x8000
	  lha       r6, 0x18(r5)
	  sub       r4, r4, r10
	  stw       r3, 0x150(r1)
	  lha       r5, 0x1C(r5)
	  stw       r0, 0x15C(r1)
	  sub       r0, r5, r6
	  lfd       f0, 0x150(r1)
	  srawi     r0, r0, 0x1
	  stw       r3, 0x158(r1)
	  subfic    r0, r0, 0x140
	  fsubs     f2, f0, f3
	  lfd       f0, 0x158(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x164(r1)
	  srawi     r4, r4, 0x1
	  subfic    r0, r4, 0xF0
	  fsubs     f1, f0, f3
	  xoris     r0, r0, 0x8000
	  stfs      f2, 0x18(r9)
	  stw       r3, 0x160(r1)
	  stw       r0, 0x16C(r1)
	  lfd       f0, 0x160(r1)
	  stfs      f1, 0x1C(r9)
	  fsubs     f1, f0, f3
	  stw       r3, 0x168(r1)
	  lfs       f2, 0x25F4(r13)
	  lfd       f0, 0x168(r1)
	  stfs      f2, 0x20(r9)
	  fsubs     f0, f0, f3
	  stfs      f1, 0x24(r9)
	  stfs      f0, 0x28(r9)
	  lfs       f0, 0x25F8(r13)
	  stfs      f0, 0x2C(r9)
	  lwz       r5, 0x58(r9)
	  lha       r0, 0x18(r5)
	  lha       r10, 0x1A(r5)
	  xoris     r0, r0, 0x8000
	  lha       r4, 0x1E(r5)
	  stw       r0, 0x154(r1)
	  xoris     r0, r10, 0x8000
	  lha       r6, 0x18(r5)
	  sub       r4, r4, r10
	  stw       r3, 0x150(r1)
	  lha       r5, 0x1C(r5)
	  stw       r0, 0x15C(r1)
	  sub       r0, r5, r6
	  lfd       f0, 0x150(r1)
	  srawi     r0, r0, 0x1
	  stw       r3, 0x158(r1)
	  subfic    r0, r0, 0x140
	  fsubs     f2, f0, f3
	  lfd       f0, 0x158(r1)
	  xoris     r0, r0, 0x8000
	  stw       r0, 0x164(r1)
	  srawi     r4, r4, 0x1
	  subfic    r0, r4, 0xF0
	  fsubs     f1, f0, f3
	  xoris     r0, r0, 0x8000
	  stfs      f2, 0x40(r9)
	  stw       r3, 0x160(r1)
	  stw       r0, 0x16C(r1)
	  lfd       f0, 0x160(r1)
	  stfs      f1, 0x44(r9)
	  fsubs     f1, f0, f3
	  stw       r3, 0x168(r1)
	  lfs       f2, 0x25F4(r13)
	  lfd       f0, 0x168(r1)
	  stfs      f2, 0x48(r9)
	  fsubs     f0, f0, f3
	  stfs      f1, 0x4C(r9)
	  stfs      f0, 0x50(r9)
	  lfs       f0, 0x25F8(r13)
	  stfs      f0, 0x54(r9)
	  addi      r9, r9, 0x50
	  bdnz+     .loc_0x790
	  li        r4, 0x1
	  stw       r4, 0x0(r7)
	  li        r0, 0x5
	  li        r3, 0x134
	  stb       r4, 0xAC(r7)
	  stw       r0, 0x4(r30)
	  bl        -0x139C90
	  b         .loc_0x930

	.loc_0x8F8:
	  mr        r3, r30
	  bl        0x7174
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  li        r0, 0x8
	  stw       r0, 0x4(r30)
	  b         .loc_0x930
	  mr        r3, r30
	  bl        0x819C
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x930
	  li        r0, -0x1
	  stw       r0, 0x4(r30)
	  li        r31, 0x1

	.loc_0x930:
	  lwz       r3, 0x34(r30)
	  lwz       r0, 0x4(r3)
	  cmpwi     r0, 0
	  beq-      .loc_0x94C
	  lbz       r0, 0x34(r3)
	  cmplwi    r0, 0
	  beq-      .loc_0x954

	.loc_0x94C:
	  mr        r3, r30
	  bl        0x86C4

	.loc_0x954:
	  lwz       r3, 0x50(r30)
	  bl        0xAB1C
	  lwz       r3, 0x54(r30)
	  lwz       r0, 0x4(r3)
	  cmpwi     r0, 0x1
	  beq-      .loc_0x9D4
	  bge-      .loc_0x97C
	  cmpwi     r0, 0
	  bge-      .loc_0x988
	  b         .loc_0x9E0

	.loc_0x97C:
	  cmpwi     r0, 0x3
	  bge-      .loc_0x9E0
	  b         .loc_0x9DC

	.loc_0x988:
	  lwz       r0, 0x8(r3)
	  cmpwi     r0, -0x1
	  beq-      .loc_0x9E0
	  rlwinm    r0,r0,2,0,29
	  add       r4, r3, r0
	  lwz       r4, 0xC(r4)
	  li        r5, 0x1
	  lbz       r0, 0xC(r4)
	  rlwimi    r0,r5,7,24,24
	  stb       r0, 0xC(r4)
	  lwz       r0, 0x8(r3)
	  lfs       f0, -0x4184(r2)
	  rlwinm    r0,r0,2,0,29
	  add       r3, r3, r0
	  lwz       r3, 0xC(r3)
	  stfs      f0, 0xC0(r3)
	  stfs      f0, 0xC4(r3)
	  stfs      f0, 0xC8(r3)
	  b         .loc_0x9E0

	.loc_0x9D4:
	  bl        0x588
	  b         .loc_0x9E0

	.loc_0x9DC:
	  bl        0x494

	.loc_0x9E0:
	  lwz       r23, 0x58(r30)
	  li        r0, 0
	  stb       r0, 0xAC(r23)
	  lwz       r20, 0x0(r23)
	  cmpwi     r20, 0
	  beq-      .loc_0xBBC
	  blt-      .loc_0xBBC
	  cmpwi     r20, 0x3
	  bge-      .loc_0xBBC
	  lwz       r3, 0x2DEC(r13)
	  lfs       f1, 0x4(r23)
	  lfs       f0, 0x28C(r3)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4(r23)
	  lfs       f0, 0x4(r23)
	  lfs       f1, 0x8(r23)
	  fcmpo     cr0, f0, f1
	  ble-      .loc_0xA30
	  stfs      f1, 0x4(r23)
	  mr        r20, r0

	.loc_0xA30:
	  lwz       r0, 0x0(r23)
	  cmpwi     r0, 0x2
	  bne-      .loc_0xAA0
	  lfs       f1, 0x4(r23)
	  lfs       f0, 0x8(r23)
	  lfs       f2, -0x4150(r2)
	  fdivs     f0, f1, f0
	  fmuls     f1, f2, f0
	  bl        0x3C9F0
	  lfs       f3, -0x4184(r2)
	  lfs       f4, -0x4154(r2)
	  fsubs     f1, f3, f1
	  lfs       f2, -0x414C(r2)
	  lfs       f0, -0x4188(r2)
	  fmuls     f31, f4, f1
	  fsubs     f1, f3, f31
	  fmuls     f1, f2, f1
	  fcmpo     cr0, f1, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xA88
	  fadds     f0, f4, f1
	  b         .loc_0xA8C

	.loc_0xA88:
	  fsubs     f0, f1, f4

	.loc_0xA8C:
	  fctiwz    f0, f0
	  stfd      f0, 0x150(r1)
	  lwz       r0, 0x154(r1)
	  rlwinm    r21,r0,0,24,31
	  b         .loc_0xAF8

	.loc_0xAA0:
	  lfs       f1, 0x4(r23)
	  lfs       f0, 0x8(r23)
	  lfs       f2, -0x4148(r2)
	  fdivs     f0, f1, f0
	  fmuls     f1, f2, f0
	  bl        0x3CB20
	  lfs       f2, -0x414C(r2)
	  fmr       f31, f1
	  lfs       f0, -0x4188(r2)
	  fmuls     f2, f2, f1
	  fcmpo     cr0, f2, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xAE0
	  lfs       f0, -0x4154(r2)
	  fadds     f0, f0, f2
	  b         .loc_0xAE8

	.loc_0xAE0:
	  lfs       f0, -0x4154(r2)
	  fsubs     f0, f2, f0

	.loc_0xAE8:
	  fctiwz    f0, f0
	  stfd      f0, 0x150(r1)
	  lwz       r0, 0x154(r1)
	  rlwinm    r21,r0,0,24,31

	.loc_0xAF8:
	  lfs       f0, -0x4184(r2)
	  mr        r24, r23
	  lfs       f29, -0x4188(r2)
	  li        r22, 0
	  fsubs     f28, f0, f31
	  lfs       f30, -0x4154(r2)

	.loc_0xB10:
	  addi      r19, r24, 0xC
	  lfs       f1, 0x1C(r24)
	  lfs       f0, 0x28(r24)
	  fmuls     f1, f1, f28
	  fmuls     f0, f0, f31
	  fadds     f0, f1, f0
	  fcmpo     cr0, f0, f29
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xB3C
	  fadds     f0, f30, f0
	  b         .loc_0xB40

	.loc_0xB3C:
	  fsubs     f0, f0, f30

	.loc_0xB40:
	  lfs       f1, 0xC(r19)
	  fctiwz    f2, f0
	  lfs       f0, 0x18(r19)
	  fmuls     f1, f1, f28
	  fmuls     f0, f0, f31
	  stfd      f2, 0x150(r1)
	  lwz       r5, 0x154(r1)
	  fadds     f0, f1, f0
	  fcmpo     cr0, f0, f29
	  cror      2, 0x1, 0x2
	  bne-      .loc_0xB74
	  fadds     f0, f30, f0
	  b         .loc_0xB78

	.loc_0xB74:
	  fsubs     f0, f0, f30

	.loc_0xB78:
	  lwz       r3, 0x24(r19)
	  fctiwz    f0, f0
	  lwz       r12, 0x0(r3)
	  stfd      f0, 0x150(r1)
	  lwz       r12, 0x14(r12)
	  lwz       r4, 0x154(r1)
	  mtlr      r12
	  blrl
	  lwz       r3, 0x24(r19)
	  addi      r22, r22, 0x1
	  cmpwi     r22, 0x4
	  stb       r21, 0xF0(r3)
	  addi      r24, r24, 0x28
	  blt+      .loc_0xB10
	  stw       r20, 0x0(r23)
	  li        r0, 0x1
	  stb       r0, 0xAC(r23)

	.loc_0xBBC:
	  li        r20, 0
	  lwz       r22, 0x5C(r30)
	  mulli     r19, r20, 0x28
	  lwz       r21, 0x249C(r13)
	  b         .loc_0xBE4

	.loc_0xBD0:
	  lwz       r0, 0x0(r22)
	  add       r3, r0, r19
	  bl        .loc_0xC14
	  addi      r19, r19, 0x28
	  addi      r20, r20, 0x1

	.loc_0xBE4:
	  cmpw      r20, r21
	  blt+      .loc_0xBD0

	.loc_0xBEC:
	  mr        r3, r31
	  lmw       r19, 0x17C(r1)
	  lwz       r0, 0x1D4(r1)
	  lfd       f31, 0x1C8(r1)
	  lfd       f30, 0x1C0(r1)
	  lfd       f29, 0x1B8(r1)
	  lfd       f28, 0x1B0(r1)
	  addi      r1, r1, 0x1D0
	  mtlr      r0
	  blr

	.loc_0xC14:
	*/
}

/*
 * --INFO--
 * Address:	801E0D38
 * Size:	000134
 */
void zen::DrawWorldMap::draw(Graphics& gfx)
{
	if (_04 != 6) {
		mBackScreen->draw();
		mLineScreen->draw();
		mPointScreen->draw();
		mData1Screen->draw();
		mData2Screen->draw();
		mMoniScreen->draw();
		mIconScreen->draw();
		mTitleScreen->draw();
		mEffectMgr2D->draw(gfx);
		mConfirmMgr->draw(gfx);
		mWipeScreen->draw();
	} else {
		mSelectDiary.draw(gfx);
	}

	mPause.draw(gfx);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000AA4
 */
void zen::DrawWorldMap::setCoursePoint(zen::DrawWorldMap::startPlaceFlag placeFlag)
{
	switch (placeFlag) {
	case PLACE_Unk0:
		mCoursePointMgr->start(WM_Practice);
		break;
	case PLACE_Unk1:
		mCoursePointMgr->start(WM_Forest);
		break;
	case PLACE_Unk2:
		mCoursePointMgr->start(WM_Cave);
		break;
	case PLACE_Unk3:
		mCoursePointMgr->start(WM_Yakushima);
		break;
	case PLACE_Unk4:
		mCoursePointMgr->start(WM_Last);
		break;
	default:
		PRINT("unknown place no : %d \n", placeFlag);
		mCoursePointMgr->start(WM_Practice);
		break;
	}
}

/*
 * --INFO--
 * Address:	801E0E6C
 * Size:	001B78
 */
void zen::DrawWorldMap::start(zen::DrawWorldMap::startModeFlag modeFlag, zen::DrawWorldMap::startPlaceFlag placeFlag)
{
	mStartMode = modeFlag;
	_04        = 0;
	_0C        = 0.0f;
	mEffectMgr2D->killAll(true);
	_08 = 5;

	P2DPaneLibrary::makeResident(mWipeScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mMoniScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mIconScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mTitleScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mData1Screen->getScreenPtr());
	P2DPaneLibrary::makeResident(mData2Screen->getScreenPtr());
	P2DPaneLibrary::makeResident(mPointScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mLineScreen->getScreenPtr());
	P2DPaneLibrary::makeResident(mBackScreen->getScreenPtr());

	mCursorMgr->init();
	setCoursePoint(placeFlag);

	int x;
	int y;
	mCoursePointMgr->getLandPos(&x, &y);
	mCursorMgr->set(x, y, 0.0f);

	mCoursePointMgr->getStayPos(&x, &y);
	mCursorMgr->move(x, y, false);

	if (mStartMode != START_Unk0) {
		switch (mStartMode) {
		case START_Unk1:
			mCoursePointMgr->appear(WM_Forest);
			break;
		case START_Unk2:
			mCoursePointMgr->appear(WM_Cave);
			break;
		case START_Unk3:
			mCoursePointMgr->appear(WM_Yakushima);
			break;
		case START_Unk4:
			mCoursePointMgr->appear(WM_Last);
			mShootingStarMgr->rapidFire();
			break;
		default:
			PRINT("unknown startMode %d \n", mStartMode);
			ERROR("unknown startMode %d \n", mStartMode);
			break;
		}
	}

	mMapImageMgr->init();

	if (playerState) {
		P2DPane* blueCount = mData1Screen->getScreenPtr()->search('p_bc', true);
		if (!playerState->displayPikiCount(Blue)) {
			blueCount->hide();
		}
		P2DPane* redCount = mData1Screen->getScreenPtr()->search('p_rc', true);
		if (!playerState->displayPikiCount(Red)) {
			redCount->hide();
		}
		P2DPane* yellowCount = mData1Screen->getScreenPtr()->search('p_yc', true);
		if (!playerState->displayPikiCount(Yellow)) {
			yellowCount->hide();
		}
	}

	mTitleMgr->init();
	mPartsInfoMgr->init();
	mPartsInfoMgr->setActiveMapNo(mCoursePointMgr->getSelectCourseNumber());
	mWipeMgr->init();
	mWipeMgr->set(320, 240);
	mWipeMgr->open(1.0f);
}

/*
 * --INFO--
 * Address:	801E2E0C
 * Size:	00047C
 */
bool zen::DrawWorldMap::modeStart(Controller* controller)
{
	bool res = false;
	f32 c    = _0C += gsys->getFrameTime();
	f32 b    = 1.0f;
	if (c > b) {
		_0C = b;
	}
	f32 a             = _0C / b;
	P2DScreen* screen = mPointScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	screen = mLineScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	screen = mTitleScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))),
	             zen::RoundOff(-2.0f * screen->getHeight() * (1.0f - NMathF::sin(HALF_PI * a))));

	screen = mMoniScreen->getScreenPtr();
	screen->move(zen::RoundOff(-2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	f32 scale = (1.0f - NMathF::sin(HALF_PI * a)) * 10.0f + 1.0f;
	screen    = mData1Screen->getScreenPtr();
	screen->setOffset(screen->getWidth() >> 1, screen->getHeight() >> 1);
	screen->setScale(scale);

	screen = mData2Screen->getScreenPtr();
	screen->move(zen::RoundOff(2.0f * screen->getWidth() * (1.0f - NMathF::sin(HALF_PI * a))), screen->getPosV());

	mConfirmMgr->init();

	if (a == 1.0f) {
		res = true;
	}

	updateScreens();
	u32 badCompiler;
	return res;
}

/*
 * --INFO--
 * Address:	801E3288
 * Size:	002744
 */
bool zen::DrawWorldMap::modeAppear(Controller* controller)
{
	bool res = false;
	mCoursePointMgr->update(controller, false);
	if (mCoursePointMgr->getEventFlag() & 0x40) {
		if (mCoursePointMgr->getSelectCourseNumber() != mStartMode) {
			closeMapInfo();
		}

		switch (mStartMode) {
		case START_Unk1:
			setCoursePoint(PLACE_Unk1);
			break;
		case START_Unk2:
			setCoursePoint(PLACE_Unk2);
			break;
		case START_Unk3:
			setCoursePoint(PLACE_Unk3);
			break;
		case START_Unk4:
			setCoursePoint(PLACE_Unk4);
			break;
		default:
			PRINT("Illegal startMode. %d \n", mStartMode);
		}

		int x, y;
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->move(x, y, false);
		res = true;
	}

	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E6184
 * Size:	000868
 */
bool zen::DrawWorldMap::modeOperation(Controller* controller)
{
	bool res = false;
	mShootingStarMgr->update();
	mCoursePointMgr->update(controller, mCursorMgr->isMoveOK());
	u32 eventFlag = mCoursePointMgr->getEventFlag();
	int x, y;
	if (eventFlag & 0x1) {
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->move(x, y, false);
		closeMapInfo();
	}

	if (eventFlag & 0x10) {
		mConfirmMgr->start();
		_04 = 4;
	}
	if (eventFlag & 0x20) {
		mCoursePointMgr->getStayPos(&x, &y);
		mCursorMgr->moveCancel(x, y);
	}

	if (mCursorMgr->getStatusFlag() == WorldMapCursorMgr::UFO_Unk2) {
		_08 = mCoursePointMgr->getSelectCourseNumber();
		mEffectMgr2D->killAll(false);
		mCoursePointMgr->createCourseInEffect();
		mWipeMgr->setDefault();
		mWipeMgr->close(0.5f, 320, 240);
		res = true;
	}

	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E69EC
 * Size:	000614
 */
bool zen::DrawWorldMap::modeConfirm(Controller* controller)
{
	bool res = mConfirmMgr->update(controller);
	if (res && mConfirmMgr->getSelectFlag() == WorldMapConfirmMgr::SELECT_Unk0) {
		int x, y;
		mCoursePointMgr->getLandPos(&x, &y);
		mCursorMgr->move(x, y, true);
	}

	mCursorMgr->update();
	updateScreens();

	u32 badCompiler[2];
	return res;
}

/*
 * --INFO--
 * Address:	801E71C8
 * Size:	000154
 */
bool zen::DrawWorldMap::modeEnd(Controller*)
{
	bool res = false;
	if (!mWipeMgr->isActive()) {
		mEffectMgr2D->killAll(true);
		res = true;
	}
	mCursorMgr->update();
	updateScreens();
	return res;
}

/*
 * --INFO--
 * Address:	801E731C
 * Size:	0000DC
 */
void zen::DrawWorldMap::updateScreens()
{
	mWipeScreen->update();
	mMoniScreen->update();
	mIconScreen->update();
	mTitleScreen->update();
	mData1Screen->update();
	mData2Screen->update();
	mPointScreen->update();
	mLineScreen->update();
	mBackScreen->update();
}

/*
 * --INFO--
 * Address:	801E73F8
 * Size:	000124
 */
void zen::DrawWorldMap::closeMapInfo()
{
	mMapImageMgr->closeMapImage();
	mTitleMgr->exitTitle();
	mPartsInfoMgr->close();
}

/*
 * --INFO--
 * Address:	801E7728
 * Size:	000220
 */
void zen::DrawWorldMap::openMapInfo()
{
	WorldMapName course = mCoursePointMgr->getSelectCourseNumber();
	mMapImageMgr->openMapImage(course);
	mTitleMgr->setTitle(course);
	mPartsInfoMgr->setActiveMapNo(course);
}
