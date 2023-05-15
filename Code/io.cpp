#include "io.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <ncurses.h>
#endif

void stratego_io::print(std::string output) {
	#ifdef _WIN32
		std::cout << output;
	#elif __linux__
		printw(output.c_str());
	#endif
}

int stratego_io::getchar() {
	int input = 0;
	#ifdef _WIN32
		input = _getch();
	#elif __linux__
		input = getch();
	#endif

	return input;
}

void stratego_io::clear() {
	#ifdef _WIN32
	system("cls");
	#elif __linux__
		erase();
	#endif
}

void stratego_io::reset() {
	#ifdef _WIN32
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
	#elif __linux__

	#endif
}

std::string stratego_io::getline() {
	std::string input = "";
#ifdef _WIN32
	std::getline(std::cin, input);
#elif __linux__
	std::string input;
	nocbreak();
	echo();

	int ch = getch();

	while (ch != '\n') {
		input.push_back(char(ch));
	}
	cbreak();
	noecho();
#endif
	return input;
}
