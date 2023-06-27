// Copyright Tryktel.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * Use as template for future GAS Project (derived from asset manager class)
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UAuraAssetManager& Get();
	
protected:

	virtual void StartInitialLoading() override;
};
