/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/Slider.h"

#include "CentralSlider.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralSliderStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSliderStyle WidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<EOrientation> Orientation;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FLinearColor SliderBarColor;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FLinearColor SliderHandleColor;

	FS_CentralSliderStyle()
		: WidgetStyle (FSliderStyle())
		, Orientation (EOrientation::Orient_Horizontal)
		, SliderBarColor (FLinearColor::White)
		, SliderHandleColor (FLinearColor::White)
	{}
};


/**
* A Central widget (centralized properties).
* A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1.
*
* * No Children
*/
UCLASS(meta = (DisplayName = "Slider (C)"))
class CENTRALUIPLUGIN_API UCentralSlider : public USlider, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralSliderStyle"))
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

	UCentralSlider(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
