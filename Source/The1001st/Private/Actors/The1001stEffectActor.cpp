// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/The1001stEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

// Sets default values
AThe1001stEffectActor::AThe1001stEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	EffectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	EffectSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AThe1001stEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	EffectSphere->OnComponentBeginOverlap.AddDynamic(this, &AThe1001stEffectActor::OnOverlap);
	EffectSphere->OnComponentEndOverlap.AddDynamic(this, &AThe1001stEffectActor::EndOverlap);
}

void AThe1001stEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UThe1001stAttributeSet* The1001stAttributeSet = Cast<UThe1001stAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UThe1001stAttributeSet::StaticClass()));
		//The1001stAttributeSet被记录为const，所以我们不能直接修改它的属性，必须通过GE
		//The1001stAttributeSet->SetHealth(The1001stAttributeSet->GetHealth() + 25.0f);
		// 
		//但是现在暂时先这么用
		UThe1001stAttributeSet* MutableThe1001stAttributeSet = const_cast<UThe1001stAttributeSet*>(The1001stAttributeSet);
		MutableThe1001stAttributeSet->SetHealth(The1001stAttributeSet->GetHealth() + 25.0f);
		Destroy();
	}
}

void AThe1001stEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


