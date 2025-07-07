// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "The1001stEffectActor.generated.h"

UCLASS()
class THE1001ST_API AThe1001stEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AThe1001stEffectActor();

protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* EffectSphere;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
public:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
