// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Character/The1001stCharacterBase.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"

#include "Abilities/GameplayAbility.h"

AThe1001stCharacterBase::AThe1001stCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AThe1001stCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AThe1001stCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AThe1001stCharacterBase::InitAbilityInfo()
{

}

void AThe1001stCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const
{
	check(GameplayEffect);
	if (GameplayEffect)
	{
		UAbilitySystemComponent* CurAbilitySystemComponent = GetAbilitySystemComponent();
		if (CurAbilitySystemComponent)
		{
			FGameplayEffectContextHandle GameplayEffectContextHandle = CurAbilitySystemComponent->MakeEffectContext();
			GameplayEffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle GameplayEffectSpecHandle = CurAbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, Level, GameplayEffectContextHandle);
			FGameplayEffectSpec* GameplayEffectSpec = GameplayEffectSpecHandle.Data.Get();

			CurAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpec, CurAbilitySystemComponent);
		}
	}
}

void AThe1001stCharacterBase::InitializeDefaultAttributes() const
{
	ApplyGameplayEffectToSelf(PrimaryAttributeInitialEffect, 1.0f);

	ApplyGameplayEffectToSelf(SecondaryAttributeInitialEffect, 1.0f);

	ApplyGameplayEffectToSelf(VitalAttributeInitialEffect, 1.0f);
}

void AThe1001stCharacterBase::InitializeDefaultAbilities() const
{
}



