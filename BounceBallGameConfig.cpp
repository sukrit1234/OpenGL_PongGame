
#include "BounceBallGameConfig.h"
#include "json.hpp"
using namespace std;

float parse_number(const json::JSON& json, float default_val = 0.0f) {
	if (json.JSONType() == json::JSON::Class::Floating)
		return (float)json.ToFloat();
	else if (json.JSONType() == json::JSON::Class::Integral)
		return json.ToInt();
	return default_val;
}
FLinearColor parse_color_object(const json::JSON& colorJson, const FLinearColor& default_val = FLinearColor::Black) {
	FLinearColor Color = default_val;
	if (colorJson.JSONType() == json::JSON::Class::Object)
	{
		Color.R = parse_number(colorJson.at("R"), default_val.R);
		Color.G = parse_number(colorJson.at("G"), default_val.G);
		Color.B = parse_number(colorJson.at("B"), default_val.B);
		Color.A = parse_number(colorJson.at("B"), default_val.A);
	}
	return Color;
}
FVector2 parse_vector2_object(const json::JSON& vectorJson, const FVector2& default_val = FVector2::Zero) {
	
	FVector2 Vector = default_val;
	if (vectorJson.JSONType() == json::JSON::Class::Object)
	{
		Vector.X = parse_number(vectorJson.at("X"), default_val.X);
		Vector.Y = parse_number(vectorJson.at("Y"), default_val.Y);
	}
	return Vector;
}
std::string parse_string(const json::JSON& json, std::string default_val = "") {
	if (json.JSONType() == json::JSON::Class::String)
		return json.ToString();
	return default_val;
}


float get_float_field(const json::JSON& json, std::string fieldname,float default_val=0.0f) {
	return json.hasKey(fieldname) ? parse_number(json.at(fieldname)) : default_val;
}
FLinearColor get_color_field(const json::JSON& json, std::string fieldname,const FLinearColor& default_val = FLinearColor::Black) {

	return json.hasKey(fieldname) ? parse_color_object(json.at(fieldname)) : default_val;
}
FVector2 get_vector2_field(const json::JSON& json, std::string fieldname, const FVector2& default_val = FVector2::Zero) {

	return json.hasKey(fieldname) ? parse_vector2_object(json.at(fieldname)) : default_val;
}

std::string get_string_field(const json::JSON& json, std::string fieldname, std::string default_val="") {

	return json.hasKey(fieldname) ? parse_string(json.at(fieldname)) : default_val;
}


FBoundBallAppConfiguation FBoundBallAppConfiguation::Load()
{
	FBoundBallAppConfiguation Config;
	std::string filename = "gameconfig.json";
	ifstream open_file(filename);
	if (open_file) {
		ostringstream ss;
		ss << open_file.rdbuf();
		string str = ss.str();

		json::JSON loadedJson = json::JSON::Load(str);
		Config.ScreenWidth = get_float_field(loadedJson, "ScreenWidth", 1000);
		Config.ScreenHeight = get_float_field(loadedJson, "ScreenHeight", 1000);
		Config.GameTitle = get_string_field(loadedJson, "GameTitle", "Bounce Ball Game");
		Config.ScoreLabel = get_string_field(loadedJson, "ScoreLabel", "Your Score : (%d)");
		Config.ContinueKeyLabel = get_string_field(loadedJson, "ContinueKeyLabel", "Press '%s' To Continue");
		Config.PauseKeyLabel = get_string_field(loadedJson, "PauseKeyLabel", "Press '%s' To Pause Game");
		Config.GameOverLabel = get_string_field(loadedJson, "GameOverLabel", "GAME OVER");
		Config.PauseLabel = get_string_field(loadedJson, "PauseLabel", "GAME PAUSED");

		Config.MoveLeftKey = get_string_field(loadedJson, "MoveLeftKey", "a");
		Config.MoveRightKey = get_string_field(loadedJson, "MoveRightKey", "d");
		Config.MoveUpKey = get_string_field(loadedJson, "MoveUpKey", "w");
		Config.MoveDownKey = get_string_field(loadedJson, "MoveDownKey", "s");
		Config.ContinueKey = get_string_field(loadedJson, "ContinueKey", "r");
		Config.PauseKey = get_string_field(loadedJson, "PauseKey", "f");
	}
	return Config;
}


