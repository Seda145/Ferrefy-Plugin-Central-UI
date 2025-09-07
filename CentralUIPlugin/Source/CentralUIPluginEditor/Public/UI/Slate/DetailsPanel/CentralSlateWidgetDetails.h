/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Templates/SharedPointer.h"


class FCentralSlateWidgetDetails : public IDetailCustomization {
	
private:

protected:

public:

private:

protected:

public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
};