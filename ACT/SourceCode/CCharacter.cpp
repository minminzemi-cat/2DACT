#include "CCharacter.h"

CCharacter::CCharacter()
	: m_pImg		( nullptr )
	, m_Position(0, 0)
	, m_MoveSpeed(4)
	, m_FrameSplit()
	, m_FrameCounter(0)
	, m_LookingRight(false)
{
}

CCharacter::~CCharacter()
{
	//ŠO•”‚Åì¬‚³‚ê‚½Ò‚È‚Ì‚Å‚±‚±‚Å‚Í”jŠü‚µ‚È‚¢
	m_pImg = nullptr; 
}
