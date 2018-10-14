//=================================================================================
//
//    SceneManager cpp
//    Author : Lin He                                作成日 : 2018/09/14
//
//=================================================================================

#include "Scene.h"

#include "../main.h"
#include "../Base/Texture.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Scene* SceneManager::current_scene_ = nullptr;

Scene::SCENE_TYPE SceneManager::next_scene_ = Scene::TITLE;

bool SceneManager::IsFadingScene_;
bool SceneManager::IsFadeIn_;
int  SceneManager::fade_count_;
LPDIRECT3DTEXTURE9 SceneManager::black_image_;

//=================================================================
// [ シーンマネジャー初期化関数 ]
//=================================================================
void SceneManager::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/black.png", &black_image_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Scene Managerテクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	SceneManager::IsFadingScene_ = true;
	SceneManager::IsFadeIn_ = true;
	SceneManager::fade_count_ = 255;

	SceneManager::current_scene_ = new TitleScene;
	SceneManager::InitScene();

}

//=================================================================
// [ シーンマネジャー終了処理関数 ]
//=================================================================
void SceneManager::Uninit()
{
	black_image_->Release();
	black_image_ = NULL;

	SceneManager::UninitScene();
}

//=================================================================
// [ シーン初期化関数 ]
//=================================================================
void SceneManager::InitScene()
{
	current_scene_->Init();
}

//=================================================================
// [ シーン終了処理関数 ]
//=================================================================
void SceneManager::UninitScene()
{
	current_scene_->Uninit();
	delete current_scene_;
}

//=================================================================
// [ シーン更新関数 ]
//=================================================================
void SceneManager::UpdateScene()
{
	if (IsFadingScene_)
	{
		UpdateSceneFade();
	}
	else
	{
		current_scene_->Update();
	}
}

//=================================================================
// [ シーン描画関数 ]
//=================================================================
void SceneManager::DrawScene()
{
	current_scene_->Draw();

	if (IsFadingScene_)
	{
		DrawSceneFade();
	}
}

//=================================================================
// [ シーン変換関数（外部呼出し） ]
//=================================================================
void SceneManager::ChangeScene(Scene::SCENE_TYPE scene)
{
	SceneManager::next_scene_ = scene;
	IsFadingScene_ = true;
	IsFadeIn_ = false;
}

//=================================================================
// [ シーン変換関数 ]
//=================================================================
void SceneManager::SwitchScene()
{
	if (current_scene_ != 0) {
		SceneManager::UninitScene();
	}

	switch (SceneManager::next_scene_)	//引数のシーン
	{
	case Scene::TITLE:
		current_scene_ = new TitleScene;      //タイトルシーンを現在のシーンにする
		break;
	case Scene::GAME:
		current_scene_ = new GameScene;       //ゲームシーンを現在のシーンにする
		break;
	case Scene::RESULT:
		current_scene_ = new ResultScene;     //リザルトシーンを現在のシーンにする
		break;
	case Scene::TUTORIAL:
		current_scene_ = new TutorialScene;     //Tutorialシーンを現在のシーンにする
		break;
	case Scene::GAMEOVER:
		current_scene_ = new GameoverScene;     //Gameoverシーンを現在のシーンにする
		break;
	default:
		break;
	}

	SceneManager::InitScene();
}

//=================================================================
// [ シーンフェード更新関数 ]
//=================================================================
void SceneManager::UpdateSceneFade()
{
	if (IsFadeIn_)
	{
		fade_count_-= 5;
		if (fade_count_ <= 0)
		{
			IsFadeIn_ = false;
			IsFadingScene_ = false;
		}
	}
	else
	{
		fade_count_ += 5;
		if (fade_count_ >= 255)
		{
			IsFadeIn_ = true;

			SwitchScene();
		}
	}
}

//=================================================================
// [ シーンフェード描画関数 ]
//=================================================================
void SceneManager::DrawSceneFade()
{
	SetTexture(black_image_);
	SetTextureColor(D3DCOLOR_RGBA(255, 255, 255, fade_count_));
	if (IsFadingScene_)
	{
		DrawTextureRect(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT);
	}

	SetTextureColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}
