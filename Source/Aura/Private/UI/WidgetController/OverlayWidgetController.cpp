// Copyright Tryktel.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"






void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());



}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//Note : Si c'est pas un dynamic multicast, on utilise AddUObject sinon AddDynamic mais mieux AddLambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) 
			{
				OnHealthChanged.Broadcast(Data.NewValue); 
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		//20-6 Del�leger les abilit�s dans la fonction OnInitializeStartUpAbilities uniquement si ils n'ont pas d�ja �t� activ�es
		if (AuraASC->bStartUpAbilitiesGiven)
		{
			//Si les abiliti�s ont d�ja �t� acquises alors on est pas oblig� d'utiliser le delegate
			OnInitializeStartUpAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartUpAbilities);
		}
		
		AuraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (auto Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartUpAbilities(UAuraAbilitySystemComponent* AuraASC)
{
	if (!AuraASC->bStartUpAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, AuraASC](const FGameplayAbilitySpec& AbilitySpec) 
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraASC->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = AuraASC->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);

		});

	AuraASC->ForEachAbility(BroadcastDelegate);
}

