
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

protected:
	virtual void BeginPlay() override;
};
