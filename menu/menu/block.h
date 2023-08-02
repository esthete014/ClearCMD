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
#include <string>
#include <ctime>
using myfunc = void* (*)(void*);
#pragma warning(disable : 4996)

//template <class TYPE> class STR {
//	std::string strline = "";
//	std::string name;
//};
//template <class TYPE> class BTN;
//template <class TYPE> class HSWITCH;

//class TYPE {
//public:
//	std::string str = "";
//
//};

class STR {
	//std::string Name = "";
	std::string Strline = "";
	STR();
public:
	//bool nameexist = false;
	//std::string* name;
	std::string* strline;
	STR(std::string _strline) {
		Strline = _strline;
		strline = &Strline;
	}
	STR(std::string* _strline) {
		strline = _strline;
	}
	/*STR(std::string _name, std::string _strline) {
		Name = _name;
		name = &Name;
		Strline = _strline;
		strline = &Strline;
		nameexist = true;
	}
	STR(std::string *_name, std::string* _strline) {
		name = _name;
		strline = _strline;
		nameexist = true;
	}*/
	/*void print() {
		std::cout << *strline << "\n";
	}*/
};

class BTN {
	std::string Name = "";
	myfunc func;
public:
	std::string* name;
	BTN(std::string _name, myfunc _func) {
		Name = _name;
		name = &Name;
		func = _func;
	}
	void release() {
		func(0);
	}
};

class DATETIME {
public:
	bool date;
	bool time;
	bool dynamic;
	DATETIME(bool _date, bool _time, bool _dynamic) {
		date = _date;
		time = _time;
		dynamic = _dynamic;
	}
};

class PAGE {
	std::string Text = "";
public:
	std::string* text;
	int cursor;
	bool bigsize;
	bool edit;
	bool pagecounter;
	PAGE(std::string _text, bool _bigsize, bool _edit, bool _pagecounter) {
		Text = _text;
		text = &Text;
		bigsize = _bigsize;
		edit = _edit;
		pagecounter = _pagecounter;
	}
};

class LIST {
protected:
	std::vector<std::string> Text;
public:
	std::vector<std::string>* text;
	bool edit;
	//bool scroll;
	bool scrollvisible;
	LIST(std::vector<std::string> _text, bool _edit, bool _scroll, bool _scrollvisible) {
		Text = _text;
		text = &Text;
		edit = _edit;
		//scroll = _scroll;
		scrollvisible = _scrollvisible;
	}
};

class SWITCH : LIST{
protected:
	int cursor = 0;
	int startLine = 0;
};
class HSWITCH : SWITCH {

};
class VSWITCH : SWITCH {

};
/////////////////////////////////////////////////////
//std::string isSingleNumber(int num) {
//	if (num > 9) { return ""; }
//	else { return "0"; }
//}

/////////////////////////////////////////////////////


// focus disabled < 50
// 50 <= focus possible < 100
// focus 100% > 100
// 100 <= switch family < 110
enum class TYPE {
	TSTR,
	TDATETIME,
	TPAGE = 50,
	TLIST,
	TTABLE,
	TTREE,
	THSWITCH = 100,
	TVSWITCH,
	TINPUTFIELD = 110,
	TBTN
};


