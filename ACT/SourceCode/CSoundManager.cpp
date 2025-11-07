#include "CSoundManager.h"
#include"MyMacro.h"

CSoundManager::CSoundManager()
	:m_pSound	()
{
	for (int i = 0; i < enList::max; i++)
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release(); 

	//インスタンス破棄
	for (int i = enList::max - 1; i >= 0; i--)
	{
		SAFE_DELETE( m_pSound[i] );
	}
}

//サウンドデータ読込関数
bool CSoundManager::Load(HWND hWnd)
{
#if 0
	if (m_pSound[enList::BGM_Bonus]->Open(
		"Data\\Sound\\BGM\\BonusGameHouse.mp3",
		"BGM_Bonus",
		hWnd) == false)
	{
		return false;
	}
	if (m_pSound[enList::SE_Jump]->Open(
		"Data\\Sound\\SE\\Jump.wav",
		"SE_Jump",
		hWnd) == false)
	{
		return false;
	}

	if (m_pSound[enList::SE_Clear]->Open(
		"Data\\Sound\\SE\\Clear.wav",
		"SE_Clear",
		hWnd) == false)
	{
		return false;
	}

# else
	struct SoundList
	{
		int listNo;			//enList列挙型を設定
		char path[256];		//ファイルの名前（パス付き）
		char alias[32];		//エイリアス名
	};
	SoundList SList[] =
	{
		{enList::SE_Jump,		"Data\\Sound\\SE\\Jump.wav",			"SE_Jump"},
		{enList::BGM_Bonus,		"Data\\Sound\\BGM\\BonusGameHouse.mp3",	"BGM_Bonus"},
		{enList::SE_Clear,		"Data\\Sound\\SE\\Clear.wav",			"SE_Clear"},
	};
	//配列の最大要素数を算出（配列全体のサイズ/配列一つ分のサイズ）
	int list_max = sizeof(SList) / sizeof( SList[0] );
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd) == false)
		{
			return false;
		}
	}

#endif
	return true;
}

//サウンドデータ解放関数
void CSoundManager::Release()
{
	for (int i = enList::max - 1; i >= 0; i--)
	{
		if (m_pSound[i] != nullptr)
		{
			m_pSound[i]->Close();
		}
	}
}
