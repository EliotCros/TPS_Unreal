#include "Components/TextBlock.h"
#include "HGameManager.h"
#include "ammo.h"

void Uammo::NativeConstruct()
{

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass

}

void Uammo::SetAmmo(int ammo)
{
	curammo->SetText(FText::AsCultureInvariant(FString::FromInt(ammo)));
}

void Uammo::SetClip(int clip)
{
	maxclip->SetText(FText::AsCultureInvariant(FString::FromInt(clip)));
}

void Uammo::SetCurClip(int xcurclip)
{
	curclip->SetText(FText::AsCultureInvariant(FString::FromInt(xcurclip)));
}


