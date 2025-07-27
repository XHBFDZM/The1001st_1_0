// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/The1001stPlayerState.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

#include "Net/UnrealNetwork.h"

AThe1001stPlayerState::AThe1001stPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UThe1001stAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UThe1001stAttributeSet>(TEXT("AttributeSet"));
}

void AThe1001stPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AThe1001stPlayerState, Level, COND_None, REPNOTIFY_Always);
}

UAbilitySystemComponent* AThe1001stPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AThe1001stPlayerState::OnRep_LevelChange(int32 OldLevel)
{

}

int32 AThe1001stPlayerState::GetOwnerLevel()
{
	return Level;
}
