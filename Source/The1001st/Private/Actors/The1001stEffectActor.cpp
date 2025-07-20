// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/The1001stEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "GameplayEffect.h"

// Sets default values
AThe1001stEffectActor::AThe1001stEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Use Scene to as RootComponent
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

// Called when the game starts or when spawned
void AThe1001stEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AThe1001stEffectActor::ApplyGameplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> UsedGameplayEffectClass)
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!AbilitySystemComponent)
	{
		return;
	}
	check(UsedGameplayEffectClass);

	//简单来说，TargetASC->Context句柄->EffectSpec句柄->EffectSpec->Effect

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);


	FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(UsedGameplayEffectClass, EffectLevel, EffectContextHandle);

	//This apply will return an active GameplayEffectHandle, 我可以 store it
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	//如果是Inifinate的Effect，Need to store it through a map
	if (GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		ActiveHandleToASCMap.Add(ActiveGameplayEffectHandle, AbilitySystemComponent);
	}
}

void AThe1001stEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectApplyPolicy == EGameplayEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationGameplayEffectApplyPolicy == EGameplayEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteGameplayEffectApplyPolicy == EGameplayEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}
void AThe1001stEffectActor::EndOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectApplyPolicy == EGameplayEffectApplyPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	// Policy did is RemoveOnEndOverlap
	if (InfiniteGameplayEffectRemovePolicy == EGameplayEffectRemovePolicy::RemoveOnEndOverlap)
	{
		//ASC 确实Exist
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (AbilitySystemComponent)
		{
			//移除Effect first,then 移除 Map's key
			TArray<FActiveGameplayEffectHandle> ActivehHandlesNeedToRemove;
			for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> CurTuple : ActiveHandleToASCMap)
			{
				if (AbilitySystemComponent == CurTuple.Value)
				{
					ActivehHandlesNeedToRemove.Add(CurTuple.Key);
					AbilitySystemComponent->RemoveActiveGameplayEffect(CurTuple.Key,1);
				}
			}
			for (FActiveGameplayEffectHandle CurActiveHandle: ActivehHandlesNeedToRemove)
			{
				ActiveHandleToASCMap.FindAndRemoveChecked(CurActiveHandle);
			}
		}
	}
}



