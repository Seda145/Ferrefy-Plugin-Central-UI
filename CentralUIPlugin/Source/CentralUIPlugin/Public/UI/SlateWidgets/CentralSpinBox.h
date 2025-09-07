/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/SpinBox.h"

#include "CentralSpinBox.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralSpinBoxStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSpinBoxStyle WidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateColor ForegroundColor;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<ETextJustify::Type> Justification;

	FS_CentralSpinBoxStyle()
		: WidgetStyle (FSpinBoxStyle())
		, ForegroundColor (FSlateColor(FLinearColor::Black))
		, Font (FSlateFontInfo())
		, Justification (ETextJustify::Left)
	{}
};


/**
* A Central widget (centralized properties).
* A numerical entry box that allows for direct entry of the number or allows the user to click and slide the number.
*/
UCLASS(meta = (DisplayName = "Spin Box (C)"))
class CENTRALUIPLUGIN_API UCentralSpinBox : public USpinBox, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralSpinBoxStyle"))
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

	UCentralSpinBox(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
