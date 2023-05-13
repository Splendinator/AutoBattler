#pragma once

class IAutoBattlerUnit;
class UAutoBattlerManager;

/** FUnitActionBase
*
* This class is used to define an action that an auto battler unit can take
*/
class FUnitActionBase
{	
public: // C++

	// Fired once when the action starts, Should be deteministic
	virtual void StartExecutingAction(IAutoBattlerUnit* Unit) {}

	// This should be overwritten to execute the action. This function should be deterministic as it will be called on the server and clients.
	virtual void ExecuteAction(IAutoBattlerUnit* Unit) PURE_VIRTUAL(FUnitActionBase::ExecuteAction, );

	// This should be overwritten to lerp the action over time if that can be done. 
	// This doesn't have to be deterministic but it shouldn't change any game state. It should be used for client side graphics
	// LerpPct will be spread across all turns (i.e 5 turns will mean after turn 1 we're at 0.2)
	virtual void LerpAction(IAutoBattlerUnit* Unit, float LerpPct) {};

	// Overwrite with the number of turns to execute an action
	virtual int32 GetNumTurnsToExecute() const { return 1; }
	
	// Overwrite to check if the action can execute (important for multi turn ones in case circumstances change)
	virtual bool CanExecute() const { return true; }

	void Initialise(UAutoBattlerManager* AutoBattlerManager);

	int32 CurrentTurn = 0;

protected: // Blueprint

protected: // C++

	TWeakObjectPtr<UAutoBattlerManager> CachedAutoBattlerManager;

private: // Blueprint

private: // C++

};
