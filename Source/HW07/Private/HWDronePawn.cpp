
#include "HWDronePawn.h"
#include "EnhancedInputComponent.h"
#include "HWPlayerController.h"

void AHWDronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHWPlayerController* PlayerController = Cast<AHWPlayerController>(GetController()))
		{
			if (PlayerController->DroneMoveAction)
			{
				EnhancedInput->BindAction(PlayerController->DroneMoveAction, ETriggerEvent::Triggered,
										  this, &AHWDronePawn::Move);
			}

			if (PlayerController->DroneLookAction)
			{
				EnhancedInput->BindAction(PlayerController->DroneLookAction, ETriggerEvent::Triggered,
										  this, &AHWDronePawn::Look);
			}
		}
	}
}

void AHWDronePawn::Move(const FInputActionValue& Value)
{
	const FVector MoveInput = Value.Get<FVector>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector DeltaLocation = GetActorForwardVector() * MoveInput.X * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector DeltaLocation = GetActorRightVector() * MoveInput.Y * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		FVector DeltaLocation = GetActorUpVector() * MoveInput.Z * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}

	UE_LOG(LogTemp, Warning, TEXT("Move"));
}

void AHWDronePawn::Look(const FInputActionValue& Value)
{
	Super::Look(Value);

	UE_LOG(LogTemp, Warning, TEXT("Look"));
}
