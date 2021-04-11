
#include <iostream>
#include <thread>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <map>

using namespace std;

// settings
wstring shapes[7];
int fieldWidth = 14;
int fieldHeight = 18; 
int sWidth = 80;
int sHeight = 30;
unsigned char* gameField = new unsigned char[fieldHeight * fieldWidth];

// keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// game variables
int currS = rand() % 7;
int cSY = 0;
int cSX = 1;
int rotation = 3;
int key;
int gameTick;

// game state 
bool gameOver = false;
int points = 0;
map<int, int> lines;

// Rotate shapes with mathematical function - 4x4 Matrix
int rotateShape(int px, int py, int r) { 
	switch (r % 4) {
	case 0: return py * 4 + px; // 0 deg
	case 1: return 12 + py - (px * 4); // 90 deg
	case 2: return 15 - (py * 4) - px; // 180 deg
	case 3: return 3 - py + (px * 4); // 270 deg
	}
	return 0;
}

void initShapes() {

	shapes[0].append(L"..x.");
	shapes[0].append(L"..x.");
	shapes[0].append(L"..x.");
	shapes[0].append(L"..x.");

	shapes[1].append(L"..x.");
	shapes[1].append(L".xx.");
	shapes[1].append(L".x..");
	shapes[1].append(L"....");

	shapes[2].append(L"....");
	shapes[2].append(L".xx.");
	shapes[2].append(L".xx.");
	shapes[2].append(L"....");

	shapes[3].append(L"....");
	shapes[3].append(L".xx.");
	shapes[3].append(L"..x.");
	shapes[3].append(L"..x.");

	shapes[4].append(L"..x.");
	shapes[4].append(L".xx.");
	shapes[4].append(L"..x.");
	shapes[4].append(L"....");

	shapes[5].append(L"....");
	shapes[5].append(L".xx.");
	shapes[5].append(L".x..");
	shapes[5].append(L".x..");

	shapes[6].append(L".x..");
	shapes[6].append(L".xx.");
	shapes[6].append(L"..x.");
	shapes[6].append(L"....");
}

bool collision(int shape, int rotation, int cSX, int cSY) {

	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++) {
			int sIndex = rotateShape(px, py, rotation);
			int gIndex = (py + cSY) * fieldWidth + (px + cSX);

			// safety first - in bounds?
			if ((fieldWidth > (px + cSX) >= 0) && (fieldHeight > (py + cSY) >= 0))
				// collision? 
				if (shapes[currS][sIndex] == L'x' && gameField[gIndex] != 0) {
					return false;
				}
		}
	return true;
}

int getArrowKey() {
	int c = 0;

	// non blocking 
	if (!_kbhit()) return 0;
	
	switch (c = _getch()) {
		case KEY_UP:
			c = 1; // key up
			break;
		case KEY_DOWN:
			c = 2; // key down
			break;
		case KEY_LEFT:
			c = 3; // key left
			break;
		case KEY_RIGHT:
			c = 4; // key right
			break;
		default:	
			break; // not arrow
		}

	return c;
}

int main() {

	// create Tetris Shapes
	initShapes();

	// initialize gameField
	for (int x = 0; x < fieldWidth; x++)
		for (int y = 0; y < fieldHeight; y++)
			gameField[y * fieldWidth + x] = (x == 0 || x == fieldWidth-1) || (y==fieldHeight-1) ? 1 : 0; // set borders and empty fields

	// console screenBuffer
	wchar_t* cScreen = new wchar_t[sWidth * sHeight*2];
	for (int x = 0; x < sHeight * sWidth; x++) cScreen[x] = L' ';
	HANDLE cBuff = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(cBuff);
	DWORD wB = 0; 

	// set fixed console size
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 610, 500, TRUE);
	// disable console resize
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	while (!gameOver) {

		// timehandle
		this_thread::sleep_for(50ms); 
		gameTick += 50;

		// keys
		key = getArrowKey(); 

		// print gameField to cScreen
		for (int x = 0; x < fieldWidth; x++)
			for (int y = 0; y < fieldHeight; y++)
				cScreen[y * sWidth + x] = L" X"[gameField[y * fieldWidth + x]];

		// print shape to cScreen
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++) 
				if (shapes[currS][rotateShape(px, py, rotation)] == L'x') cScreen[(py + cSY) * sWidth + (px + cSX)] = L'#'; // + offsetX of border // 65 + currS == ASCII ABCDEFG		
			
		// logic --------------------------------------------------
		cSX -= (key == 3 && collision(currS, rotation, cSX-1, cSY)) ? 1 : 0; // left
		cSX += (key == 4 && collision(currS, rotation, cSX+1, cSY)) ? 1 : 0; // right
		cSY += (key == 2 && collision(currS, rotation, cSX, cSY+1)) ? 1 : 0; // down
		rotation += (key == 1 && collision(currS, rotation+1, cSX, cSY)) ? 1 : 0; // rotation

		// downforce
		if (gameTick >= 1000) {
			gameTick = 0; 
			if (collision(currS, rotation, cSX, cSY + 1)) cSY++;
			else {
				// lock shape 
				points += 25;
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++) 
						if (shapes[currS][rotateShape(px, py, rotation)] == L'x') {
							gameField[(py + cSY) * fieldWidth + (px + cSX)] = 1;
							// add to lines 
							if (lines.find(cSY + py) != lines.end()) {
								lines[lines.find(cSY + py)->first] = lines.find(cSY + py)->second + 1;
							}
							else {
								lines.insert(pair<int, int>(cSY + py, 1));
							}

							// check for lines						
							if (lines.find(cSY + py)->second == fieldWidth - 2) {
								lines[lines.find(cSY + py)->first] = 0;
								// move down pieces above
								for (int y = (cSY + py); y > 0; y--)
									for (int x = 1; x < fieldWidth - 1; x++) {
										// clear line because we have one
										gameField[(y)*fieldWidth + x] = 0;
										// -1 because we take the piece from above -- add piece from above
										gameField[y * fieldWidth + x] = gameField[(y - 1) * fieldWidth + x];
										// add changed pieces to map --- fix this
										if (gameField[y * fieldWidth + x] == 1) {
											// remove piece from line above
											lines[lines.find(y - 1)->first] = lines.find(y - 1)->second - 1;
											// add piece to cleared line
											lines[lines.find(y)->first] = lines.find(y)->second + 1;
										}
									}
								points += 100;
							}

						}
				// generate new shape 
				currS = rand() % 7;
				cSY = 0;
				cSX = 1;
				rotation = 0;	

				// game over
				gameOver = !collision(currS, rotation, cSX, cSY);
			}
		}

		// logic --------------------------------------

		// display cScreen/Game - whole cScreen with gameField inside
		WriteConsoleOutputCharacter(cBuff, cScreen, sWidth * sHeight, { 0, 0 }, &wB);

		// print score
		swprintf_s(&cScreen[fieldWidth * 2], 16, L"Score: %d", points);
	} 

	CloseHandle(cBuff);
	cout << "Your final score: " << points << endl;
	system("pause");
	 
	return 0; 
}