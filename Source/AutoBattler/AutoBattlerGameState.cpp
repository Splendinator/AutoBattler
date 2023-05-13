#include "AutoBattlerGameState.h"

#include "AutoBattlerManager.h"
#include "Unit/AutoBattlerUnitActor.h"
#include "Unit/FactionComponent.h"
#include "Unit/HealthComponent.h"

AAutoBattlerGameState::AAutoBattlerGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAutoBattlerGameState::Tick(float DeltaSeconds)
{
	if (AutoBattlerManager)
	{
		AutoBattlerManager->Tick(DeltaSeconds);
	}
}

void AAutoBattlerGameState::BeginPlay()
{
	Super::BeginPlay();

	AutoBattlerManager = NewObject<UAutoBattlerManager>(this, AutoBattlerManagerClass);

	// Init manager
	if (AutoBattlerManager)
	{
		AutoBattlerManager->Init();
		
		if (GridPieceOne && GridPieceTwo)
		{
			bool bIsGridPieceOneOuter = true; // Changes every row
			for (int32 X = 0; X < AutoBattlerManager->GetGridWidth(); ++X)
			{
				bool bIsGridPieceOneInner = bIsGridPieceOneOuter; // Changes every tile
				for (int32 Y = 0; Y < AutoBattlerManager->GetGridHeight(); ++Y)
				{
					GetWorld()->SpawnActor<AActor>(bIsGridPieceOneInner ? GridPieceOne.Get() : GridPieceTwo.Get(), GetWorldPositionFromGridSpace(X, Y) - FVector(DistanceBetweenGridPieces * 0.5f, DistanceBetweenGridPieces * 0.5f, 0.0f), FRotator::ZeroRotator);
					bIsGridPieceOneInner = !bIsGridPieceOneInner;
				}
				bIsGridPieceOneOuter = !bIsGridPieceOneOuter;
			}
		}

		// Set up initial units
		auto AddUnit = [this](EFaction Faction)
		{
			int32 StartX = FMath::RandRange(0, AutoBattlerManager->GetGridWidth() - 1);
			int32 StartY = FMath::RandRange(0, AutoBattlerManager->GetGridHeight() - 1);

			while (AutoBattlerManager->HasUnitAt(StartX, StartY))
			{
				// #TODO: Optimise
				StartX = FMath::RandRange(0, AutoBattlerManager->GetGridWidth() - 1);
				StartY = FMath::RandRange(0, AutoBattlerManager->GetGridHeight() - 1);
			}

			AAutoBattlerUnitActor* NewUnit = GetWorld()->SpawnActor<AAutoBattlerUnitActor>(Faction == EFaction::Red ? RedUnitClass.Get() : BlueUnitClass.Get(), GetWorldPositionFromGridSpace(StartX, StartY), FRotator::ZeroRotator);
			
			if (UFactionComponent* FactionComponent = NewUnit->GetFactionComponent())
			{
				FactionComponent->Faction = Faction;
			}
			if (UHealthComponent* HealthComponent = NewUnit->GetHealthComponent())
			{
				HealthComponent->CurrentHealth = FMath::RandRange(2, 5);
			}

			AutoBattlerManager->AddUnit(NewUnit, StartX, StartY);
		};

		for (int32 Index = 0; Index < NumUnits; ++Index)
		{
			AddUnit(EFaction::Blue);
			AddUnit(EFaction::Red);
		}
	}
}

void AAutoBattlerGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AutoBattlerManager)
	{
		AutoBattlerManager->UnInit();
		AutoBattlerManager->MarkAsGarbage();
		AutoBattlerManager = nullptr;
	}
	

	Super::EndPlay(EndPlayReason);
}

