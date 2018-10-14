//=================================================================================
//
//    3DS�Q�[���ڐA
//    Author : Lin He                                �쐬�� : 2018/09/11
//
//=================================================================================

//**********************************************************************
// �C���N���[�h��
//**********************************************************************

#include <stdio.h>
#include <crtdbg.h>

#include "main.h"
#include "Base/DirectX9.h"

//**********************************************************************
// �}�N����`
//**********************************************************************

#define CLASS_NAME		L"2D"
#define WINDOW_NAME		L"2D��b"

//**********************************************************************
// �O���[�o���ϐ�
//**********************************************************************

HWND g_hWnd;

//================================================================================
// [ �E�B���h�E�v���V�[�W���\�֐� ]
//
// [ ���� ]
// �hWnd           : �E�B���h�E�n���h��
// �uMsg           : �����������b�Z�[�W
// �wParam, lParam : �����������b�Z�[�W�̕t�����
//
// [ �߂�l ]
// �LRESULT�^ : �E�B���h�E�v���V�[�W������Ԃ����32�r�b�g�̒l
//
// [ �ڍ� ]
// ��e�탁�b�Z�[�W�̏������s��
//================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//================================================================================
// [ �A�v���P�[�V�����̃G���g���[�֐� ]
//
// [ ���� ]
// �hInstance     : �C���X�^���X�n���h��(�����̃v���O���������ʂ���)
// �hPrevinstance : Win16�̎Y��(�g���Ȃ��̂ŏ��NULL)
// �lpCmdLine     : �R�}���h���C������(������)
// �nCmdShow      : �A�v���P�[�V�����̏����\�����@�̎w��
//
// [ �߂�l ]
// �int�^
//
// [ �ڍ� ]
// �Win32�A�v���P�[�V�����̃��C���֐�����
//================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �g���Ă��Ȃ������̏���
	lpCmdLine = lpCmdLine;
	hPrevinstance = hPrevinstance;

	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	// �E�B���h�E�N���X�̓o�^
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = NULL;

	// WNDCLASSEX�^��wcex�̒��g��o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�T�C�Y�̐ݒ�
	DWORD WStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// ��`�f�[�^

	AdjustWindowRect(&wr, WStyle, FALSE);

	int nWindowWidth = wr.right - wr.left;
	int nWindowHeight = wr.bottom - wr.top;

	// �E�B���h�E�̏ꏊ�𒆉��ɕύX
	RECT DesktopRect;

	GetWindowRect(GetDesktopWindow(), &DesktopRect);		// �f�X�N�g�b�v�T�C�Y�̎擾
	int nWindowPosX = (DesktopRect.right - nWindowWidth) / 2;
	int nWindowPosY = (DesktopRect.bottom - nWindowHeight) / 2;

	(DesktopRect.right - DesktopRect.left) < nWindowPosX ? nWindowPosX = 0 : nWindowPosX;
	(DesktopRect.bottom - DesktopRect.top) < nWindowPosY ? nWindowPosY = 0 : nWindowPosY;

	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WStyle,
		nWindowPosX,
		nWindowPosY,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W&�Q�[�����[�v
	MSG msg;
	DWORD dwTime = timeGetTime();
	DWORD dwOldTime = timeGetTime();

	// �^�C�}�[�̐��\���グ��
	timeBeginPeriod(1);

	//������(�`�F�b�N����)
	if (!InitDirectX9(hInstance, hWnd, TRUE, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		MessageBox(hWnd, L"�������Ɏ��s���܂���!!", L"�x��", MB_OK);

		return -1;
	}

	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{// ���b�Z�[�W����

			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// �Q�[������
			dwTime = timeGetTime();

			if ((dwTime - dwOldTime) >= (1000 / 60))
			{
				// �X�V
				UpdateDirectX9();

				// �`��
				DrawDirectX9();

				// �V�[���}�l�W�����g
				/*SceneManagerDirectX9();*/

				// �O��̎����̍X�V
				dwOldTime = dwTime;
			}
		}
	}

	// �I��
	UninitDirectX9();

	timeEndPeriod(1);

	return (int)msg.wParam;
}

//================================================================================
// [ �E�B���h�E�v���V�[�W���\�֐� ]
//
// [ ���� ]
// �hWnd           : �E�B���h�E�n���h��
// �uMsg           : �����������b�Z�[�W
// �wParam, lParam : �����������b�Z�[�W�̕t�����
//
// [ �߂�l ]
// �LRESULT�^ : �E�B���h�E�v���V�[�W������Ԃ����32�r�b�g�̒l
//
// [ �ڍ� ]
// ��e�탁�b�Z�[�W�̏������s��
//================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT: // �E�B���h�E���`��X�V����
		{
			//DrawDirectX9();
			ValidateRect(hWnd, NULL); //�E�B���h�E���X�V
			break;
		}
		case WM_DESTROY: // �E�B���h�E�j�����b�Z�[�W
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN: 
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{// �I�����b�Z�[�W

					int nID = MessageBox(hWnd, L"�I�����܂����H", L"�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
					if (nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
			break;
		}
		case WM_CLOSE:
		{
			int nID = MessageBox(hWnd, L"�I�����܂����H", L"�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}
		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND GetWindow(void)
{
	return g_hWnd;
}