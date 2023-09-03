#include "BounceBallApp.h"

void UBounceBallApp::DoCaptureBounce(int Score) {
	Uint64 NewBounceTime = SDL_GetPerformanceCounter();
	float BounceTimeInterval = (double)(NewBounceTime - LastBounceTimeStamp) / (double)SDL_GetPerformanceFrequency();
	if (BounceTimeInterval > 0.1f)
	{
		Player.IncreaseScore(Score);
		LastBounceTimeStamp = NewBounceTime;
	}
}
void UBounceBallApp::Initialize()
{
	LevelConfig = FBoundBallLevelConfiguation::Load(CurrentLevelName);

	Player.ResetGame();
	CollectableSpawner.Initialize(LevelConfig);

	LastBounceTimeStamp = SDL_GetPerformanceCounter();

	float BallInitY_Offset = fmax(AppConfig.ScreenHeight*0.15f, LevelConfig.BallRadius*2.0f);
	int BallInitX_Min = AppConfig.ScreenWidth*0.35f;
	int BallInitX_Max = AppConfig.ScreenWidth*0.65f;
	int InitX_Offset = rand() % (BallInitX_Max - BallInitX_Min) + BallInitX_Min;

	TheBall = new UBall(LevelConfig);
	TheBall->SetLocation(FVector2(InitX_Offset, AppConfig.ScreenHeight - BallInitY_Offset));
	TheBall->SetLinearVelocity(FVector2::RanomConeDirection(FVector2::Down, 1.22173048f)*LevelConfig.BallSpeed);
	AllObjects.push_back(TheBall);

	ControlledPlank = new UControlPlank(LevelConfig);
	float PlankCenter_Offset = AppConfig.ScreenWidth*0.5f;
	float PlankInitY_Offset = fmin(AppConfig.ScreenHeight*0.25f, 200.0f);
	ControlledPlank->SetLocation(FVector2(PlankCenter_Offset, PlankInitY_Offset));

	AllObjects.push_back(ControlledPlank);
	WaitTimeForNextCollectable = LevelConfig.SampleNextCollectableSpawnTime();
}
void UBounceBallApp::ProcesssKeys()
{
	if (Player.IsGameOver())
		return;
	if (ControlledPlank != nullptr)
	{
		FVector2 MoveDirection = FVector2::Zero;
		const FBox& PlankBox = ControlledPlank->GetBox();
		if (Player.GetKeyState(MoveLeftKey))
		{
			float X = PlankBox.Center.X - PlankBox.Extents.X;
			MoveDirection = (X > 0.0f) ? FVector2::Left : FVector2::Zero;
		}
		if (Player.GetKeyState(MoveRightKey))
		{
			float X = PlankBox.Center.X + PlankBox.Extents.X;
			MoveDirection = (X < AppConfig.ScreenWidth) ? FVector2::Right : FVector2::Zero;
		}
		if (Player.GetKeyState(MoveUpKey))
		{
			float Y = PlankBox.Center.Y + PlankBox.Extents.Y;
			MoveDirection = (Y < AppConfig.ScreenHeight) ? FVector2::Up : FVector2::Zero;
		}
		if (Player.GetKeyState(MoveDownKey))
		{
			float Y = PlankBox.Center.Y - PlankBox.Extents.Y;
			MoveDirection = (Y > 0.0f) ? FVector2::Down : FVector2::Zero;
		}


		ControlledPlank->SetLinearVelocity(MoveDirection*LevelConfig.PlankSpeed);
	}
}
void UBounceBallApp::CheckBallHitWithPlank(float deltaTime)
{
	if (TheBall != nullptr && ControlledPlank != nullptr) {
		FVector2 ImpactPoint, ImpactNormal;
		const FSphere& BallSphere = TheBall->GetSphere();
		if (ControlledPlank->GetBox().IsCollide(BallSphere, ImpactPoint, ImpactNormal)) {
			FVector2 RelfectVel = TheBall->GetLinearVelocity().Reflect(ImpactNormal);

			TheBall->SetLocation(ImpactPoint + ImpactNormal * BallSphere.Radius);
			
			float Speed = RelfectVel.Length();
			RelfectVel += ControlledPlank->GetLinearVelocity();
			RelfectVel = RelfectVel.GetNormalize()*Speed;

			TheBall->SetLinearVelocity(RelfectVel);
			DoCaptureBounce(LevelConfig.ScoreForBouncePlank);
		}
	}
}
void UBounceBallApp::RemoveObjectFromBuffer(UGameObject* Object)
{
	AllObjects.erase(std::remove(AllObjects.begin(), AllObjects.end(), Object), AllObjects.end());
}
void UBounceBallApp::CheckHitWithCollectables(float deltaTime)
{
	if (TheBall != nullptr) {
		FSphere BallSphere = TheBall->GetSphere();
		for (size_t i = 0; i < AllObjects.size(); i++) {
			UGameObject* Collectable = AllObjects[i];
			if (Collectable != nullptr &&
				Collectable != TheBall &&
				Collectable != ControlledPlank)
			{
				IBounceBallCollectable* AsBallLogic = dynamic_cast<IBounceBallCollectable*>(Collectable);
				if ((AsBallLogic != nullptr) && AsBallLogic->IsOverlap(BallSphere))
				{
					AsBallLogic->OnCollected(&Player, TheBall, ControlledPlank);
					RemoveObjectFromBuffer(Collectable);
					i--;
					delete Collectable;
				}
			}
		}
	}
}

