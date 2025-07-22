#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HWPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PRACTICEPROJECT_API AHWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHWPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
	UUserWidget* MainMenuWidgetInstance;

	UFUNCTION(Blueprintpure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;
	UFUNCTION(Blueprintcallable, Category = "HUD")
	void ShowGameHUD();

	UFUNCTION(Blueprintcallable, Category = "Menu")
	void ShowMainMenu(bool bIsRestaart);
	UFUNCTION(Blueprintcallable, Category = "Menu")
	void StartGame();

	virtual void BeginPlay() override;
};
