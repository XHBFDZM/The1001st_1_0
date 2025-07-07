// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "The1001stHUD.generated.h"

class UBasePrefab;
class UOverlayMediator;

struct FMediatorParams;

/**
 * 
 */
UCLASS()
class THE1001ST_API AThe1001stHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UBasePrefab* OverlayPrefab;

	UOverlayMediator* GetOverlayMediator(const FMediatorParams& Params);

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TSubclassOf<UBasePrefab> OverlayPrefabClass;

	UPROPERTY()
	TObjectPtr<UOverlayMediator> OverlayMediator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TSubclassOf<UOverlayMediator> OverlayMediatorClass;
public:
	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
