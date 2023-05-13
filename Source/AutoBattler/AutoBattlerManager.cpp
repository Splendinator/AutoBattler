#include "AutoBattlerManager.h"

#include "AutoBattlerUnit.h"
#include "Unit/AutoBattlerUnitActor.h"
#include "UnitActions/UnitActionBase.h"

static TAutoConsoleVariable<int32> CVarShowLerp(TEXT("AutoBattler.ShowLerp"), 1, TEXT("Whether to show lerp animations"));

void UAutoBattlerManager::Init()
{
	CollisionGrid = new bool[GridWidth * GridHeight];
	memset(CollisionGrid, 0, sizeof(bool) * GridWidth * GridHeight);
}

void UAutoBattlerManager::UnInit()
{
	delete[] CollisionGrid;
}

void UAutoBattlerManager::AddUnit(IAutoBattlerUnit* Unit, int32 X, int32 Y)
{
	if (Unit)
	{
		Unit->OnAddedToManager(this, X, Y);
		Units.Add(Unit);
		GetCollisionRefAt(X, Y) = true;
	}
}

void UAutoBattlerManager::RemoveUnit(IAutoBattlerUnit* Unit)
{
	if (Unit)
	{
		int32 UnitsRemoved = Units.RemoveSingleSwap(Unit);

		if (UnitsRemoved > 0)
		{
			Unit->OnRemovedFromManager();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Trying to remove unit that doesn't exist"));
		}
	}
}

void UAutoBattlerManager::ReserveUnitMove(int32 ToX, int32 ToY)
{
	GetCollisionRefAt(ToX, ToY) = true;
}

void UAutoBattlerManager::MoveUnit(IAutoBattlerUnit* Unit, int32 ToX, int32 ToY)
{
	GetCollisionRefAt(Unit->XCoord, Unit->YCoord) = false;
	GetCollisionRefAt(ToX, ToY) = true;
	Unit->XCoord = ToX;
	Unit->YCoord = ToY;
}

void UAutoBattlerManager::Tick(float DeltaTime)
{
	TimeSinceLastGameTurn += DeltaTime;
	
	while (TimeSinceLastGameTurn > TimeBetweenGameTurn)
	{
		GameTurn();
		TimeSinceLastGameTurn -= TimeBetweenGameTurn;
	}

	if (CVarShowLerp.GetValueOnGameThread() > 0)
	{
		for (IAutoBattlerUnit* Unit : Units)
		{
			const TSharedPtr<FUnitActionBase>& CurrentAction = Unit->CurrentAction;
			if (CurrentAction.IsValid())
			{
				const float RawLerpPct = TimeSinceLastGameTurn / TimeBetweenGameTurn;

				const float TotalLerpPct = (RawLerpPct + CurrentAction->CurrentTurn) / CurrentAction->GetNumTurnsToExecute();

				CurrentAction->LerpAction(Unit, TotalLerpPct);

			}
		}
	}
}

void UAutoBattlerManager::GameTurn()
{
	for (IAutoBattlerUnit* Unit : Units)
	{
		TSharedPtr<FUnitActionBase>& CurrentAction = Unit->CurrentAction;
		if (CurrentAction.IsValid())
		{
			if (CurrentAction->CanExecute())
			{
				++(CurrentAction->CurrentTurn);
				if (CurrentAction->CurrentTurn >= CurrentAction->GetNumTurnsToExecute())
				{
					CurrentAction->LerpAction(Unit, 1.0f); // Send final LERP to clean up action
					CurrentAction->ExecuteAction(Unit);
					CurrentAction.Reset();
				}
			}
			else
			{
				CurrentAction->LerpAction(Unit, 1.0f);  // Send final LERP to clean up action
				CurrentAction.Reset();
			}
		}

		if (!CurrentAction.IsValid())
		{
			CurrentAction = Unit->SelectAction();

			if (CurrentAction.IsValid())
			{
				CurrentAction->Initialise(this);
				CurrentAction->StartExecutingAction(Unit);
			}
		}
		
	}
}

bool& UAutoBattlerManager::GetCollisionRefAt(int32 X, int32 Y)
{
	X = FMath::Clamp(X, 0, GridWidth - 1);
	Y = FMath::Clamp(Y, 0, GridHeight - 1);

	return CollisionGrid[X + Y * GridWidth];
}

