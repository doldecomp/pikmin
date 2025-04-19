#ifndef _TAI_MIURIN_H
#define _TAI_MIURIN_H

#include "types.h"
#include "TAI/Aattack.h"
#include "TAI/Areaction.h"
#include "TAI/Ajudge.h"
#include "TAI/Amove.h"
#include "TAI/EffectAttack.h"
#include "TekiParameters.h"
#include "TAI/Animation.h"
#include "Pcam/CameraManager.h"
#include "RumbleMgr.h"
#include "YaiStrategy.h"
#include "NaviMgr.h"
#include "SoundMgr.h"
#include "zen/CallBack.h"
#include "PaniAnimator.h"

struct CollPart;

BEGIN_ENUM_TYPE(TAImiurinFloatParams)
enum {
	RelaxTime = TPF_COUNT, // 50
	EyeRollTime,           // 51
	CheckNaviPercent,      // 52
	AngryRotationSpeed,    // 53
	COUNT,                 // 54
} END_ENUM_TYPE;

BEGIN_ENUM_TYPE(TAImiurinIntParams)
enum {
	MaxStickPiki = TPI_COUNT, // 20
	ShakeOffHitCount,         // 21
	RelaxingFlowerNum,        // 22
	COUNT,                    // 23
} END_ENUM_TYPE;

BEGIN_ENUM_TYPE(TAImiurinStateID)
enum {
	Unk0  = 0,
	Unk1  = 1,
	Unk2  = 2,
	Unk3  = 3,
	Unk4  = 4,
	Unk5  = 5,
	Unk6  = 6,
	Unk7  = 7,
	Unk8  = 8,
	Unk9  = 9,
	Unk10 = 10,
	Unk11 = 11,
	Unk12 = 12,
	Unk13 = 13,
	Unk14 = 14,
	Unk15 = 15,
	Unk16 = 16,
	Unk17 = 17,
	Unk18 = 18,
	Unk19 = 19,
	Unk20 = 20,
	Unk21 = 21,
	Unk22 = 22,
	Unk23 = 23,
	COUNT, // 24
} END_ENUM_TYPE;

BEGIN_ENUM_TYPE(TAImiurinMotionID)
enum {
	Unk0  = 0,  //
	Unk2  = 2,  //
	Unk3  = 3,  //
	Unk4  = 4,  //
	Unk5  = 5,  //
	Unk6  = 6,  //
	Unk7  = 7,  //
	Unk8  = 8,  //
	Unk9  = 9,  //
	Unk10 = 10, //
	Unk13 = 13, //
} END_ENUM_TYPE;

/////////// Mamuta AI Actions ///////////

/**
 * @brief TODO
 */
struct TAImiurinSoundTable : public PaniSoundTable {
	TAImiurinSoundTable();

	// _00-_08 = PaniSoundTable
};

/**
 * @brief TODO
 */
struct TAImiurinParameters : public TekiParameters {
	TAImiurinParameters();

	// _00     = VTBL
	// _00-_88 = TekiParameters
};

/**
 * @brief TODO
 */
struct TAImiurinStrategy : public YaiStrategy {
	TAImiurinStrategy();

	virtual bool interact(Teki&, TekiInteractionKey&); // _20

	// _00     = VTBL
	// _00-_10 = YaiStrategy
};

/**
 * @brief TODO
 */
struct TAImiurinAnimation : public TAIanimation {
	TAImiurinAnimation()
	    : TAIanimation(TEKI_KabekuiB, "tekis/miurin/anims.bun") // yep, really had this.
	{
	}

	virtual void makeDefaultAnimations(); // _08

	// _0C     = VTBL
	// _00-_0C = TAIanimation
};

/**
 * @brief TODO
 */
