#ifndef _TAI_MOVEACTIONS_H
#define _TAI_MOVEACTIONS_H

#include "TAI/Action.h"
#include "TAI/MotionActions.h"

/**
 * @brief TODO
 */
struct TaiMoveNestPositionAction : public TaiAction {
	inline TaiMoveNestPositionAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiStopMoveAction : public TaiAction {
	TaiStopMoveAction()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual void start(Teki& teki); // _08

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiStartFlyingAction : public TaiAction {
	inline TaiStartFlyingAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual void start(Teki& teki); // _08

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiFinishFlyingAction : public TaiAction {
	inline TaiFinishFlyingAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual void start(Teki& teki); // _08

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiMakeVelocityDirectionAction : public TaiAction {
	inline TaiMakeVelocityDirectionAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiMakeAccelerationDirectionAction : public TaiAction {
	inline TaiMakeAccelerationDirectionAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiMakingNextVelocityAction : public TaiAction {
	TaiMakingNextVelocityAction()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiMakingNextDriveAction : public TaiAction {
	inline TaiMakingNextDriveAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiAccelerationAction : public TaiAction {
	TaiAccelerationAction()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiParabolaAction : public TaiAction {
	inline TaiParabolaAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiCircleMoveAction : public TaiAction {
	inline TaiCircleMoveAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiHorizontalSinWaveAction : public TaiAction {
	TaiHorizontalSinWaveAction()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiClampMaxHeightAction : public TaiAction {
	inline TaiClampMaxHeightAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiClampMinHeightAction : public TaiAction {
	inline TaiClampMinHeightAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiClampMinVelocityYAction : public TaiAction {
	inline TaiClampMinVelocityYAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiImpassableAction : public TaiAction {
	inline TaiImpassableAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual void start(Teki& teki); // _08
	virtual bool act(Teki& teki);   // _10

	void resetPosition(Teki& teki);

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiRandomWanderingRouteAction : public TaiContinuousMotionAction {
	inline TaiRandomWanderingRouteAction() // TODO: this is a guess
	    : TaiContinuousMotionAction(0, 0)
	{
	}

	virtual void start(Teki& teki);  // _08
	virtual void finish(Teki& teki); // _0C
	virtual bool act(Teki& teki);    // _10

	void makeTargetPosition(Teki& teki);

	// _04 = VTBL
	// _00-_08 = TaiContinuousMotionAction?
};

struct TaiTracingAction : public TaiContinuousMotionAction {
	inline TaiTracingAction() // TODO: this is a guess
	    : TaiContinuousMotionAction(0, 0)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiContinuousMotionAction?
};

/**
 * @brief TODO
 */
struct TaiGoingHomeAction : public TaiContinuousMotionAction {
	TaiGoingHomeAction(int motionIdx, f32 p2)
	    : TaiContinuousMotionAction(TAI_NO_TRANSIT, motionIdx)
	{
		_0C = p2;
	}

	virtual void finish(Teki& teki); // _0C
	virtual bool act(Teki& teki);    // _10

	// _04 = VTBL
	// _00-_0C = TaiContinuousMotionAction
	f32 _0C; // _0C
};

/**
 * @brief TODO
 */
struct TaiDirectTurnAction : public TaiAction {
	inline TaiDirectTurnAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiTurningAction : public TaiContinuousMotionAction {
	inline TaiTurningAction() // TODO: this is a guess
	    : TaiContinuousMotionAction(0, 0)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiContinuousMotionAction?
};

/**
 * @brief TODO
 */
struct TaiTurningAwayAction : public TaiContinuousMotionAction {
	TaiTurningAwayAction(int nextState, int motionIdx, f32 p3)
	    : TaiContinuousMotionAction(nextState, motionIdx)
	{
		_0C = p3;
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_10 = TaiContinuousMotionAction
	f32 _0C; // _0C
};

/**
 * @brief TODO
 */
struct TaiTraceTurningAction : public TaiContinuousMotionAction {
	inline TaiTraceTurningAction() // TODO: this is a guess
	    : TaiContinuousMotionAction(0, 0)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiContinuousMotionAction?
};

/**
 * @brief TODO
 */
struct TaiOutOfTraceAngleAction : public TaiAction {
	inline TaiOutOfTraceAngleAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiTurningToTargetPositionAction : public TaiContinuousMotionAction {
	TaiTurningToTargetPositionAction(int nextState, int motionIdx, f32 p3)
	    : TaiContinuousMotionAction(nextState, motionIdx)
	{
		_0C = p3;
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_0C = TaiContinuousMotionAction
	f32 _0C; // _0C
};

/**
 * @brief TODO
 */
struct TaiRotatingAction : public TaiAction {
	inline TaiRotatingAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiRunningAwayToTargetDirectionAction : public TaiContinuousMotionAction {
	TaiRunningAwayToTargetDirectionAction(int nextState, int motionIdx, f32 p3)
	    : TaiContinuousMotionAction(nextState, motionIdx)
	{
		_0C = p3;
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_0C = TaiContinuousMotionAction
	f32 _0C; // _0C
};

/**
 * @brief TODO
 */
struct TaiRunningAwayAction : public TaiContinuousMotionAction {
	inline TaiRunningAwayAction() // TODO: this is a guess
	    : TaiContinuousMotionAction(0, 0)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiContinuousMotionAction?
};

/**
 * @brief TODO
 */
struct TaiWatchOffTerritoryCenterAction : public TaiAction {
	inline TaiWatchOffTerritoryCenterAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool act(Teki& teki); // _10

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiTargetNestAction : public TaiAction {
	TaiTargetNestAction()
	    : TaiAction(TAI_NO_TRANSIT)
	{
	}

	virtual void start(Teki& teki); // _08

	// _04 = VTBL
	// _00-_08 = TaiAction
};

/**
 * @brief TODO
 */
struct TaiHeadOnCollisionAvoidanceAction : public TaiAction {
	inline TaiHeadOnCollisionAvoidanceAction() // TODO: this is a guess
	    : TaiAction(-1)
	{
	}

	virtual bool actByEvent(TekiEvent& event); // _14

	// _04 = VTBL
	// _00-_08 = TaiAction
};

#endif
