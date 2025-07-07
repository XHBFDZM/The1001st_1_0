// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/The1001stHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Prefabs/BasePrefab.h"

void AThe1001stHUD::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (!World)   
	{
		return;
	}
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(World, OverlayPrefabClass);
	UserWidget->AddToViewport();
}