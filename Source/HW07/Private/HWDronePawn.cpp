#include "HWDronePawn.h"
#include "EnhancedInputComponent.h"
#include "HWPlayerController.h"
#include "Components/CapsuleComponent.h"

AHWDronePawn::AHWDronePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	GravityScale = -980.0f;
	bSimulateGravity = true;
	Velocity = FVector::ZeroVector;
	bMoving = false;
	TraceDistance = 100.0f;
	bShowDebugTrace = false;
}

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
				EnhancedInput->BindAction(PlayerController->DroneMoveAction, ETriggerEvent::Completed,
				                          this, &AHWDronePawn::MoveComplete);
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
	bMoving = !MoveInput.IsNearlyZero();

	bool bIsGrounded = CheckGround();
	float CurrentMoveSpeed = bIsGrounded ? MoveSpeed : MoveSpeed * 0.5f;

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector NewLocation = FVector::ForwardVector * MoveInput.X * CurrentMoveSpeed;
		AddActorLocalOffset(NewLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector NewLocation = FVector::RightVector * MoveInput.Y * CurrentMoveSpeed;
		AddActorLocalOffset(NewLocation);
	}
	if (!FMath::IsNearlyZero(MoveInput.Z))
	{
		if (MoveInput.Z < 0.0f)
		{
			if (!bIsGrounded)
			{
				FVector NewLocation = FVector::UpVector * MoveInput.Z * CurrentMoveSpeed;
				AddActorLocalOffset(NewLocation);
			}
		}
		else
		{
			FVector NewLocation = FVector::UpVector * MoveInput.Z * CurrentMoveSpeed;
			AddActorLocalOffset(NewLocation);
		}
	}
}

void AHWDronePawn::MoveComplete(const FInputActionValue& Value)
{
	bMoving = false;
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

void AHWDronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSimulateGravity)
	{
		bool bIsGrounded = CheckGround();
		if (!bIsGrounded && !bMoving)
		{
			Velocity.Z += GravityScale * DeltaTime;

			FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
		else
		{
			Velocity = FVector::ZeroVector;
		}
	}
}

bool AHWDronePawn::CheckGround()
{
	FVector StartLocation = CapsuleComponent->GetComponentLocation();
	FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,
	                                                 ECC_WorldStatic, QueryParams);

	if (bShowDebugTrace)
	{
		FColor LineColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			LineColor,
			false,
			-1.0f,
			0,
			1.0f
		);
	}

	return bHit;
}
