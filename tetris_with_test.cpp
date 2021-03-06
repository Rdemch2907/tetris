/*
Випадкові фігурки тетраміно падають зверху в прямокутний стакан (матрицю) визначеної ширини і висоти (наприклад, 10х20 клітинок). 
Варіанти фігур описані нижче:

      o      o  oo
oooo  ooo  ooo  oo

 oo  o  oo
oo  ooo  oo

Під час польоту гравець може переміщувати фігуру вліво, вправо по горизонталі, а також вниз, прискорюючи падіння (за допомогою клавіш управління курсором). На 12 балів реалізувати також поворот фігури.
Кожна фігурка летить зверху, поки не наштовхнеться на іншу фігурку або не впаде на дно матриці. Якщо при цьому заповниться горизонтальний ряд, тоді він пропадає і все, що було його вище, опускається на 1 клітинку. Гра закінчується, коли нова фігурка не може поміститись в матрицю.
Гравець отримує очки за кожну фігурку, тому його задача — заповнювати ряди, не заповнюючи саму матрицю (стакан) як можна довше, щоб таким чином отримати як можна більше очків. Сам підрахунок очків в різних версіях «Тетріса» різний. Очки можуть нараховуватись за прибрані лінії, за скинуті фігурки, за перехід на нову швидкість і т. д.
Орієнтовна структура класів:
1. Point, який описує окрему точку матриці
2. Matrix (матриця), яка має певний розмір, а також управляє фігурами, підраховує бали, перемальовує саме поле тетрісу тощо. Він також може містити орієнтовно наступні методи:
- Конструктор, який по бажанню може містити темп гри, ініціалізує очки нулем тощо.
- Draw або Fill, який дозволяє розташовувати фігуру на полі матриці. При першому виклику цього метода, буде відображатись весь тетріс.
- Метод генерування фігури.
- Move, який дозволяє переміщувати фігуру вліво/вправо.
- Rotate - метод повороту фігури.
- Метод падіння фігури
- Метод перевірки на заповнення горизонтального ряду в тих місцях, де розміщується фігура, що щойно впала.
3. Shape (фігура), який дозволяє згенерувати випадкову фігуру. Можна також створити окремі класи для різних типів фігур.
Передбачити також можливість збереження гри в файл та завантаження її з файлу.

*/

//#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream> 
#include <string>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <vector>


using namespace std;

#define DGREEN 2
#define GRAY 8 
#define DBLUE 9
#define GREEN 10
#define BLUE 11 
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15


void gotoxy(int x, int y);
void setColor(int color = WHITE);

const int width = 22;
const int height = 22;
int timeGame;
int delay = 1000;

struct Score
{
	int score;
	int duration;
	
	void print()
	{
		cout << "\t" << score << "\t\t" << duration <<  endl;
	}
} s;

class Point
{
public:

	void setPoint( int x, int y, int color)
	{
		setColor(color);
		gotoxy(x, y);
		cout << "\xDB\xDB";
		setColor();
	}
};


class Shape abstract
{
protected:
	int shape[4][4][4] = {};

public:

	void showShape(int x, int y, int r = 0)
	{
		Point p;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (shape[r][i][j] != 0)
					p.setPoint(i + x, j * 2 + y, shape[r][i][j]);
	}

	void hideShape(int x, int y, int r)
	{
		Point p;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (shape[r][i][j] != 0)
					p.setPoint(i + x, j * 2 + y, 0);
	}


	void getShape(int sh[4][4][4], int r)
	{
		int xpos = 16;
		gotoxy(xpos, 50);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				sh[r][i][j] = shape[r][i][j];
			}
			gotoxy(xpos + i + 1, 50);
		}
	}


};

// паличка блакитна
class Figure0 : public Shape
{
public:

