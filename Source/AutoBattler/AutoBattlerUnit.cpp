#include "AutoBattlerUnit.h"

#include "AutoBattlerManager.h"

void IAutoBattlerUnit::OnAddedToManager(UAutoBattlerManager* Manager, int32 X, int32 Y)
{
	CachedAutoBattlerManager = Manager; 
	XCoord = X; 
	YCoord = Y;
}

