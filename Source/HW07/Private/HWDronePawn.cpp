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
		FVector DeltaLocation = FVector::ForwardVector * MoveInput.X * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector DeltaLocation = FVector::RightVector * MoveInput.Y * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		FVector DeltaLocation = FVector::UpVector * MoveInput.Z * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
}

void AHWDronePawn::Look(const FInputActionValue& Value)
{
	const FVector LookInput = Value.Get<FVector>();

	FRotator CurrentRotation = GetActorRotation();

	float NewYaw = CurrentRotation.Yaw;
	float NewPitch = CurrentRotation.Pitch;
	float NewRoll = CurrentRotation.Roll;

	if (!FMath::IsNearlyZero(LookInput.X))
	{
		NewYaw += LookInput.X;
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		NewPitch = FMath::ClampAngle(NewPitch + LookInput.Y, -80.0f, 80.0f);
	}
	if (!FMath::IsNearlyZero(LookInput.Z))
	{
		NewRoll += LookInput.Z;
	}

	SetActorRotation(FRotator(NewPitch, NewYaw, NewRoll));
}
