// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001stGameplayTags.h"

#include "GameplayTagsManager.h"

FThe1001stGameplayTags FThe1001stGameplayTags::The1001stGameplayTags;

FThe1001stGameplayTags& FThe1001stGameplayTags::GetThe1001stGameplayTags()
{
	return The1001stGameplayTags;
}

void FThe1001stGameplayTags::InitializeThe1001stGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	//Primary Attributes
	The1001stGameplayTags.Attributes_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Primary.Strength")), FString(TEXT("Add Physical Damage.")));
	The1001stGameplayTags.Attributes_Primary_Resilience = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Primary.Resilience")), FString(TEXT("Influence Armor and ArmorPenetration.")));
	The1001stGameplayTags.Attributes_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Primary.Vigor")), FString(TEXT("Influence MaxHealth and HealthRegeneration.")));
	The1001stGameplayTags.Attributes_Primary_Intelliengence = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Primary.Intelliengence")), FString(TEXT("Influence MaxMana and ManaRegeneration.")));

	//Secondary Attributes
	The1001stGameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.Armor")), FString(TEXT("Influence CriticalHit.")));
	The1001stGameplayTags.Attributes_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.ArmorPenetration")), FString(TEXT("Influence CriticalHit and BlockChance.")));
	The1001stGameplayTags.Attributes_Secondary_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.CriticalHitChance")), FString(TEXT("Add CriticalHitChance.")));
	The1001stGameplayTags.Attributes_Secondary_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.CriticalHitDamage")), FString(TEXT("Add CriticalHitDamage.")));
	The1001stGameplayTags.Attributes_Secondary_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.CriticalHitResistance")), FString(TEXT("Add CriticalHitResistance.")));
	The1001stGameplayTags.Attributes_Secondary_BlockChance = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.BlockChance")), FString(TEXT("Add BlockChance.")));
	The1001stGameplayTags.Attributes_Secondary_HealthRegeneration = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.HealthRegeneration")), FString(TEXT("Add HealthRegeneration Value.")));
	The1001stGameplayTags.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.ManaRegeneration")), FString(TEXT("Add ManaRegeneration Value."))); 
	The1001stGameplayTags.Attributes_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.MaxHealth")), FString(TEXT("Add MaxHealth.")));
	The1001stGameplayTags.Attributes_Secondary_MaxMana = GameplayTagsManager.AddNativeGameplayTag(FName(TEXT("Attributes.Secondary.MaxMana")), FString(TEXT("Add MaxMana.")));
}
