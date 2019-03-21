#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Dice.h"
namespace game_framework
{
	Dice::Dice(): _diceNumber(0){}

	int Dice::GetDiceNumber() {
		return _diceNumber;
	}
	void Dice::TossDice() {
	}

	void Dice::LoadBitmap() {
		_one.LoadBitmap(IDB_DICEONE);
		_two.LoadBitmap(IDB_DICETWO);
		_three.LoadBitmap(IDB_DICETHREE);
		_four.LoadBitmap(IDB_DICEFOUR);
		_five.LoadBitmap(IDB_DICEFIVE);
		_six.LoadBitmap(IDB_DICESIX);
		
	}
	void Dice::OnShow() {
		_one.SetTopLeft(580, 420);
		_two.SetTopLeft(580, 420);
		_three.SetTopLeft(580, 420);
		_four.SetTopLeft(580, 420);
		_five.SetTopLeft(580, 420);
		_six.SetTopLeft(580, 420);
	}
}