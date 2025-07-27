// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "The1001stAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API UThe1001stAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UThe1001stAssetManager& GetThe1001stAssetManager();
protected:
	void StartInitialLoading() override;
};
