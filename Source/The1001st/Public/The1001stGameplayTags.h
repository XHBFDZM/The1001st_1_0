// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

/**
 * 全局唯一实例
 */
struct FThe1001stGameplayTags
{
public:
	static FThe1001stGameplayTags & GetThe1001stGameplayTags();
	static void InitializeThe1001stGameplayTags();
private:
	static FThe1001stGameplayTags The1001stGameplayTags;
public:
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Intelliengence;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
public:
	FGameplayTag Input_Dot1;
	FGameplayTag Input_Dot2;
	FGameplayTag Input_Dot3;
	FGameplayTag Input_Dot4;
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
};
