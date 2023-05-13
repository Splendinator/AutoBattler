#include "UnitActionMove.h"

#include "AutoBattler/AutoBattlerGameState.h"
#include "AutoBattler/AutoBattlerManager.h"
#include "AutoBattler/AutoBattlerUnit.h"

void FUnitActionMove::StartExecutingAction(IAutoBattlerUnit* Unit)
{
	if (CachedAutoBattlerManager.IsValid())
	{
		CachedAutoBattlerManager->ReserveUnitMove(EndX, EndY);
	}
}

void FUnitActionMove::ExecuteAction(IAutoBattlerUnit* Unit)
{
	if (CachedAutoBattlerManager.IsValid())
	{
		CachedAutoBattlerManager->MoveUnit(Unit, EndX, EndY);
	}
}

void FUnitActionMove::LerpAction(IAutoBattlerUnit* Unit, float LerpPct)
{
	if (AActor* Actor = Unit->GetBattlerUnitActor())
	{
		if (UWorld* World = Actor->GetWorld())
		{
			if (AAutoBattlerGameState* GameState = World->GetGameState<AAutoBattlerGameState>()) // hacky, should probably pass in the GridSize instead
			{
				const float GridSize = static_cast<float>(GameState->GetDistanceBetweenGridPieces());
				FVector StartLocation(StartX * GridSize, StartY * GridSize, 0.f);
				FVector EndLocation(EndX * GridSize, EndY * GridSize, 0.f);

				Actor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, LerpPct));
			}
		}
	}
}
