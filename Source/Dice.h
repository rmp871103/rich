#pragma once
namespace game_framework
{
	class Dice {
	public:
		Dice();
		int GetDiceNumber();
		void TossDice();
		void OnShow();
		void LoadBitmap();

	private:
		CMovingBitmap _one, _two, _three, _four, _five, _six;
		int _diceNumber;
	};
}