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
	//����Ķ���
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	//GE���Բ�����
	FGameplayEffectAttributeCaptureDefinition VigorCaptureDefinition;
};
