// Fill out your copyright notice in the Description page of Project Settings.


#include "ModMagnitudeCalculations/MMC_MaxHealth.h"

#include "AbilitySystem/The1001stAttributeSet.h"

#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//Ҫ�����Attribute���ࡷ��ֻ���࣬����ʵ����
	VigorCaptureDefinition.AttributeToCapture = UThe1001stAttributeSet::GetVigorAttribute();
	//����GE Target��Vigor�������Լ���
	VigorCaptureDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//��GE Applyʱ�޸Ķ��ǲ���ʱ�޸�
	VigorCaptureDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorCaptureDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//���� GAS �ҵ�ǰ��������ֵʱ��Ҫ����˭���ϵı�ǩ
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	float CaptureVigorValue;
	//��ȡ�Ѳ�������ֵ
	GetCapturedAttributeMagnitude(VigorCaptureDefinition, Spec, AggregatorEvaluateParameters, CaptureVigorValue);
	CaptureVigorValue = FMath::Max<float>(CaptureVigorValue, 0.0f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	check(CombatInterface);

	return 80.0f + CaptureVigorValue * 2.5f + CombatInterface->GetOwnerLevel();


	//������Considerһ��ͨ��MMC���޸�һ��Vigorֵ��Ҫ��Щ����
	// �����ҵ���Vigor->�ҵ��õ�Target��Vigor->��ô�Ҿ�Ҫ�õ�AttributeSet���VigorValue

	// �ҵ���Level��Level��SourceObject��CastICombatInterface�õ�

	// ������֪������Spec��ֱ��ͨ��Context�����õ����ؼ�����ǰ��
	// 
	// Ϊʲô�Ҳ�ֱ��ͨ��Spec�õ�Target�أ����У���Ϊ�����Ļ�Spec������Target������
	//
	// �������°취����˵GetCapturedAttributeMagnitude���������ͨ���趨��������ĸ�ASData��GE��˭���ϵ�AS��ʲôʱ�򲶻񣩣��Լ�Specʵ�����Լ������tags������ͨ��tags�õ���Ӧ��Value
}
