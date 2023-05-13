#pragma once

class IAutoBattlerUnit;
class UAutoBattlerManager;

namespace AutoBattlerUtils
{
	int32 GetDistance(int32 StartX, int32 StartY, int32 EndX, int32 EndY);

	IAutoBattlerUnit* GetClosestUnitNotInFaction(IAutoBattlerUnit* Unit, UAutoBattlerManager& Manager);

}