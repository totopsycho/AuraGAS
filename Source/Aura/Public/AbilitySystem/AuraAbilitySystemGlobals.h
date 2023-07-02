// Copyright Tryktel.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * Permet d'utiliser le FGameplayEffectContext que nous avons crée dans AuraAbilityTypes.h. Attention, il faut ajouter dans le fichier config
 * Defaultgame.ini [/Script/GameplayAbilities.AbilitySystemGlobals]
+AbilitySystemGlobalsClassName="/Script/Aura.AuraAbilitySystemGlobals"

 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
