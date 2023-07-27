// Copyright Tryktel.


#include "AbilitySystem/Data/AbilityInfo.h"


FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)

	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AbilityTag [%s] on Ability Info [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAbilityInfo();
}
