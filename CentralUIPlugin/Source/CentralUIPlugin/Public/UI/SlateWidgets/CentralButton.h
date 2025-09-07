/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/Button.h"

#include "CentralButton.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralButtonStyle : public FTableRowBase {
	GENERATED_BODY()

	 UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FButtonStyle WidgetStyle;

	FS_CentralButtonStyle()
		: WidgetStyle (FButtonStyle())
	{}
};


/**
* A Central widget (centralized properties).
* The button is a click-able primitive widget to enable basic interaction, you
* can place any other widget inside a button to make a more complex and 
* interesting click-able element in your UI.
*
* * Single Child
* * Clickable
*/
UCLASS(meta = (DisplayName = "Button (C)"))
class CENTRALUIPLUGIN_API UCentralButton : public UButton, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralButtonStyle"))
		FDataTableRowHandle CentralStyle = FDataTableRowHandle();

public:

private:

#if WITH_EDITOR

	UFUNCTION()
		void ActOnCentralStyleDataTableChanged();

#endif // WITH_EDITOR

	virtual bool LoadCentralStyle() override;

protected:

	virtual void OnWidgetRebuilt() override;

public:

	UCentralButton(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	TSharedPtr<SButton> GetSlateButton(bool bInRebuildIfRequired = true);

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
