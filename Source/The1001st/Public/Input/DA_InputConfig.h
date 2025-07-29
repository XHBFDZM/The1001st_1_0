// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "DA_InputConfig.generated.h"

USTRUCT(BlueprintType)
struct FInputConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameplayTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* InputAction = nullptr;
};
/**
 * 
 */
UCLASS()
class THE1001ST_API UDA_InputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputConfig")
	TArray<FInputConfig> InputConfigs;
	UInputAction* GetInputActionThroughGameplayTag(FGameplayTag GameplayTag, bool bLogIfNotFind) const;
};
