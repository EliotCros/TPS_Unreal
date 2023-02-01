#include "timer.h"
#include "Components/TextBlock.h"
#include "HGameManager.h"

void Utimer::NativeConstruct()
{

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass
	if (time)
	{
		time->SetText(FText::FromString(FString::SanitizeFloat(8)));
	}

}

void Utimer::SetTime(float curtime)
{
	time->SetText(FText::FromString(FString::SanitizeFloat(curtime)));
}

