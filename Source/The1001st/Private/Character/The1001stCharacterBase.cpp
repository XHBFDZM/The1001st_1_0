// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Character/The1001stCharacterBase.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"

AThe1001stCharacterBase::AThe1001stCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AThe1001stCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AThe1001stCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AThe1001stCharacterBase::InitAbilityInfo()
{

}


