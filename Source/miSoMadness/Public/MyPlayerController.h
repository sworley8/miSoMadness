UCLASS()
class MYGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
 
public:
	/* Constructor */
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);
 
	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }
 
protected:
	/* Return The Correct Pawn Class Client-Side */
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	virtual void DeterminePawnClass_Implementation();
 
	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;
 
	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);
 
	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;
 
	/* First Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<AGESGame_ServerPawn> PawnToUseA;
 
	/* Second Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	TSubclassOf<AGESGame_Pawn> PawnToUseB;
};