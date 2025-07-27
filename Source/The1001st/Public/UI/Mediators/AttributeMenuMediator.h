// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Mediators/BaseMediator.h"
#include "AttributeMenuMediator.generated.h"

class UDA_AttributeInformations;
struct FAttributeInformations;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeImformationChangedSignature, const FAttributeInformations&, AttributeInformation);
/**
 * 
 */
UCLASS()
class THE1001ST_API UAttributeMenuMediator : public UBaseMediator
{
	GENERATED_BODY()
public:
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeInfomations")
	TObjectPtr<UDA_AttributeInformations> DA_AttributeInformations;

public:
	UPROPERTY(BlueprintAssignable, Category = "Imformation")
	FOnAttributeImformationChangedSignature OnAttributeImformationChangedSignature;
};
