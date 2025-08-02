// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "The1001stAbilitySystemComponent.generated.h"

class UGameplayAbility;

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayTagsDelegate, const FGameplayTagContainer& Container);

UCLASS()
class THE1001ST_API UThe1001stAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	//已经初始化好了，可以绑定委托了
	void AbilitySystemComponentAlreadyInitInfo();

public:
	FGameplayTagsDelegate GameplayTagsDelegate;

public:
	//标记为Client与Reliable，表示这个函数会在Server调用，在Client执行，并且可靠(不丢包)
	UFUNCTION(Client,Reliable)
	void Client_OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

/*初始应用SetupAbility*/
public:
	void ApplySetupAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);

/*根据Input开关Ability*/
public:
	void InputAbilityHeld(const FGameplayTag& GameplayTag);
	void InputAbilityReleased(const FGameplayTag& GameplayTag);
};
