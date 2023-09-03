#pragma once
#include "FoundamentalStructures.h"
#include <iostream>
#include <fstream>
#include <sstream>

struct FBoundBallAppConfiguation {
	
	//Screen Settings
	std::string GameTitle;
	std::string ScoreLabel;
	std::string GameOverLabel;
	std::string ContinueKeyLabel;
	std::string PauseLabel;
	std::string PauseKeyLabel;
	int ScreenWidth; //Width
	int ScreenHeight; //Height

	std::string MoveLeftKey;
	std::string MoveRightKey;
	std::string MoveUpKey;
	std::string MoveDownKey;
	std::string ContinueKey;
	std::string PauseKey;
	static FBoundBallAppConfiguation Load();
};


struct FBoundBallLevelConfiguation {
	
	//Ball Settings
	float BallSpeed; //Initial Speed
	float BallRadius; //Initial Radius
	FLinearColor BallColor; //Color

	//Plank Settings
	float PlankSpeed; //Initial Speed
	float PlankWidth; //Initial Width
	float PlankHeight; //Initial Height
	FLinearColor PlankColor; //Color

	//Background Color Settings.
	FLinearColor BackgroundColor;
	
	//Forground Text Color Settings.
	FLinearColor ForegroundColor;

	//Score Logics
	int ScoreForBounceBoundary; //Score when Ball Bounce boundary
	int ScoreForBouncePlank;    //Score when Ball Bounce Plank

	//Collectable Spawn config
	//Min time wait for next spawn (in seconds)
	float MinWaitTimeToSpawnCollectable; 
	//Max time wait for next spawn (in seconds)
	float MaxWaitTimeToSpawnCollectable;

	//Collectable "Coin" Settings*/
	float CoinRadius; //Raidius
	FLinearColor CoinColor; //Color
	int CoinRewardScore;  //Score when collected
	float CoinChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)

	//Collectable : "BallSpeedUp" Settings
	float BallSpeedUpRadius; //Radius
	FLinearColor BallSpeedUpColor; //Color
	float BallSpeedUpValue; //Speed append to ball when collected.
	float BallSpeedUpChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)

	//Collectable : "BallSlowDown" Settings
	float BallSlowDownRadius; //Radius
	FLinearColor BallSlowDownColor; //Color
	float BallSlowDownValue; //Speed subtract from ball when collected.
	float BallSlowDownChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)

	//Collectable : "PlankBarIncrease" Settings
	float PlankBarIncreaseWidth;  //Width
	float PlankBarIncreaseHeight; //Height
	FLinearColor PlankBarIncreaseColor; //Color
	float PlankBarIncreaseValue; //Bar width that append to plank when collected
	float PlankBarIncreaseChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)


	//Collectable : "PlankBarDecrease" Settings
	float PlankBarDecreaseWidth; //Width
	float PlankBarDecreaseHeight;//Height
	FLinearColor PlankBarDecreaseColor; //Color
	float PlankBarDecreaseValue; //Bar width that append to plank when collected
	float PlankBarDecreaseChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)

	float ShuffleBoxWidth; //Width
	float ShuffleBoxHeight;//Height
	FLinearColor ShuffleBoxColor; //Color
	float ShuffleBoxSpeedUpValue; //Ball will increase speed when collected.
	float ShuffleBoxChanceToSpawn;  //Chance to spawn (0.0 never , 1.0 always)

	static FBoundBallLevelConfiguation Load(std::string Levelname);

	float SampleNextCollectableSpawnTime() const;
};