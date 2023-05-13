#include "UnitActionFactoryMove.h"

#include "AutoBattler/AutoBattlerManager.h"
#include "AutoBattler/AutoBattlerUnit.h"
#include "AutoBattler/AutoBattlerUtils.h"
#include "AutoBattler/Unit/AutoBattlerUnitActor.h"
#include "AutoBattler/Unit/FactionComponent.h"
#include "UnitActionMove.h"

TSharedPtr<FUnitActionBase> UUnitActionFactoryMove::TryCreateUnitAction(AAutoBattlerUnitActor& Actor, UAutoBattlerManager& Manager)
{
	IAutoBattlerUnit* ClosestUnit = AutoBattlerUtils::GetClosestUnitNotInFaction(&Actor, Manager);

	if (ClosestUnit)
	{
		const int32 TargetX = Actor.GetXCoord() + FMath::Sign(ClosestUnit->GetXCoord() - Actor.GetXCoord());
		const int32 TargetY = Actor.GetYCoord() + FMath::Sign(ClosestUnit->GetYCoord() - Actor.GetYCoord());

		if (!Manager.HasUnitAt(TargetX, TargetY))
		{
			return MakeShared<FUnitActionMove>(
				Actor.GetXCoord(),
				Actor.GetYCoord(),
				TargetX,
				TargetY);
		}
	}
	
	return {};
}
