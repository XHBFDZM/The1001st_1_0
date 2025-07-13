// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseMediator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthValueChangeSignature, float, NewHealthValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthValueChangeSignature, float, NewMaxHealthValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaValueChangeSignature, float, NewManaValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaValueChangeSignature, float, NewMaxManaValue);

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FMediatorParams
{
	// Add parameters for widget controller here
	GENERATED_BODY()

	FMediatorParams() {}
	FMediatorParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		:PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {
	}
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Mediator")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mediator")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mediator")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mediator")
	TObjectPtr<UAttributeSet> AttributeSet;
};
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class THE1001ST_API UBaseMediator : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetParams(const FMediatorParams& Params);

protected:

	UPROPERTY(BlueprintReadOnly,Category = "Mediator")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category = "Mediator")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly, Category = "Mediator")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Mediator")
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthValueChangeSignature OnHealthValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthValueChangeSignature OnMaxHealthValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaValueChangeSignature OnManaValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaValueChangeSignature OnMaxManaValueChanged;
	//π„≤•≥ı º÷µ

	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
};
