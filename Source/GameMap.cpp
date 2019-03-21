#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	GameMap::GameMap()
		:x(0), y(0), MW(640), MH(480)
	{
		Initialize();
	}
	
	int GameMap::GetX1()
	{
		return x;
	}

	int GameMap::GetY1()
	{
		return y;
	}
	

	void GameMap::Initialize()
	{
		int map_init[5][3] = { {0,1,2},
							   {3,4,5},
							   {6,7,8},
						       {9,10,11},
						       {12,13,14} };
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 3; j++)
				map[i][j] = map_init[i][j];
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void GameMap::LoadBitmap()
	{
		zero.LoadBitmap(IDB_zero);
		one.LoadBitmap(IDB_one);
		two.LoadBitmap(IDB_two);
		three.LoadBitmap(IDB_three);
		four.LoadBitmap(IDB_four);
		five.LoadBitmap(IDB_five);
		six.LoadBitmap(IDB_six);
		seven.LoadBitmap(IDB_seven);
		eight.LoadBitmap(IDB_eight);
		nine.LoadBitmap(IDB_nine);
		ten.LoadBitmap(IDB_ten);
		eleven.LoadBitmap(IDB_eleven);
		twelve.LoadBitmap(IDB_twelve);
		thirsteen.LoadBitmapA(IDB_thirsteen);
		fourteen.LoadBitmapA(IDB_fourteen);

	}

	void GameMap::OnMove()
	{
		const int STEP_SIZE = 10;
		//animation.OnMove();
		if( x + STEP_SIZE <= 0){
			if (isMovingLeft)
				x += STEP_SIZE;
		}
		if( x - STEP_SIZE >= -1280){
			if (isMovingRight)
				x -= STEP_SIZE;
		}
		if( y + STEP_SIZE <= 0){
			if (isMovingUp)
				y += STEP_SIZE;
		}
		if( y - STEP_SIZE >= -1920){
			if (isMovingDown)
				y -= STEP_SIZE;
		}
	}

	void GameMap::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void GameMap::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void GameMap::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void GameMap::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	

	void GameMap::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void GameMap::OnShow()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 5; j++)
			{
				if (x + (MW*i) < 639 && x + (MW*i) > -639 && y + (MH*j) < 479 && y + (MH*j) > -479) {
					switch (map[j][i])
					{
					case 0:
						zero.SetTopLeft(x + (MW*i), y + (MH*j));//
						zero.ShowBitmap();
						break;
					case 1:
						one.SetTopLeft(x + (MW*i), y + (MH*j));//
						one.ShowBitmap();
						break;
					case 2:
						two.SetTopLeft(x + (MW*i), y + (MH*j));
						two.ShowBitmap();
						break;
					case 3:
						three.SetTopLeft(x + (MW*i), y + (MH*j));//
						three.ShowBitmap();
						break;
					case 4:
						four.SetTopLeft(x + (MW*i), y + (MH*j));//
						four.ShowBitmap();
						break;
					case 5:
						five.SetTopLeft(x + (MW*i), y + (MH*j));//
						five.ShowBitmap();
						break;
					case 6:
						six.SetTopLeft(x + (MW*i), y + (MH*j));//
						six.ShowBitmap();
						break;
					case 7:
						seven.SetTopLeft(x + (MW*i), y + (MH*j));//
						seven.ShowBitmap();
						break;
					case 8:
						eight.SetTopLeft(x + (MW*i), y + (MH*j));//
						eight.ShowBitmap();
						break;
					case 9:
						nine.SetTopLeft(x + (MW*i), y + (MH*j));//
						nine.ShowBitmap();
						break;
					case 10:
						ten.SetTopLeft(x + (MW*i), y + (MH*j));//
						ten.ShowBitmap();
						break;
					case 11:
						eleven.SetTopLeft(x + (MW*i), y + (MH*j));//
						eleven.ShowBitmap();
						break;
					case 12:
						twelve.SetTopLeft(x + (MW*i), y + (MH*j));//
						twelve.ShowBitmap();
						break;
					case 13:
						thirsteen.SetTopLeft(x + (MW*i), y + (MH*j));//
						thirsteen.ShowBitmap();
						break;
					case 14:
						fourteen.SetTopLeft(x + (MW*i), y + (MH*j));//
						fourteen.ShowBitmap();
						break;
					default:
						ASSERT(0);
					}
				}
			}
	}
}