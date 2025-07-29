// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DA_AttributeInformations.h"

FAttributeInformations UDA_AttributeInformations::FindAttributeInformationThroughTag(const FGameplayTag& AttributeTag, bool bLogIfNotFind)
{
	for (FAttributeInformations& Info : AttributeInformations)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	
	if (bLogIfNotFind)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute tag '%s' not found in DA_AttributeInformations."), *AttributeTag.ToString());
	}

	return FAttributeInformations();
}
