#pragma once
namespace game_framework
{
	class Role
	{
	public:
		Role();
		int GetCameraX();
		int GetCameraY();
		void SetRoleTurn(bool flag);
		void SetStepNum(int dieNum); //步數
		void ToNextState(int nextX, int nextY); //去下一個點
		void OnMove();  //視角切換
		void OnShow();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void LoadBitmap();

	private:
		CMovingBitmap _rolePicture;
		int _x, _y, _stepNum, _referenceX, _referenceY;
		bool _roleTurn;
		bool _isMovingDown;
		bool _isMovingLeft;
		bool _isMovingRight;
		bool _isMovingUp;
	};

}