//template <class ... t>
class Block {
	void checkCoords() {
		if (start_x < 0 || start_y < 0 || end_x < 0 || end_y < 0) { std::_Throw_range_error("coords cant be less then 0!"); }
		if (start_x > 9 || start_y > 10 || end_x > 9 || end_y > 10) { std::_Throw_range_error("coords cant be more then 10 for x and 14 for y!"); }
		int minx = 0;
		int miny = 0;
		if (type == TYPE::TLIST) {
			minx = 1;
			miny = 1;
		}
		if (type == TYPE::TDATETIME) {
			miny = 0;
			if ((static_cast<DATETIME*>(data))->date && (static_cast<DATETIME*>(data))->time) {
				minx = 1;
			}
			else { minx = 1; }
		}
		// TABLE !!!!!!!! одна ячейка 
		if (end_x - start_x < minx || end_y - start_y < miny) { std::_Throw_range_error("end coords cant be less then start!"); }
	}
	void printByPos(std::string str, int _x, int _y, HANDLE hStdOut) {
		COORD cor;
		cor.X = _x;
		cor.Y = _y;
		SetConsoleCursorPosition(hStdOut, cor);
		std::cout << str;
	}
public:
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	void* data;
	TYPE type;
	/// <summary>
	/// be carefull that ur block have got correct coordinates!
	/// </summary>
	Block(STR* str, int _start_x, int _start_y, int _end_x, int _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
		type = TYPE::TSTR;
		data = (void*)str;
		checkCoords();
		//(*static_cast<STR*>(data)).print();
	}
	Block(BTN* btn, int _start_x, int _start_y, int _end_x, int _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
		type = TYPE::TBTN;
		data = (void*)btn;
		checkCoords();
	}
	Block(DATETIME* dt, int _start_x, int _start_y) {
		start_x = _start_x;
		start_y = _start_y;
		type = TYPE::TDATETIME;
		data = (void*)dt;
		checkCoords();
	}
	Block(PAGE* pg, int _start_x, int _start_y, int _end_x, int _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
		type = TYPE::TPAGE;
		data = (void*)pg;
		checkCoords();
	}
	Block(LIST* ls, int _start_x, int _start_y, int _end_x, int _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
		type = TYPE::TLIST;
		data = (void*)ls;
		checkCoords();
	}
	void printContent(HANDLE hStdOut) {
		int xlength = 12 * (end_x-start_x + 1) - 2;/*((end_x - start_x + 1) * 10) + ((end_x - start_x < 0 ? 0 : end_x - start_x) * 2)*//*(12 * ((end_x + 1) - (start_x + 1))) - 2;*/
		int ylength = 3 * (end_y - start_y + 1) - 2; //(end_y - start_y + 1) + ((end_y - start_y < 0 ? 0 : end_y - start_y) * 2);
		std::vector<std::string> linesvec;
		if (type == TYPE::TSTR) {
			bool endline = false;
			std::string& linestr = *static_cast<STR*>(data)->strline;
			for (int i = 0; i < ylength; i++) {
				if (linestr.size() > xlength * i && linestr.size() < xlength * (i + 1)) {
					linesvec.push_back(linestr.substr(xlength * i, linestr.size() % xlength) + std::string(xlength - (linestr.size() % xlength), ' '));
					endline = true;
				}
				else if (endline) {
					linesvec.push_back(std::string(xlength, ' '));
				}
				else {
					if (i == ylength - 1) {
						linesvec.push_back(linestr.substr(xlength * i, xlength - 3) + "...");
					}
					else { linesvec.push_back(linestr.substr(xlength * i, xlength)); }
				}
				/*if (!endline) {
					linesvec[ylength - 1][xlength - 3] = '.';
					linesvec[ylength - 1][xlength - 2] = '.';
					linesvec[ylength - 1][xlength - 1] = '.';
				}*/
			}
			for (int i = 0; i < linesvec.size(); i++) {
				printByPos(linesvec[i], (start_x * 12) + 1, (start_y  * 3) + 1 + i, hStdOut);
			}
			/*int linecount = (*static_cast<STR*>(data)->strline).size() / xlength;
			if ((*static_cast<STR*>(data)->strline).size() % xlength > 0) { linecount++; }
			if (linecount > ylength) { linecount = ylength; }
			for (int i = 0; i < linecount; i++) {
				if ((*static_cast<STR*>(data)->strline).size() - (xlength * i) > xlength) { 
					linesvec.push_back((*static_cast<STR*>(data)->strline).substr(i * xlength, (*static_cast<STR*>(data)->strline).size() - (xlength * i)));
				}
				else { linesvec.push_back((*static_cast<STR*>(data)->strline).substr(i * xlength, xlength)); }
			}*/
		}
		if (type == TYPE::TBTN) {
			int halfylength = ylength / 2;
			int halfxlength = (ylength - (*static_cast<BTN*>(data)->name).size()) / 2;
		}
	}
};

//template <class ... t>
//using Block = void* (*)(t ...);