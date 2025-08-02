// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mediators/OverlayMediator.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"





void UOverlayMediator::BroadcastInitialValues()
{
	UThe1001stAttributeSet* The1001stAttributeSet = CastChecked<UThe1001stAttributeSet>(AttributeSet);

	OnHealthValueChanged.Broadcast(The1001stAttributeSet->GetHealth());
	OnMaxHealthValueChanged.Broadcast(The1001stAttributeSet->GetMaxHealth());
	OnManaValueChanged.Broadcast(The1001stAttributeSet->GetMana());
	OnMaxManaValueChanged.Broadcast(The1001stAttributeSet->GetMaxMana());
}

void UOverlayMediator::BindCallbacksToDependencies()
{
	UThe1001stAttributeSet* The1001stAttributeSet = CastChecked<UThe1001stAttributeSet>(AttributeSet);

	//gas��AttributeSetֵ�޸�ʱ���ж�Ӧ�ص�����BroadcastInitialValues()��ʱ����԰�ί�У����յ������Ժ���Prefab�����µ�ֵ
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(The1001stAttributeSet->GetHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthValueChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(The1001stAttributeSet->GetMaxHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthValueChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(The1001stAttributeSet->GetManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaValueChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(The1001stAttributeSet->GetMaxManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaValueChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UThe1001stAbilitySystemComponent>(AbilitySystemComponent)->GameplayTagsDelegate.AddLambda
	(
		[this](const FGameplayTagContainer& GameplayContainer)
		{
			for (const FGameplayTag& Tag : GameplayContainer)
			{
				FGameplayTag MatchDadTag = FGameplayTag::RequestGameplayTag(FName("Messages"));
				if (Tag.MatchesTag(MatchDadTag))
				{
					FMessageTagRow *RowData = GetRowDataByGameplayTag<FMessageTagRow>(MessageDataTable, Tag);
					if(RowData)
					{
						OnMessageTagSignature.Broadcast(*RowData);
					}
				}
			}
		}
	);
}

