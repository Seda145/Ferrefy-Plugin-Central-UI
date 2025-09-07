/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"

#include "CentralSlateWidgetInterface.generated.h"


UINTERFACE(NotBlueprintable)
class CENTRALUIPLUGIN_API UCentralSlateWidgetInterface : public UInterface {
    GENERATED_BODY()
};

class CENTRALUIPLUGIN_API ICentralSlateWidgetInterface {    
    GENERATED_BODY()

public:

    /* Get the central style datatable + row. */
    UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Appearance")
        virtual FDataTableRowHandle GetCentralStyle() const = 0;

    /* Set the central style datatable + row. Optionally load the style immediately. */
    UFUNCTION(BlueprintCallable, Category = "Appearance")
        virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle = true) = 0;

    /* Get the names of a parent class its properties we centralized. */
    virtual TArray<FString> GetCentralManagedPropertyNames() const = 0;

    /* Update style using the central properties. */
    UFUNCTION(BlueprintCallable, Category = "Appearance")
        virtual bool LoadCentralStyle() = 0;

};