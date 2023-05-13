#pragma once

#include "AutoBattlerManager.generated.h"

class IAutoBattlerUnit;

/** UAutoBattlerManager
*
* This class is used to manager the auto battler.
* Contains only the game logic, something similar will be on server
*/
UCLASS(Blueprintable)
class UAutoBattlerManager : public UObject
{
	GENERATED_BODY()
	
public: // Blueprint

public: // C++

	void Init();
	void UnInit();
	void Tick(float DeltaTime);

	void AddUnit(IAutoBattlerUnit* Unit, int32 X, int32 Y);
	void RemoveUnit(IAutoBattlerUnit* Unit);

	int32 GetGridWidth() const { return GridWidth; }
	int32 GetGridHeight() const { return GridHeight; }

	void ReserveUnitMove(int32 ToX, int32 ToY); // Reserve movement to a grid so that no one else can move into it
	void MoveUnit(IAutoBattlerUnit* Unit, int32 ToX, int32 ToY);

	bool HasUnitAt(int32 X, int32 Y) { return GetCollisionRefAt(X, Y); }

	template<typename TLogic>
	void ForEachUnit(TLogic Logic)
	{
		for (IAutoBattlerUnit* Unit : Units)
		{
			Logic(Unit);
		}
	}

protected: // Blueprint

	// Width of the grid that the autobattle takes place
	UPROPERTY(EditDefaultsOnly)
	int32 GridWidth = 0;

	// Height of the grid that the autobattle takes place
	UPROPERTY(EditDefaultsOnly)
	int32 GridHeight = 0;

	// Time between each deterministic tick in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float TimeBetweenGameTurn = 0.1f;

protected: // C++

	void GameTurn();

	TArray<IAutoBattlerUnit*> Units;

private: // Blueprint

private: // C++

	bool& GetCollisionRefAt(int32 X, int32 Y);

	float TimeSinceLastGameTurn = 0.0f;

	// 2D array of all units
	bool* CollisionGrid = nullptr;
};
