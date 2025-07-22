// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAbilitySystemComponent.h"

void UThe1001stAbilitySystemComponent::AbilitySystemComponentAlreadyInitInfo()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UThe1001stAbilitySystemComponent::OnEffectAppliedToSelf);
}

void UThe1001stAbilitySystemComponent::OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("OnGameplayEffectAppliedToSelf"))
	FGameplayTagContainer GameplayContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayContainer);
	GameplayTagsDelegate.Broadcast(GameplayContainer);
}
