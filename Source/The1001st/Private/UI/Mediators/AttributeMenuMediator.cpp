// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mediators/AttributeMenuMediator.h"

#include "Data/DA_AttributeInformations.h"
#include "The1001stGameplayTags.h"

void UAttributeMenuMediator::BroadcastInitialValues()
{
	//ͨ��tag��DA�����õ���Ӧ��imformation
	check(this->DA_AttributeInformations);
	
	//�㲥��ʼֵ֮ǰ�Ĵ���������úã�����GetAttributeMenuMediator()֮ǰ
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AttributeSet);
	check(The1001stAttributeSet)
	for(auto & Pair : The1001stAttributeSet->GameplayTagToAttributeSignatureMap)
	{
		this->BroadcastAttributeChange(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuMediator::BindCallbacksToDependencies()
{
	//ͨ��tag��DA�����õ���Ӧ��imformation
	check(this->DA_AttributeInformations);

	//�㲥��ʼֵ֮ǰ�Ĵ���������úã�����GetAttributeMenuMediator()֮ǰ
	UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AttributeSet);
	check(The1001stAttributeSet)
	for (auto& Pair : The1001stAttributeSet->GameplayTagToAttributeSignatureMap)
	{
		//����Pair.Value���ص�һ������ָ�룬������()�õ�����
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda
		(
			//��ʵ���ﶼ������Data��
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
