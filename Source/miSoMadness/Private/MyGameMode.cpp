AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Use our custom Player-Controller Class */
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
 
UClass* AMyGameMode::GetDefaultPawnClassForController(AController* InController)
{
	/* Override Functionality to get Pawn from PlayerController */
	AMyPlayerController* MyController = Cast<AMyPlayerController>(InController);
	if (MyController)
	{
		return MyController->GetPlayerPawnClass();
	}
 
	/* If we don't get the right Controller, use the Default Pawn */
	return DefaultPawnClass;
}