#pragma once

#include "UnitActionFactoryBase.h"

#include "UnitActionFactoryMove.generated.h"

/**
* UUnitActionFactoryMove
*
* This class is used to create an action to move to the nearest enemy.
*/
UCLASS()
class UUnitActionFactoryMove : public UUnitActionFactoryBase
{
	GENERATED_BODY()

public: // C++

	//~ Begin UUnitActionFactoryBase Interface
	TSharedPtr<FUnitActionBase> TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager) override;
	//~ End UUnitActionFactoryBase Interface
};
