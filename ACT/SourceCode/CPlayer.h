#pragma once
#include "CCharacter.h" //キャラクタークラス
#include"CBoss.h"

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
		Attack,     //攻撃

		None = -1,	//未設定
	};

	//キャラクター構造体
	struct CHARA
	{
		int x;
		int y;
	};

public:
	CPlayer();//コンストラクタ
	~CPlayer();//デストラクタ

	//動作関数
	void Update();
	//描画関数
	void Draw( CCamera* pCamera);

	//画像が三つあるのでそれぞれ読み込むための関数
	void ThreeSetImage(CImage* pImg, CImage* pImg2, CImage* pImg3)
	{
		m_pImg = pImg;
		m_pImg_Right = pImg;
		m_pImg_Left = pImg2;
		m_pImg_Atk = pImg3;
	}
private:
	//操作処理
	void KeyInput();
	//アニメーション処理
	void Animation();

	CImage* m_pImg_Right;
	CImage* m_pImg_Left;
	CImage* m_pImg_Atk;
	

private:
	CHARA		m_Player;

	CBoss*		m_Boss;

	int			m_GroundPos;	//地面の位置（定数でも可）

	VECTOR2		m_OldPosition;	//移動前の座標

	int			m_Action;		//動作状態

	bool		m_Atacking;		//攻撃中

	//ジャンプ処理
	bool		m_Jumping;	//ジャンプ中
	float		m_JumpAcc;	//加速度:Acceleration(ジャンプ減速用)
	float		m_JumpPower;//ジャンプ力（定数でも可）
	float		m_Gravity;	//重力（定数でも可）
	
	//円と円の当たり判定
	bool CircleCollisionDetection(
		float Ax, float Ay, float Ar,		//円Aのｘ、ｙ座標と半径
		float Bx, float By, float Br);		//円Bのｘ、ｙ座標と半径

	//プレイヤーのHP
	int        m_PlayerHP = 100;



};