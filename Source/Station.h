#pragma once

namespace game_framework
{
	class Station  
	{
	public:
		Station(int, int);
		Station();
		//	int GetX();
		//	int GetY();
		void SetXY(int nx, int ny);
		//	bool IsEmpty();
		void LoadBitmap();
	//	void Initialize();
		void OnShow();
		void OnMove();
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動

	protected:
		int x, y;
		bool _isEmpty;
		int _referenceX, _referenceY;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		CMovingBitmap station;
	};

}