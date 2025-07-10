
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "UObject/Interface.h"
#include "HWPawnInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHWPawnInterface : public UInterface
{
	GENERATED_BODY()
};

class HW07_API IHWPawnInterface
{
	GENERATED_BODY()

public:
	virtual void Move(const FInputActionValue& Value) = 0;
	virtual void Look(const FInputActionValue& Value) = 0;
};
