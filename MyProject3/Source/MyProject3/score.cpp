#include "score.h"
#include "Components/TextBlock.h"
#include "HGameManager.h"

void Uscore::NativeConstruct()
{

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass
	if (points)
	{
		points->SetText(FText::FromString(FString::SanitizeFloat(8)));
	}

}

void Uscore::SetPoint(int point)
{
	points->SetText(FText::FromString(FString::SanitizeFloat(point)));
}

