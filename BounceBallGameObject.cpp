#include "BounceBallGameObject.h"
#include "GLRenderUtility.h"
#include <random>

void USphereObject::Move(const FVector2& Delta)
{
	Sphere.Center += Delta;
}
void USphereObject::Rotate(float Delta)
{
	/*Sphere never rotate*/
}
void USphereObject::Draw(float DeltaSeconds)
{
	if (bIsFilled)
		UDrawUtil::DrawFilledCircle(GetCenter(), GetRadius(), Color);
	else
		UDrawUtil::DrawCircle(GetCenter(), GetRadius(), Color);
}

void URectangleObject::Move(const FVector2& Delta)
{
	Box.Center += Delta;
}
void URectangleObject::Rotate(float Delta)
{

}
void URectangleObject::Draw(float DeltaSeconds)
{
	if (bIsFilled)
		UDrawUtil::DrawFilledRectangle(GetCenter(), GetExtent(), 0.0f, Color);
	else
		UDrawUtil::DrawRectangle(GetCenter(), GetExtent(), 0.0f, Color);
}


UControlPlank::UControlPlank(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.PlankColor);
	SetSize(FVector2(Config.PlankWidth, Config.PlankHeight));
}

UCoin::UCoin(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.CoinColor);
	SetRadius(Config.CoinRadius);
	RewardScore = Config.CoinRewardScore;
}
void UCoin::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Player != nullptr) 
		Player->IncreaseScore(RewardScore);
}
bool UCoin::IsOverlap(const FSphere& BallSphere) const
{
	return Sphere.IsOverlap(BallSphere);
}


UBallSpeedUp::UBallSpeedUp(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.BallSpeedUpColor);
	SetRadius(Config.BallSpeedUpRadius);
	Value = Config.BallSpeedUpValue;
}
void UBallSpeedUp::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Ball != nullptr)
	{
		FVector2 Linear = Ball->GetLinearVelocity();
		float Length = Linear.Length();
		Ball->SetLinearVelocity(Linear.GetNormalize()*(Length + Value));
	}
}
bool UBallSpeedUp::IsOverlap(const FSphere& BallSphere) const
{
	return Sphere.IsOverlap(BallSphere);
}


UBallSlowDown::UBallSlowDown(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.BallSlowDownColor);
	SetRadius(Config.BallSlowDownRadius);
	Value = Config.BallSlowDownValue;

}
void UBallSlowDown::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Ball != nullptr)
	{
		FVector2 Linear = Ball->GetLinearVelocity();
		float Length = Linear.Length();
		Length -= Value;
		if (Length < 100.0f)
			Length = 100.0f;
		Ball->SetLinearVelocity(Linear.GetNormalize()*Length);
	}

}
bool UBallSlowDown::IsOverlap(const FSphere& BallSphere) const
{
	return Sphere.IsOverlap(BallSphere);
}


UPlankBarIncrease::UPlankBarIncrease(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.PlankBarIncreaseColor);
	SetSize(FVector2(Config.PlankBarIncreaseWidth, Config.PlankBarIncreaseHeight));
	Value = Config.PlankBarIncreaseValue;
}
void UPlankBarIncrease::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Plank != nullptr) {
		FVector2 Extents = Plank->GetExtent();
		Extents.X += (Value*0.5f);
		Plank->SetSize(Extents*2.0f);
	}
}
bool UPlankBarIncrease::IsOverlap(const FSphere& BallSphere) const
{
	return Box.IsOverlap(BallSphere);
}

UPlankBarDecrease::UPlankBarDecrease(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.PlankBarDecreaseColor);
	SetSize(FVector2(Config.PlankBarDecreaseWidth, Config.PlankBarDecreaseHeight));
	Value = Config.PlankBarDecreaseValue;
}
void UPlankBarDecrease::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Plank != nullptr) {
		FVector2 Extents = Plank->GetExtent();
		Extents.X -= (Value*0.5f);
		if (Extents.X < 10.0f)
			Extents.X = 10.0f;
		Plank->SetSize(Extents*2.0f);
	}
}
bool UPlankBarDecrease::IsOverlap(const FSphere& BallSphere) const
{
	return Box.IsOverlap(BallSphere);
}


