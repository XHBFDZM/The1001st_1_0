// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/DA_InputConfig.h"

#include "InputAction.h"

UInputAction* UDA_InputConfig::GetInputActionThroughGameplayTag(FGameplayTag GameplayTag, bool bLogIfNotFind) const
{
	for(auto& InputConfig : InputConfigs)
	{
		if(InputConfig.GameplayTag == GameplayTag)
		{
			return InputConfig.InputAction;
		}
	}
	if (bLogIfNotFind)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputAction not found for GameplayTag: %s"), *GameplayTag.ToString());
	}
	return nullptr;
}
