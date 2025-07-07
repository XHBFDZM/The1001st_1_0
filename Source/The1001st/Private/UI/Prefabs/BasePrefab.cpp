// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Prefabs/BasePrefab.h"

void UBasePrefab::SetOwenerMediator(UObject* InOwenerMediator)
{
	if (OwenerMediator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwenerMediator is nullptr"));
		return;
	}
	if (OwenerMediator == InOwenerMediator)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwenerMediator is already set to the same instance."));
		return;
	}
	OwenerMediator = InOwenerMediator;
	OwenerMediatorIsSetted();
}