#pragma once

#include "UnitActionFactoryBase.h"

#include "UnitActionFactoryDie.generated.h"

/**
* UUnitActionFactoryDie
*
* This class is used to create die actions if the actor's health is 0
*/
UCLASS()
class UUnitActionFactoryDie : public UUnitActionFactoryBase
{
	GENERATED_BODY()

public: // C++

	//~ Begin UUnitActionFactoryBase Interface
	TSharedPtr<FUnitActionBase> TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager) override;
	//~ End UUnitActionFactoryBase Interface
};
