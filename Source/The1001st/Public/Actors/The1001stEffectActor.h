// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ActiveGameplayEffectHandle.h"

#include "The1001stEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EGameplayEffectApplyPolicy : uint8 {
	DoNotApply,
	ApplyOnOverlap,
	ApplyOnEndOverlap
};

UENUM(BlueprintType)
enum class EGameplayEffectRemovePolicy : uint8 {
	DoNotRemove,
	RemoveOnEndOverlap
};

UCLASS()
class THE1001ST_API AThe1001stEffectActor : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool bDestroyOnEndOverlap = true;
public:
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);
	
public:	
	AThe1001stEffectActor();

protected:
	virtual void BeginPlay() override;
protected:
	//Effect which Use on Actor
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Effect")
	EGameplayEffectApplyPolicy InstantGameplayEffectApplyPolicy = EGameplayEffectApplyPolicy::DoNotApply;


	//Effect which Use on Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	EGameplayEffectApplyPolicy DurationGameplayEffectApplyPolicy = EGameplayEffectApplyPolicy::DoNotApply;


	//Effect which Use on Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	EGameplayEffectApplyPolicy InfiniteGameplayEffectApplyPolicy = EGameplayEffectApplyPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	EGameplayEffectRemovePolicy InfiniteGameplayEffectRemovePolicy = EGameplayEffectRemovePolicy::RemoveOnEndOverlap;

protected:
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyGameplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> UsedGameplayEffectClass);
public:
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveHandleToASCMap;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	float EffectLevel = 1.0f;
};
