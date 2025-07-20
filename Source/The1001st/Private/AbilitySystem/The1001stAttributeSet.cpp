// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAttributeSet.h"

#include "Net/UnrealNetwork.h"

UThe1001stAttributeSet::UThe1001stAttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);
	InitMana(25.0f);
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

void UThe1001stAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}


void UThe1001stAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//Saveһ��Effect���ݰ���
	SaveGameplayEffectData(Data, EffectProps);
}

void UThe1001stAttributeSet::SaveGameplayEffectData(const struct FGameplayEffectModCallbackData& Data, FEffectProperties EffectProperties)
{
	
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	//�õ�Source��ASC���ǵģ���������ȴ�һ��,�����е���ѧ
	//�ҵ�Context��û�б���Source��ASC������ô�õ��ģ����ұ�����Source��Ҳ��������һ�£�
	EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (EffectProperties.EffectContextHandle.IsValid() && EffectProperties.SourceASC)
	{
		EffectProperties.SourceAvatorActor = EffectProperties.SourceASC->AbilityActorInfo.Get()->AvatarActor.Get();
		//�������Controller�����������ģ��Ҷ�û��ֵ
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		if (EffectProperties.SourceController == nullptr)
		{
			APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatorActor);
			EffectProperties.SourceController = Pawn->GetController();
		}
		if(EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	EffectProperties.TargetASC = &Data.Target;

	if (EffectProperties.TargetASC)
	{
		EffectProperties.TargetAvatorActor = EffectProperties.TargetASC->GetAvatarActor();
		EffectProperties.TargetController = EffectProperties.TargetASC->AbilityActorInfo.Get()->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetController->GetPawn());
	}
}

