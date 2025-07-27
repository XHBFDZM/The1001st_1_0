// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Character/Enemy.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"


AEnemy::AEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UThe1001stAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet= CreateDefaultSubobject<UThe1001stAttributeSet>(TEXT("AttributeSet"));
}

void AEnemy::HighlightActor()
{
	bHighlighted = true;
	//设置后处理材质深度为真->高光
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AEnemy::UnhighlightActor()
{
	bHighlighted = false;
	//设置后处理材质深度为假->取消高光
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
	InitAbilityInfo();
}


void AEnemy::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UThe1001stAbilitySystemComponent* The1001stAbilitySystemComponent = Cast<UThe1001stAbilitySystemComponent>(AbilitySystemComponent);
	The1001stAbilitySystemComponent->AbilitySystemComponentAlreadyInitInfo();
}

int32 AEnemy::GetOwnerLevel()
{
	return Level;
}