UShuffleBox::UShuffleBox(const FBoundBallLevelConfiguation& Config)
{
	SetColor(Config.ShuffleBoxColor);
	SetSize(FVector2(Config.ShuffleBoxWidth, Config.ShuffleBoxHeight));
	Value = Config.ShuffleBoxSpeedUpValue;
}
void UShuffleBox::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Ball != nullptr) {
		FVector2 Linear = Ball->GetLinearVelocity();
		float Length = Linear.Length();
		
		FVector2 NewDirection = FVector2::RanomConeDirection(FVector2::Down, 1.22173048f);
		Ball->SetLinearVelocity(NewDirection*(Length + Value));
	}
}
bool UShuffleBox::IsOverlap(const FSphere& BallSphere) const
{
	return Box.IsOverlap(BallSphere);
}


UGameObject* FCollectionSpawner::Spawn(UCollectableSpawner& Spawner, const FBoundBallLevelConfiguation& Config) {
	
	float random_val = (float)rand() / (float)RAND_MAX;
	bool bShouldSpawn = (random_val <= Chance);
	return bShouldSpawn && (SpawnFunc != nullptr) ? (Spawner.*SpawnFunc)(Config) : nullptr;
}

void UCollectableSpawner::Initialize(const FBoundBallLevelConfiguation& Config)
{
	_spawners.clear();
	_spawners.push_back(FCollectionSpawner(Config.CoinChanceToSpawn, &UCollectableSpawner::SpawnCoin));
	_spawners.push_back(FCollectionSpawner(Config.BallSpeedUpChanceToSpawn, &UCollectableSpawner::SpawnBallSpeedUp));
	_spawners.push_back(FCollectionSpawner(Config.BallSlowDownChanceToSpawn, &UCollectableSpawner::SpawnBallSlowDown));
	_spawners.push_back(FCollectionSpawner(Config.PlankBarIncreaseChanceToSpawn, &UCollectableSpawner::SpawnPlankBarIncrease));
	_spawners.push_back(FCollectionSpawner(Config.PlankBarDecreaseChanceToSpawn, &UCollectableSpawner::SpawnPlankBarDecrease));
	_spawners.push_back(FCollectionSpawner(Config.ShuffleBoxChanceToSpawn, &UCollectableSpawner::SpawnShuffleBox));
	
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(_spawners), std::end(_spawners), rng);
	LastSpawnIndex = -1;
}
UGameObject* UCollectableSpawner::RandomSpawn(const FBoundBallLevelConfiguation& Config)
{
	if (LastSpawnIndex < 0)
		LastSpawnIndex = 0;
	
	int limitCount = _spawners.size();
	for (int i = 0; i < limitCount; i++) {
		UGameObject* Collectable = _spawners[LastSpawnIndex].Spawn(*this, Config);
		LastSpawnIndex++;
		LastSpawnIndex = LastSpawnIndex%limitCount;
		if (Collectable != nullptr) 
			return Collectable;
	}
	return nullptr;
}
UGameObject* UCollectableSpawner::SpawnCoin(const FBoundBallLevelConfiguation& Config)
{
	return new UCoin(Config);
}
UGameObject* UCollectableSpawner::SpawnBallSpeedUp(const FBoundBallLevelConfiguation& Config)
{
	return new UBallSpeedUp(Config);
}
UGameObject* UCollectableSpawner::SpawnBallSlowDown(const FBoundBallLevelConfiguation& Config)
{
	return new UBallSlowDown(Config);
}
UGameObject* UCollectableSpawner::SpawnPlankBarIncrease(const FBoundBallLevelConfiguation& Config)
{
	return new UPlankBarIncrease(Config);
}
UGameObject* UCollectableSpawner::SpawnPlankBarDecrease(const FBoundBallLevelConfiguation& Config)
{
	return new UPlankBarDecrease(Config);
}
UGameObject* UCollectableSpawner::SpawnShuffleBox(const FBoundBallLevelConfiguation& Config)
{
	return new UShuffleBox(Config);
}