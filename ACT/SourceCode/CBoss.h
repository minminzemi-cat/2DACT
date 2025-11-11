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
private:
	void AttackPattern1();
	void AttackPattern2();
	void Animation();

private:
	CHARA m_Boss;


};
