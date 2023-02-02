// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "Components/CanvasPanel.h"
#include "ammo.generated.h"

UCLASS(Abstract)
class MYPROJECT3_API Uammo : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* maxclip;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* curclip;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* curammo;
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* canvas;

	void NativeConstruct();
public:
	void SetAmmo(int ammo);
	void SetClip(int clip);
	void SetCurClip(int xcurclip);

};
