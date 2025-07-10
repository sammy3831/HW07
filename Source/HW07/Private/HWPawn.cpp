#include "HWPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

AHWPawn::AHWPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->InitCapsuleSize(34.f, 88.f);
	CapsuleComponent->SetCollisionProfileName("Pawn");
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	MeshComponent->SetCollisionProfileName("Pawn");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	CapsuleComponent->SetSimulatePhysics(false);
	MeshComponent->SetSimulatePhysics(false);

	MoveSpeed = 6.0f;
}

void AHWPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AHWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHWPawn::Move(const FInputActionValue& Value)
{
}

void AHWPawn::Look(const FInputActionValue& Value)
{
}
