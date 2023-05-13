#pragma once

#include "AutoBattler/AutoBattlerUnit.h"

#include "AutoBattlerUnitActor.generated.h"

class UAttackComponent;
class UFactionComponent;
class UHealthComponent;
class FUnitActionBase;
class UUnitActionFactoryBase;

/** AAutoBattlerUnitActor
*
* All units that want to be visual in the world should derrive from this
*/
UCLASS()
class AAutoBattlerUnitActor : public AActor, public IAutoBattlerUnit
{
	GENERATED_BODY()
	
public: // Blueprint

public: // C++

	AAutoBattlerUnitActor();

	//~ Begin IAutoBattlerUnit Interface
	virtual void OnAddedToManager(UAutoBattlerManager* Manager, int32 X, int32 Y) override;
	virtual void OnRemovedFromManager() override;
	virtual AActor* GetBattlerUnitActor() { return this; }
	//~ End IAutoBattlerUnit Interface

	UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	UFactionComponent* GetFactionComponent() const { return FactionComponent; }
	UAttackComponent* GetAttackComponent() const { return AttackComponent; }

protected:

	//~ Begin IAutoBattlerUnit Interface
	virtual TSharedPtr<FUnitActionBase> SelectAction();
	//~ End IAutoBattlerUnit Interface
	
protected: // Blueprint

	// Factories used to create actions, the factories at the start of the array take priority
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UUnitActionFactoryBase*> Factories;

protected: // C++

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UFactionComponent* FactionComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAttackComponent* AttackComponent = nullptr;

private: // Blueprint

private: // C++

};
