// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "DA_AttributeInformations.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAttributeInformations
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FGameplayTag AttributeTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FName AttributeName = FName();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	FName AttributeDescription = FName();
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	float AttributeValue = 0.0f;
};

UCLASS()
class THE1001ST_API UDA_AttributeInformations : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TArray<FAttributeInformations> AttributeInformations;
	UFUNCTION()
	FAttributeInformations FindAttributeInformationThroughTag(const FGameplayTag& AttributeTag, bool bLogIfNotFind);
};
