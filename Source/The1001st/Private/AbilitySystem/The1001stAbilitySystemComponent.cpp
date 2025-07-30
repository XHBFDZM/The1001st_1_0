// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

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

//������������ֻ����SetupGameplayTag��Ability�ŻᱻӦ�ã��Ҳ����Զ�����
void UThe1001stAbilitySystemComponent::ApplySetupAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities)
{
	for(TSubclassOf<UGameplayAbility> & AbilityClass : Abilities)
	{
		if (AbilityClass)
		{

			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this);

			UBaseGameplayAbility* BaseGameplayAbility = Cast<UBaseGameplayAbility>(AbilitySpec.Ability);
			if (BaseGameplayAbility && BaseGameplayAbility->SetupInputTag.IsValid())
			{
				AbilitySpec.DynamicAbilityTags.AddTag(BaseGameplayAbility->SetupInputTag);

				GiveAbility(AbilitySpec);

				//���������const AbilitySpec
				//GiveAbilityAndActivateOnce
			}
		}
	}
}

void UThe1001stAbilitySystemComponent::InputAbilityHeld(const FGameplayTag& GameplayTag)
{
	if (!GameplayTag.IsValid())
	{
		return;
	}
	TArray<FGameplayAbilitySpec>& AllActivatableAbilities = GetActivatableAbilities();
	for (FGameplayAbilitySpec& CurSpec : AllActivatableAbilities)
	{
		if (CurSpec.Ability && CurSpec.DynamicAbilityTags.HasTag(GameplayTag))
		{
			AbilitySpecInputPressed(CurSpec);
			if (CurSpec.IsActive())
			{
				//����Ѿ������˾Ͳ��ټ���
				continue; 
			}
			else
			{
				//����Ϊʲô����Spec����Handle�����岻��
				TryActivateAbility(CurSpec.Handle);
			}
		}
	}
}
void UThe1001stAbilitySystemComponent::InputAbilityReleased(const FGameplayTag& GameplayTag)
{
	if (!GameplayTag.IsValid())
	{
		return;
	}
	TArray<FGameplayAbilitySpec>& AllActivatableAbilities = GetActivatableAbilities();
	for (FGameplayAbilitySpec& CurSpec : AllActivatableAbilities)
	{
		if (CurSpec.Ability && CurSpec.DynamicAbilityTags.HasTag(GameplayTag))
		{
			AbilitySpecInputReleased(CurSpec);
		}
	}
}