FBoundBallLevelConfiguation FBoundBallLevelConfiguation::Load(std::string Levelname)
{
	FBoundBallLevelConfiguation Config;
	std::string filename = "levels/" + Levelname + ".json";
	ifstream open_file(filename);
	if (open_file) {
		ostringstream ss;
		ss << open_file.rdbuf();
		string str = ss.str();

		json::JSON loadedJson = json::JSON::Load(str);
		Config.BallSpeed = get_float_field(loadedJson, "BallSpeed", 500.0f);
		Config.BallRadius = get_float_field(loadedJson, "BallRadius", 10.0f);
		Config.BallColor = get_color_field(loadedJson, "BallColor", FLinearColor::White);

		Config.PlankSpeed = get_float_field(loadedJson, "PlankSpeed", 500.0f);
		Config.PlankWidth = get_float_field(loadedJson, "PlankWidth", 200.0f);
		Config.PlankHeight = get_float_field(loadedJson, "PlankHeight", 20.0f);
		Config.PlankColor = get_color_field(loadedJson, "PlankColor", FLinearColor::White);

		Config.BackgroundColor = get_color_field(loadedJson, "BackgroundColor", FLinearColor::Black);
		Config.ForegroundColor = get_color_field(loadedJson, "ForegroundColor", FLinearColor::White);

		Config.ScoreForBounceBoundary = get_float_field(loadedJson, "ScoreForBounceBoundary", 1);
		Config.ScoreForBouncePlank = get_float_field(loadedJson, "ScoreForBouncePlank", 2);
		
		Config.MinWaitTimeToSpawnCollectable = get_float_field(loadedJson, "MinWaitTimeToSpawnCollectable", 3.0f);
		Config.MaxWaitTimeToSpawnCollectable = get_float_field(loadedJson, "MaxWaitTimeToSpawnCollectable", 10.0f);

		Config.CoinRadius = get_float_field(loadedJson, "CoinRadius", 20.0f);
		Config.CoinColor = get_color_field(loadedJson, "CoinColor", FLinearColor::Orange);
		Config.CoinRewardScore = get_float_field(loadedJson, "CoinRewardScore", 1);
		Config.CoinChanceToSpawn = get_float_field(loadedJson, "CoinChanceToSpawn", 0.5f);

		Config.BallSpeedUpRadius = get_float_field(loadedJson, "BallSpeedUpRadius", 20.0f);
		Config.BallSpeedUpColor = get_color_field(loadedJson, "BallSpeedUpColor", FLinearColor::Red);
		Config.BallSpeedUpValue = get_float_field(loadedJson, "BallSpeedUpValue", 50.0f);
		Config.BallSpeedUpChanceToSpawn = get_float_field(loadedJson, "BallSpeedUpChanceToSpawn", 0.5f);

		Config.BallSlowDownRadius = get_float_field(loadedJson, "BallSlowDownRadius", 20.0f);
		Config.BallSlowDownColor = get_color_field(loadedJson, "BallSlowDownColor", FLinearColor::Green);
		Config.BallSlowDownValue = get_float_field(loadedJson, "BallSlowDownValue", 50.0f);
		Config.BallSlowDownChanceToSpawn = get_float_field(loadedJson, "BallSlowDownChanceToSpawn", 0.5f);

		Config.PlankBarIncreaseWidth = get_float_field(loadedJson, "PlankBarIncreaseWidth", 40.0f);
		Config.PlankBarIncreaseHeight = get_float_field(loadedJson, "PlankBarIncreaseHeight", 40.0f);
		Config.PlankBarIncreaseColor = get_color_field(loadedJson, "PlankBarIncreaseColor", FLinearColor::Green);
		Config.PlankBarIncreaseValue = get_float_field(loadedJson, "PlankBarIncreaseValue", 10.0f);
		Config.PlankBarIncreaseChanceToSpawn = get_float_field(loadedJson, "PlankBarIncreaseChanceToSpawn", 0.5f);

		Config.PlankBarDecreaseWidth = get_float_field(loadedJson, "PlankBarDecreaseWidth", 10.0f);
		Config.PlankBarDecreaseHeight = get_float_field(loadedJson, "PlankBarDecreaseHeight", 40.0f);
		Config.PlankBarDecreaseColor = get_color_field(loadedJson, "PlankBarDecreaseColor",FLinearColor::Orange);
		Config.PlankBarDecreaseValue = get_float_field(loadedJson, "PlankBarDecreaseValue", 10.0f);
		Config.PlankBarDecreaseChanceToSpawn = get_float_field(loadedJson, "PlankBarDecreaseChanceToSpawn", 0.5f);

		Config.ShuffleBoxWidth = get_float_field(loadedJson, "ShuffleBoxWidth", 10.0f);
		Config.ShuffleBoxHeight = get_float_field(loadedJson,"ShuffleBoxHeight", 50.0f);
		Config.ShuffleBoxColor = get_color_field(loadedJson, "ShuffleBoxColor", FLinearColor::Magenta);
		Config.ShuffleBoxSpeedUpValue = get_float_field(loadedJson, "ShuffleBoxSpeedUpValue", 10.0f);
		Config.ShuffleBoxChanceToSpawn = get_float_field(loadedJson, "ShuffleBoxChanceToSpawn", 0.5f);
	}
	return Config;
}

float FBoundBallLevelConfiguation::SampleNextCollectableSpawnTime() const
{
	return fmod(rand(), MaxWaitTimeToSpawnCollectable - MinWaitTimeToSpawnCollectable) + MaxWaitTimeToSpawnCollectable;
}