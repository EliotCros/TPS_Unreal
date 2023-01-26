// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT3_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UWeapon();
	int currentAmmo;
	int maxAmmo;
	int currentClip;
	int maxClip;
	int weaponType;

	UPROPERTY(EditAnywhere)
		float fireRate = 0.1f;


	void ChangeToWeapon1();
	void ChangeToWeapon2();
		
};
