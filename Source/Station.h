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
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����

	protected:
		int x, y;
		bool _isEmpty;
		int _referenceX, _referenceY;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		CMovingBitmap station;
	};

}