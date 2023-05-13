#include "UnitActionBase.h"

#include "AutoBattler/AutoBattlerManager.h"

void FUnitActionBase::Initialise(UAutoBattlerManager* AutoBattlerManager)
{
	CachedAutoBattlerManager = AutoBattlerManager;
}
