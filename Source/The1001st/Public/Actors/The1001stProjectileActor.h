// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "The1001stProjectileActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class THE1001ST_API AThe1001stProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AThe1001stProjectileActor();

protected:
	virtual void BeginPlay() override;

/*Åö×²*/
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComponent;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

/*ÔË¶¯*/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;
};
