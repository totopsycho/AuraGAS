// Copyright Tryktel.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * Tous nos user widgets nécessitant un callback (d'attributs majoritairement) sont dérivés de ce user widget
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Permet d'initialiser le widget controller à l'intérieur d'un user widget
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//Permet de lier le widget controller avec le user widget dans lequel on se trouve
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//Dès que le widget controller est initialiser, l'event permet d'éditer les paramètres dans le blueprint 
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
