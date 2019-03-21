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
		void SetStepNum(int dieNum); //�B��
		void ToNextState(int nextX, int nextY); //�h�U�@���I
		void OnMove();  //��������
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