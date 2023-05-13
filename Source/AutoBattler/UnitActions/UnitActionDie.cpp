#include "UnitActionDie.h"

#include "AutoBattler/AutoBattlerManager.h"
#include "AutoBattler/AutoBattlerUnit.h"

void FUnitActionDie::ExecuteAction(IAutoBattlerUnit* Unit)
{
	if (AActor* Actor = Unit->GetBattlerUnitActor())
	{
		// Remove unit from manager (next frame to prevent removing mid-loop)
		FTimerManager& TimerManager = Actor->GetWorldTimerManager();
		UAutoBattlerManager* Manager = CachedAutoBattlerManager.Get();
		TimerManager.SetTimerForNextTick([Manager, Unit, Actor]()
			{
				if (Manager)
				{
					Manager->RemoveUnit(Unit);
				}
				
				Actor->Destroy();
			});

	}
}

void FUnitActionDie::LerpAction(IAutoBattlerUnit* Unit, float LerpPct)
{
	if (AActor* Actor = Unit->GetBattlerUnitActor())
	{
		Actor->SetActorLocation(Actor->GetActorLocation() + FVector(0.0f, 0.0f, -100.f * LerpPct));
	}
	
}
