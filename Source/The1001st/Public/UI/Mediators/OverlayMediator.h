// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Mediators/BaseMediator.h"

#include "AbilitySystem/The1001stAttributeSet.h"

#include "OverlayMediator.generated.h"


class UThe1001stAbilitySystemComponent;
class UGameplayEffectTypes;
/**
 * 
 */
UCLASS()
class THE1001ST_API UOverlayMediator : public UBaseMediator
{
	GENERATED_BODY()
public:
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;
public:
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
};
