#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralMeshComponent.h"

#include "DES_L_System.generated.h"

// Seed vertex information, used for normalising turtle drawings...
USTRUCT(BlueprintType)
struct DES502_BUILD_API FDES_SeedVertex
{
	GENERATED_BODY()

	int Parent;
	FTransform Transform;
	FVector Position;
	float Depth;
};

// Tree vertex information, used for 'structuring' turtle drawings...
USTRUCT(BlueprintType)
struct DES502_BUILD_API FDES_TreeVertex
{
	GENERATED_BODY()

	int Parent;
	FTransform Transform;
	FVector Position;
	float Width;
	int Degree;
};

USTRUCT(BlueprintType)
struct DES502_BUILD_API FDES_L_Module
{
	GENERATED_BODY()

	FString Letter;

	float Period;
	float Aperiodicity;
	float Synchronisation;
	float Asynchronicity;

	float StaticLength;
	float RandomStaticLength;
	float PeriodicLength;
	float RandomPeriodicLength;

	float StaticRotation;
	float RandomStaticRotation;
	float PeriodicRotation;
	float RandomPeriodicRotation;

	float StaticWidth;
	float RandomStaticWidth;
	float PeriodicWidth;
	float RandomPeriodicWidth;

	float Asymmetry;
	float StaticAsymmetry;
	float RandomStaticAsymmetry;

	FDES_L_Module();
};

USTRUCT(BlueprintType)
struct DES502_BUILD_API  FDES_ProductionRule
{
	GENERATED_BODY()

	TArray<TFunction<FDES_L_Module(FDES_L_Module)>> Productions;
	float Weight;
};

UCLASS()
class DES502_BUILD_API ADES_L_System : public AActor
{
	GENERATED_BODY()

public:
	ADES_L_System();
	~ADES_L_System();

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable, Category = "Generation")
	virtual void Initialize(UProceduralMeshComponent* Mesh, TArray<FDES_L_Module> Axiom, int Iterations, float Seed = 0.0f, float Rotation = 0.0f, FVector2D Anchoring = FVector2D(0.5f, 0.5f));

	UFUNCTION(BlueprintCallable, Category = "Generation")
		void Update(float DeltaTime, float DeltaIntensity);

	// DEBUG:
	UFUNCTION(BlueprintCallable, Category = "Generation")
		FString GetSentence();

protected:
	virtual void BeginPlay() override;

	void AddProductionRule(FString Letter, FDES_ProductionRule ProductionRule);

private:
	void InitializeSentence(float Seed, TArray<FDES_L_Module> Axiom, int Iterations);
	void InitializeTree(float Seed, float Rotation, FVector2D Anchoring);
	void InitializeMesh(UProceduralMeshComponent* Mesh);

	void UpdateTree(float DeltaTime, float DeltaIntensity);
	//void UpdateMesh(); // FIXME: Add this!

	FDES_ProductionRule GetProductionRule(FString Letter, FRandomStream* rng);

private:
	TMap<FString, TArray<FDES_ProductionRule>> ProductionRules;
	TArray<FDES_L_Module> Sentence;

	float LSeed, LRotation, LScale, LDepth;
	TArray<FDES_SeedVertex> SeedVertices;

	float Time, Intensity;
	TArray<FDES_TreeVertex> TreeVertices;

	TArray<FVector> Vertices;
	TArray<int32> Indices;
	UProceduralMeshComponent* LMesh;
};