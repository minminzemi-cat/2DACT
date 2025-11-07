#pragma once
#include"CCharacter.h"		//キャラクタークラス

/**********************************
*		エネミークラス
***/

class CEnemy
	: public CCharacter  //キャラクタークラスを継承
{
public:
		CEnemy();//コンストラクタ
		~CEnemy() override ;//デストラクタ
		
		//動作関数
		void Update() override;//override:再定義前の関数が仮想関数かチェックできる
								//		仮想関数でない場合はエラーになる
		//描画関数
		void Draw( CCamera* pCamera) override;

private:

	
};