// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAbilitySystemComponent.h"

#include "Abilities/GameplayAbility.h"

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

void UThe1001stAbilitySystemComponent::ApplyAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
	for(auto& Ability : Abilities)
	{
		if (Ability)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this);

			//GiveAbility(AbilitySpec);

			//这个不能是const AbilitySpec
			GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}
