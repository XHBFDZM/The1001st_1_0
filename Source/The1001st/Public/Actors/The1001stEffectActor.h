// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "The1001stEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class THE1001ST_API AThe1001stEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AThe1001stEffectActor();

protected:
	virtual void BeginPlay() override;
protected:
	//Effect which Use on Actor
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	//Effect which Use on Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
protected:
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyGameplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> UsedGameplayEffectClass);
};
