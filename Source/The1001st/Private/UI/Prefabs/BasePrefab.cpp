// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Prefabs/BasePrefab.h"

void UBasePrefab::SetOwnerMediator(UObject* InOwnerMediator)
{
	if (InOwnerMediator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InOwnerMediator is nullptr"));
		return;
	}
	if (OwnerMediator == InOwnerMediator)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerMediator is already set to the same instance."));
		return;
	}
	OwnerMediator = InOwnerMediator;
	OwnerMediatorIsSetted();
}