// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/The1001stEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"

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

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(UsedGameplayEffectClass, 1.0f, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
}



