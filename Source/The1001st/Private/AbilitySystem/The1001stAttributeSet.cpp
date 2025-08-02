// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stAttributeSet.h"

#include "Net/UnrealNetwork.h"

#include "The1001stGameplayTags.h"

UThe1001stAttributeSet::UThe1001stAttributeSet()
{
	const FThe1001stGameplayTags& The1001stGameplayTags = FThe1001stGameplayTags::GetThe1001stGameplayTags();

	//template <typename RetValType, typename... ParamTypes, typename UserPolicy, typename... VarTypes>
	// 
	//���ﲻ��&Ҳ���ԣ����ĺ���������ʽת���ɺ�������ָ��

	//Primary Attribute
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Primary_Strength, &GetIntelliengenceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Primary_Resilience, &GetResilienceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Primary_Intelliengence, &GetIntelliengenceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Primary_Vigor, &GetVigorAttribute);

	//Secondary Attribute
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_Armor, &GetArmorAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_ArmorPenetration, &GetArmorPenetrationAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_BlockChance, &GetBlockChanceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_CriticalHitChance, &GetCriticalHitChanceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_CriticalHitDamage, &GetCriticalHitDamageAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_CriticalHitResistance, &GetCriticalHitResistanceAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_HealthRegeneration, &GetHealthRegenerationAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_ManaRegeneration, &GetManaRegenerationAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_MaxHealth, &GetMaxHealthAttribute);
	GameplayTagToAttributeSignatureMap.Add(The1001stGameplayTags.Attributes_Secondary_MaxMana, &GetMaxManaAttribute);
}

void UThe1001stAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//ע����� UE �˱�����Ҫ���縴�Ʋ�ͨ��On_Repͬ�����ͻ���
	//Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	//Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Intelliengence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	//Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UThe1001stAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
}

//Vital
void UThe1001stAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//�ȼ���GetOwningAbilitySystemComponent()->AttributeValueChanged.Broadcast(...);
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Health, OldHealth);
}
void UThe1001stAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Mana, OldMana);
}

//Primary
void UThe1001stAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Strength, OldStrength);
}
void UThe1001stAttributeSet::OnRep_Intelliengence(const FGameplayAttributeData& OldIntelliengence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Intelliengence, Intelliengence);
}
void UThe1001stAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Resilience, OldResilience);
}
void UThe1001stAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Vigor, OldVigor);
}

//Secondary
void UThe1001stAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, MaxHealth, OldMaxHealth);
}
//����Ǹ�const�ǰ�this��Ϊ��const
void UThe1001stAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, MaxMana, OldMaxMana);
}
void UThe1001stAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, Armor, OldArmor);
}
void UThe1001stAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, ArmorPenetration, OldArmorPenetration);
}
void UThe1001stAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, BlockChance, OldBlockChance);
}
void UThe1001stAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, CriticalHitChance, OldCriticalHitChance);
}
void UThe1001stAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
void UThe1001stAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
void UThe1001stAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, HealthRegeneration, OldHealthRegeneration);
}
void UThe1001stAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UThe1001stAttributeSet, ManaRegeneration, OldManaRegeneration);
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
	//Clamp in post is truly work, not pre
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
}

