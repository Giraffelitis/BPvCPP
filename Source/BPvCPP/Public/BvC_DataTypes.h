// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "BvC_DataTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Category = "BvC")
struct FPerformanceTestList : public FTableRowBase
{
 GENERATED_BODY()

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BvC")
 FText TestingMethod;
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BvC")
 int NumOfTestIterations;
 
};
