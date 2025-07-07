// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasePrefab.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API UBasePrefab : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Prefab")
	void SetOwnerMediator(UObject* InOwnerMediator);
public:
	UPROPERTY(BlueprintReadOnly, Category = "Prefab")
	TObjectPtr<UObject> OwnerMediator;
protected:
	UFUNCTION(BlueprintimplementableEvent, Category = "Prefab")
	void OwnerMediatorIsSetted();
};
