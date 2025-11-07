#include "CStage.h"
#include<stdio.h>		//ファイルの入出力で必要
#include<crtdbg.h>		//ASSERTマクロで必要
#include<string.h>		//strtok_s関数で必要
#include<stdlib.h>		//atoi関数で必要

CStage::CStage()
	:m_pImg			(nullptr)
	, m_Chip		( 0 , 0 , 32 , 32 )		//チップ一つ当たり縦横32
	, m_Data		()
	, m_MapMax		()
	, m_ppData		( nullptr )
	,m_Position		()
{
}

CStage::~CStage()
{
	ReleaseData();//csvデータ破棄 

	m_pImg = nullptr;
}

void CStage::Update()
{
}

void CStage::Draw( CCamera* pCamera)
{
	//ステージの表示座標を算出
	m_Position = pCamera->CalcToStagePosition();

	//縦に15個描画
	for (int y = 0; y < m_MapMax.y; y++)
	{
		for (int x = 0; x < m_MapMax.x; x++)
		{
			//一番奥の模様（画像固定）

		m_pImg->BBlt(		//画像の座標から 目的のものを呼び出す
			x * m_Chip.w + m_Position.x,	//x方向にチップ幅分ずらして一つずつ表示
			y * m_Chip.h,					//ｙ方向にチップ高さ分ずらして一つずつ表示
			m_Chip.w,		
			m_Chip.h,
			1* m_Chip.w,	//1つ目のチップを固定
			96);			//ひとまず９６で固定

		//15番目の画像は透過色なので表示する必要がないためスキップする
		if (m_ppData[y][x] == 15)		continue;

		//外壁や乗れる床（データ依存）
		m_pImg->TransBlt(		//画像の座標から 目的のものを呼び出す
			x * m_Chip.w + m_Position.x,	//x方向にチップ幅分ずらして一つずつ表示
			y * m_Chip.h,					//ｙ方向にチップ高さ分ずらして一つずつ表示
			m_Chip.w,
			m_Chip.h,
			m_ppData[y][x] * m_Chip.w,	//データ依存で読み込みチップ変更
			96);						//９６で固定
		}
	}
}

//マップデータ読み込み
bool CStage::LoadData(const char* fileName )
{

	FILE* pf;
	errno_t error;

	//ファイルを開く
	error = fopen_s(&pf, fileName, "r");
	if (error != 0)
	{
		_ASSERT_EXPR(false, L"マップデータ読み込み失敗");
		return false;
	}
	//一行分の最大取得文字数
	char line[512] = "";	//""を入れて0で初期化

	char delim[] = ",";		//デリミタ:区切り文字.csvデータなので「,（カンマ）]を指定
	char* ctx = nullptr;	//内部使用
	char* pNext = nullptr;

	//cavの読込最初の行にマップデータの「縦の個数」「横の個数」が入っているので特殊な処理を入れる
	if (fgets(line, 512, pf) == nullptr)
	{
		return false;		//読み込むデータがないので終了
	}
	//一行目データを取り出し","一つ目までを取り出す
	pNext = strtok_s(line, delim, &ctx);
	//一行目データがマップデータの「縦の個数」「横の個数」の２種類なので２回処理する
	for (int cnt = 0; cnt < 2; cnt++)
	{
		switch (cnt) {
		case 0:m_MapMax.y = atoi(pNext); break;
		case 1:m_MapMax.x = atoi(pNext); break;
		default:						 break;
		}
		pNext = strtok_s(nullptr, delim, &ctx);
	}

	//int型ポインタをマップデータの縦の個数分だけ動的メモリ確保
	m_ppData = new int* [m_MapMax.y]();


	//マップデータ縦の最大数分処理する
	for (int line_no = 0; line_no < DATA_Y_MAX; line_no++)
	{
		if (fgets(line, 512, pf) == nullptr)
		{
			break;		//読み込むデータがなくなったら終了
		}
		//カンマ区切りで一つデータを取り出す
		pNext = strtok_s(line, delim, &ctx);

		//int型をマップデータの横の個数分だけ動的メモリ確保
		m_ppData[line_no] = new int[m_MapMax.x]();

		//マップデータ横の最大分処理する
		for (int x = 0; x < m_MapMax.x; x++)
		{
			if (pNext == nullptr)
			{
				break;	//データなくなったら終了
			}
			m_ppData[line_no][x] = atoi(pNext);			//atoi関数：文字列をint型に変換
			pNext = strtok_s(nullptr, delim, &ctx);		//注意：第一引数はnullptr
		}
	}

	//ファイルを閉じる
	fclose(pf);

	return true;
}

//マップデータ解放
void CStage::ReleaseData()
{
	if (m_ppData != nullptr)
	{
		//マップデータ縦の個数分処理する（配列の最後から順番）
		for (int line_no = m_MapMax.y - 1; line_no >= 0; line_no--)
		{
			//データが入っているか？
			if (m_ppData[line_no] != nullptr)
			{
				//マップデータ横の個数分を確保したメモリを破棄
				delete[]m_ppData[line_no];	//配列を確保したのでdelete[]を使う
				m_ppData[line_no] = nullptr;//nullptrで初期化
			}
		}

		//マップデータ縦の個数分を確保したメモリを破棄
		delete[]m_ppData;
		m_ppData = nullptr;//nullptrで初期化
	}
}


#if 0//不要なので無効化
//マップデータ読み込み
bool CStage::LoadData()
{
	int data[DATA_Y_MAX][DATA_X_MAX]
	{
		/*		  _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11_12,_13,_14,_15,_16,_17,_18,_19*/
		/*	_0*/ { 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
		/*  _1*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _2*/ { 7,15,15,15,15,15,12,13,14,15,15,15,15,15,15,15,15,15,15,15},
		/*  _3*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _4*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _5*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _6*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _7*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _8*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  _9*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  10*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  11*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  12*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  13*/ { 7,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
		/*  14*/ { 9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}
	};

	//上記で作成したマップデータをメンバ変数のマップデータにコピーする
	memcpy_s(m_Data, sizeof(m_Data), data, sizeof(data));

	return true;
}

#endif