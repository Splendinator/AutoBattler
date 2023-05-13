#include "AutoBattlerUtils.h"

#include "AutoBattlerManager.h"
#include "AutoBattlerUnit.h"
#include "Unit/FactionComponent.h"

int32 AutoBattlerUtils::GetDistance(int32 StartX, int32 StartY, int32 EndX, int32 EndY)
{
	return FMath::Abs(StartX - EndX) + FMath::Abs(StartY - EndY);
}

IAutoBattlerUnit* AutoBattlerUtils::GetClosestUnitNotInFaction(IAutoBattlerUnit* Unit, UAutoBattlerManager& Manager)
{	
	IAutoBattlerUnit* ClosestUnit = nullptr;
	int32 LowestDistance = TNumericLimits<int32>::Max();

	Manager.ForEachUnit([&](IAutoBattlerUnit* TheirUnit)
		{
			if (AActor* MyActor = Unit->GetBattlerUnitActor())
			{
				if (UFactionComponent* MyFactionComponent = MyActor->FindComponentByClass<UFactionComponent>())
				{
					if (AActor* TheirActor = TheirUnit->GetBattlerUnitActor())
					{
						if (UFactionComponent* TheirFactionComponent = TheirActor->FindComponentByClass<UFactionComponent>())
						{
							if (MyFactionComponent->Faction != TheirFactionComponent->Faction)
							{
								const int32 Distance = AutoBattlerUtils::GetDistance(Unit->GetXCoord(), Unit->GetYCoord(), TheirUnit->GetXCoord(), TheirUnit->GetYCoord());
								if (Distance < LowestDistance)
								{
									LowestDistance = Distance;
									ClosestUnit = TheirUnit;
								}
							}
						}
					}
				}
			}
		});

	return ClosestUnit;
}

