// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "The1001st/Public/Character/The1001stCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API AEnemy : public AThe1001stCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemy();
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
protected:
	virtual void BeginPlay() override;
private:
	void InitAbilityInfo() override;
};
