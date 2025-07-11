#include "HWPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "HWPlayerController.h"
#include "GameFramework/SpringArmComponent.h"

void AHWPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHWPlayerController* PlayerController = Cast<AHWPlayerController>(GetController()))
		{
			if (PlayerController->PlayerMoveAction)
			{
				EnhancedInput->BindAction(PlayerController->PlayerMoveAction, ETriggerEvent::Triggered,
				                          this, &AHWPlayerPawn::Move);
			}

			if (PlayerController->PlayerLookAction)
			{
				EnhancedInput->BindAction(PlayerController->PlayerLookAction, ETriggerEvent::Triggered,
				                          this, &AHWPlayerPawn::Look);
			}
		}
	}
}

void AHWPlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector NewLocation = FVector::ForwardVector * MoveInput.X * MoveSpeed;
		AddActorLocalOffset(NewLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector NewLocation = FVector::RightVector * MoveInput.Y * MoveSpeed;
		AddActorLocalOffset(NewLocation);
	}
}

void AHWPlayerPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	FRotator CurrentRotation = SpringArm->GetRelativeRotation();
	float NewYaw = CurrentRotation.Yaw;
	float NewPitch = CurrentRotation.Pitch;

	if (!FMath::IsNearlyZero(LookInput.X))
	{
		NewYaw += LookInput.X;
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		NewPitch = FMath::ClampAngle(NewPitch + LookInput.Y, -80.0f, 80.0f);
	}

	SpringArm->SetRelativeRotation(FRotator(NewPitch, NewYaw, 0.0f));
}
