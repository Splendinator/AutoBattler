// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AutoBattlerGameModeBase.generated.h"

/** The game is an autobattler across a grid
 * 
 */
UCLASS()
class AUTOBATTLER_API AAutoBattlerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	//~ Begin AGameModeBase Interface
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	//~ End AGameModeBase Interface

};
