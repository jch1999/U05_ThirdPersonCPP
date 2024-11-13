#include "CHealthWidget.h"
#include "Components/ProgressBar.h"

void UCHealthWidget::Update(float InCurrentHelath, float InMaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(InCurrentHelath / InMaxHealth);
	}
}