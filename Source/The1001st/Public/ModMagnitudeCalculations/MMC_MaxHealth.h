// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxHealth();
public:
	//计算的定义
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	//GE属性捕获定义
	FGameplayEffectAttributeCaptureDefinition VigorCaptureDefinition;
};
