/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/BackgroundBlur.h"

#include "CentralBackgroundBlur.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralBackgroundBlurStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bApplyAlphaToBlur;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		float BlurStrength;	
	
	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateBrush LowQualityFallbackBrush;

	FS_CentralBackgroundBlurStyle()
		 : bApplyAlphaToBlur (true)
		 , BlurStrength (0.f)
		 , LowQualityFallbackBrush (FSlateBrush())
	{}
};


/**
* A Central widget (centralized properties).
* A background blur is a container widget that can contain one child widget, providing an opportunity 
* to surround it with adjustable padding and apply a post-process Gaussian blur to all content beneath the widget.
*
* * Single Child
* * Blur Effect
*/
UCLASS(meta = (DisplayName = "Background Blur (C)"))
class CENTRALUIPLUGIN_API UCentralBackgroundBlur : public UBackgroundBlur, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralBackgroundBlurStyle"))
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

	UCentralBackgroundBlur(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
