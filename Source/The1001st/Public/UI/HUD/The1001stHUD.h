// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "The1001stHUD.generated.h"

class UBasePrefab;

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
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TSubclassOf<UBasePrefab> OverlayPrefabClass;
};
