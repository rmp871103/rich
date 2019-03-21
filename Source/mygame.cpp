/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(IDB_BACKGROUND);
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}
	


	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		//logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		//logo.ShowBitmap();
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		if (ENABLE_GAME_PAUSE)
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), STATION(81)
	{  
		Role* role;
		role = new Role;
		players.push_back(role);
		station = new Station[STATION];

	}

	CGameStateRun::~CGameStateRun()
	{
		delete [] station;
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;

		/*for (int i = 0; i < STATION; i++) {				// 設定球的起始座標
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			station[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);

		}*/
		////////  at map[0] ////////////                ////////  at map[1] ////////////		////////  at map[2] ////////////
		station[0].SetXY(561, 274);						station[76].SetXY(1128, 291);			station[58].SetXY(1590, 377);
		station[1].SetXY(494, 332);						station[77].SetXY(1041, 200);			station[59].SetXY(1481, 276);
		station[2].SetXY(550, 416);						station[78].SetXY(943, 274);			station[60].SetXY(1386, 226);
														station[80].SetXY(699, 280);			station[61].SetXY(1427, 414);
		////////  at map[3] ////////////			    ////////  at map[4] ////////////		////////  at map[5] ////////////		
		station[3].SetXY(560, 560);						station[72].SetXY(1155, 871);			station[55].SetXY(1739, 863);
		station[4].SetXY(437, 571);						station[73].SetXY(905, 774);			station[56].SetXY(1692, 662);
		station[5].SetXY(344, 554);						station[74].SetXY(994, 677);			station[57].SetXY(1553, 517);
		station[6].SetXY(284, 620);						station[75].SetXY(1064, 528);			station[62].SetXY(1323, 634);
		station[7].SetXY(250, 680);						station[79].SetXY(853, 501);			station[63].SetXY(1426, 704);
		station[8].SetXY(380, 1080);															station[64].SetXY(1312, 767);
		station[9].SetXY(400, 760);																station[65].SetXY(1416, 840);
		station[10].SetXY(456, 870);															station[66].SetXY(1514, 909);
		station[11].SetXY(430, 980);															
		////////  at map[6] ////////////				////////  at map[7] ////////////		////////  at map[8] ////////////
		station[11].SetXY(223, 961);					station[68].SetXY(1065, 1106);			station[50].SetXY(1686, 1364);
		station[12].SetXY(367, 1000);					station[69].SetXY(939, 1122);		    station[51].SetXY(1515, 1323);
		station[13].SetXY(253, 1135);					station[70].SetXY(896, 1022);			station[52].SetXY(1556, 1222);
		station[14].SetXY(213, 1235);					station[71].SetXY(1039, 981);			station[53].SetXY(1665, 1141);
		station[15].SetXY(167, 1353);															station[54].SetXY(1725, 987);
																								station[67].SetXY(1310, 1013);
		////////  at map[9] ////////////			    ////////  at map[10] ////////////		////////  at map[11] ////////////
		station[16].SetXY(151, 1508);					station[31].SetXY(743, 1841);			station[42].SetXY(1664, 1853);
		station[17].SetXY(172, 1593);					station[32].SetXY(868, 1788);			station[43].SetXY(1500, 1853);
		station[18].SetXY(129, 1697);					station[33].SetXY(1020, 1785);			station[44].SetXY(1346, 1784);
		station[19].SetXY(129, 1823);					station[34].SetXY(1155, 1759);			station[45].SetXY(1434, 1713);
		station[20].SetXY(319, 1827);					station[35].SetXY(1107, 1846);			station[46].SetXY(1351, 1632);
		station[21].SetXY(424, 1782);															station[47].SetXY(1460, 1582);
		station[22].SetXY(533, 1856);															station[48].SetXY(1575, 1560);
																								station[49].SetXY(1789, 1500);
		////////  at map[12] ////////////				////////  at map[13] ////////////		////////  at map[13] ////////////
		station[23].SetXY(502, 1969);					station[28].SetXY(703, 2111);			station[37].SetXY(1320, 2016);
		station[24].SetXY(367, 2000);					station[29].SetXY(703, 2039);			station[38].SetXY(1411, 2092);
		station[25].SetXY(273, 2073);					station[30].SetXY(703, 1946);			station[39].SetXY(1497, 2018);
		station[26].SetXY(427, 2109);					station[36].SetXY(1175, 1958);			station[40].SetXY(1639, 1967);
		station[27].SetXY(543, 2108);															station[41].SetXY(1735, 1959);

		gamemap.Initialize();
		background.SetTopLeft(BACKGROUND_X, 0);				// 設定背景的起始座標
		help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// 指定剩下撞擊數的座標
		CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//
		if (background.Top() > SIZE_Y)
			background.SetTopLeft(60, -background.Height());
		background.SetTopLeft(background.Left(), background.Top() + 1);

		if (picX <= SIZE_Y) {
			picX += 100;
			picY += 100;
		}
		else {
			picX = picY = 0;
		}
		gamemap.OnMove();
		for (int i = 0; i < STATION; i++)
			station[i].OnMove();
		for (unsigned int i = 0; i < 1; i++) {
			players[i]->OnMove();
		}
		//
		// 移動球
		//
		//
		// 移動擦子
		//

		//
		// 判斷擦子是否碰到球
		//
		/*
		for (i = 0; i < NUMBALLS; i++)
			if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
				ball[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_DING);
				hits_left.Add(-1);
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		//
		// 移動彈跳的球
		//
		bball.OnMove();
		*/
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		gamemap.LoadBitmap();
		for (unsigned int i = 0; i < 1; i++) {
			players[i]->LoadBitmap();
		}
		for (int i = 0; i < STATION; i++)
			station[i].LoadBitmap();
		x = gamemap.GetX1();
		y = gamemap.GetY1();
		background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		corner.ShowBitmap(background);							// 將corner貼到background
																// 載入圖形
		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const int STEP_SIZE = 10;
		if (nChar == KEY_LEFT ) {
			gamemap.SetMovingLeft(true);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingLeft(true);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingLeft(true);
			}
		}
		//////////////////////////////////////////////////////

		if (nChar == KEY_RIGHT) {
			gamemap.SetMovingRight(true);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingRight(true);
			for (unsigned int i = 0 ;i < 1; i++) {
				players[i]->SetMovingRight(true);
			}
			
		}

		//////////////////////////////////////////////////////

		if (nChar == KEY_UP ) {
			gamemap.SetMovingUp(true);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingUp(true);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingUp(true);
			}
		}

		//////////////////////////////////////////////////////
		if (nChar == KEY_DOWN) {
			gamemap.SetMovingDown(true);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingDown(true);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingDown(true);
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)  
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
		{
			gamemap.SetMovingLeft(false);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingLeft(false);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingLeft(false);
			}
		}
			
		if (nChar == KEY_RIGHT)
		{
			gamemap.SetMovingRight(false);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingRight(false);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingRight(false);
			}
		}
			
		if (nChar == KEY_UP)
		{
			gamemap.SetMovingUp(false);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingUp(false);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingUp(false);
			}
		}
			
		if (nChar == KEY_DOWN)
		{
			gamemap.SetMovingDown(false);
			for (int i = 0; i < STATION; i++)
				station[i].SetMovingDown(false);
			for (unsigned int i = 0; i < 1; i++) {
				players[i]->SetMovingDown(false);
			}
		}
			
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		gamemap.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		gamemap.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		gamemap.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		gamemap.SetMovingRight(false);
	}



	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
	//	background.ShowBitmap();			// 貼上背景圖
		help.ShowBitmap();					// 貼上說明圖
		hits_left.ShowBitmap();

		gamemap.OnShow();					// 貼上擦子
		for (int i = 0; i < STATION; i++)
			station[i].OnShow();
		for (unsigned int i = 0; i < 1; i++) {
			players[i]->OnShow();
		}
		//
		//  貼上左上及右下角落的圖
		//
		corner.SetTopLeft(0, 0);
		corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		corner.ShowBitmap();

		
	}
}