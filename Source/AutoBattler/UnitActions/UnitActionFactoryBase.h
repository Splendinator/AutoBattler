#pragma once

#include "UnitActionFactoryBase.generated.h"

class AAutoBattlerUnitActor;
class UAutoBattlerManager;
class FUnitActionBase;

/** UUnitActionFactoryBase
*
* This class is used to create UUnitActionBases. It will create it only if it can (i.e attack will only work when standing next to an enemy)
*/
UCLASS(Abstract, Blueprintable, EditInlineNew)
class UUnitActionFactoryBase : public UObject
{
	GENERATED_BODY()

public: // C++
	
	virtual TSharedPtr<FUnitActionBase> TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager) PURE_VIRTUAL(UUnitActionFactoryBase::TryCreateUnitAction, return nullptr;);

};
