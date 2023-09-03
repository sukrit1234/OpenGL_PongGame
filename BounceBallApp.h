#pragma once
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>
#include<GL/glu.h>
#include <vector>
#include <algorithm>
#include <map>
#include "GLRenderUtility.h"
#include "BounceBallGameObject.h"
#include "BounceBallGameConfig.h"

class UBounceBallApp
{
private:

	/*Track all object in Game*/
	std::vector<UGameObject*> AllObjects;
	
	/*Player Object*/
	UPlayer Player;

	/*Collectable Spawner use to spawn collectable during game*/
	UCollectableSpawner CollectableSpawner;

	/*Controlled Plank that player controll*/
	UControlPlank* ControlledPlank = nullptr;
	
	/*Ball for main logic of game.*/
	UBall* TheBall = nullptr;
	
	/*Temporary buffer*/
	char score_text_buffer[1024];

	/*Level name that currently play*/
	std::string CurrentLevelName;

	/*Application config*/
	FBoundBallAppConfiguation AppConfig;

	/*Current Level Settings*/
	FBoundBallLevelConfiguation LevelConfig;


	float TimepassForCollectableSpawn = 0.0f;
	float WaitTimeForNextCollectable = 0.0f;
	Uint64 LastBounceTimeStamp = 0;
	
	void DoCaptureBounce(int Score);
	void Initialize();
	void ProcesssKeys();
	void CheckBallHitWithPlank(float deltaTime);
	void RemoveObjectFromBuffer(UGameObject* Object);
	void CheckHitWithCollectables(float deltaTime);

	//Return true if Bounce
	bool CheckBallBounceScreenBound(bool& bHitGround);
	void Render(float deltaTime);
	void Update(float deltaTime);
	void CleanUp();
	void ResetGame();
	void PauseGame();
	void SetupKeysBinding();

	/*
		For very time limit. 
		use ascii base key config instead of real input settings
	*/
	char MoveLeftKey;  //Move plank left
	char MoveRightKey; //Move plank right
	char MoveUpKey;    //Move plank up
	char MoveDownKey;  //Move plank down
	char ContinueKey;  //Continue after failed.
	char PauseKey;  //Key to Pause Game

public:

	void Start(std::string levelname);
};

