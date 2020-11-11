UCLASS()
class MYGAME_API AMyGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
 
	/* Override To Read In Pawn From Custom Controller */
	UClass* GetDefaultPawnClassForController(AController* InController) override;
};