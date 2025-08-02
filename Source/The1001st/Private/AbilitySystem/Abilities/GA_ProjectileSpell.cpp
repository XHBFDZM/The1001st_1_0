// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_ProjectileSpell.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Interaction/CombatInterface.h"

void UGA_ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	//仅Server运行
	if (!HasAuthority(&ActivationInfo))
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(ActorInfo->AvatarActor.Get());
	if (CombatInterface && ProjectileActor)
	{
		FTransform ActorTransform;
		//Instigater是责任来源
		AThe1001stProjectileActor* ProjectileActorInstance = GetWorld()->SpawnActorDeferred<AThe1001stProjectileActor>(ProjectileActor, ActorTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		ActorTransform.SetLocation(CombatInterface->GetWeaponSocketLocation());
		ProjectileActorInstance->FinishSpawning(ActorTransform);
	}	
}
