#pragma once

#include "UnitActionBase.h"

/** UUnitActionMove
*
* This class is used for moving a unit
*/
class FUnitActionMove : public FUnitActionBase
{

public: // C++
	FUnitActionMove() = default;
	FUnitActionMove(int32 InStartX, int32 InStartY, int32 InEndX, int32 InEndY) : StartX(InStartX), StartY(InStartY), EndX(InEndX), EndY(InEndY) {}

	//~ Begin UUnitActionBase Interface
	void StartExecutingAction(IAutoBattlerUnit* Unit) override;
	void ExecuteAction(IAutoBattlerUnit* Unit) override;
	void LerpAction(IAutoBattlerUnit* Unit, float LerpPct) override;
	//~ End UUnitActionBase Interface

	int32 StartX;
	int32 StartY;
	int32 EndX;
	int32 EndY;
};
