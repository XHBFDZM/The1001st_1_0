// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/The1001stPlayerState.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

AThe1001stPlayerState::AThe1001stPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UThe1001stAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UThe1001stAttributeSet>(TEXT("AttributeSet"));

}
UAbilitySystemComponent* AThe1001stPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