	Figure0()
	{
		shape[0][0][1] = BLUE;
		shape[0][1][1] = BLUE;
		shape[0][2][1] = BLUE;
		shape[0][3][1] = BLUE;

		shape[1][1][0] = BLUE;
		shape[1][1][1] = BLUE;
		shape[1][1][2] = BLUE;
		shape[1][1][3] = BLUE;

		shape[2][0][1] = BLUE;
		shape[2][1][1] = BLUE;
		shape[2][2][1] = BLUE;
		shape[2][3][1] = BLUE;

		shape[3][1][0] = BLUE;
		shape[3][1][1] = BLUE;
		shape[3][1][2] = BLUE;
		shape[3][1][3] = BLUE;
	}
};

// гачок направо світлозелений
class Figure1 : public Shape
{
public:

	Figure1()
	{
		shape[0][0][1] = GREEN;
		shape[0][1][1] = GREEN;
		shape[0][2][1] = GREEN;
		shape[0][0][2] = GREEN;

		shape[1][1][1] = GREEN;
		shape[1][1][2] = GREEN;
		shape[1][1][3] = GREEN;
		shape[1][2][3] = GREEN;

		shape[2][0][2] = GREEN;
		shape[2][1][2] = GREEN;
		shape[2][2][2] = GREEN;
		shape[2][2][1] = GREEN;

		shape[3][2][1] = GREEN;
		shape[3][2][2] = GREEN;
		shape[3][2][3] = GREEN;
		shape[3][1][1] = GREEN;
	}
};

//гачок наліво зелений
class Figure2 : public Shape
{
public:

	Figure2()
	{
		shape[0][0][1] = DGREEN;
		shape[0][1][1] = DGREEN;
		shape[0][2][1] = DGREEN;
		shape[0][2][2] = DGREEN;

		shape[1][1][1] = DGREEN;
		shape[1][1][2] = DGREEN;
		shape[1][1][3] = DGREEN;
		shape[1][2][1] = DGREEN;

		shape[2][0][2] = DGREEN;
		shape[2][1][2] = DGREEN;
		shape[2][2][2] = DGREEN;
		shape[2][0][1] = DGREEN;

		shape[3][2][1] = DGREEN;
		shape[3][2][2] = DGREEN;
		shape[3][2][3] = DGREEN;
		shape[3][1][3] = DGREEN;
	}
};

// квадрат жовтий
class Figure3 : public Shape
{
public:

	Figure3()
	{
		shape[0][1][1] = YELLOW;
		shape[0][1][2] = YELLOW;
		shape[0][2][1] = YELLOW;
		shape[0][2][2] = YELLOW;

		shape[1][1][1] = YELLOW;
		shape[1][1][2] = YELLOW;
		shape[1][2][1] = YELLOW;
		shape[1][2][2] = YELLOW;

		shape[2][1][1] = YELLOW;
		shape[2][1][2] = YELLOW;
		shape[2][2][1] = YELLOW;
		shape[2][2][2] = YELLOW;

		shape[3][1][1] = YELLOW;
		shape[3][1][2] = YELLOW;
		shape[3][2][1] = YELLOW;
		shape[3][2][2] = YELLOW;
	}
};

// дві цеглинки зі зсувом вправо рожева
class Figure4 : public Shape
{
public:

	Figure4()
	{
		shape[0][2][2] = PINK;
		shape[0][3][2] = PINK;
		shape[0][1][1] = PINK;
		shape[0][2][1] = PINK;

		shape[1][1][2] = PINK;
		shape[1][1][3] = PINK;
		shape[1][2][1] = PINK;
		shape[1][2][2] = PINK;

		shape[2][2][2] = PINK;
		shape[2][3][2] = PINK;
		shape[2][1][1] = PINK;
		shape[2][2][1] = PINK;

		shape[3][1][2] = PINK;
		shape[3][1][3] = PINK;
		shape[3][2][1] = PINK;
		shape[3][2][2] = PINK;
	}
};

// паличка з відротком посередині синя
class Figure5 : public Shape
{
public:

