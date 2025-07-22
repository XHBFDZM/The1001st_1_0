// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "The1001stAbilitySystemComponent.generated.h"

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

	FGameplayTagsDelegate GameplayTagsDelegate;
public:
	void OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
