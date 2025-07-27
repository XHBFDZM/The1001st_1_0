// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

#include "The1001stAttributeSet.generated.h"

 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
//Just 一个结构体 about Effect的相关信息
USTRUCT()
struct FEffectProperties {
	GENERATED_BODY()
	FEffectProperties(){}
	//来源
	UPROPERTY()
	ACharacter* SourceCharacter;
	UPROPERTY()
	AController* SourceController;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
	UPROPERTY()
	AActor* SourceAvatorActor;
	//目标
	UPROPERTY()
	ACharacter* TargetCharacter;
	UPROPERTY()
	AController* TargetController;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC;
	UPROPERTY()
	AActor* TargetAvatorActor;
	//你保存上下文干嘛
	FGameplayEffectContextHandle EffectContextHandle;
};


UCLASS()
class THE1001ST_API UThe1001stAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UThe1001stAttributeSet();

	//现在不太需要知道这是在干嘛
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Primary
	//力量
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Strength);

	//智慧
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelliengence, Category = "Primary Attributes")
	FGameplayAttributeData Intelliengence;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Intelliengence);
	//韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Resilience);
	//活力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelliengence(const FGameplayAttributeData& OldIntelliengence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	//Vital
	//健康
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Health);
	//魔力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//Secondary

	//护甲,基于韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Armor);
	//护甲穿透，基于韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, ArmorPenetration);
	//格挡机会，基于韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, BlockChance);
	//暴击几率，基于护甲穿透
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitChance);
	//暴击伤害，基于护甲穿透
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitDamage);
	//暴击抗性，基于护甲
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitResistance);
	//健康再生，基于活力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, HealthRegeneration);
	//魔力再生，基于智慧
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, ManaRegeneration);
	//最大健康，基于活力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxHealth);
	//最大魔力，基于智慧
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;



public:
	//做个Clamp而已
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//数据修改前的核心Deal
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

//保存Effect Apply的信息
public:
	FEffectProperties EffectProps;
private:
	void SaveGameplayEffectData(const struct FGameplayEffectModCallbackData& Data, FEffectProperties EffectProperties);
};
