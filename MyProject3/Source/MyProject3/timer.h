// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "timer.generated.h"


UCLASS(Abstract)
class MYPROJECT3_API Utimer : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* time;

	void NativeConstruct();
public:
	void SetTime(float curtime);

};
