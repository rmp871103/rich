#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include"Station.h"
namespace game_framework
{
	Station::Station():_referenceX(0), _referenceY(0),_isEmpty(false) { isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false; }
	Station::Station(int X,int Y) : _referenceX(0), _referenceY(0), _isEmpty(false),x(X),y(Y)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}
	void Station::OnShow()
	{
		if (x<639 && x>-639 && y<479 && y>-479)
		{
			station.SetTopLeft(x, y);
			station.ShowBitmap();
		}
		
	}

	void Station::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Station::LoadBitmap()
	{

		station.LoadBitmap(IDB_dot, RGB(255, 255, 255));
	}

	void Station::OnMove()
	{
		const int STEP_SIZE = 10;
		//animation.OnMove();
		if (_referenceX + STEP_SIZE <= 0) {
			if (isMovingLeft)
			{
				x += STEP_SIZE;
				_referenceX += STEP_SIZE;
			}
		}
		if (_referenceX - STEP_SIZE >= -1280) {
			if (isMovingRight)
			{
				x -= STEP_SIZE;
				_referenceX -= STEP_SIZE;
			}
				
		}
		if (_referenceY + STEP_SIZE <= 0) {
			if (isMovingUp)
			{
				y += STEP_SIZE;
				_referenceY += STEP_SIZE;

			}
				
		}
		if (_referenceY - STEP_SIZE >= -1920) {
			if (isMovingDown)
			{
				y -= STEP_SIZE;
				_referenceY -= STEP_SIZE;
			}
				
		}
	}
	void Station::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Station::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Station::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Station::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	

}
