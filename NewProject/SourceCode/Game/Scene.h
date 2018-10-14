//=================================================================================
//
//    Scene header
//    Author : Lin He                                作成日 : 2018/09/14
//
//=================================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class Background;
class Stage;
class NumberManager;
class Pen;
class RectButton;
class StartButton;

//*****************************************************************************
// Scene Class (pure abstract class)
//*****************************************************************************
class Scene {

	// ============================================================
	// 列挙型定義
	// ============================================================
	public:
		enum SCENE_TYPE {
			TITLE,
			GAME,
			RESULT,
			TUTORIAL,
			GAMEOVER
		};

	// ============================================================
	// メンバ関数
	// ============================================================
	public:
		virtual ~Scene() = 0;

		virtual void Init() = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
};
inline Scene::~Scene() {}

//*****************************************************************************
// TitleScene Class
//*****************************************************************************
class TitleScene : public Scene
{
	private:
		Background* background_;
		StartButton* start_button_;

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();
};

//*****************************************************************************
// GameScene Class
//*****************************************************************************
class GameScene : public Scene
{
	private:
		Stage* current_stage_; //現在進行するステージ
		Pen* player_pen_;	   //プレイヤーのペン

		LPDIRECT3DTEXTURE9 ui_heart_; //ハートテクスチャー

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();
};

//*****************************************************************************
// ResultScene Class
//*****************************************************************************
class ResultScene : public Scene
{
	private:
		Background* background_;
		NumberManager* number_manager_;
		LPDIRECT3DTEXTURE9 score_texture_;
		RectButton* go_title_button_;

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();
};

//*****************************************************************************
// TutorialScene Class
//*****************************************************************************
class TutorialScene : public Scene
{
	private:
		Background* background_;
		RectButton* go_button_;

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();
};

//*****************************************************************************
// GameoverScene Class
//*****************************************************************************
class GameoverScene : public Scene
{
private:
	Background* background_;
	RectButton* again_button_;
	RectButton* go_title_button_;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

//*****************************************************************************
// SceneManager Class
//*****************************************************************************
class SceneManager 
{
	public:
		static Scene* current_scene_;

		static Scene::SCENE_TYPE next_scene_;
		static bool IsFadingScene_;
		static bool IsFadeIn_;
		static int fade_count_;
		static LPDIRECT3DTEXTURE9 black_image_;

	public:
		static void Init();
		static void Uninit();

		static void InitScene();
		static void UninitScene();
		static void UpdateScene();
		static void DrawScene();

		static void UpdateSceneFade();
		static void DrawSceneFade();

		//=================================================================
		// [ シーン変換関数 ]
		//
		// [ Parameters ]
		// [Scene::SCENE_TYPE]	scene	: 次に変更するシーン
		//=================================================================
		static void ChangeScene(Scene::SCENE_TYPE scene);

		static void SwitchScene();
};

#endif