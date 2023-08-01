// / ============================= \
// | -------  esthete014  -------- |
// | ============================= |
// |     || copyright 2023 ||      |
// |     || Nikolay        ||      |
// |     || Kochetov       ||      |
// | _____________________________ |
// | https://github.com/esthete014 |
// \ ============================= /

#include "visual.h"

class MyClass {
public:
	std::string str1 = "4rd";

	void* func1(void*) {
		std::cout << "i am btn1" + str1;
	}

};




void* func2(void*) {
	std::cout << "i am btn2";
	return 0;
}

std::string time_format(int t) {
	if (t - 9 > 0) {
		return std::to_string(t);
	}
	else {
		return "0" + std::to_string(t);
	}
}
//void printByPos1(std::string str, int _x, int _y) {
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD cor;
//	cor.X = _x;
//	cor.Y = _y;
//	SetConsoleCursorPosition(hStdOut, cor);
//	std::cout << str;
//}
//void printBlockWalls(int xstart, int ystart, int xend, int yend) {
//	int xlength = xend - xstart;
//	int ylength = yend - ystart;
//	std::string line = "------------";
//	for (int i = 0; i <= xlength; i++) { 
//		/*if (i == 0 && i == xlength) { line = "+----------+"; }
//		else if (i == 0) { line = "+-----------"; }
//		else if (i == xlength) { line = "-----------+"; }
//		else { line = "------------"; }*/
//		printByPos1(line, (xstart + i) * 11, ystart * 2); 
//		printByPos1(line, (xstart + i) * 11, (yend + 1) * 2);
//	}
//	//for (int i = 0; i <= xlength; i++) 
//	for (int j = 0; j <= ylength; j++) {
//		for (int i = 0; i < 3; i++) {
//			if (!((j == 0 && i == 0) || (j == ylength && i == 2))) {
//				
//				printByPos1("|", xstart * 11, (ystart + j) * 2 + i);
//				printByPos1("|", (xend + 1) * 11, (ystart + j) * 2 + i);
//			}
//		}
//	}
//	/*for (int j = 0; j <= ylength; j++) for (int i = 0; i < 3; i++)*/ 
//}
//void printBlockAngles(int xstart, int ystart, int xend, int yend) {
//	printByPos1("+", xstart * 11, (ystart + 0) * 2 + 0);
//	printByPos1("+", (xend + 1) * 11, (ystart + 0) * 2 + 0);
//	printByPos1("+", xstart * 11, (ystart + yend - ystart) * 2 + 2);
//	printByPos1("+", (xend + 1) * 11, (ystart + yend - ystart) * 2 + 2);
//}

int main() {
	//std::vector<std::vector<Block<void*>>> layout;
	//void* temp = new STR("234");
	//layout[0].push_back(temp);
	//
	//auto myCMDLITE = Visual(layout);
	/*Visual(
		{
			{(void*)Block<void*>(new STR("2r")), Block<void*>(new STR("4rd"))}
		}
	);*/
	std::string str2 = "5246";
	
	std::unordered_map<std::string, myfunc> f;
	f.insert({ "btn1", func2 });
	/*HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	SetConsoleTitle(L"Clear CMD Client");
	SetWindowPos(consoleWindow, 0, 315, 170, 0, 0, SWP_NOSIZE | SWP_NOZORDER);*/
	
	MyClass myobj;
	/*for (int i = 0; i < 3751; i++) {
		std::cout << i % 10;
	}*/
	/*printBlockWalls(0, 0, 10, 14);
	printBlockWalls(0, 0, 5, 5);
	printBlockWalls(6, 0, 6, 7);
	printBlockWalls(0, 0, 0, 0);
	printBlockWalls(0, 1, 0, 1);
	printBlockWalls(0, 2, 1, 2);
	printBlockWalls(0, 3, 0, 3);
	printBlockWalls(0, 6, 0, 6);
	printBlockWalls(3, 7, 5, 9);
	printBlockAngles(0, 0, 10, 14);
	printBlockAngles(0, 0, 5, 5);
	printBlockAngles(6, 0, 6, 7);
	printBlockAngles(0, 0, 0, 0);
	printBlockAngles(0, 1, 0, 1);
	printBlockAngles(0, 2, 1, 2);
	printBlockAngles(0, 3, 0, 3);
	printBlockAngles(0, 6, 0, 6);
	printBlockAngles(3, 7, 5, 9);*/

	//while (1);
			//{
			/*},
			{*/
			//}

	
	Visual (
		{
			Block(new STR("234"), 0, 0, 0, 0), 
			Block(new STR(&myobj.str1, &str2), 1, 0, 1, 0), 
			Block(new BTN("btn2", func2), 2, 0, 2, 0),
			Block(new STR("dfgge"), 0, 1, 0, 1), 
			Block(new STR(&str2, &myobj.str1), 1, 1, 1, 1), 
			Block(new BTN("btn2 #2", func2), 2, 1, 2, 3)
		},
		std::unordered_map<std::string, myfunc>{ {"btn2", func2 } }
	);
	/*while (1) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cor;
		cor.X = 0;
		cor.Y = 5;
		SetConsoleCursorPosition(hStdOut, cor);
		std::cout << "-----------------------\n";
		std::string strtime = "";
		time_t now = time(0);
		tm* ltm = localtime(&now);
		strtime += "Date: " + time_format(ltm->tm_mday) + '/';
		strtime += time_format(1 + ltm->tm_mon) + '/';
		strtime += time_format(ltm->tm_year - 100) + " | ";
		strtime += "Time: " + time_format(ltm->tm_hour) + ":";
		strtime += time_format(ltm->tm_min) + ":";
		strtime += time_format(ltm->tm_sec) + '\n';
		std::cout << strtime;
	}*/
	while (1);
	return 0;
}