	Figure5()
	{
		shape[0][1][1] = DBLUE;
		shape[0][2][1] = DBLUE;
		shape[0][3][1] = DBLUE;
		shape[0][2][2] = DBLUE;

		shape[1][2][1] = DBLUE;
		shape[1][2][2] = DBLUE;
		shape[1][2][3] = DBLUE;
		shape[1][3][2] = DBLUE;

		shape[2][1][2] = DBLUE;
		shape[2][2][2] = DBLUE;
		shape[2][3][2] = DBLUE;
		shape[2][2][1] = DBLUE;

		shape[3][2][1] = DBLUE;
		shape[3][2][2] = DBLUE;
		shape[3][2][3] = DBLUE;
		shape[3][1][2] = DBLUE;
	}
};

// дві цеглинки зі зсувом вліво червона
class Figure6 : public Shape
{
public:

	Figure6()
	{
		shape[0][2][1] = RED;
		shape[0][3][1] = RED;
		shape[0][1][2] = RED;
		shape[0][2][2] = RED;

		shape[1][1][1] = RED;
		shape[1][1][2] = RED;
		shape[1][2][2] = RED;
		shape[1][2][3] = RED;

		shape[2][2][1] = RED;
		shape[2][3][1] = RED;
		shape[2][1][2] = RED;
		shape[2][2][2] = RED;

		shape[3][1][1] = RED;
		shape[3][1][2] = RED;
		shape[3][2][2] = RED;
		shape[3][2][3] = RED;
	}
};

class Matrix
{
private:
	int point;
	int speed;
	Shape * figure[7] = { new Figure0, new Figure1, new Figure2, new Figure3, new Figure4, new Figure5, new Figure6 };
	int matrix[height][width] = {};

public:

	Matrix(int point = 0, int speed = 0)
	{
		setPoint(0);
		setSpeed(0);
		timeGame = 0;
	}

	~Matrix()
	{
		for (int i = 0; i < 7; ++i)
			delete[] figure[i];
	}

