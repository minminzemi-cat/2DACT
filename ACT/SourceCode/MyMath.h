#pragma once

//ベクトル構造体
struct VECTOR2
{
	int x;
	int y;

	VECTOR2( int xSrc, int ySrc)
		:x( xSrc )
		,y( ySrc )
	{}
	VECTOR2()
		:VECTOR2(0, 0)
	{ }
};