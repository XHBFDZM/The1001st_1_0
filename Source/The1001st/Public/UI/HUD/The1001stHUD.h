// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "The1001stHUD.generated.h"

class UBasePrefab;
class UOverlayMediator;
class UAttributeMenuMediator;

struct FMediatorParams;

/**
 * 
 */
UCLASS()
class THE1001ST_API AThe1001stHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UBasePrefab* OverlayPrefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TSubclassOf<UBasePrefab> OverlayPrefabClass;

public:
	UOverlayMediator* GetOverlayMediator(const FMediatorParams& Params);
	UPROPERTY()
	TObjectPtr<UOverlayMediator> OverlayMediator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Overlay")
	TSubclassOf<UOverlayMediator> OverlayMediatorClass;

public:
	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

public:
	UAttributeMenuMediator* GetAttributeMenuMediator(const FMediatorParams& Params);
	UPROPERTY()
	UAttributeMenuMediator* AttributeMenuMediator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeMenu")
	TSubclassOf<UAttributeMenuMediator> AttributeMenuMediatorClass;
};
