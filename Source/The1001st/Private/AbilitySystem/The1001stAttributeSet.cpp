// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAttributeSet.h"
#include "Net/UnrealNetwork.h"

UThe1001stAttributeSet::UThe1001stAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitMana(50.0f);
	InitMaxMana(50.0f);
}

void UThe1001stAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//ע����� UE ���������Ҫͬ����
	//Ѫ��
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	//����
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UThe1001stAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//��Ҫ#include "AbilitySystem/The1001stAbilitySystemComponent.h"
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Health, OldHealth);
}

void UThe1001stAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Health, OldMaxHealth);
}

void UThe1001stAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Mana, OldMana);
}

//����Ǹ�const�ǰ�this��Ϊ��const
void UThe1001stAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, MaxMana, OldMaxMana);
}

