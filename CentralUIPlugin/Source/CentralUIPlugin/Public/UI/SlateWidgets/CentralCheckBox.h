/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/CheckBox.h"

#include "CentralCheckBox.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralCheckBoxStyle : public FTableRowBase {
	GENERATED_BODY()

	 UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FCheckBoxStyle WidgetStyle;

	FS_CentralCheckBoxStyle()
		: WidgetStyle (FCheckBoxStyle())
	{}
};


/**
* A Central widget (centralized properties).
* The checkbox widget allows you to display a toggled state of 'unchecked', 'checked' and 
* 'indeterminable.  You can use the checkbox for a classic checkbox, or as a toggle button,
* or as radio buttons.
* 
* * Single Child
* * Toggle
*/
UCLASS(meta = (DisplayName = "Check Box (C)"))
class CENTRALUIPLUGIN_API UCentralCheckBox : public UCheckBox, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralCheckBoxStyle"))
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

	UCentralCheckBox(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
