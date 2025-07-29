// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mediators/AttributeMenuMediator.h"

#include "Data/DA_AttributeInformations.h"
#include "The1001stGameplayTags.h"

void UAttributeMenuMediator::BroadcastInitialValues()
{
	//通过tag在DA里面拿到对应的imformation
	check(this->DA_AttributeInformations);
	
	//广播初始值之前四大参数得设置好，及在GetAttributeMenuMediator()之前
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AttributeSet);
	check(The1001stAttributeSet)
	for(auto & Pair : The1001stAttributeSet->GameplayTagToAttributeSignatureMap)
	{
		this->BroadcastAttributeChange(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuMediator::BindCallbacksToDependencies()
{
	//通过tag在DA里面拿到对应的imformation
	check(this->DA_AttributeInformations);

	//广播初始值之前四大参数得设置好，及在GetAttributeMenuMediator()之前
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AttributeSet);
	check(The1001stAttributeSet)
	for (auto& Pair : The1001stAttributeSet->GameplayTagToAttributeSignatureMap)
	{
		//这里Pair.Value返回的一个函数指针，所以用()得到函数
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda
		(
			//其实这里都不用拿Data的
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				this->BroadcastAttributeChange(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuMediator::BroadcastAttributeChange(FGameplayTag GameplayTag,FGameplayAttribute GamelayAttribute)
{
	check(this->DA_AttributeInformations);
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(this->AttributeSet);
	check(The1001stAttributeSet);
	float CurValue = GamelayAttribute.GetNumericValueChecked(The1001stAttributeSet);
	FAttributeInformations CurAttributeInformation = this->DA_AttributeInformations->FindAttributeInformationThroughTag(GameplayTag, true);
	CurAttributeInformation.AttributeValue = CurValue;
	OnAttributeImformationChangedSignature.Broadcast(CurAttributeInformation);
}
