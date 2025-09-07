/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/Throbber.h"

#include "CentralThrobber.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralThrobberStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		int32 NumberOfPieces;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bAnimateHorizontally;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bAnimateVertically;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bAnimateOpacity;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateBrush Image;

	FS_CentralThrobberStyle()
		: NumberOfPieces (3)
		, bAnimateHorizontally (true)
		, bAnimateVertically (true)
		, bAnimateOpacity (true)
		, Image (FSlateBrush())
	{}
};


/**
* A Central widget (centralized properties).
* A Throbber widget that shows several zooming circles in a row.
*/
UCLASS(meta = (DisplayName = "Throbber (C)"))
class CENTRALUIPLUGIN_API UCentralThrobber : public UThrobber, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralThrobberStyle"))
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

	UCentralThrobber(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
