// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Target.h"
#include "WeaponV3.h"

#include "PlayerCharacter.generated.h"

class UNiagaraSystem;

UCLASS()
class MYPROJECT3_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		class UCharacterMovementComponent* CharacterMove;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere)
		class AWeaponV3* Weapon;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* PShoot;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* Pfire;

	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);

	UPROPERTY(EditAnywhere)
		float camAngleMax = 50.0f;
	UPROPERTY(EditAnywhere)
		float camAngleMin = -89.0f;

	FTimerHandle shootTimerHandle;
	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();
	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	FVector recoil(FVector aim, float offset_aim);


	//Input Cam
	void Cam_PitchAxis(float AxisValue);
	void Cam_YawAxis(float AxisValue);	
	
	FRotator CamVelocity;

	UPROPERTY(EditAnywhere)
		float camSpeed = 7.5f;
	UPROPERTY(EditAnywhere)
		TSubclassOf < UCameraShakeBase > ShakeClass;



	//raycast stuff
	UFUNCTION()
		void shoot();
	void startShoot();
	void stopShoot();
	void tryShoot();
	void startShootTimer();
	void stopShootTimer();
	UFUNCTION()
		void recoil();
	void ShootSound();
	bool isShooting;

	FHitResult camhit;
	FVector Startcam;
	FVector ForwardVectorCam;
	FVector EndCam;


	FHitResult Playerhit;
	FVector ForwardVectorPlayer;
	FVector Startplayer;
	FVector EndPlayer;


	float speed;
	void StartSprint();
	void StopSprint();
	bool isSPrinting;

	void StartAim();
	void StopAim();
	void rayShoot();
	bool isAim;
	void startPlayer();

	void ChangeWeapon1();
	void ChangeWeapon2();
	void ChangeWeaponUp();
	void ChangeWeaponDown();
	FVector MuzzleLocation;
	FVector ForwardAim;

	void reload();


	void WalkOnAmmo(int count, WeaponType type);

	
};
