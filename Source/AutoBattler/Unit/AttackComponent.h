#pragma once

#include <Components/ActorComponent.h>

#include "AttackComponent.generated.h"

/** UAttackComponent
*
* Component for attacking
*/
UCLASS()
class UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public: // Blueprint

	// Attack range in grid space
	UPROPERTY(EditDefaultsOnly)
	int32 AttackRange = 0;

	// Game turns between attacks
	UPROPERTY(EditDefaultsOnly)
	int32 TurnsPerAttack = 0;

};
