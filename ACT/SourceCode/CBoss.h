#pragma once
#include"CCharacter.h"		//キャラクタークラス

/**********************************
* 		ボスクラス
*	***/

class CBoss
	: public CCharacter  //キャラクタークラスを継承
{
	public:
		CBoss();//コンストラクタ
		~CBoss() override ;//デストラクタ

		struct CHARA
		{
			int x;
			int y;
		};
		
		//動作関数
		void Update() override;//override:再定義前の関数が仮想関数かチェックできる
								//		仮想関数でない場合はエラーになる
		//描画関数
		void Draw(CCamera* pCamera) override;
		//アニメーション処理
		void Animation();
		void AttackPattern1();
		void AttackPattern2();

		CHARA m_Boss;


private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	//攻撃の処理
	bool	m_Atak1;
	bool	m_Atak2;

};
