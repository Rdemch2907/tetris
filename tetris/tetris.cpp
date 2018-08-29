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
int delay = 500;

struct Score
{
	int score;
	string duration;
	string date;
	
	void print()
	{
		cout << "\t" << score << "\t\t" << duration << "\t\t" << date << endl;
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
		/*
		for (int i = 0; i < 255; ++i)
		{
			setColor(i);
			cout << i << "  ";
		}
		system("pause");
		*/
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
private:

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

	int getShape() const
	{
		return shape[4][4][4];
	}


};

// гачок направо синій
class Figure1 : public Shape
{
private:

public:

	Figure1()
	{


		shape[0][0][1] = GREEN;
		shape[0][1][1] = GREEN;
		shape[0][2][1] = GREEN;
		shape[0][0][2] = GREEN;

		shape[1][1][0] = GREEN;
		shape[1][1][1] = GREEN;
		shape[1][1][2] = GREEN;
		shape[1][2][2] = GREEN;

		shape[2][0][2] = GREEN;
		shape[2][1][2] = GREEN;
		shape[2][2][2] = GREEN;
		shape[2][2][1] = GREEN;

		shape[3][2][0] = GREEN;
		shape[3][2][1] = GREEN;
		shape[3][2][2] = GREEN;
		shape[3][1][0] = GREEN;

	}

	//int getShape() const
	//{
	//	return shape[4][4][4];
	//}

};

//гачок наліво сірий
class Figure2 : public Shape
{
private:

public:

	Figure2()
	{


		shape[0][0][1] = DGREEN;
		shape[0][1][1] = DGREEN;
		shape[0][2][1] = DGREEN;
		shape[0][2][2] = DGREEN;

		shape[1][1][0] = DGREEN;
		shape[1][1][1] = DGREEN;
		shape[1][1][2] = DGREEN;
		shape[1][2][0] = DGREEN;

		shape[2][0][2] = DGREEN;
		shape[2][1][2] = DGREEN;
		shape[2][2][2] = DGREEN;
		shape[2][0][1] = DGREEN;

		shape[3][2][0] = DGREEN;
		shape[3][2][1] = DGREEN;
		shape[3][2][2] = DGREEN;
		shape[3][1][2] = DGREEN;

	}

};

// квадрат жовтий
class Figure3 : public Shape
{
private:

public:

	Figure3()
	{


		shape[0][1][1] = 14;
		shape[0][1][2] = 14;
		shape[0][2][1] = 14;
		shape[0][2][2] = 14;

		shape[1][1][1] = 14;
		shape[1][1][2] = 14;
		shape[1][2][1] = 14;
		shape[1][2][2] = 14;

		shape[2][1][1] = 14;
		shape[2][1][2] = 14;
		shape[2][2][1] = 14;
		shape[2][2][2] = 14;

		shape[3][1][1] = 14;
		shape[3][1][2] = 14;
		shape[3][2][1] = 14;
		shape[3][2][2] = 14;

	}

};

// дві цеглинки зі зсувом вправо зелена
class Figure4 : public Shape
{
private:

public:

	Figure4()
	{


		shape[0][1][2] = PINK;
		shape[0][1][3] = PINK;
		shape[0][2][1] = PINK;
		shape[0][2][2] = PINK;

		shape[1][2][2] = PINK;
		shape[1][3][2] = PINK;
		shape[1][1][1] = PINK;
		shape[1][2][1] = PINK;

		shape[2][1][2] = PINK;
		shape[2][1][3] = PINK;
		shape[2][2][1] = PINK;
		shape[2][2][2] = PINK;

		shape[3][2][2] = PINK;
		shape[3][3][2] = PINK;
		shape[3][1][1] = PINK;
		shape[3][2][1] = PINK;

	}

};

// паличка з відротком посередині рожева
class Figure5 : public Shape
{
private:

public:

	Figure5()
	{


		shape[0][2][1] = DBLUE;
		shape[0][2][2] = DBLUE;
		shape[0][2][3] = DBLUE;
		shape[0][1][2] = DBLUE;

		shape[1][1][1] = DBLUE;
		shape[1][2][1] = DBLUE;
		shape[1][3][1] = DBLUE;
		shape[1][2][2] = DBLUE;

		shape[2][2][1] = DBLUE;
		shape[2][2][2] = DBLUE;
		shape[2][2][3] = DBLUE;
		shape[2][3][2] = DBLUE;

		shape[3][1][2] = DBLUE;
		shape[3][2][2] = DBLUE;
		shape[3][3][2] = DBLUE;
		shape[3][2][1] = DBLUE;

	}

};

// дві цеглинки зі зсувом вліво червона
class Figure6 : public Shape
{
private:

public:

	Figure6()
	{


		shape[0][1][1] = 12;
		shape[0][1][2] = 12;
		shape[0][2][2] = 12;
		shape[0][2][3] = 12;

		shape[1][2][1] = 12;
		shape[1][3][1] = 12;
		shape[1][1][2] = 12;
		shape[1][2][2] = 12;

		shape[2][1][1] = 12;
		shape[2][1][2] = 12;
		shape[2][2][2] = 12;
		shape[2][2][3] = 12;

		shape[3][2][1] = 12;
		shape[3][3][1] = 12;
		shape[3][1][2] = 12;
		shape[3][2][2] = 12;

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
		
			for (int j = 0; j < height; j++)
			{
				matrix[j][0] = 1;
				matrix[j][width - 1] = 1;
			}
			for (int i = 0; i < width; i++)
			{
				matrix[height - 1][i] = 1;
			}
	}

