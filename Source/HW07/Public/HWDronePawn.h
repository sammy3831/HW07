#pragma once

#include "CoreMinimal.h"
#include "HWPawn.h"
#include "HWDronePawn.generated.h"

UCLASS()
class HW07_API AHWDronePawn : public AHWPawn
{
	GENERATED_BODY()

public:
	AHWDronePawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float GravityScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	bool bSimulateGravity;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceDistance = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Trace")
	bool bShowDebugTrace = false;

	FVector Velocity;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value) override;
	void MoveComplete(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value) override;

	virtual void Tick(float DeltaTime) override;

private:
	bool bMoving;

	bool CheckHitGround();
};
