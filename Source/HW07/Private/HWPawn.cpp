// Fill out your copyright notice in the Description page of Project Settings.


#include "HWPawn.h"

// Sets default values
AHWPawn::AHWPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHWPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHWPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

