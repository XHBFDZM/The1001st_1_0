// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "The1001stBlueprintFuncLib.generated.h"

/**
 * 
 */
class UOverlayMediator;
class UAttributeMenuMediator;

UCLASS()
class THE1001ST_API UThe1001stBlueprintFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "The1001stBlueprintFuncLib|UI|Mediator")
	static UOverlayMediator* GetOverlayMediator(UObject* WorldContext);

	UFUNCTION(BlueprintPure, Category = "The1001stBlueprintFuncLib|UI|Mediator")
	static UAttributeMenuMediator* GetAttributeMenuMediator(UObject* WorldContext);
};
