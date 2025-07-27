// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001stAssetManager.h"

#include "The1001stGameplayTags.h"

UThe1001stAssetManager& UThe1001stAssetManager::GetThe1001stAssetManager()
{
	check(GEngine);

	UThe1001stAssetManager* The1001stAssetManager = Cast<UThe1001stAssetManager>(GEngine->AssetManager);
	return *The1001stAssetManager;
}

void UThe1001stAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FThe1001stGameplayTags::InitializeThe1001stGameplayTags();
}
