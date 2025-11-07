#pragma once
#include"CCamera.h"		//カメラクラス

/**************************************
*		ゲームオブジェクトクラス
*		継承することを前提としたクラス
**/
class CGameObject
{
public:
	CGameObject(){}
	virtual ~CGameObject(){}

	//純粋仮想関数：関数の引数より後ろに「＝０」をつける
	//				このクラスで定義を作成せず、継承先のクラスで作成する
	//				継承先で継承しなかった場合はエラーになる
	virtual void Update() = 0;
	virtual void Draw(CCamera* pCamera) = 0;

private:

};
