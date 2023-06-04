// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "BvC_BaseGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestResponse, FString, InResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateTestsTable);

class UDataTable;

UCLASS(minimalapi)
class ABvC_BaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABvC_BaseGameMode();
	
	FOnRequestResponse OnResponseDelegate;
	FOnUpdateTestsTable UpdateTestsTable;
	FString ResponseString;

	UDataTable* GetTestTable() { return TestTable; }
	void SetTestTable(UDataTable* InVal) { TestTable = InVal; }
	void UpdateTestTable();
	
	UPROPERTY()
	UDataTable* TestTable;

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;
	void RetrieveTestTableData();

private:

	void ProcessResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);
	
	FString ApiBaseUrl;
	FString Subroute;
	FString DocID;
	
	FHttpModule* Http;
};



