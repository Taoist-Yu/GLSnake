#include "StartScene.h"
#include "StartCanvas.h"
#include "Time.h"
#include "Input.h"
#include "GameData.h"

#include <string>
#include <sstream>

StartScene::StartScene()
{
	camera = new Camera(this);
	camera->Activate();

	canvas = new StartCanvas(this);
}


StartScene::~StartScene()
{
	if (camera != NULL) {
		delete camera;
	}
	
	if (canvas != NULL) {
		delete canvas;
	}
	
}

void StartScene::setSky(int num)
{
	std::string path("skybox/level");
	std::stringstream ss;
	ss << num;
	std::string numstr;
	ss >> numstr;
	path = path + numstr;
	camera->AttachSkybox(new Skybox(path));
}

void StartScene::Postcycle()
{
	if (currentLevel != GameData::currentLevel) {
		currentLevel = GameData::currentLevel;
		setSky(currentLevel);
	}
	camera->transform.Rotate(0, 5 * Time.GetUnscaledDeltaTime(), 0);
	
}
