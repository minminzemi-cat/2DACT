#pragma once
#include"CCharacter.h"		//キャラクタークラス

/**********************************
* 		ボスクラス
*	***/

class CBoss
	: public CCharacter  //キャラクタークラスを継承
{
public:
	//動作処理列挙型
	enum enBossAction
	{
		Wait = 0,	//待機
		
		Attack,     //攻撃

		dei,		//死亡

		None = -1,	//未設定
	};
	public:
		CBoss();//コンストラクタ
		~CBoss() override ;//デストラクタ

		//キャラクター構造体
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

		DWORD nowTime = 0;		//現在の時間.

private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	//攻撃の処理
	bool	m_Atak1;
	bool	m_Atak2;

};
