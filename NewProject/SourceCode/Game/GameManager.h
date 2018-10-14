//=================================================================================
//
//    GameManager header
//    Author : Lin He                                作成日 : 2018/10/07
//
//=================================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

//*****************************************************************************
// クラス宣言
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
	// [ GameManagerインスタンス取得関数 ]
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
	// [ スコアアップ関数 ]
	//
	// [ Parameters ]
	// [int]	num	: スコアアップ数(負数も大丈夫)
	//=================================================================
	void AddScore(int num);

	//=================================================================
	// [ ライフダメージ関数 ]
	//
	// [ Parameters ]
	// [int]	num	: ライフダメージ
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