#pragma once
#include "GameObject.h"
#include <vector>
#include "BounceBallGameConfig.h"

class UBall;
class UControlPlank;
class UPlayer;

class IBounceBallCollectable
{

public:
	
	virtual bool IsOverlap(const FSphere& BallSphere) const = 0;
	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) = 0;
};

/*Keep player statistics*/
class UPlayer
{
public:
	
	void MarkAsGameOver() { bIsGameOver = true; }
	bool IsGameOver() const { return bIsGameOver; }
	bool IsPaused() const { return bIsPaused; }

	int GetScore() const { return Score; }
	void IncreaseScore(int ToAdd) { Score += ToAdd; }
	void ResetGame() 
	{
		Score = 0; 
		bIsGameOver = false; 
		bIsPaused = false;
	}
	void TogglePause() { bIsPaused = !bIsPaused; }

	UPlayer() {
		for (int i = 0; i < MAX_KEY_ID; i++)
			KEYS[i] = false;
	}

	void SetKeyState(int KeyID,bool bState) 
	{
		if (KeyID < MAX_KEY_ID)
			KEYS[KeyID] = bState;
	}
	bool GetKeyState(int KeyID) const { return KEYS[KeyID]; }

protected:
	
	int Score = 0;
	bool bIsGameOver = false;
	bool bIsPaused = false;

	static const int MAX_KEY_ID = 322;
	bool KEYS[MAX_KEY_ID];
};
class UBall : public USphereObject
{
public:

	UBall(const FBoundBallLevelConfiguation& Config)
	{
		SetColor(Config.BallColor);
		SetRadius(Config.BallRadius);
	}

protected:


};
class UControlPlank : public URectangleObject
{
public:
	UControlPlank(const FBoundBallLevelConfiguation& Config);
};

class UCoin : public USphereObject, public IBounceBallCollectable
{
public:
	UCoin(const FBoundBallLevelConfiguation& Config);

protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	int RewardScore = 1;
};

class UBallSpeedUp : public USphereObject, public IBounceBallCollectable
{
public:
	UBallSpeedUp(const FBoundBallLevelConfiguation& Config);
protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Value = 50.0f;
};

class UBallSlowDown : public USphereObject, public IBounceBallCollectable
{
public:
	UBallSlowDown(const FBoundBallLevelConfiguation& Config);

protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Value = 50.0f;
};

class UPlankBarIncrease : public URectangleObject, public IBounceBallCollectable
{
public:
	UPlankBarIncrease(const FBoundBallLevelConfiguation& Config);

protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Value = 10.0f;
};

class UPlankBarDecrease : public URectangleObject, public IBounceBallCollectable
{
public:
	UPlankBarDecrease(const FBoundBallLevelConfiguation& Config);

protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Value = 10.0f;
};

class UShuffleBox : public URectangleObject, public IBounceBallCollectable
{
public:
	UShuffleBox(const FBoundBallLevelConfiguation& Config);

protected:

	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Value = 10.0f;
};

class UCollectableSpawner;

typedef UGameObject* (UCollectableSpawner::*FCollectableSpawnFunc)(const FBoundBallLevelConfiguation& Config);

struct FCollectionSpawner {

	float Chance = 1.0f;
	FCollectableSpawnFunc SpawnFunc;

	FCollectionSpawner() {
		Chance = 0.5f;
	}
	FCollectionSpawner(float chance,const FCollectableSpawnFunc& spawnFunc) {
		Chance = chance;
		SpawnFunc = spawnFunc;
	}
	UGameObject* Spawn(UCollectableSpawner& Spawner, const FBoundBallLevelConfiguation& Config);
};

class UCollectableSpawner
{
public:
	void Initialize(const FBoundBallLevelConfiguation& Config);
	UGameObject* RandomSpawn(const FBoundBallLevelConfiguation& Config);

protected:

	std::vector<FCollectionSpawner> _spawners;
	int LastSpawnIndex = -1;

	UGameObject* SpawnCoin(const FBoundBallLevelConfiguation& Config);
	UGameObject* SpawnBallSpeedUp(const FBoundBallLevelConfiguation& Config);
	UGameObject* SpawnBallSlowDown(const FBoundBallLevelConfiguation& Config);
	UGameObject* SpawnPlankBarIncrease(const FBoundBallLevelConfiguation& Config);
	UGameObject* SpawnPlankBarDecrease(const FBoundBallLevelConfiguation& Config);
	UGameObject* SpawnShuffleBox(const FBoundBallLevelConfiguation& Config);
};
