#pragma once

class UAutoBattlerManager;
class FUnitActionBase;

/** UAutoBattlerUnit
*
* Interface that any unit should implement if it wants to go in the manager
*/
class IAutoBattlerUnit
{
	friend class UAutoBattlerManager;
public:
	virtual ~IAutoBattlerUnit() {};

	virtual void OnAddedToManager(UAutoBattlerManager* Manager, int32 X, int32 Y);
	virtual void OnRemovedFromManager() {};

	// Get actor representing this unit if one exists
	virtual AActor* GetBattlerUnitActor() { return nullptr; }

	int32 GetXCoord() const { return XCoord; }
	int32 GetYCoord() const { return YCoord; }

protected:

	virtual TSharedPtr<FUnitActionBase> SelectAction() = 0;

	TWeakObjectPtr<UAutoBattlerManager> CachedAutoBattlerManager;

private:
	int32 XCoord = 0;
	int32 YCoord = 0;

	TSharedPtr<FUnitActionBase> CurrentAction;
};