	// тимчасова промальовка матриці числами
	void showMatrix01()
	{
		gotoxy(0, 0);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << matrix[i][j];
			}
			cout << endl;
		}
	}
	// end

	// тимчасова промальовка 
	void showMatrixGraph()
	{
		for (int j = height - 2; j > 0; --j)
		{
			gotoxy(j, 1);
			for (int i = 1; i < width - 1; ++i)
			{
				setColor(matrix[j][i]);
				cout << "\xDB";
			}
		}
	}
	// end

	void setPoint(int p)
	{
		point = p;
	}

	int getPoint()
	{
		return point;
	}

	void setSpeed(int s)
	{
		speed = s;
	}

	int getSpeed()
	{
		return speed;
	}

	//промальовка рамки для гри
	void frame(char begin, char middle, char end, int width)
	{
		for (int i = 0; i < width; ++i)
			if (i == 0)
				cout << char(begin);
			else
				if (i == width - 1)
					cout << char(end);
				else
					cout << char(middle);
		cout << endl;
	}

	// промальовка ігрового поля
	void field(int x, int y, int height, int width)
	{
		gotoxy(x, y);
		frame(201, 205, 187, width);
		for (int j = 1; j < height - 1; ++j)
		{
			gotoxy(x + j, y);
			frame(186, ' ', 186, width);
		}
		gotoxy(x + height - 1, y);
		frame(200, 205, 188, width);
	}


	// перевірка чи досягнула фігура дна або інших фігур
	bool audit(int x, int y, int r, int curr)
	{
		int shape[4][4][4];
		if (r == 4)
			r = 0;
		figure[curr]->getShape(shape, r);

		// demonstration - delete after
		int xpos = 10;
		gotoxy(xpos, 80);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
				cout << shape[r][i][j];
			gotoxy(xpos + i + 1, 80);
		}
		//

		for (int i = 3; i >= 0; --i)
		{
			for (int j = 3; j >= 0; --j)
			{
				//gotoxy(xpos + 10 + j, 80); //це просот для інфо, ніякої нагрузки для гри не несе
				//cout << "shape: " << shape[r][i][j] << " matrix: " << matrix[x + i + 1][y + j * 2 + 1];
				if (shape[r][i][j] != 0 && matrix[x + i + 1][y + j * 2 + 1] != 0)
				{
					for (int i = 0; i < 4; ++i)
						for (int j = 0; j < 4; ++j)
						{
							if (shape[r][i][j])
							{
								matrix[x + i][y + j * 2] = shape[r][i][j];
								matrix[x + i][y + j * 2 + 1] = shape[r][i][j];
							}
						}
					return true;
				}
			}
		}
		return false;
	}

	void auditRows()
	{
		int rows = 0;
		bool flag = 1;
		int i;
		int j = height - 2;

		// перевірка чи є заповнені рядки
		do
		{
			i = 1;
			do
			{
				if (matrix[j][i] == 0)
				{
					flag = 0;
					break;
				}
				++i;
			} while (i < width - 1);

			// якщо є - видаляємо заповнені
			if (flag)
			{
				++rows;
				for (int delj = j; delj > 0; --delj)
					for (int deli = 1; deli < width - 1; ++deli)
						matrix[delj][deli] = matrix[delj - 1][deli];
				for (int deli = 1; deli < width - 1; ++deli)
					matrix[1][deli] = 0;
			}
			else
				--j;
			flag = 1;
			if (rows >= 4)
				break;
		} while (j > 0);

		// перемальовуємо усю матрицю
		if (rows > 0)
			for (int j = height - 2; j > 0; --j)
			{
				gotoxy(j, 1);
				for (int i = 1; i < width - 1; ++i)
				{
					setColor(matrix[j][i]);
					cout << "\xDB";
				}
			}

		// нараховуємо бали за заповнені рядки
		switch (rows)
		{
		case 1:
			rows = 100;
			break;
		case 2:
			rows = 300;
			break;
		case 3:
			rows = 700;
			break;
		case 4:
			rows = 1500;
			break;
		default:
			rows = 0;
			break;
		}

		setPoint(getPoint() + rows);

		// міняємо швидкість за кожні 10 тис балів
		if (getPoint() > 10000)
			setSpeed((getPoint() / 10000) * 100);
	}

	// інфо про гру
	void score()
	{
		int pos = 8;
		gotoxy(pos, width);
		cout << "\tScore:\t" << getPoint() << "  ";
		gotoxy(pos + 2, width);
		cout << "\tLevel:\t" << getSpeed() / 100;
		gotoxy(pos + 3, width);
		cout << "\tTime:\t" << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60;
	}

	// поворот фігури за часовою стрілкою
	int rotate(int x, int y, int r, int curr)
	{
		if ((y != 15) && (curr != 0 || y < 17 ) && (curr != 0 || y != -1))
		{
			figure[curr]->hideShape(x, y, r);
			if (r == 3)
				r = 0;
			else
				++r;
			figure[curr]->showShape(x, y, r);
		}
		return r;
	}

	// рух фігури вліво-вправо
	int move(int x, int y, int r, int curr, int leftrigth)
	{
		int shape[4][4][4];
		figure[curr]->getShape(shape, r);
		bool empty = true;

		if (leftrigth < 0)
		{
			for (int j = 0; j < 4; ++j)
				for (int i = 0; i < 4; ++i)
				{
					if (shape[r][i][j] != 0)
					{
						gotoxy(0, 80);
						cout << "shape[" << i << "][" << j << "] = " << shape[r][i][j];
						for (int i = 0; i < 4; ++i)
							if (shape[r][i][j] != 0 && matrix[x + i][y + j - 1] != 0)
							{
								gotoxy(1, 80);
								cout << "matrix[" << x + i << "][" << y + j - 1 << "] = " << matrix[x + i][y + j - 1] << "shape[" << i << "][" << j << "] = " << shape[r][i][j];
								empty = false;
								break;
							}
						if (empty)
						{
							figure[curr]->hideShape(x, y, r);
							y += leftrigth;
							figure[curr]->showShape(x, y, r);
							return y;
						}
						break;

					}

					gotoxy(i + 2, 80);
					cout << matrix[x + i][y - 1] << " - " << shape[r][i][j];
				}
		}
		else
		{
			for (int j = 3; j >= 0; --j)
				for (int i = 0; i < 4; ++i)
				{
					if (shape[r][i][j] != 0)
					{
						for (int i = 0; i < 4; ++i)
							if (shape[r][i][j] != 0 && matrix[x + i][y + (j + 1) * 2] != 0)
							{
								empty = false;
								break;
							}
						if (empty)
						{
							figure[curr]->hideShape(x, y, r);
							y += leftrigth;
							figure[curr]->showShape(x, y, r);
							return y;
						}
						break;

					}

				}
		}
		return y;
	}

	// прискорення падіння фігури
	int fall(int x, int y, int r, int curr)
	{
		if (!audit(x + 1, y, r, curr))
		{
			figure[curr]->hideShape(x, y, r);
			++x;
			figure[curr]->showShape(x, y, r);
		}
		return x;
	}

	void loadGame(int &x, int &y, int &r, int curr)
	{
		ifstream load;
		load.open("save", ios::binary);
		if (!load.is_open())
			return;
		figure[curr]->hideShape(x, y, r);
		x = 1;
		y = width / 2 - 4;
		r = 0;
		load.read((char*)&speed, sizeof(speed));
		load.read((char*)&point, sizeof(point));
		load.read((char*)&timeGame, sizeof(timeGame));
		load.read((char*)&matrix, sizeof(matrix));
		load.close();
		showMatrixGraph();
		text(GRAY, YELLOW);
	}

	void saveGame()
	{
		ofstream save;
		save.open("save", ios::binary);
		if (!save.is_open())
			return;
		save.write((char*)&speed, sizeof(speed));
		save.write((char*)&point, sizeof(point));
		save.write((char*)&timeGame, sizeof(timeGame));
		save.write((char*)&matrix, sizeof(matrix));
		save.close();
		text(YELLOW, GRAY);
	}

	void saveScore()
	{
		if (getPoint() != 0)
		{
			vector<Score> table;
			ifstream load("score", ios::binary);

			while (load.read((char*)&s, sizeof(s)))
			{
				table.push_back(s);
			}
					
			load.close();

			ofstream save;
			save.open("score", ios::binary);

			if (!save.is_open())
				return;

			s.score = getPoint();
			s.duration = timeGame;
			
			table.push_back(s);
			sort(table.begin(), table.end(), [](Score & s1, Score & s2) {return s1.score > s2.score; });
			int count = 0;
			for (auto elem : table)
			{
				save.write((char*)&elem, sizeof(elem));
				if (++count > 9)
					break;
			}
			save.close();
		}
	
	}

	void loadScore()
	{
		vector<Score> table;
		system("cls");
		ifstream load("score", ios::binary);
		if (!load.is_open())
			return;
		Score tmp;
		while (load.read((char*)&tmp, sizeof(tmp)))
		{
			table.push_back(tmp);
		}
		load.close();

		int xcell = 5;
		int ycell = 25;
		int count = 0;
		gotoxy(xcell, ycell);
		cout << "#\tScore\t\tDuration";
		gotoxy(++xcell, ycell);
		cout << "==================================";

		for (auto elem : table)
		{
			if (count == 0)
				setColor();
			else
				setColor(GRAY);
			gotoxy(++xcell, ycell);
			cout << ++count << "\t" << elem.score << "\t\t" << (elem.duration / 1000) / 60 << ":" << setfill('0') << setw(2) << (elem.duration / 1000) % 60 << endl;
		}
			
		setColor(0);
		cout << endl << endl;
		system("pause");
	}

	void rules()
	{
		system("cls");
		setColor();
		cout << "\tRules game Tetris\n";
		cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
		cout << "Random figures fall from the top into a rectangular glass with a width of 10 and a height of 20 cells. In the\n";
		cout << "flight, the player can rotate the figure and move it horizontally.You can also dump the figure, that is, to\n";
		cout << "accelerate its fall, when it has already been decided where the figure should fall.The figure flies until it\n";
		cout << "stumbles on another figurine or bottom of the glass.If this is filled with a horizontal number of 10 cages, it\n";
		cout << "disappears and everything above it falls into one cage.In a special field the player sees the figure that will\n";
		cout << "follow after the current one - this tooltip allows you to plan your actions.The pace of the game is gradually\n";
		cout << "increasing.The game ends when a new figure can not fit in the glass.The player gets points for each piece,\n";
		cout << "so his task is to fill the rows without filling the glass for as long as possible so as to get as many points as\n";
		cout << "possible.\n";
		cout << "\n\t1 row  - 100 points\n\t2 rows - 300 points\n\t3 rows - 700 points\n\t4 rows - 1500 points\n";
		setColor(GRAY);
		cout << "\n\nAbout:\n\tCourse work: Tetris\t\tAutor:  Olexandr Finyuk\n\tIT STEP Rivne, Aug-Sep 2018\t\tfinyuk@ukr.net\n";
		setColor(0);
		system("pause");
	}

	void gameOver()
	{
		saveScore();
		setColor(RED);
		field(height / 2 - 5, 2, 6, 18);
		setColor(YELLOW);
		gotoxy(height / 2 - 3, 6);
		cout << "GAME OVER";
		setColor(GREEN);
		gotoxy(height / 2 - 2, 6);
		cout << "Score: " << getPoint();
		Sleep(1500);
	}

	void text(int color1 = GRAY, int color2 = GRAY)
	{
		setColor();
		gotoxy(1, width);
		cout << "\tNext";

		setColor(GRAY);
		gotoxy(height - 8, width);
		cout << "\t<--  Move  -->";
		gotoxy(height - 7, width);
		cout << "\tSpace - Rotate";
		gotoxy(height - 5, width);
		setColor(color1);
		cout << "\tS - Save";
		setColor(color2);
		gotoxy(height - 4, width);
		cout << "\tL - Load";
		setColor(GRAY);
		gotoxy(height - 2, width);
		cout << "\tEsc - Exit";
		setColor();
	}

	void draw()
	{
		system("cls");
		field(0, 0, height, width);

		// обнуляємо стакан і всі показники: час гри, очки, швидкість
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
				matrix[j][i] = 0;
		for (int j = 0; j < height; j++)
		{
			matrix[j][0] = 1;
			matrix[j][width - 1] = 1;
		}
		for (int i = 0; i < width; i++)
		{
			matrix[height - 1][i] = 1;
		}

		setSpeed(0);
		setPoint(0);
		timeGame = 0;

		int r = 0;
		int curr, next;
		int x, y;
		int end = 0; // прапорець заповнення матриці, якщо фігури нема куди рухатись при першій промальовці - кінець гри

		r = 0;
		x = 1;
		y = width / 2 - 4;

		// тимчасова промальовка усіх фігур у всіх позиціях для загального перегляду
		int ix = 1;
		int iy = 40;
		
		for (int i = 0; i < 4; ++i)
		{
			gotoxy(0, i * 2 + iy);
			cout << i;
			gotoxy(0, i * 2 + iy + 10);
			cout << i;
			gotoxy(0, i * 2 + iy + 20);
			cout << i;
			gotoxy(0, i * 2 + iy + 30);
			cout << i;
		}

		for (int r = 0; r < 4; r++)
		{
			for (int f = 0; f < 7; f++)
			{
				figure[f]->showShape(ix, iy, r);
				ix += 4;	
			}
			ix = 1;
			iy += 10;
		}
		// end
			
		curr = rand() % 7;
		next = rand() % 7;
		text();
		figure[next]->showShape(3, width + 3, 0);
		do
		{
			++timeGame;

			if (timeGame % (delay - getSpeed()) == 0)
			{
				figure[curr]->showShape(x, y, r);
				Sleep(delay - getSpeed());
				figure[curr]->hideShape(x, y, r);
				++end;
				++x;
				score();
				if (audit(x, y, r, curr))
				{		
						figure[curr]->showShape(x, y, r);
						if (end == 1)
						{
							gameOver();
							break;
						}
						figure[next]->hideShape(3, width + 3, 0);
						x = 1;
						y = width / 2 - 4;
						r = 0;
						end = 0;
						curr = next;
						next = rand() % 7;
						figure[next]->showShape(3, width + 3, 0);
						auditRows();
				}
			}

			if (_kbhit())
			{
				switch (_getch())
				{
				case 80: // вниз
					x = fall(x, y, r, curr);
					break;
				case 75: // вліво
					y = move(x, y, r, curr, -2);
					break;
				case 77: // вправо
					y = move(x, y, r, curr, 2);
					break;
				case 32: // пробіл
					r = rotate(x, y, r, curr);
					break;
				case 27: // Esc вихід
					gameOver();
					return;
				case 115: // s запис поточного стану гри
					saveGame();
					break;
				case 108: // l завантаження записаної гри
					loadGame(x, y, r, curr);
					break;
				case 13: // Enter для тестів
					//showMatrix01();
						speed += 100;
					break;
				}
			}
			
		} while (true);
	}


};

