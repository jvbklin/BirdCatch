//=================================================================================
//
//    GameManager header
//    Author : Lin He                                �쐬�� : 2018/10/07
//
//=================================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class NumberManager;

//*****************************************************************************
// GameManager Class (Singleton)
//*****************************************************************************
class GameManager {

private:
	int score_;
	int player_life_;

	NumberManager* number_manager_;

public:
	//=================================================================
	// [ GameManager�C���X�^���X�擾�֐� ]
	//=================================================================
	static GameManager& Instance() {
		static GameManager thisGameManager;
		return thisGameManager;
	}

	void Init();
	void Uninit();
	//void Update();
	//void Draw();

	//=================================================================
	// [ �X�R�A�A�b�v�֐� ]
	//
	// [ Parameters ]
	// [int]	num	: �X�R�A�A�b�v��(���������v)
	//=================================================================
	void AddScore(int num);

	//=================================================================
	// [ ���C�t�_���[�W�֐� ]
	//
	// [ Parameters ]
	// [int]	num	: ���C�t�_���[�W
	//=================================================================
	void DamageLife(int num);

	int GetPlayerLife();
	int GetScore();

private:
	GameManager();                            // constructor hidden
	GameManager(GameManager const&) {};          // copy constructor hidden
	~GameManager();                           // destructor hidden
};

#endif