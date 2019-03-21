#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Role.h"

namespace game_framework
{
	Role::Role()
		:_referenceX(0), _referenceY(0), _stepNum(0), _x(600), _y(400) {
		_roleTurn = _isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
	}

	int Role::GetCameraX()
	{
		return _x - 320;
	}
	int Role::GetCameraY()
	{
		return _y - 240;
	}
	void Role::SetRoleTurn(bool flag)
	{
		_roleTurn = flag;
	}
	void Role::SetStepNum(int dieNum)
	{
		if (_stepNum == 0 && _roleTurn)
			_stepNum = dieNum;
	}
	void Role::ToNextState(int nextX, int nextY)
	{
		int sizeStep = 1;
		if (_stepNum != 0 && _roleTurn)
		{
			if (_x != nextX)
			{
				_x += sizeStep;
			}
			if (_y != nextY)
			{
				_y += sizeStep;
			}
		}
		else
			_roleTurn = false;
		_stepNum -= 1;
	}
	void Role::OnMove()
	{
		const int STEP_SIZE = 10;
		if (_referenceX + STEP_SIZE <= 0 && _isMovingLeft) {
			_x += STEP_SIZE;
			_referenceX += STEP_SIZE;
		}
		if (_referenceX - STEP_SIZE >= -1280 && _isMovingRight) {
			_x -= STEP_SIZE;
			_referenceX -= STEP_SIZE;
		}
		if (_referenceY + STEP_SIZE <= 0 && _isMovingUp) {
			_y += STEP_SIZE;
			_referenceY += STEP_SIZE;
		}
		if (_referenceY - STEP_SIZE >= -1920 && _isMovingDown) {
			_y -= STEP_SIZE;
			_referenceY -= STEP_SIZE;
		}
	}
	void Role::LoadBitmap() {
		_rolePicture.LoadBitmap(IDB_BALL);
	}
	void Role::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void Role::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void Role::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void Role::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}
	void Role::OnShow()
	{
		if (_x <= 640 && _x >= 0 && _y >= 0 && _y <= 480) {
			_rolePicture.SetTopLeft(_x, _y);
			_rolePicture.ShowBitmap();
		}
	}
}