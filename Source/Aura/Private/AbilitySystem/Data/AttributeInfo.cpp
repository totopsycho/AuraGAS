// Copyright Tryktel.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))

		{
			return Info;
		}

	}

	if (bLogNotFound)
	{

		UE_LOG(LogTemp, Error, TEXT("Cant Find Info for attribute Tag[%s] on attribute info [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
