
#pragma once

#include "CoreMinimal.h"
#include "HWPawn.h"
#include "HWDronePawn.generated.h"

UCLASS()
class HW07_API AHWDronePawn : public AHWPawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;
};