struct TAIAinitMiurin : public TaiAction {
	TAIAinitMiurin(int nextState)
	    : TaiAction(nextState)
	{
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAgroggyMiurin : public TAIAreserveMotion {
	TAIAgroggyMiurin(int nextState, int motionID)
	    : TAIAreserveMotion(nextState, motionID)
	{
	}

	virtual void start(Teki& teki) // _08
	{
		TAIAreserveMotion::start(teki);
		teki.setFrameCounter(0.0f);
		teki.mDamageCount = 0.0f;
	}
	virtual bool act(Teki& teki) // _10
	{
		bool res = false;
		if (TAIAreserveMotion::act(teki)) {
			if (teki.addFrameCounter(gsys->getFrameTime()) > teki.getParameterF(TAImiurinFloatParams::EyeRollTime)) {
				teki.mTekiAnimator->finishMotion(PaniMotionInfo(-1, &teki));
			}

			if (teki.mCurrentAnimEvent == KEY_Finished) {
				res = true;
			}
		}
		return res;
	}

	// _04     = VTBL
	// _00-_0C = TAIAreserveMotion
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAresetAnimSpeedMiurin : public TaiAction {
	TAIAresetAnimSpeedMiurin()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual void start(Teki& teki) { teki.setManualAnimation(false); } // _08

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 *
 * @note Lives in TAImiurin.cpp to use the PRINT function in that file.
 */
struct TAIAangryMiurin;

/**
 * @brief TODO
 *
 * @note Lives in TAImiurin.cpp to use the PRINT function in that file.
 */
struct TAIAcheckNaviMiurin;

/**
 * @brief TODO
 *
 * @note Lives in TAImiurin.cpp to use the PRINT function in that file.
 */
struct TAIAcheckFlowerPikmin;

/**
 * @brief TODO
 */
struct TAIAsatisfyMiurin : public TAIAreserveMotion {
	TAIAsatisfyMiurin(int nextState, int motionID)
	    : TAIAreserveMotion(nextState, motionID)
	{
	}

	virtual void start(Teki& teki) // _08
	{
		TAIAreserveMotion::start(teki);
		teki.setFrameCounter(0.0f);
		teki.mDamageCount = 0.0f;
	}
	virtual bool act(Teki& teki) // _10
	{
		bool res = false;
		if (TAIAreserveMotion::act(teki)) {
			if (teki.addFrameCounter(gsys->getFrameTime()) > teki.getParameterF(TAImiurinFloatParams::RelaxTime)) {
				teki.mTekiAnimator->finishMotion(PaniMotionInfo(-1, &teki));
			}

			if (teki.mCurrentAnimEvent == KEY_Finished) {
				res = true;
			}
			if (teki.mCurrentAnimEvent == KEY_LoopStart) {
				teki.playEventSound(&teki, SE_MIURIN_SING);
			}
		}

		if (teki.mCurrentAnimEvent == KEY_Action0) {
			Vector3f pos(teki.getPosition());
			pos.y = mapMgr->getMinY(pos.x, pos.z, true);
			effectMgr->create(EffectMgr::EFF_SmokeRing_M, pos, nullptr, nullptr);
			teki.playEventSound(&teki, SE_CHAPPY_DOWN);
		}
		return res;
	}

	// _04     = VTBL
	// _00-_0C = TAIAreserveMotion
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAwatchNaviMiurin : public TaiAction {
	TAIAwatchNaviMiurin(int nextState, int p2)
	    : TaiAction(nextState)
	{
		_08 = nextState;
		_0C = p2;
	}

	virtual bool act(Teki&);             // _10
	virtual bool actByEvent(TekiEvent&); // _14

	// _04     = VTBL
	// _00-_08 = TaiAction
	int _08; // _08
	int _0C; // _0C
};

/**
 * @brief TODO
 */
struct TAIAoutsideTerritoryMiurin : public TAIAoutsideTerritory {
	TAIAoutsideTerritoryMiurin(int nextState)
	    : TAIAoutsideTerritory(nextState)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TAIAoutsideTerritory?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAflickingMiurin : public TAIAflickingReserveMotion {
	TAIAflickingMiurin(int nextState, int motionID)
	    : TAIAflickingReserveMotion(nextState, motionID)
	{
	}

	virtual f32 getFlickDirection(Teki&); // _20

	// _04     = VTBL
	// _00-_0C = TAIAflickingReserveMotion?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAflickCheckMiurin : public TAIAflickCheck {
	TAIAflickCheckMiurin(int nextState)
	    : TAIAflickCheck(nextState, -1)
	{
	}

	virtual bool act(Teki&);                // _10
	virtual int getDamageCountLimit(Teki&); // _1C

	// _04     = VTBL
	// _00-_08 = TAIAflickCheck?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAstickingPikiMiurin : public TAIAstickingPiki {
	TAIAstickingPikiMiurin(int nextState)
	    : TAIAstickingPiki(nextState, 0)
	{
	}

	virtual int getPikiNum(Teki&); // _1C

	// _04     = VTBL
	// _00-_08 = TAIAstickingPiki?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAcheckSatisfyMiurin : public TaiAction {
	TAIAcheckSatisfyMiurin(int nextState)
	    : TaiAction(nextState)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TaiAction
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAattackMiurin : public TAIAreserveMotion {
	TAIAattackMiurin(int nextState, int p2, int motionID, int p4)
	    : TAIAreserveMotion(nextState, motionID)
	{
		_0C = p2;
		_10 = p4;
		_14 = motionID;
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_0C = TAIAreserveMotion
	int _0C; // _0C
	int _10; // _10
	int _14; // _14
};

/**
 * @brief TODO
 */
struct TAIAattackPosture : public TAIAreserveMotion {
	TAIAattackPosture(int nextState, int motionID)
	    : TAIAreserveMotion(nextState, motionID)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_0C = TAIAreserveMotion
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAattackableTargetMiurin : public TAIAattackableTarget {
	TAIAattackableTargetMiurin(int nextState)
	    : TAIAattackableTarget(nextState)
	{
	}

	virtual bool act(Teki&); // _10

	// _04     = VTBL
	// _00-_08 = TAIAattackableTarget?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAapproachTargetPriorityFaceDirMiurin : public TAIAapproachTargetPriorityFaceDir {
	TAIAapproachTargetPriorityFaceDirMiurin(int nextState, int motionID)
	    : TAIAapproachTargetPriorityFaceDir(nextState, motionID)
	{
	}

	virtual void start(Teki&);      // _08
	virtual f32 getVelocity(Teki&); // _1C

	// _04     = VTBL
	// _00-_08 = TAIAapproachTargetPriorityFaceDir?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAturnFocusCreatureMiurin : public TAIAturnFocusCreature {
	TAIAturnFocusCreatureMiurin(int nextState, int leftMotionID, int rightMotionID, bool p4)
	    : TAIAturnFocusCreature(nextState, leftMotionID, rightMotionID, p4)
	{
	}

	virtual void start(Teki&);          // _08
	virtual f32 getTurnVelocity(Teki&); // _1C

	// _04     = VTBL
	// _00-_08 = TAIAturnFocusCreature?
	// TODO: members
};

/**
 * @brief TODO
 */
struct TAIAdyingMiurin : public TAIAdying {
	TAIAdyingMiurin(int nextState, int motionID)
	    : TAIAdying(nextState, motionID)
	{
	}

	virtual void start(Teki&); // _08
	virtual bool act(Teki&);   // _10

	// _04     = VTBL
	// _00-_0C = TAIAdying?
	// TODO: members
};

#endif
