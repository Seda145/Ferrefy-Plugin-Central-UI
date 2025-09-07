/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/CircularThrobber.h"

#include "CentralCircularThrobber.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralCircularThrobberStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		int32 NumberOfPieces;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		float Period;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		float Radius;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateBrush Image;

	FS_CentralCircularThrobberStyle()
		: NumberOfPieces (6)
		, Period (0.75f)
		, Radius (16.f)
		, Image (FSlateBrush())
	{}
};


/**
* A Central widget (centralized properties).
* A throbber widget that orients images in a spinning circle.
* 
* * No Children
* * Spinner Progress
*/
UCLASS(meta = (DisplayName = "Circular Throbber (C)"))
class CENTRALUIPLUGIN_API UCentralCircularThrobber : public UCircularThrobber, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralCircularThrobberStyle"))
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

	UCentralCircularThrobber(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
