#pragma once

#include "UnitActionFactoryBase.h"

#include "UnitActionFactoryAttack.generated.h"

/**
* UUnitActionFactoryAttack
*
* This class is used to create an action to attack if there's an enemy in attack range
*/
UCLASS()
class UUnitActionFactoryAttack : public UUnitActionFactoryBase
{
	GENERATED_BODY()

public: // C++

	//~ Begin UUnitActionFactoryBase Interface
	TSharedPtr<FUnitActionBase> TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager) override;
	//~ End UUnitActionFactoryBase Interface
};
