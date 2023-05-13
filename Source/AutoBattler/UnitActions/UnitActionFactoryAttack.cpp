#include "UnitActionFactoryAttack.h"

#include "AutoBattler/AutoBattlerUnit.h"
#include "AutoBattler/AutoBattlerUtils.h"
#include "AutoBattler/Unit/AttackComponent.h"
#include "AutoBattler/Unit/AutoBattlerUnitActor.h"
#include "AutoBattler/Unit/HealthComponent.h"
#include "UnitActionAttack.h"

TSharedPtr<FUnitActionBase> UUnitActionFactoryAttack::TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager)
{
	IAutoBattlerUnit* ClosestUnit = AutoBattlerUtils::GetClosestUnitNotInFaction(&Actor, Manager);

	if (ClosestUnit)
	{
		if (UAttackComponent* AttackComponent = Actor.GetAttackComponent())
		{
			if (AutoBattlerUtils::GetDistance(Actor.GetXCoord(), Actor.GetYCoord(), ClosestUnit->GetXCoord(), ClosestUnit->GetYCoord()) <= AttackComponent->AttackRange)
			{
				if (AActor* TheirActor = ClosestUnit->GetBattlerUnitActor())
				{
					if (UHealthComponent* HealthComponent = TheirActor->FindComponentByClass<UHealthComponent>())
					{
						return MakeShared<FUnitActionAttack>(HealthComponent, ClosestUnit, AttackComponent->TurnsPerAttack);
					}
				}
			}
		}
	}
	
	return {};
}

