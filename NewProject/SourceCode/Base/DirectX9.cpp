//=================================================================================
//
//    DirectX9 cpp
//    Author : Lin He                                �쐬�� : 2017/12/04
//
//=================================================================================

#include "DirectX9.h"

#include <windows.h>

#include "input.h"
#include "sound.h"
#include "Texture.h"
#include "../Game/Scene.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define SAFE_RELEASE(p) {if(p){ (p)->Release(); (p) = NULL; }}

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static LPDIRECT3D9	g_pD3D = NULL;				// �_�C���N�g3D�C���^�t�F�[�X
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// �_�C���N�g3D�f�o�C�X

static CInputMouse* g_pInputMouse = NULL;		// �}�E�X�ւ̃|�C���^

//=================================================================
// [ DirextX9�������֐� ]
//=================================================================
bool InitDirectX9(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, int nWindowWidth, int nWindowHeight)
{
	// �_�C���N�g3D�C���^�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return false;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE d3ddm;
	HRESULT hr = g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,	// �f�B�X�v���C�E�A�_�v�^���w�肷��( ����̎w��͏����̃f�B�X�v���C�E�A�_�v�^ )
		&d3ddm);				// ���݂̃f�B�X�v���C�E�A�_�v�^�̏����󂯎��ϐ��̐擪�A�h���X

	if (FAILED(hr))
	{
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^(�f�o�C�X���쐬���邽�߂̃f�[�^)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//�@���̂��̂�S�Ă�����������(����������擪�A�h���X, ����������T�C�Y)
	d3dpp.BackBufferWidth = nWindowWidth;				//�@�����(�o�b�N�o�b�t�@)�̕�
	d3dpp.BackBufferHeight = nWindowHeight;				//	�����(�o�b�N�o�b�t�@)�̍���
	d3dpp.BackBufferFormat = d3ddm.Format;				//	�F��( �o�b�N�o�b�t�@�̃t�H�[�}�b�g )
	d3dpp.BackBufferCount = 1;							//	�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//	�f���M���̓���(DISCARD�͐����������C�ɂ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						//	TRUE�ŗǂ�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//	���͂���ŗǂ���̃t�H�[�}�b�g
	d3dpp.Windowed = bWindow;						//	TRUE�ŃE�B���h�E���[�h,FALSE�Ńt���X�N���[�����[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//	�t���X�N���[�����[�h�̎��̃��t���b�V�����[�g��Hz����ύX
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//	���j�^�[��Hz���ɍ��킹�ĕ`�悳���(IMMEDIATE���Ɛ���������҂����ɕ`�悷��)( D3DPRESENT_INTERVAL_ONE�@�ɂ���ƃw���c�œ��� )


	// �f�o�C�X�I�u�W�F�N�g�̐���( ��`�棂Ƣ���_��������n�[�h�E�F�A�ōs��
	hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,						// �f�B�X�v���C�E�A�_�v�^���w�肷��( ����̎w��͏����̃f�B�X�v���C�E�A�_�v�^ )
		D3DDEVTYPE_HAL,							// �f�o�C�X�^�C�v( ����̎w��̓n�[�h�E�F�A�ɂ�鏈�����s�� )
		hWnd,									// ���̃f�o�C�X�Ńt�H�[�J�X��ݒ肷��E�B���h�E�n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�̍쐬�𐧌䂷��t���O�̑g�ݍ��킹( ����̎w��̓n�[�h�E�F�A�ɂ�钸�_�������w�� )
		&d3dpp,									// �f�o�C�X�̐ݒ���w�肵���ϐ��̐擪�A�h���X
		&g_pD3DDevice);							// �쐬�����f�o�C�X���󂯎��ϐ��̐擪�A�h���X

	if (FAILED(hr))
	{
		// �G���[����
		MessageBox(hWnd, L"�_�C���N�g3D�f�o�C�X��\n�쐬�Ɏ��s���܂���!!", L"�G���[", MB_OK);
		return false;
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�t�@�C�^�����O
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	
	// �}�E�X����������
	g_pInputMouse = new CInputMouse;
	g_pInputMouse->Init(hInstance, hWnd);

	//�`��֐�������
	InitTexture();

	//�T�E���h
	InitSound(hWnd);

	//�V�[���}�l�W���[�̏�����
	SceneManager::Init();

	return true;
}

//=================================================================
// [ DirextX9�I�������֐� ]
//=================================================================
void UninitDirectX9()
{
	//�V�[���}�l�W���[�̏I������
	SceneManager::Uninit();

	//�T�E���h
	UninitSound();

	//�`��֐��̏I������
	UninitTexture();

	// �}�E�X�̉������
	if (g_pInputMouse)
	{
		g_pInputMouse->Uninit();
		delete g_pInputMouse;
		g_pInputMouse = NULL;
	}

	// �L�[�{�[�h���͂̏I������

	// �f�o�C�X�̉��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̉��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=================================================================
// [ DirextX9�X�V�֐� ]
//=================================================================
void UpdateDirectX9()
{
	// �}�E�X�̍X�V����
	if (g_pInputMouse)
	{
		g_pInputMouse->Update();
	}

	SceneManager::UpdateScene();

}

//=================================================================
// [ DirextX9�`��֐� ]
//=================================================================
void DrawDirectX9()
{
	// ��ʃo�b�t�@���N���A����
	g_pD3DDevice->Clear(0,						// RECT�\���̔z��̋�`�̐�
		NULL,									// RECT�\���̂̐擪�A�h���X(��ʑS�̂�NULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGET�͐F�̃N���A�AZBUFFER��Z�o�b�t�@�̃N���A
		D3DCOLOR_RGBA(32, 64, 192, 255),		// �N���A�J���\(TARGET������Ƃ�)
		1.0f,									// Z�o�b�t�@�̃N���A�l
		0);										// �X�e���V���l�̃N���A�l

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SceneManager::DrawScene();

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// ��ŕ`�悵�����̂����ۂɃE�B���h�E�ɔ��f������
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=================================================================
// [ DirextX9�f�o�C�X�擾�֐� ]
//=================================================================
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}

//=================================================================
// [ DirextX9�}�E�X�擾�֐� ]
//=================================================================
CInputMouse* GetMouse()
{
	return g_pInputMouse;
}