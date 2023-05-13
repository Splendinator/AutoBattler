#pragma once

#include <GameFramework/GameStateBase.h>

#include "AutoBattlerGameState.generated.h"

class AAutoBattlerUnitActor;
class UAutoBattlerManager;

/** AAutoBattlerGameState
*
* Game state for the auto battler client
*/
UCLASS()
class AAutoBattlerGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public: // Blueprint

public: // C++

	AAutoBattlerGameState();
	
	//~ Begin AGameStateBase Interface
	virtual void Tick(float DeltaSeconds);
	//~ End AGameStateBase Interface

	int32 GetDistanceBetweenGridPieces() const { return DistanceBetweenGridPieces; }

protected: // Blueprint

	// The auto battle manager responsible for handling the game logic
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAutoBattlerManager> AutoBattlerManagerClass;

	// Grid Piece One -- These will be placed in the world and alternated to visualize the autobattler grid
	UPROPERTY(EditDefaultsOnly, Category = "Grid Visuals")
	TSubclassOf<AActor> GridPieceOne;

	// Grid Piece Two -- These will be placed in the world and alternated to visualize the autobattler grid
	UPROPERTY(EditDefaultsOnly, Category = "Grid Visuals")
	TSubclassOf<AActor> GridPieceTwo;
	
	// Distance between grid pieces when spawning them in
	UPROPERTY(EditDefaultsOnly, Category = "Grid Visuals")
	int32 DistanceBetweenGridPieces = 100;

	// The red unit
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAutoBattlerUnitActor> RedUnitClass;

	// The blue unit
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAutoBattlerUnitActor> BlueUnitClass;

	// Number of units to spawn on each faction
	UPROPERTY(EditDefaultsOnly)
	int32 NumUnits = 10;

protected: // C++

	//~ Begin AGameStateBase Interface
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AGameStateBase Interface

	UPROPERTY()
	UAutoBattlerManager* AutoBattlerManager = nullptr;

	// Translate auto battle grid coordinates to world coordinates
	FVector GetWorldPositionFromGridSpace(int32 X, int32 Y) const { return FVector(X * DistanceBetweenGridPieces, Y * DistanceBetweenGridPieces, 0); }

private: // Blueprint

private: // C++

};
