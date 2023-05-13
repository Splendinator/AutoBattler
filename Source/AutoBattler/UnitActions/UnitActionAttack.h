#pragma once

#include "UnitActionBase.h"

class UHealthComponent;

/** UUnitActionAttack
*
* This class is used for attacking another unit
*/
class FUnitActionAttack : public FUnitActionBase
{
public: // C++

	FUnitActionAttack(TWeakObjectPtr<UHealthComponent> InTheirHealth, IAutoBattlerUnit* InTheirUnit, int32 InNumberTurns) : TheirHealth(InTheirHealth), TheirUnit(InTheirUnit), NumberTurns(InNumberTurns) {}

	//~ Begin UUnitActionBase Interface
	void ExecuteAction(IAutoBattlerUnit* Unit) override;
	void LerpAction(IAutoBattlerUnit* Unit, float LerpPct) override;
	virtual bool CanExecute() const override;
	virtual int32 GetNumTurnsToExecute() const { return NumberTurns; }
	//~ End UUnitActionBase Interface

	TWeakObjectPtr<UHealthComponent> TheirHealth;
	IAutoBattlerUnit* TheirUnit = nullptr;
	int32 NumberTurns = 1; // Number of turns before attacking
};
