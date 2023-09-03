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
## Level Config
You will see folder levels and in the folder has "level1.json" this is scene level file in json format. let's see the file.
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
Let's see each properties
  + BallSpeed - Ball initial speed
  + BallRadius - Ball radius
  + BallColor - Ball color
  + PlankSpeed - Plank max move speed
  + PlankWidth - Plank width unit
  + PlankHeight - Plank height unit
  + PlankCOlor - Plank fill color in RGBA format (0.0 - 1.0)
  + BackgroundColor - Color of Level background in RGB format
  + ForegroundColor - Color of Text display during game. (Not include Game Over and Pause menu)
  + ScoreForBounceBoundary - Score that player will gain when ball bounce with boundary
  + ScoreForBouncePlank    - Score that player will gain when ball bounce with plank
  + MinWaitTimeToSpawnCollectable - Minimum time variant that wait next collectable will be spawned (in seconds)
  + MaxWaitTimeToSpawnCollectable - Maximum time variant that wait next collectable will be spawned (in seconds)
  + CoinRadius - Radius of coin collectable
  + CoinColor - Color of coin collectable
  + CoinRewardScore - Score that player will gain when it is collected
  + CoinChanceToSpawn - Chance to be spawned (0.0 - 1.0)
  + BallSpeedUpRadius - Radius of BallSpeedUp collectable
  + BallSpeedUpColor - Color of BallSpeedUp collectable
  + BallSpeedUpValue - Speed that append to ball when it is collected
  + BallSpeedUpChanceToSpawn - Chance to be spawned (0.0 - 1.0)
  + BallSlowDownRadius - Radius of BallSpeedUp collectable
  + BallSlowDownColor - Color of BallSpeedUp collectable
  + BallSlowdownValue - Speed that subtract from ball when it is collected
  + BallSpeedUpChanceToSpawn - Chance to be spawned (0.0 - 1.0)
  + PlankBarIncreaseWidth , PlankBarIncreaseHeight - Size of PlankBarIncrease collectable
  + PlankBarIncreaseValue - Width that append to plank when it is collected
  + PlankBarIncreaseColor - Color of PlankBarIncrease collectable
  + PlankBarIncreaseChanceToSpawn - Chance to be spawned (0.0 - 1.0)
  + PlankBarDecreaseWidth , PlankBarDecreaseHeight - Size of PlankBarDecrease collectable
  + PlankBarDecreaseValue - Width that subtract from plank when it is collected
  + PlankBarDecreaseColor - Color of PlankBarDecrease collectable
  + PlankBarDecreaseChanceToSpawn - Chance to be spawned (0.0 - 1.0)
  + ShuffleBoxWidth , ShuffleBoxHeight - Size of ShuffleBox collectable
  + ShuffleBoxSpeedUpValue - Speed that append to ball when it is collected
  + ShuffleBoxColor - Color of ShuffleBox collectable
  + ShuffleBoxChanceToSpawn - Chance to be spawned (0.0 - 1.0)
