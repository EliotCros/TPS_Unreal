// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterfaceShootable.h"
#include "TargetV2.generated.h"

UCLASS()
class MYPROJECT3_API ATargetV2 : public AActor, public IMyInterfaceShootable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetV2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ProcessEvent_Implementation(FName Name, float Float) override;

};
