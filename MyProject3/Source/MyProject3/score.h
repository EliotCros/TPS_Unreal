// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "score.generated.h"


UCLASS(Abstract)
class MYPROJECT3_API Uscore : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* points;
	
	void NativeConstruct();
public:
	void SetPoint(int point);

};