class Game
{
public:
	//стартове меню
	int menu()
	{
		system("cls");
		int nameX = 2, nameY = 15;
		setColor(8);
		gotoxy(nameX + 0, nameY); cout << "TTTTT  EEEE  TTTTT  RRR   I   SSS " << endl;
		gotoxy(nameX + 1, nameY); cout << "  T    E       T    R  R  I  S    " << endl;
		gotoxy(nameX + 2, nameY); cout << "  T    EEE     T    RRR   I    S  " << endl;
		gotoxy(nameX + 3, nameY); cout << "  T    E       T    R R   I      S" << endl;
		gotoxy(nameX + 4, nameY); cout << "  T    EEEE    T    R  R  I   SSS " << endl;
		setColor();
		int const X = 10;
		int const Y = 25;
		int const item = 4;
		int choose = 0;
		string menuItem[item] = { "* Play game", "* Points","* Rules", "* Exit" };
		for (int i = 0; i < item; ++i)
		{
			gotoxy(X + i, Y);
			if (i == 0)
				setColor(240);
			else
				setColor();
			cout << menuItem[i];
		}
		gotoxy(0, 0);
		for (;;) {
			switch (_getch()) {
			case 72:
				gotoxy(X + choose, Y);
				setColor();
				cout << menuItem[choose];
				--choose;
				if (choose < 0)
					choose = item - 1;
				gotoxy(X + choose, Y);
				setColor(240);
				cout << menuItem[choose];
				break;
			case 80:
				gotoxy(X + choose, Y);
				setColor();
				cout << menuItem[choose];
				++choose;
				if (choose > item - 1)
					choose = 0;
				gotoxy(X + choose, Y);
				setColor(240);
				cout << menuItem[choose];
				setColor();
				break;
			case 13:
				setColor();
				return choose;
			}
		}

	}

	//прибираємо курсор, взято звідси http://www.cyberforum.ru/cpp-beginners/thread102665.html
	void hidecursor()
	{
		void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(handle, &structCursorInfo);
	}


	void start()
	{
		hidecursor();
		Matrix m;
		for (;;)
		{
			switch (menu())
			{
			case 0:
				m.draw();
				break;
			case 1:
				m.loadScore();
				break;
			case 2:
				m.rules();
				break;
			case 3:
				return;
			}
		}
	}
	
		
};

int main()
{
	srand(unsigned(time(0)));
	Game g;
	g.start();
	
	return 0;
}

// позиціонування курсора на екрані згідно заданих координат
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//колір тексту
void setColor(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

//time_t t = time(0);  
//struct tm * now = localtime(&t);

/*
save << getPoint() << "\t\t" << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60 <<
"\t\t" << now->tm_mday << "." << setfill('0') << setw(2) << (now->tm_mon + 1) << "." << (now->tm_year + 1900) << endl;
*/