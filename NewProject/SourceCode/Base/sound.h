//==============================================================================
//
// �T�E���h���� [sound.h]
//
//==============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_BGM_TITLE = 0,
	SOUND_BGM_GAME,
	SOUND_BGM_GAME_OVER,
	SOUND_BGM_GAME_CLEAR,
	SOUND_SE_CLICK,
	SOUND_SE_GET,
	SOUND_SE_BREAK,
	SOUND_SE_FAILURE,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
#endif