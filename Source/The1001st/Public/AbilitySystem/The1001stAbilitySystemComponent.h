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
	//�Ѿ���ʼ�����ˣ����԰�ί����
	void AbilitySystemComponentAlreadyInitInfo();

public:
	FGameplayTagsDelegate GameplayTagsDelegate;

public:
	//���ΪClient��Reliable����ʾ�����������Server���ã���Clientִ�У����ҿɿ�(������)
	UFUNCTION(Client,Reliable)
	void Client_OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

/*��ʼӦ��SetupAbility*/
public:
	void ApplySetupAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);

/*����Input����Ability*/
public:
	void InputAbilityHeld(const FGameplayTag& GameplayTag);
	void InputAbilityReleased(const FGameplayTag& GameplayTag);
};
