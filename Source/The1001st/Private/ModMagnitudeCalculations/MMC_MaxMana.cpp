// Fill out your copyright notice in the Description page of Project Settings.


#include "ModMagnitudeCalculations/MMC_MaxMana.h"

#include "AbilitySystem/The1001stAttributeSet.h"

#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelliengenceAttributeCaptureDefinition.AttributeToCapture = UThe1001stAttributeSet::GetIntelliengenceAttribute();
	IntelliengenceAttributeCaptureDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelliengenceAttributeCaptureDefinition.bSnapshot = false;
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	check(CombatInterface);

	float Level = CombatInterface->GetOwnerLevel();

	float CaptureIntelliengenceValue = 0.0f;

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	GetCapturedAttributeMagnitude(IntelliengenceAttributeCaptureDefinition, Spec, EvaluationParameters, CaptureIntelliengenceValue);
	CaptureIntelliengenceValue = FMath::Max<float>(CaptureIntelliengenceValue, 0.0f);

	return 50.0f + Level * 15.0f + CaptureIntelliengenceValue * 2.5f;
}