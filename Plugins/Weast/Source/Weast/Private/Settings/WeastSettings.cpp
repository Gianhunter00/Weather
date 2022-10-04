// Copyright (c) 2022 Maurious Paul Vincent. All rights reserved.

#include "Settings/WeastSettings.h"

FName UWeastSettings::GetContainerName() const
{
	return "Project";
}

FName UWeastSettings::GetCategoryName() const
{
	return "Plugins";
}

FName UWeastSettings::GetSectionName() const
{
	return "Weast";
}

#if WITH_EDITOR

FText UWeastSettings::GetSectionText() const
{
	return NSLOCTEXT("WeastSettings", "WeastSettingsSection", "Weast");
}

#endif // WITH_EDITOR

EWeastApp::Theme UWeastSettings::GetActiveTheme() const
{
	return ActiveTheme;
}

ETemperature::Unit UWeastSettings::GetTemperatureUnit() const
{
	return TemperatureUnit;
}

bool UWeastSettings::GetAutoRefresh() const
{
	return bAutoRefresh;
}

float UWeastSettings::GetRefreshFrequency() const
{
	return RefreshFrequency;
}
