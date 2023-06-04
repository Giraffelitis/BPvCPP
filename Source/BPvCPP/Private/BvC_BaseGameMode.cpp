// Copyright Epic Games, Inc. All Rights Reserved.

#include "BvC_BaseGameMode.h"
#include "BvC_DataTypes.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

ABvC_BaseGameMode::ABvC_BaseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	Http = &FHttpModule::Get();
	ApiBaseUrl = TEXT("https://docs.google.com/spreadsheets/d/");
	DocID = TEXT("1FMx0AtfPwXPzlOdKIgYyFYh62jZGZWYV1viUZpTwNLc");

	// https://docs.google.com/spreadsheets/d/1FMx0AtfPwXPzlOdKIgYyFYh62jZGZWYV1viUZpTwNLc/edit?usp=sharing
	
	//Gets the DT Blueprint
	static ConstructorHelpers::FObjectFinder<UDataTable>
	TestTable_BP(TEXT("DataTable'/Game/TestingHub/Data/DT_PerformanceTestList'"));

	SetTestTable(TestTable_BP.Object);
	ResponseString = "None";
}

void ABvC_BaseGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	UpdateTestTable();
}

void ABvC_BaseGameMode::UpdateTestTable()
{
	RetrieveTestTableData();
//	TestTable->EmptyTable();
	
	FPerformanceTestList Row;

	TArray<FString> stringArray ;
	ResponseString.ParseIntoArray(stringArray, TEXT("\r\n"), false);
	
	for (int i = 1; i < stringArray.Num(); i++)
	{
		if (stringArray.Num() == 0){continue;}
		FString LineLabel = stringArray[0];
		if ((LineLabel.Len() == 0)  || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
		{
			continue;	// Skip comments or lines with no label
		}
		Row.TestingMethod = FText::FromString(TEXT("method"));//stringArray[1];
		Row.NumOfTestIterations = FCString::Atoi(*stringArray[2]);

		// add the row to the table
		TestTable->AddRow(FName(*stringArray[i]), Row);
	}
}

void ABvC_BaseGameMode::RetrieveTestTableData()
{
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> Request = Http->CreateRequest();

	//Bind request response
	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::ProcessResponse);

	// Sets document ID and adds request for csv format 
	Subroute = FString::Printf(TEXT("%s/export?format=csv"), *DocID);
	
	// Set Request URL
	Request->SetURL(ApiBaseUrl + Subroute);

	// This is where we set the HTTP method (GET, POST, etc)
	Request->SetVerb("GET");
	
	// We'll need to tell the server what type of content to expect in the POST data
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("text/csv"));
	Request->SetHeader(TEXT("Accepts"), TEXT("text/csv"));

	// Submit the request for processing
	Request->ProcessRequest();
}

void ABvC_BaseGameMode::ProcessResponse(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	if (!ResponseIsValid(InResponse, bWasSuccessful)) return;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *InResponse->GetContentAsString())
	ResponseString = *InResponse->GetContentAsString();
	
	OnResponseDelegate.Broadcast(InResponse->GetContentAsString());
}

bool ABvC_BaseGameMode::ResponseIsValid(FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	if (!bWasSuccessful || !InResponse.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode())) return true;
	
	UE_LOG(LogTemp, Error, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
	return false;
	
}
