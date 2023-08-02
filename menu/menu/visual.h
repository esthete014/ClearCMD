// / ============================= \
// | -------  esthete014  -------- |
// | ============================= |
// |     || copyright 2023 ||      |
// |     || Nikolay        ||      |
// |     || Kochetov       ||      |
// | _____________________________ |
// | https://github.com/esthete014 |
// \ ============================= /

#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include <unordered_map>
#include "block.h"
//#define _WIN32_WINNT 0x0500


//#define Xpoints 15
//#define Ypoints 10

//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	wchar_t msg[32];
//	switch (uMsg)
//	{
//	case WM_SYSKEYDOWN:
//		swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
//		OutputDebugString(msg);
//		break;
//
//	case WM_SYSCHAR:
//		swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
//		OutputDebugString(msg);
//		break;
//
//	case WM_SYSKEYUP:
//		swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
//		OutputDebugString(msg);
//		break;
//
//	case WM_KEYDOWN:
//		swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
//		OutputDebugString(msg);
//		break;
//
//	case WM_KEYUP:
//		swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
//		OutputDebugString(msg);
//		break;
//
//	case WM_CHAR:
//		swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
//		OutputDebugString(msg);
//		break;
//
//		/* Handle other messages (not shown) */
//
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}

class Visual {
	bool timetread = false;
	HANDLE hStdOut;
	int focusid = 0;
	std::vector</*std::pair<int,*/ int/*>*/> focus;
	//std::vector</*std::vector<*/int/*>*/> markupVec;
	std::vector</*std::vector<*/Block/*>*/> container;
	std::unordered_map<std::string, myfunc> functions;
	/*markupTable.resize(Xpoints, std::vector<int>(Ypoints, default_value));*/
	
public:
	Visual(std::vector</*std::vector<*/Block/*>*/> layout, std::unordered_map<std::string, myfunc> _functions = std::unordered_map<std::string, myfunc>{}) {
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		HWND consoleWindow = GetConsoleWindow();
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
		SetConsoleTitle(L"Clear CMD Client");
		SetWindowPos(consoleWindow, 0, 315,170, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		Blinking();
		SetConsoleOutputCP(65001);
		std::thread exitkey([] {while (true) { if (GetAsyncKeyState(VK_ESCAPE)) { exit(0); } } });
		exitkey.detach();
		
		//TableFill(markupTable, 0);
		container = layout;
		functions = _functions;
		for (int i = 0; i < layout.size(); i++) {
			/*for (int j = 0; j < layout[i].size(); j++) {*/
			//void* b = (void*)(layout[i][j]);
			//(*static_cast<STR*>(layout[i][j].data));
			//std::cout << layout[i][j].type << ' ';

			//проверка на элементы, которые 100% имеют фокус
			if (layout[i]/*[j]*/.type >= (TYPE)(100)) {
				focus.push_back(i/*std::make_pair(i, j)*/);
				//(*static_cast<BTN*>(layout[i][j].data)).release();
			}
			//проверка на элементы, которые могут иметь фокус
			else if (layout[i]/*[j]*/.type < (TYPE)(100) && layout[i]/*[j]*/.type >= (TYPE)(50)) {
				focus.push_back(i/*std::make_pair(i, j)*/);
			}
			// элементы не имеющие фокус
			else {
				// проверка на динамичность DATETIME для того, чтобы предотвратить конфликт вывода времени и остальных действий 
				if (layout[i]/*[j]*/.type == TYPE::TDATETIME
					&& (*static_cast<DATETIME*>(layout[i]/*[j]*/.data)).dynamic == true) {
					timetread = true;
				}
				/*if (layout[i][j].type == TYPE::TSTR) {
					if ((*static_cast<STR*>(layout[i][j].data)).nameexist) {
						std::cout << *((*static_cast<STR*>(layout[i][j].data)).name) << " | ";
					}
					std::cout << *((*static_cast<STR*>(layout[i][j].data)).strline) << "\n";
				}*/
			}
			/*}*/
		}
		std::string command = "mode con cols=120 lines=33";
		system(command.c_str());

		paint(focusid);

		//std::thread switchfocusthrplus([&]() {while (true) { if (GetAsyncKeyState(VK_TAB)) { focusid++; focusid == container.size() ? focusid = 0 : 0; paint(focusid); Sleep(300); } }});
		//switchfocusthrplus.detach();
		std::thread switchfocusthr([&]() 
			{
				while (true) { 
					if ( GetAsyncKeyState(VK_SHIFT)) {
						int previous = focusid;
						focusid--; focusid < 0 ? focusid = container.size() - 1 : 0;
						paintFocus(focusid, previous);
						Sleep(300); 
					}
					else if (GetAsyncKeyState(VK_TAB)) {
						int previous = focusid;
						focusid++; focusid > container.size() -1 ? focusid = 0 : 0; 
						paintFocus(focusid, previous); Sleep(300);
					}
				}
			}
		);
		switchfocusthr.detach();



		while (1);
		//bool A = false;
		//printBlock(A, 0, 0, 0, 0);
		//printBlock(A, 1, 0, 1, 0);
		//printBlock(A, 1, 2, 4, 7);
		//printBlock(A, 0, 1, 0, 1);

		//printBlockAngles(A, 0, 0, 9, 10);
		//printBlockWalls(A, 0, 0, 9, 10);

		//printBlockAngles(A, 0, 0, 0, 0);
		//printBlockAngles(A, 1, 0, 1, 0);
		//printBlockAngles(A, 1, 2, 4, 7);
		//printBlockAngles(A, 0, 1, 0, 1);

		/*printBlockWalls(A, 0, 0, 5, 5);
		printBlockWalls(A, 6, 0, 6, 7);
		printBlockWalls(A, 0, 2, 1, 2);
		printBlockWalls(A, 0, 3, 0, 3);
		printBlockWalls(A, 0, 6, 0, 6);
		printBlockWalls(A, 3, 7, 5, 9);
		printBlockAngles(A, 0, 0, 5, 5);
		printBlockAngles(A, 6, 0, 6, 7);
		printBlockAngles(A, 0, 2, 1, 2);
		printBlockAngles(A, 0, 3, 0, 3);
		printBlockAngles(A, 0, 6, 0, 6);
		printBlockAngles(A, 3, 7, 5, 9);*/
		/*std::thread openlink([] {while (true) { if (GetAsyncKeyState(VK_F1)) { system("start https://github.com/esthete014/ClearCMD"); } } });
		openlink.detach();*/

	}
	/*void realeseCMDLITE() {
		try {
			build();
		}
		catch (...) {
		}
	}*/
private:
	/*void switchfocus(int id) {
		while (true) { if (GetAsyncKeyState(VK_TAB)) { id++; paint(id); } }
	}*/
	void build() {
		markup();
		//paint();
	}
	void markup() {

	}
	void paintFocus(int focusid, int previous) {
		printBlock(true, container[focusid].start_x, container[focusid].start_y, container[focusid].end_x, container[focusid].end_y);
		printBlock(false, container[previous].start_x, container[previous].start_y, container[previous].end_x, container[previous].end_y);
	}
	void paint(int focusid) {
		for (int i = 0; i < container.size(); i++) {
			printBlock(i == focusid ? true : false, container[i].start_x, container[i].start_y, container[i].end_x, container[i].end_y);
			container[i].printContent(hStdOut);
		}

		//std::vector<int> temp;
		//for (int i = 0; i < 15; i++) {
		//	for (int j = 0; j < 10; j++) {
		//		paintmark[i].push_back(j + (i * 10));
		//	}
		//}
		//for (int i = 0; i < 15; i++) {
		//	for (int j = 0; j < 10; j++) {
		//		bool leftwall = false;
		//		bool upperwall = false;
		//		/*if (paintmark[i][j] != ) {

		//		}*/
		//		if (j == 0 && i == 0) {
		//			
		//		}
		//	}
		//}
	}
	void printBlock(bool focus, int xstart, int ystart, int xend, int yend) {
		int xlength = xend - xstart;
		int ylength = yend - ystart;
		std::string line = "————————————";
		std::string ch1 = "│";
		std::string ch2 = "○";
		if (focus) { line = "════════════"; ch1 = "║"; ch2 = "■"; };
		for (int i = 0; i <= xlength; i++) {
			printByPos(line, (xstart + i) * 12, ystart * 3);
			printByPos(line, (xstart + i) * 12, yend * 3 + 2);
		}
		for (int j = 0; j <= ylength; j++) {
			for (int i = 0; i < 3; i++) {
				if (!((j == 0 && i == 0) || (j == ylength && i == 2))) {

					printByPos(ch1, xstart * 12, (ystart + j) * 3 + i);
					printByPos(ch1, (xend) * 12 + 11, (ystart + j) * 3 + i);
				}
			}
		}
		printByPos(ch2, xstart * 12, ystart * 3);
		printByPos(ch2, xend * 12 + 11, ystart * 3);
		printByPos(ch2, xstart * 12, yend * 3 + 2);
		printByPos(ch2, xend * 12 + 11, yend * 3 + 2);
	}
	//void printBlockAngles(bool focus, int xstart, int ystart, int xend, int yend) {
	//}
	//void printBlockWalls(bool focus, int xstart, int ystart, int xend, int yend) {
	//	int xlength = xend - xstart;
	//	int ylength = yend - ystart;
	//	std::string line = "————————————";
	//	std::string ch = "│";
	//	if (focus) { line = "════════════"; ch = "█"; };
	//	for (int i = 0; i <= xlength; i++) {
	//		/*if (i == 0 && i == xlength) { line = "+----------+"; }
	//		else if (i == 0) { line = "+-----------"; }
	//		else if (i == xlength) { line = "-----------+"; }
	//		else { line = "------------"; }*/
	//		printByPos(line, (xstart + i) * 11, ystart * 2);
	//		printByPos(line, (xstart + i) * 11, (yend + 1) * 2);
	//	}
	//	//for (int i = 0; i <= xlength; i++) 
	//	for (int j = 0; j <= ylength; j++) {
	//		for (int i = 0; i < 3; i++) {
	//			if (!((j == 0 && i == 0) || (j == ylength && i == 2))) {
	//				printByPos(ch, xstart * 11, (ystart + j) * 2 + i);
	//				printByPos(ch, (xend + 1) * 11, (ystart + j) * 2 + i);
	//			}
	//		}
	//	}
	//	/*for (int j = 0; j <= ylength; j++) for (int i = 0; i < 3; i++)*/
	//}
	//void printBlockAngles(bool focus, int xstart, int ystart, int xend, int yend) {
	//	std::string ch = "◘";
	//	if (focus) { ch = "■"; }
	//	printByPos(ch, xstart * 11, (ystart + 0) * 2 + 0);
	//	printByPos(ch, (xend + 1) * 11, (ystart + 0) * 2 + 0);
	//	printByPos(ch, xstart * 11, (ystart + yend - ystart) * 2 + 2);
	//	printByPos(ch, (xend + 1) * 11, (ystart + yend - ystart) * 2 + 2);
	//}
	/*void printBlock(int xstart, int ystart, int xend, int yend) {
		int xlength = xend - xstart;
		int ylength = yend - ystart;
		for (int i = 0; i < xlength; i++) printByPos("++++++++", (xstart + i) * 8, ystart * 3);
		for (int j = 0; j < ylength; j++) for (int i = 0; i < 3; i++) printByPos("+", xstart * 8, ystart * 3 + i);
	}*/
	void printByPos(std::string str, int _x, int _y) {
		COORD cor;
		cor.X = _x;
		cor.Y = _y;
		SetConsoleCursorPosition(hStdOut, cor);
		std::cout << str;
	}
	void Blinking() {
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(hStdOut, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	}
	void TableFill(std::vector<std::vector<int>> &vec, int n) {
		std::vector<int> temp;
		for (int i = 0; i < 15; i++) {
			temp.push_back(n);
		}
		for (int i = 0; i < 10; i++) {
			vec.push_back(temp);
		}
	}

	std::string time_format(int t) {
		if (t - 9 > 0) {
			return std::to_string(t);
		}
		else {
			return "0" + std::to_string(t);
		}
	}
	std::string getStrTime(bool _date, bool _time) {
		std::string strtime = "";
		time_t now = time(0);
		tm* ltm = localtime(&now);
		if (_date) {
			strtime += "Date: " + time_format(ltm->tm_mday) + '/';
			strtime += time_format(1 + ltm->tm_mon) + '/';
			strtime += time_format(ltm->tm_year - 100);
		}
		if (_date && _time) { strtime += " | "; }
		if (_time) {
			strtime += "Time: " + time_format(ltm->tm_hour) + ":";
			strtime += time_format(ltm->tm_min) + ":";
			strtime += time_format(ltm->tm_sec);
		}
		return strtime;
	}
};