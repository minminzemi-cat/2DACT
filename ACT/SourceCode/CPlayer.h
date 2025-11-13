#pragma once
#include "CCharacter.h" //キャラクタークラス


/********************************************
*		プレイヤークラス
**/
class CPlayer
	:public CCharacter  //キャラクタークラスを継承
{
public:
	//動作処理列挙型
	enum enAction
	{
		Wait = 0,	//待機
		MoveLeft,	//左移動
		MoveRight,	//右移動

		None = -1,	//未設定
	};
public:
	CPlayer();//コンストラクタ
	~CPlayer();//デストラクタ

	//動作関数
	void Update();
	//描画関数
	void Draw( CCamera* pCamera );

private:
	//操作処理
	void KeyInput();
	//アニメーション処理
	void Animation();

	//左向きに歩くようにアニメーション追加
	void Animation2();

private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	VECTOR2		m_OldPosition;	//移動前の座標

	int			m_Action;		//動作状態

	//アタック処理
	bool		m_Attacking;	//攻撃中

	//ジャンプ処理
	bool		m_Jumping;	//ジャンプ中
	float		m_JumpAcc;	//加速度:Acceleration(ジャンプ減速用)
	float		m_JumpPower;//ジャンプ力（定数でも可）
	float		m_Gravity;	//重力（定数でも可）

};