
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
		FVector DeltaLocation = GetActorForwardVector() * MoveInput.X * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector DeltaLocation = GetActorRightVector() * MoveInput.Y * MoveSpeed;
		AddActorLocalOffset(DeltaLocation);
	}
}

void AHWPlayerPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();
	
	FRotator CurrentRotation = SpringArm->GetRelativeRotation();
	
	float NewPitch = FMath::ClampAngle(CurrentRotation.Pitch + LookInput.Y, -80.0f, 80.0f);
	float NewYaw = CurrentRotation.Yaw + LookInput.X;
	
	SpringArm->SetRelativeRotation(FRotator(NewPitch, NewYaw, 0.0f));
}
