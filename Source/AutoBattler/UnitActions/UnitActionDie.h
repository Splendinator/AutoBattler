#pragma once

#include "UnitActionBase.h"

/** UUnitActionDie
*
* This class is used for killing a unit
*/
class FUnitActionDie : public FUnitActionBase
{
public: // C++

	//~ Begin UUnitActionBase Interface
	void ExecuteAction(IAutoBattlerUnit* Unit) override;
	void LerpAction(IAutoBattlerUnit* Unit, float LerpPct) override;
	//~ End UUnitActionBase Interface
};