	~Matrix()
	{
		for (int i = 0; i < 7; ++i)
			delete [] figure[i];
	}

	// тимчасова промальовка
	void showMatrix()
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
		//shape[4][4][4] = figure[curr]->getShape();
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

		for (int i = 3; i >=0 ; --i) 
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
			}	while (i < width - 1);

			// якщо є видаляємо заповнені
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
		cout << "\tScore:\t" << getPoint();
		gotoxy(pos + 2, width);
		cout << "\tLevel:\t" << getSpeed() / 100 << " - " << getSpeed();
		gotoxy(pos + 3, width);
		cout << "\tTime:\t" << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60;

	}

	// поворот фігури за часовою стрілкою
	int rotate(int x, int y, int r, int curr)
	{
		figure[curr]->hideShape(x, y, r);

		if (r == 3)
			r = 0;
		else
			++r;

		figure[curr]->showShape(x, y, r);

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
								cout << "matrix[" << x + i << "][" << y + j - 1 << "] = " << matrix[x + i][y + j - 1]  << "shape[" << i << "][" << j << "] = " << shape[r][i][j];
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
			for (int j = 3; j >=0 ; --j)
				for (int i = 0; i < 4; ++i)
				{
					if (shape[r][i][j] != 0)
					{
					//	gotoxy(0, 80);
					//	cout << "shape[" << i << "][" << j << "] = " << shape[r][i][j];
						for (int i = 0; i < 4; ++i)
							if (shape[r][i][j] != 0 && matrix[x + i][y + (j + 1) * 2] != 0)
							{
							//	gotoxy(1, 80);
							//	cout << "matrix[" << x + i << "][" << y + j * 2  + 1 << "] = " << matrix[x + i][y + j * 2 + 1]  << "shape[" << i << "][" << j << "] = " << shape[r][i][j];
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

						//gotoxy(i + 2, 80);
						//cout << matrix[x + i][y - 1] << " - " << shape[r][i][j];
				}
		}

		return y;
	}

	// прискорення падіння фігури
	int fall(int x, int y, int r, int curr)
	{
			figure[curr]->hideShape(x, y, r);
			++x;
			figure[curr]->showShape(x, y, r);
		return x;
	}

	void saveScore()
	{
		vector<Score> table;
		if (getPoint() != 0)
		{
			ifstream load("score", ios::binary);
			if (!load.is_open());
			else
				//return;
			{
				load.read((char*)&table, sizeof(table));
				for (auto elem : table)
					elem.print();
			}
			load.close();
			ofstream save;
			save.open("score", ios::binary | ios::app);

			if (!save.is_open())
				return;
			time_t t = time(0);  
			struct tm * now = localtime(&t);
			s.score = getPoint();
			s.date = now->tm_mday + "." /* + setfill('0')* + setw(2)*/ + (now->tm_mon + 1) + '.' + (now->tm_year + 1900);
			s.duration = (timeGame / 1000) / 60 + ":" + /*setfill('0') + setw(2) +*/ (timeGame / 1000) % 60;
			/*
			save << getPoint() << "\t\t" << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60 << 
				"\t\t" << now->tm_mday << "." << setfill('0') << setw(2) << (now->tm_mon + 1) << "." << (now->tm_year + 1900) << endl;
				*/
			table.push_back(s);
			save.write((char*)&table, sizeof(table));
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
		load.read((char*)&table, sizeof(table));
		for (auto elem : table)
			elem.print();
	/*	ifstream load;
		load.open("score", ios::out);
		if (!load.is_open())
			return;

		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);
	

		string str;
		int xcell = 5;
		int ycell = 25;
		int count = 0;
		gotoxy(xcell, ycell);
		cout << "#\tScore\t\tDuration\tDate";
		gotoxy(++xcell, ycell);
		cout << "==================================================";
		while (getline(load, str))
		{
			if (count == 0)
				setColor();
			else
				setColor(GRAY);
			gotoxy(++xcell, ycell);
			cout << ++count << "\t" << str << endl;
		}*/
		load.close();

		setColor(0);
		cout << endl << endl;
		system("pause");
		//_getch();
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

	void draw()
	{
		system("cls");
		field(0, 0, height, width);

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
		gotoxy(1, width);
		cout << "\tNext";
		
		setColor(GRAY);
		gotoxy(height - 8, width);
		cout << "\t<--  Move  -->";
		gotoxy(height - 7, width);
		cout << "\tSpace - Rotate";
		gotoxy(height - 5, width);
		cout << "\tF5 - Save";
		gotoxy(height - 4, width);
		cout << "\tF7 - Load";
		gotoxy(height - 2, width);
		cout << "\tEsc - Exit";
		setColor();
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
				case 13: //Enter для тестів
					showMatrix();
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
		int const item = 5;
		int choose = 0;
		string menuItem[item] = { "* Play new game", "* Load game", "* Points","* Rules and about", "* Exit" };
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
				cout << "1";
				break;
			case 2:
				m.loadScore();
				break;
			case 3:
				cout << "3";
				break;
			case 4:
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

