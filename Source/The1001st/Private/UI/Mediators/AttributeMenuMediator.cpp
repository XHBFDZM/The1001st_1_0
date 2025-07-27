// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mediators/AttributeMenuMediator.h"

#include "Data/DA_AttributeInformations.h"
#include "AbilitySystem/The1001stAttributeSet.h"
#include "The1001stGameplayTags.h"

void UAttributeMenuMediator::BroadcastInitialValues()
{
	//全局唯一GameTags
	FThe1001stGameplayTags The1001stGameplayTags = FThe1001stGameplayTags::GetThe1001stGameplayTags();
	//通过tag在DA里面拿到对应的imformation
	check(DA_AttributeInformations);
	FAttributeInformations AttributeInformations = DA_AttributeInformations->FindAttributeInformationThroughTag(The1001stGameplayTags.Attributes_Primary_Strength, true);

	//广播初始值之前四大参数得设置好，及在GetAttributeMenuMediator()之前
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AttributeSet);
	check(The1001stAttributeSet)
	float LengthValue = The1001stAttributeSet->GetStrength();

	AttributeInformations.AttributeValue = LengthValue;

	OnAttributeImformationChangedSignature.Broadcast(AttributeInformations);
}

void UAttributeMenuMediator::BindCallbacksToDependencies()
{
}
