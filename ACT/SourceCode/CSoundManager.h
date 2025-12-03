#pragma once
#include"CSound.h"

/************************************
*     サウンドマネージャークラス
*		Manager(マネージャー)：管理者
*			Singleton(シングルトン：デザインパターンの一つ）で作成
**/
class CSoundManager
{
public:
	//サウンドリスト列挙型
	enum enList 
	{
		BGM_Bonus,		//ボーナスステージ
		SE_Jump,		//ジャンプ
		SE_Clear,		//クリア
		SE_EX,			//爆発音

		BGM_Title,			//タイトル
		BGM_Main,			//メイン
		BGM_Kuria,			//クリア
		BGM_GameOver,		//ゲームオーバー

		//音が増えたら「ここ」に追加しえください
		max,			//最大数
	};
public:
	//インスタンス習得（唯一のアクセス経路）
	//※関数の前にstaticをつけることでインスタンス生成しなくても使用できる
	static CSoundManager* GetInstance()
	{
		//唯一のインスタンスを作成する
		//※staticで作成されたので2回目以降は、下の１行は無視される
		static CSoundManager s_Instace;		//s_:staticの意味
		return &s_Instace;
	}

	//CSoundManager();
	~CSoundManager();

	//サウンドデータ読込関数
	bool	Load(HWND hWnd);
	//サウンドデータ解放関数
	void Release();

	//SEを再生する
	static void PlaySE(enList list) {
		CSoundManager::GetInstance()->m_pSound[list]->PlaySE();
	}
	//ループ再生する
	static void PlayLoop(enList list) {
		CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();
	}
	//停止する
	static void Stop(enList list) {
		CSoundManager::GetInstance()->m_pSound[list]->Stop();
	}

private://外部からアクセス不可能
		//外部からコンストラクタへのアクセスを禁止する
	CSoundManager();
	//コピーコンストラクタによるコピーを禁止する
	//「=delete」で関数の定義を削除できる
	CSoundManager(const CSoundManager& rhs) = delete;
	//代入演算子によるコピーを禁止する
	//operator（オペレータ）：演算子のオーバーロードで、演算子の中身を拡張できる
	CSoundManager& operator = (const CSoundManager& rhs) = delete;

private: 
	CSound* m_pSound[enList::max];
};

