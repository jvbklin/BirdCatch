//=================================================================================
//
//    SceneManager cpp
//    Author : Lin He                                �쐬�� : 2018/09/14
//
//=================================================================================

#include "Scene.h"

#include "../main.h"
#include "../Base/Texture.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Scene* SceneManager::current_scene_ = nullptr;

Scene::SCENE_TYPE SceneManager::next_scene_ = Scene::TITLE;

bool SceneManager::IsFadingScene_;
bool SceneManager::IsFadeIn_;
int  SceneManager::fade_count_;
LPDIRECT3DTEXTURE9 SceneManager::black_image_;

//=================================================================
// [ �V�[���}�l�W���[�������֐� ]
//=================================================================
void SceneManager::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/black.png", &black_image_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Scene Manager�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}

	SceneManager::IsFadingScene_ = true;
	SceneManager::IsFadeIn_ = true;
	SceneManager::fade_count_ = 255;

	SceneManager::current_scene_ = new TitleScene;
	SceneManager::InitScene();

}

//=================================================================
// [ �V�[���}�l�W���[�I�������֐� ]
//=================================================================
void SceneManager::Uninit()
{
	black_image_->Release();
	black_image_ = NULL;

	SceneManager::UninitScene();
}

//=================================================================
// [ �V�[���������֐� ]
//=================================================================
void SceneManager::InitScene()
{
	current_scene_->Init();
}

//=================================================================
// [ �V�[���I�������֐� ]
//=================================================================
void SceneManager::UninitScene()
{
	current_scene_->Uninit();
	delete current_scene_;
}

//=================================================================
// [ �V�[���X�V�֐� ]
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
// [ �V�[���`��֐� ]
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
// [ �V�[���ϊ��֐��i�O���ďo���j ]
//=================================================================
void SceneManager::ChangeScene(Scene::SCENE_TYPE scene)
{
	SceneManager::next_scene_ = scene;
	IsFadingScene_ = true;
	IsFadeIn_ = false;
}

//=================================================================
// [ �V�[���ϊ��֐� ]
//=================================================================
void SceneManager::SwitchScene()
{
	if (current_scene_ != 0) {
		SceneManager::UninitScene();
	}

	switch (SceneManager::next_scene_)	//�����̃V�[��
	{
	case Scene::TITLE:
		current_scene_ = new TitleScene;      //�^�C�g���V�[�������݂̃V�[���ɂ���
		break;
	case Scene::GAME:
		current_scene_ = new GameScene;       //�Q�[���V�[�������݂̃V�[���ɂ���
		break;
	case Scene::RESULT:
		current_scene_ = new ResultScene;     //���U���g�V�[�������݂̃V�[���ɂ���
		break;
	case Scene::TUTORIAL:
		current_scene_ = new TutorialScene;     //Tutorial�V�[�������݂̃V�[���ɂ���
		break;
	case Scene::GAMEOVER:
		current_scene_ = new GameoverScene;     //Gameover�V�[�������݂̃V�[���ɂ���
		break;
	default:
		break;
	}

	SceneManager::InitScene();
}

//=================================================================
// [ �V�[���t�F�[�h�X�V�֐� ]
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
// [ �V�[���t�F�[�h�`��֐� ]
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
