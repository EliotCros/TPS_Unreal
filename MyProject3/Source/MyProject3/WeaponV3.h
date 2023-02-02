// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "WeaponV3.generated.h"


UENUM()
enum class WeaponType : uint8 {
	SHOOTGUN = 0 UMETA(DisplayName = "SHOOTGUN"),
	RIFLE = 1 UMETA(DisplayName = "RIFLE")
};



USTRUCT()
struct FWeapon {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		FString name;
	UPROPERTY(editAnywhere)
		WeaponType type;
	UPROPERTY(EditAnywhere)
		int currentAmmo;
	UPROPERTY(EditAnywhere)
		int maxAmmo;
	UPROPERTY(EditAnywhere)
		int maxClip;
	UPROPERTY(EditAnywhere)
		int currentClip;
	UPROPERTY(EditAnywhere)
		float spread;
	UPROPERTY(EditAnywhere)
		float fireRate;
	UPROPERTY(EditAnywhere)
		int nbBullet;
	//UPROPERTY(EditAnywhere)
	//	UTexture2D image;
	UPROPERTY(EditAnywhere)
		TSubclassOf <UCameraShakeBase> weaponShake;
	UPROPERTY(EditAnywhere)
		USoundBase* ShootSound;
};


UCLASS(BlueprintType, Blueprintable)
class MYPROJECT3_API AWeaponV3 : public AActor
{
	GENERATED_BODY()
public:
	AWeaponV3();

	UPROPERTY(EditAnywhere)
		TArray<FWeapon> weaponlist;

	//currentAmmo
	int getCurrentAmmo();
	void usedAmmo();

	//MaxAmmo
	int getMaxAmmo();

	//maxClip
	int getMaxClip();

	//CurrentClip
	int getCurrentClip();
	void usedClipAmmo();
	//Spread
	float getSpread();

	//Firerate
	float getFireRate();

	bool canShoot();

	void changeWeapon(int weapon);
	void changeWeapon(bool scroll);

	void shooted();

	bool reload();

	void getNewAmmo(WeaponType weapon, int Quantity);

	int GetNbBullet();
	UTexture2D GetImage();

	USoundBase* getSound();

	TSubclassOf <UCameraShakeBase> getShake();

	WeaponType currentWeapon = WeaponType::RIFLE;
	UPROPERTY(EditAnywhere)
	WeaponType f_Weapon = WeaponType::RIFLE;
	UPROPERTY(EditAnywhere)
	WeaponType l_Weapon = WeaponType::SHOOTGUN;

};
