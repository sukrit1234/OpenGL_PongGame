## Game Features
  + Player can move plank in 4 direction  Left / Right / Up / Down
  + Ball random spawn on the top of level far from plank with intial velocity
  + Ball will bounce with window boundary and plank if it's touch the ground , the game is over.
  + While during game , the collectables will be spawned in random peroid of time.
  + When ball overlap the collectable , It's will collected and take effect to player , ball , or plank.
  + When game over , Player can replay it.
    
### Collectables 
![plot](https://github.com/sukrit1234/ObjectManager_ECS/blob/main/Output_ECS.png)
I define some collectable that use in game. It's collected by ball overlap it.
  + Coin (Orange Circle) - player will get more score. (Score can config in Level config)
  + BallSpeedUp (Red Circle) - Increase ball speed by X unit , player will play harder (Unit will config in Level Config)
  + BallSlowDown (Green Circle) - Decrease ball speed by X unit , player will play easier (Unit will config in Level Config)
  + PlankBarIncrease (Green Square) - Increase plank bar width by X unit , player will play easier (Unit will config in Level Config)
  + PlankBarDecrease  (Red Square) - Decrease plank bar width by X unit , player will play harder (Unit will config in Level Config)
  + ShuffleBox (Purple Box)  - Random change velocity of ball but still same speed.
