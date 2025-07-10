
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HWPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HW07_API AHWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHWPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Player")
	UInputMappingContext* PlayerInputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Player")
	UInputAction* PlayerMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Player")
	UInputAction* PlayerLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Drone")
	UInputMappingContext* DroneInputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Drone")
	UInputAction* DroneMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Drone")
	UInputAction* DroneLookAction;

protected:
	virtual void BeginPlay() override;
};
