#pragma once

#include <Components/ActorComponent.h>

#include "HealthComponent.generated.h"

/** UHealthComponent
*
* This class is used for storing the health of a unit
*/
UCLASS()
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	int32 CurrentHealth = 0;

};
