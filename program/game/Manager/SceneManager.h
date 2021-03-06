#pragma once
#include "../Scene/Scene.h"

class Scene;

class SceneManager {
public:
	/*enum SCENE {
		TITLE,
		INGAME


	};*/
	enum class SCENE {
		TITLE,
		SELECT,
		CUSTOM,
		INGAME
	};


	static void ChangeScene(SCENE Scene);     //
	static void Update();                     //
	static void Render();                     //

	static BaseScene* nowScene;               //

	static void Save();
	static void Load();

};