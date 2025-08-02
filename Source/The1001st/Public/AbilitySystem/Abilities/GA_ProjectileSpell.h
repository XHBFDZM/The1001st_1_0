// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

#include "Actors/The1001stProjectileActor.h"

#include "GA_ProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API UGA_ProjectileSpell : public UBaseGameplayAbility
{
	GENERATED_BODY()
/*º§ªÓƒ‹¡¶*/
public:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

/*ProjectileClass*/
public:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AThe1001stProjectileActor> ProjectileActor;
};
