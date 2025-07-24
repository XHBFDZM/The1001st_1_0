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
	//最大健康
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxHealth);
	//最大魔力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxMana);
	//护甲
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Primary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Armor);
	//护甲穿透
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Primary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, ArmorPenetration);
	//格挡机会
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Primary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, BlockChance);
	//？？
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritialHitChange, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitChange;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitChange);
	//？？
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitDamage);
	//？？
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Primary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, CriticalHitResistance);
	//健康再生
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegneration, Category = "Primary Attributes")
	FGameplayAttributeData HealthRegneration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, HealthRegneration);
	//魔力再生
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegneration, Category = "Primary Attributes")
	FGameplayAttributeData ManaRegneration;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, ManaRegneration);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChange(const FGameplayAttributeData& OldCriticalHitChange) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegnerationh(const FGameplayAttributeData& OldHealthRegneration) const;
	UFUNCTION()
	void OnRep_ManaRegneration(const FGameplayAttributeData& OldManaRegneration) const;



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
