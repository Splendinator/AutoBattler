#include "UnitActionFactoryDie.h"

#include "AutoBattler/Unit/AutoBattlerUnitActor.h"
#include "AutoBattler/Unit/HealthComponent.h"
#include "UnitActionDie.h"

TSharedPtr<FUnitActionBase> UUnitActionFactoryDie::TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager)
{
	if (UHealthComponent* HealthComponent = Actor.GetHealthComponent())
	{
		if (HealthComponent->CurrentHealth <= 0)
		{
			return MakeShared<FUnitActionDie>();
		}
	}
	return {};
}
