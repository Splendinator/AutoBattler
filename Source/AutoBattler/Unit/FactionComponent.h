#pragma once

#include <Components/ActorComponent.h>

#include "FactionComponent.generated.h"

enum class EFaction : uint8
{
	Red,
	Blue
};

/** UFactionComponent
*
* This class is used for storing the faction of a unit
*/
UCLASS()
class UFactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	EFaction Faction = EFaction::Red;
	
};
