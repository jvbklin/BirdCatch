//=================================================================================
//
//    Stage header
//    Author : Lin He                                �쐬�� : 2018/09/14
//
//=================================================================================

#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Background;

//*****************************************************************************
// Stage Class
//*****************************************************************************
class Stage
{
	private:
		int count_frames_;
		int count_seconds_;
		int next_spawn_enemy_index_;

		Background* background_;

	public:
		void Init();
		void Uninit();
		void Update();
		void Draw();
};

#endif