#include "UnitActionAttack.h"

#include "AutoBattler/AutoBattlerManager.h"
#include "AutoBattler/AutoBattlerUnit.h"
#include "AutoBattler/Unit/HealthComponent.h"

#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>

void FUnitActionAttack::ExecuteAction(IAutoBattlerUnit* Unit)
{
	TheirHealth->CurrentHealth -= 1;

	// Make them get darker as they take damage perhaps
	if (AActor* Actor = TheirUnit->GetBattlerUnitActor())
	{
		// #TODO: Would take too long to do this
	}
}

void FUnitActionAttack::LerpAction(IAutoBattlerUnit* Unit, float LerpPct)
{
	// Attack animation
	const float Scale = 1.0f + (0.5f - FMath::Abs(LerpPct - 0.5f));
	if (AActor* Actor = Unit->GetBattlerUnitActor())
	{
		Actor->SetActorScale3D(FVector(Scale, Scale, Scale));
	}
}

bool FUnitActionAttack::CanExecute() const
{
	// Can't do if they're dead
	return TheirHealth.IsValid();
}
