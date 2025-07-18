
#pragma once

#include "CoreMinimal.h"
#include "HWPawnInterface.h"
#include "GameFramework/Pawn.h"
#include "HWPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class HW07_API AHWPawn : public APawn, public IHWPawnInterface
{
	GENERATED_BODY()

public:
	AHWPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MoveSpeed;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

};
