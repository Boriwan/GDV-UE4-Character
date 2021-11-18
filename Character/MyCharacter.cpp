// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Camera boom");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540,0);

	TurnRate = 45;
	LookUpRate = 45;

	SprintSpeedMultiplier = 2.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Forward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Side", this, &AMyCharacter::MoveSide);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprint);
}

void AMyCharacter::MoveForward(float Direction)
{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator Yaw(0, Rotation.Yaw, 0);
		FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	
		AddMovementInput(direction, Direction);
	
}


inline void AMyCharacter::MoveSide(float Direction)
{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator Yaw(0, Rotation.Yaw, 0);
		FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
	
		AddMovementInput(direction, Direction);
}

void AMyCharacter::Turn(float Rate)
{
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void AMyCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * LookUpRate);

}

void AMyCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AMyCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}


