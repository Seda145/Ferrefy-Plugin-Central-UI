/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "CentralUIPluginEditorSettings.generated.h"


UCLASS(config=Game, defaultconfig, meta = (DisplayName = "Central UI Plugin (Editor)"))
class CENTRALUIPLUGINEDITOR_API UCentralUIPluginEditorSettings : public UDeveloperSettings {
	GENERATED_BODY()

private:

protected:

public:

	/* Hide the original slate widgets which don't have a centralized style on the widget palette. */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "UI")
		bool bHideReplacedSlateWidgetPalette = false;
		
private:

protected:

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent);

public:

};

