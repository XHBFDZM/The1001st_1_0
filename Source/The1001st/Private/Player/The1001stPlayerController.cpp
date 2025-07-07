// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Player/The1001stPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AThe1001stPlayerController::AThe1001stPlayerController()
{
	bReplicates = true;
	//这个bReplicates用作多人游戏中的复制功能（服务器上的变化），目前暂时不知道
}

void AThe1001stPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//断言，如果没有指定输入直接不继续游戏
	check(The1001stContext);

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(SubSystem);
	SubSystem->AddMappingContext(The1001stContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	//不锁定视口
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//捕获不会隐藏光标？？啥意思
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AThe1001stPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThe1001stPlayerController::Move);

}

void AThe1001stPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator WorldRotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f,WorldRotation.Yaw,0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AThe1001stPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AThe1001stPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if(!HitResult.bBlockingHit)
	{
		return;
	}
	CurActor = NowActor;
	NowActor= Cast<IEnemyInterface>(HitResult.GetActor());
	//上次点击和这次点击是同一个或都为空
	if (CurActor == NowActor)
	{
		return;
	}
	//上次点击不为空
	if (CurActor)
	{
		CurActor->UnhighlightActor();
	}
	//这次点击不为空
	if(NowActor)
	{
		NowActor->HighlightActor();
	}
}
