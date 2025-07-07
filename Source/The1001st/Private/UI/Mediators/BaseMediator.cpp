// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mediators/BaseMediator.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

void UBaseMediator::SetParams(const FMediatorParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}