//Return true if Bounce
bool UBounceBallApp::CheckBallBounceScreenBound(bool& bHitGround)
{
	bool bIsBounced = false;
	bHitGround = false;
	if (TheBall != nullptr) {

		FVector2 Ball_C = TheBall->GetCenter();
		float Ball_R = TheBall->GetRadius();

		FVector2 Ball_V = TheBall->GetLinearVelocity();

		float BallShift_X = 0.0f;
		float BallShift_Y = 0.0f;
		if ((Ball_C.X + Ball_R) >= AppConfig.ScreenWidth) {
			Ball_V.X = -Ball_V.X;
			BallShift_X = AppConfig.ScreenWidth - (Ball_C.X + Ball_R);
			bIsBounced = true;
		}
		if ((Ball_C.Y + Ball_R) >= AppConfig.ScreenHeight) {
			Ball_V.Y = -Ball_V.Y;
			BallShift_Y = AppConfig.ScreenHeight - (Ball_C.Y + Ball_R);
			bIsBounced = true;
		}
		if ((Ball_C.X - Ball_R) <= 0) {
			Ball_V.X = -Ball_V.X;
			BallShift_X = -(Ball_C.X - Ball_R);
			bIsBounced = true;
		}
		if ((Ball_C.Y - Ball_R) <= 0) {
			bHitGround = true;
			Ball_V.Y = -Ball_V.Y;
			BallShift_Y = -(Ball_C.Y - Ball_R);
			bIsBounced = true;
		}
		TheBall->SetLocation(Ball_C + FVector2(BallShift_X, BallShift_Y));
		TheBall->SetLinearVelocity(Ball_V);
	}
	return bIsBounced;
}
void UBounceBallApp::Render(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT);

	if (!Player.IsGameOver()) {
		sprintf_s(score_text_buffer, AppConfig.ScoreLabel.c_str(), Player.GetScore());
		UDrawUtil::DrawScreenText(FVector2(20.0f, AppConfig.ScreenHeight - 24.0f), score_text_buffer, LevelConfig.ForegroundColor, false, GLUT_BITMAP_TIMES_ROMAN_24);
	
		sprintf_s(score_text_buffer, AppConfig.PauseKeyLabel.c_str(), AppConfig.PauseKey.c_str());
		UDrawUtil::DrawScreenText(FVector2(AppConfig.ScreenWidth*0.5f, AppConfig.ScreenHeight - 24.0f), score_text_buffer, LevelConfig.ForegroundColor, true, GLUT_BITMAP_TIMES_ROMAN_24);
	}


	for (size_t i = 0; i < AllObjects.size(); i++) {
		if (AllObjects[i] != nullptr)
			AllObjects[i]->Draw(deltaTime);
	}


	if (Player.IsGameOver()) {
		FVector2 ScreenCenter = FVector2(AppConfig.ScreenWidth, AppConfig.ScreenHeight)*0.5f;
		FVector2 ScreenSize = FVector2(AppConfig.ScreenWidth, AppConfig.ScreenHeight);
		UDrawUtil::DrawFilledRectangle(ScreenCenter, ScreenSize*0.25f, 0.0f, FLinearColor::White*0.5f);

		UDrawUtil::DrawScreenText(ScreenCenter + FVector2(0.0f, 48.0f), AppConfig.GameOverLabel.c_str(), FLinearColor::White, true);
		sprintf_s(score_text_buffer, AppConfig.ScoreLabel.c_str(), Player.GetScore());
		UDrawUtil::DrawScreenText(ScreenCenter, score_text_buffer, FLinearColor::White, true, GLUT_BITMAP_TIMES_ROMAN_24);
		
		sprintf_s(score_text_buffer, AppConfig.ContinueKeyLabel.c_str(), AppConfig.ContinueKey.c_str());
		UDrawUtil::DrawScreenText(ScreenCenter - FVector2(0.0f, 48.0f), score_text_buffer, FLinearColor::White, true, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (Player.IsPaused()) {
		FVector2 ScreenCenter = FVector2(AppConfig.ScreenWidth, AppConfig.ScreenHeight)*0.5f;
		FVector2 ScreenSize = FVector2(AppConfig.ScreenWidth, AppConfig.ScreenHeight);
		UDrawUtil::DrawFilledRectangle(ScreenCenter, ScreenSize*0.25f, 0.0f, FLinearColor::White*0.5f);
		UDrawUtil::DrawScreenText(ScreenCenter, AppConfig.PauseLabel.c_str(), FLinearColor::White, true, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	glFlush();
}
void UBounceBallApp::Update(float deltaTime)
{
	if (Player.IsGameOver() || Player.IsPaused())
		return;

	/*Use for iteration*/
	float timeStep = deltaTime * 0.25f;
	for (int step = 0; step < 4; step++)
	{
		for (size_t i = 0; i < AllObjects.size(); i++) {
			if (AllObjects[i] != nullptr)
				AllObjects[i]->Update(timeStep);
		}
		CheckBallHitWithPlank(timeStep);
		CheckHitWithCollectables(timeStep);

		bool bHitGround = false;
		if (CheckBallBounceScreenBound(bHitGround))
		{
			if (bHitGround)
				Player.MarkAsGameOver();
			else
				DoCaptureBounce(LevelConfig.ScoreForBounceBoundary);
		}
	}


	TimepassForCollectableSpawn += deltaTime;
	if (TimepassForCollectableSpawn > WaitTimeForNextCollectable) {
		UGameObject* Collectable = CollectableSpawner.RandomSpawn(LevelConfig);
		if (Collectable != nullptr) {

			int MinColArea_X = AppConfig.ScreenWidth*0.25f;
			int MaxColArea_X = AppConfig.ScreenWidth*0.75f;

			int MinColArea_Y = AppConfig.ScreenHeight*0.5f;
			int MaxColArea_Y = AppConfig.ScreenHeight*0.85f;

			int PointColArea_X = rand() % (MaxColArea_X - MinColArea_X) + MinColArea_X;
			int PointColArea_Y = rand() % (MaxColArea_Y - MinColArea_Y) + MinColArea_Y;

			Collectable->SetLocation(FVector2(PointColArea_X, PointColArea_Y));
			AllObjects.push_back(Collectable);
			TimepassForCollectableSpawn = 0.0f;
			WaitTimeForNextCollectable = LevelConfig.SampleNextCollectableSpawnTime();
		}
	}
}
void UBounceBallApp::CleanUp()
{
	for (int i = 0; i < AllObjects.size(); i++)
	{
		if (AllObjects[i] != nullptr)
		{
			delete AllObjects[i];
			AllObjects[i] = nullptr;
		}
	}
	TheBall = nullptr;
	ControlledPlank = nullptr;
}
void UBounceBallApp::ResetGame()
{
	if (Player.IsGameOver())
	{
		CleanUp();
		Initialize();
	}
}
void UBounceBallApp::PauseGame()
{
	Player.TogglePause();
}
void UBounceBallApp::SetupKeysBinding()
{
	if (AppConfig.MoveLeftKey.length() > 0)
		MoveLeftKey = AppConfig.MoveLeftKey.c_str()[0];
	if (AppConfig.MoveRightKey.length() > 0)
		MoveRightKey = AppConfig.MoveRightKey.c_str()[0];
	if (AppConfig.MoveUpKey.length() > 0)
		MoveUpKey = AppConfig.MoveUpKey.c_str()[0];
	if (AppConfig.MoveDownKey.length() > 0)
		MoveDownKey = AppConfig.MoveDownKey.c_str()[0];
	if (AppConfig.ContinueKey.length() > 0)
		ContinueKey = AppConfig.ContinueKey.c_str()[0];
	if (AppConfig.PauseKey.length() > 0)
		PauseKey = AppConfig.PauseKey.c_str()[0];
}
void UBounceBallApp::Start(std::string levelname)
{
	CurrentLevelName = levelname;
	AppConfig = FBoundBallAppConfiguation::Load();

	uint32_t WindowFlags = SDL_WINDOW_OPENGL;
	SDL_Window *Window = SDL_CreateWindow(AppConfig.GameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, AppConfig.ScreenWidth, AppConfig.ScreenHeight, WindowFlags);
	assert(Window);
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	SetupKeysBinding();
	Initialize();

	bool Running = true;
	glMatrixMode(GL_PROJECTION);
	glClearColor(LevelConfig.BackgroundColor.R, LevelConfig.BackgroundColor.G, LevelConfig.BackgroundColor.B, LevelConfig.BackgroundColor.A);
	Uint64 LastTime = SDL_GetPerformanceCounter();
	while (Running)
	{
		Uint64 NowTime = SDL_GetPerformanceCounter();
		float deltaTime = (float)((double)(NowTime - LastTime) / (double)SDL_GetPerformanceFrequency());

		SDL_Event Event;
		while (SDL_PollEvent(&Event))
		{
			SDL_Keycode Keycode = Event.key.keysym.sym;
			if (Event.type == SDL_KEYDOWN)
			{
				if (Keycode == ContinueKey)
					ResetGame();
				else if (Keycode == PauseKey)
					PauseGame();
				else if(Keycode == SDLK_ESCAPE)
					Running = 0;
				Player.SetKeyState(Keycode, true);
			}
			else if (Event.type == SDL_KEYUP)
				Player.SetKeyState(Keycode, false);
			else if (Event.type == SDL_QUIT)
			{
				Running = 0;
			}
		}

		ProcesssKeys();

		Update(deltaTime);
		glLoadIdentity();
		gluOrtho2D(0.0f, AppConfig.ScreenWidth, 0.0f, AppConfig.ScreenHeight);
		glViewport(0, 0, AppConfig.ScreenWidth, AppConfig.ScreenHeight);
		Render(deltaTime);

		SDL_GL_SwapWindow(Window);
		LastTime = NowTime;
	}
}