// Copyright Tryktel.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	

	virtual void HighlightActor() override;
	virtual void UnHightlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHightlighted = false;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;


	
};
