#include "AutoBattlerUnitActor.h"

#include "AttackComponent.h"
#include "AutoBattler/UnitActions/UnitActionFactoryBase.h"
#include "FactionComponent.h"
#include "HealthComponent.h"

AAutoBattlerUnitActor::AAutoBattlerUnitActor()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	FactionComponent = CreateDefaultSubobject<UFactionComponent>(TEXT("FactionComponent"));;
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));;
}

void AAutoBattlerUnitActor::OnAddedToManager(UAutoBattlerManager* Manager, int32 X, int32 Y)
{
	IAutoBattlerUnit::OnAddedToManager(Manager, X, Y);
}

void AAutoBattlerUnitActor::OnRemovedFromManager()
{
	IAutoBattlerUnit::OnRemovedFromManager();
}

TSharedPtr<FUnitActionBase> AAutoBattlerUnitActor::SelectAction()
{
	if (CachedAutoBattlerManager.IsValid())
	{
		for (UUnitActionFactoryBase* Factory : Factories)
		{
			TSharedPtr<FUnitActionBase> NewAction = Factory->TryCreateUnitAction(*this, *CachedAutoBattlerManager.Get());
			if (NewAction.IsValid())
			{
				return NewAction;
			}
		}
	}

	return {};
}

