// Fill out your copyright notice in the Description page of Project Settings.


#include "ModMagnitudeCalculations/MMC_MaxHealth.h"

#include "AbilitySystem/The1001stAttributeSet.h"

#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//要捕获的Attribute《类》（只是类，不是实例）
	VigorCaptureDefinition.AttributeToCapture = UThe1001stAttributeSet::GetVigorAttribute();
	//基于GE Target的Vigor，而非自己的
	VigorCaptureDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//在GE Apply时修改而非捕获时修改
	VigorCaptureDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorCaptureDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//告诉 GAS 我当前计算属性值时，要考虑谁身上的标签
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	float CaptureVigorValue;
	//获取已捕获属性值
	GetCapturedAttributeMagnitude(VigorCaptureDefinition, Spec, AggregatorEvaluateParameters, CaptureVigorValue);
	CaptureVigorValue = FMath::Max<float>(CaptureVigorValue, 0.0f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	check(CombatInterface);

	return 80.0f + CaptureVigorValue * 2.5f + CombatInterface->GetOwnerLevel();


	//我们来Consider一下通过MMC来修改一个Vigor值需要哪些东西
	// 首先我得有Vigor->我得拿到Target的Vigor->那么我就要拿到AttributeSet里的VigorValue

	// 我得有Level，Level是SourceObject中CastICombatInterface得到

	// 后者我知道，有Spec则直接通过Context可以拿到，关键在于前者
	// 
	// 为什么我不直接通过Spec拿到Target呢，不行，因为这样的话Spec又有了Target的引用
	//
	// 现在想新办法，传说GetCapturedAttributeMagnitude这个函数，通过设定捕获规则（哪个ASData，GE在谁身上的AS，什么时候捕获），以及Spec实例，以及捕获的tags，可以通过tags拿到对应的Value
}
