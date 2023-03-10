// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponV3.h"


AWeaponV3::AWeaponV3()
{
}

int AWeaponV3::getCurrentAmmo(){
	return weaponlist[(int)currentWeapon].currentAmmo;
}

void AWeaponV3::usedAmmo(){
	if (weaponlist[(int)currentWeapon].currentAmmo > 0) {
		weaponlist[(int)currentWeapon].currentAmmo -= 1;
	}
}

int AWeaponV3::getMaxAmmo(){
	return weaponlist[(int)currentWeapon].maxAmmo;
}

int AWeaponV3::getMaxClip(){
	return weaponlist[(int)currentWeapon].maxClip;
}

int AWeaponV3::getCurrentClip(){
	return weaponlist[(int)currentWeapon].currentClip;
}

void AWeaponV3::usedClipAmmo(){
	if (weaponlist[(int)currentWeapon].currentClip > 0) {
		weaponlist[(int)currentWeapon].currentClip -= 1;
	}
}

float AWeaponV3::getSpread(){
	return weaponlist[(int)currentWeapon].spread;
}

/*UTexture2D AWeaponV3::GetImage() {
	return weaponlist[(int)currentWeapon].image;
}*/

float AWeaponV3::getFireRate(){
	return weaponlist[(int)currentWeapon].fireRate;
}

bool AWeaponV3::canShoot(){
	return (weaponlist[(int)currentWeapon].currentClip>0);
}

void AWeaponV3::changeWeapon(int weapon){
	if (weapon >= (int)f_Weapon && weapon <= (int)l_Weapon) {
		currentWeapon = (WeaponType)weapon;
	}
}

void AWeaponV3::changeWeapon(bool scroll){
	int nextWeapon = (int)currentWeapon + ((scroll) ? 1 : -1);

	if (nextWeapon >= (int)f_Weapon && nextWeapon <= (int)l_Weapon) {
		currentWeapon = (WeaponType)nextWeapon;
	}else if (nextWeapon < (int)f_Weapon) {
		currentWeapon = l_Weapon;
	}else if (nextWeapon > (int)l_Weapon) {
		currentWeapon = f_Weapon;
	}

}

void AWeaponV3::shooted(){
	usedClipAmmo();
}

bool AWeaponV3::reload(){
	int i = (int)currentWeapon;
	int missingAmmo = weaponlist[i].maxClip - weaponlist[i].currentClip;
	if (missingAmmo != 0) {
		if (weaponlist[i].currentAmmo > missingAmmo) {
			weaponlist[i].currentClip = weaponlist[i].maxClip;
			weaponlist[i].currentAmmo -= missingAmmo;
		}
		else {
			weaponlist[i].currentClip += weaponlist[i].currentAmmo;
			weaponlist[i].currentAmmo = 0;
		}
		return true;
	}
	return false;
}

void AWeaponV3::getNewAmmo(WeaponType weapon, int Quantity){
	weaponlist[(int)weapon].currentAmmo += Quantity;
	if (weaponlist[(int)weapon].currentAmmo > weaponlist[(int)weapon].maxAmmo) {
		weaponlist[(int)weapon].currentAmmo = weaponlist[(int)weapon].maxAmmo;
	}
}

int AWeaponV3::GetNbBullet() {
	return weaponlist[(int)currentWeapon].nbBullet;
}
 

USoundBase* AWeaponV3::getSound()
{
	return weaponlist[(int)currentWeapon].ShootSound;
}

TSubclassOf <UCameraShakeBase> AWeaponV3::getShake() {
	return weaponlist[(int)currentWeapon].weaponShake;
}
