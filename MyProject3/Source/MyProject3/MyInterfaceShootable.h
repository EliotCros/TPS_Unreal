// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterfaceShootable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyInterfaceShootable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT3_API IMyInterfaceShootable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		void ProcessEvent(FName TestParamName, float TestParamFloat);
};
