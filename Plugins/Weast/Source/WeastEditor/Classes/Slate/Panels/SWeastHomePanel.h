#pragma once

#include "CoreMinimal.h"
#include "Models/IWeastModel.h"
#include "Widgets/SCompoundWidget.h"

class SWeastHomePanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeastHomePanel)
	{}


	SLATE_END_ARGS()

public:

	WEASTEDITOR_API void Construct(const FArguments& InArgs, const IWeastModelRef& InModel);

private:
	IWeastModelPtr Model;
};