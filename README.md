## Game Features
  + Player can move plank in 4 direction  Left / Right / Up / Down
  + Ball random spawn on the top of level far from plank with intial velocity
  + Ball will bounce with window boundary and plank if it's touch the ground , the game is over.
  + While during game , the collectables will be spawned in random peroid of time.
  + When ball overlap the collectable , It's will collected and take effect to player , ball , or plank.
  + When game over , Player can replay it.
    
### Collectables 
![plot](https://github.com/sukrit1234/OpenGL_PongGame/blob/main/BounceBall_ScreenShot.png)
You will see some colorful circle and square these are collectables that spawn during gameplay.
  + Coin (Orange Circle) - player will get more score. (Score can config in Level config)
  + BallSpeedUp (Red Circle) - Increase ball speed by X unit , player will play harder (Unit will config in Level Config)
  + BallSlowDown (Green Circle) - Decrease ball speed by X unit , player will play easier (Unit will config in Level Config)
  + PlankBarIncrease (Green Square) - Increase plank bar width by X unit , player will play easier (Unit will config in Level Config)
  + PlankBarDecrease  (Red Square) - Decrease plank bar width by X unit , player will play harder (Unit will config in Level Config)
  + ShuffleBox (Magenta Box)  - Random and change ball direction and increase velocity by X Unit (Unit will config in Level Config)

## Customization
My implementation of this game. I try to let's creator can adjust and customize some logic to make the game more or less challenge.
and try to implement it look like framework as much as possible for easy to add more collectable or logic later.
```
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UBounceBallApp App;
   /*Run the game with level1  scene.*/
	App.Start("level1");
	return 0;
}
```
## Configuration
This project contain 2 categories configuration "Level Config" and "App Config"
+ Level Config - Scene config that allow to adjust logic and in-game appearance
+ App config - config application preference and inputs such as input keys , screen size.
    
### Level Config
You will see folder levels and in the folder has "level1.json" this is scene level file in json format. let's see the file.
<details>
  <summary>See descrion of each properties</summary>
	  <li><b>BallSpeed</b> - Ball initial speed</li>
	  <li> <b>BallRadius</b> - Ball radius</li>
	  <li> <b>BallColor</b> - Ball color</li>
	  <li> <b>PlankSpeed</b> - Plank max move speed</li>
	  <li> <b>PlankWidth</b> - Plank width unit</li>
	  <li> <b>PlankHeight</b> - Plank height unit</li>
	  <li> <b>PlankCOlor</b> - Plank fill color in RGBA format (0.0 - 1.0)</li>
	  <li> <b>BackgroundColor</b> - Color of Level background in RGB format</li>
	  <li> <b>ForegroundColor</b> - Color of Text display during game. (Not include Game Over and Pause menu)</li>
	  <li> <b>ScoreForBounceBoundary</b> - Score that player will gain when ball bounce with boundary</li>
	  <li> <b>ScoreForBouncePlank</b>    - Score that player will gain when ball bounce with plank</li>
	  <li> <b>MinWaitTimeToSpawnCollectable</b> - Minimum time variant that wait next collectable will be spawned (in seconds)</li>
	  <li> <b>MaxWaitTimeToSpawnCollectable</b> - Maximum time variant that wait next collectable will be spawned (in seconds)</li>
	  <li> <b>CoinRadius</b> - Radius of coin collectable</li>
	  <li> <b>CoinColor</b> - Color of coin collectable</li>
	  <li> <b>CoinRewardScore</b> - Score that player will gain when it is collected</li>
	  <li> <b>CoinChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
	  <li> <b>BallSpeedUpRadius</b> - Radius of BallSpeedUp collectable</li>
	  <li> <b>BallSpeedUpColor</b> - Color of BallSpeedUp collectable</li>
	  <li> <b>BallSpeedUpValue</b> - Speed that append to ball when it is collected</li>
	  <li> <b>BallSpeedUpChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
	  <li> <b>BallSlowDownRadius</b> - Radius of BallSpeedUp collectable</li>
	  <li> <b>BallSlowDownColor</b> - Color of BallSpeedUp collectable</li>
	  <li> <b>BallSlowdownValue</b> - Speed that subtract from ball when it is collected</li>
	  <li> <b>BallSpeedUpChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
	  <li> <b>PlankBarIncreaseWidth</b> , <b>PlankBarIncreaseHeight</b> - Size of PlankBarIncrease collectable</li>
	  <li> <b>PlankBarIncreaseValue</b> - Width that append to plank when it is collected</li>
	  <li> <b>PlankBarIncreaseColor</b> - Color of PlankBarIncrease collectable</li>
	  <li> <b>PlankBarIncreaseChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
	  <li> <b>PlankBarDecreaseWidth</b> , <b>PlankBarDecreaseHeight</b> - Size of PlankBarDecrease collectable</li>
	  <li> <b>PlankBarDecreaseValue</b> - Width that subtract from plank when it is collected</li>
	  <li> <b>PlankBarDecreaseColor</b> - Color of PlankBarDecrease collectable</li>
	  <li> <b>PlankBarDecreaseChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
	  <li> <b>ShuffleBoxWidth</b> , <b>ShuffleBoxHeight</b> - Size of ShuffleBox collectable</li>
	  <li> <b>ShuffleBoxSpeedUpValue</b> - Speed that append to ball when it is collected</li>
	  <li> <b>ShuffleBoxColor</b> - Color of ShuffleBox collectable</li>
	  <li> <b>ShuffleBoxChanceToSpawn</b> - Chance to be spawned (0.0 - 1.0)</li>
</details>

```
{
	"BallSpeed" : 500,
        "BallRadius" : 10.0,
	"BallColor" : {"R" : 1.0,"G": 1.0,"B": 1.0,"A": 1.0},

	"PlankSpeed" : 500,
	"PlankWidth" : 200.0,
	"PlankHeight" : 20.0,
	"PlankColor" : {"R" : 1.0,"G": 1.0,"B": 1.0,"A": 1.0},
	
	"BackgroundColor" : {"R" : 0.0,"G": 0.0,"B": 1.0,"A": 1.0},
	"ForegroundColor" : {"R" : 1.0,"G": 1.0,"B": 1.0,"A": 1.0},

	"ScoreForBounceBoundary" : 1,
	"ScoreForBouncePlank" : 2,
	
	"MinWaitTimeToSpawnCollectable" : 1.0,
	"MaxWaitTimeToSpawnCollectable" : 2.0,

	"CoinRadius" : 20.0,
	"CoinColor" : {"R" : 1.0,"G": 0.647,"B": 0.0,"A": 1.0},
	"CoinRewardScore" : 1,
	"CoinChanceToSpawn" : 0.2,

	"BallSpeedUpRadius" : 20.0,
	"BallSpeedUpColor"  : {"R" : 1.0,"G": 0.0,"B": 0.0,"A": 1.0},
	"BallSpeedUpValue" : 50.0,
	"BallSpeedUpChanceToSpawn" : 0.5,

	"BallSlowDownRadius" : 20.0,
	"BallSlowDownColor" : {"R" : 0.0,"G": 1.0,"B": 0.0,"A": 1.0},
	"BallSlowDownValue" : 50.0,
	"BallSlowDownChanceToSpawn" : 0.3,

	"PlankBarIncreaseWidth" : 40.0,
	"PlankBarIncreaseHeight" : 40.0,
	"PlankBarIncreaseColor" : {"R" : 0.0,"G": 1.0,"B": 0.0,"A": 1.0},
	"PlankBarIncreaseValue" : 10.0,
	"PlankBarIncreaseChanceToSpawn" : 0.3,

	"PlankBarDecreaseWidth" : 40.0,
	"PlankBarDecreaseHeight" : 40.0,
	"PlankBarDecreaseColor" : {"R" : 1.0,"G": 0.647,"B": 0.0,"A": 1.0},
	"PlankBarDecreaseValue" : 10.0,
	"PlankBarDecreaseChanceToSpawn" : 0.5,

	"ShuffleBoxWidth" : 40.0,
	"ShuffleBoxHeight" : 40.0,
	"ShuffleBoxColor" : {"R" : 1.0,"G": 0.0,"B": 1.0,"A": 1.0},
	"ShuffleBoxSpeedUpValue" : 10.0,
	"ShuffleBoxChanceToSpawn" : 1.0,
}
```

### App Config
You will see file gameconfig.json  let's see the file.
Properties in this file is cleary self explanation so It's easy to modify. 
Because of limit of time , I can't implement UI framework in time (Although using library or from scratch) so At this time only change option in config file.
and the input key configuration still limit for only ascii keyboard keycode.
```
{
    "GameTitle" : "Bounce Ball The Game",
    "ScoreLabel" : "Your Score : (%d)",
    "ContinueKeyLabel" : "Press '%s' To Continue",
    "PauseKeyLabel" : "Press '%s' To Pause Game",
    "GameOverLabel" : "GAME OVER",
    "PauseLabel" : "GAME PAUSED 222",
    "ScreenWidth"  : 1000,
    "ScreenHeight" : 1000,
    "MoveLeftKey" : "a",
    "MoveRightKey" : "d",
    "MoveUpKey" : "w",
    "MoveDownKey" : "s",
    "ContinueKey" : "r",
    "PauseKey" : "f",
}
```
## Implementation detail
### Include Library
  + OpenGL - use via gl,glu and glut to draw 2D element and front text
  + SDL    - use for Input event polling
### Game Entry point.
At [**TestOpenGL.cpp**](https://github.com/sukrit1234/OpenGL_PongGame/blob/main/TestOpenGL.cpp) file will see this.
```
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UBounceBallApp App;
    App.Start("level1");
    return 0;
}
```
The game is encapsulate in class UBounceBallApp and it's simple run with Start() function and pass level config file. Level config that I mention earlier it allow creator can adjust and custom some logic for BounceBall game.

*** UBounceBallApp will read gameconfig.json and apply settings to application preferences.
You can duplicate level1.json in levels folder and rename to otherlevel.json and modify the config and can start BoundBall game with another logic.
```
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UBounceBallApp App;
    App.Start("otherlevel");
    return 0;
}
```
### Add New type collectables
If I need to add bomb when Ball overlap Bomb ball speed will increase in opposite direction. Let's do it.

Open [**BounceBallGameObject.h**](https://github.com/sukrit1234/OpenGL_PongGame/blob/main/BounceBallGameObject.h)
and add class.
```
class UTheBomb : public USphereObject, public IBounceBallCollectable
{
public:
     UTheBomb(const FBoundBallLevelConfiguation& Config);
protected:
	virtual void OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank) override;
	virtual bool IsOverlap(const FSphere& BallSphere) const override;
	float Impulse = 500.0f;
};
```
and add method SpawnTheBomb in UCollectableSpawner class

```
class UCollectableSpawner
{
	//...
	UGameObject* SpawnTheBomb(const FBoundBallLevelConfiguation& Config);
};
```


Open [**BounceBallGameObject.cpp**](https://github.com/sukrit1234/OpenGL_PongGame/blob/main/BounceBallGameObject.cpp)
and implement UTheBomb class
```
UTheBomb::UTheBomb(const FBoundBallLevelConfiguation& Config)
{
    //Define color
    SetColor(FLinearColor(1.0f,1.0f,0.0f,1.0f));
    SetRadius(50.0f); //Define radius of Bomb
    Value = 100.0f; //Define impulse of Bomb
}
void UTheBomb::OnCollected(UPlayer* Player, UBall* Ball, UControlPlank* Plank)
{
	if (Ball != nullptr) {
		FVector2 ImpulseDirection = (Ball->GetCenter() - GetCenter()).GetNormalize();
		FVector2 Linear = Ball->GetLinearVelocity();
		Linear += ImpulseDirection * Value;
		Ball->SetLinearVelocity(Linear);
	}
}
bool UTheBomb::IsOverlap(const FSphere& BallSphere) const
{
   /*Just call overlap sphere*/
   return Sphere.IsOverlap(BallSphere);
}

```
and then implment method SpawnTheBomb in UCollectableSpawner class

```
UGameObject* UCollectableSpawner::SpawnTheBomb(const FBoundBallLevelConfiguation& Config)
{
	return new UTheBomb(Config);
}
```
and add spawn method for UTheBomb in UCollectableSpawner::Initialize()
```
void UCollectableSpawner::Initialize(const FBoundBallLevelConfiguation& Config)
{
	// Chance to spawn the bomb is 85% (0.85) and SpawnTheBomb is spawn function
	_spawners.push_back(FCollectionSpawner(0.85, &UCollectableSpawner::SpawnTheBomb));
}
```
This still not flexible but very easy enough to add new type of collectable and logic without touching with game app.

## Many things must be improve
 + UI for application configuarion instead of directly modify to json file.
 + UI for creator to adjust level config.
 + Next level after clear current level , It's simple by implement next level to level config file and goal score. When player gain to goal score the game will load next level file.
 + Use CCD collision check for Ball for much more quality physics.
 + Add sound effect , texture instead of solid color
 + Rework design pattern that make new collectable type easier and more flexible.
 + Fine tune for collectable spawn location more equal sparse.
