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

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <stdio.h>

using namespace std;

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

const int width = 20;
const int heigth = 20;
int timeGame;
int delay = 500;

struct Pos
{
	int x, y;
};


class Point
{
private:
	Pos pos;
	
public:

	void setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}

	Pos getPos() const
	{
		return pos;
	}

	void setPoint( int x, int y, int color)
	{
		setPos(x, y);
		setColor(color);
		cout << "\xDB\xDB";
		setColor();
		/*
		for (int i = 0; i < 255; ++i)
		{
			setColor(i);
			cout << i << "  ";
		}
		*/
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
	void setColor(int color = 15)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, color);
	}
};


class Shape abstract
{
protected:
	int shape[4][4][4] = {};

public:


	int showShape(int x, int y, int r = 0)
	{
		Point p;
		//gotoxy(x, y);
		for (size_t i = 0; i < 4; i++)
		{
			//cout << "i" << i;
			gotoxy(x + i, y);
			for (size_t j = 0; j < 4; j++)
			{
				if (shape[r][i][j] != 0)
					p.setPoint(i * 2 + x, j + y, shape[r][i][j]);
				//cout << shape[r][i][j];
			}
			//cout << endl;
			
		}

	/*	
		if (r == 3)
			r = 0;
		else
			++r;
	*/

		return r;
	}

	int hideShape(int x, int y, int r = 0)
	{
		Point p;
		gotoxy(x, y);
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				//if (shape[r][i][j] != 0)
					p.setPoint(i * 2 + x, j + y, 0);
			}
			//cout << endl;
			gotoxy(i + x, y);
		}

		return r;
	}

	int rotate(int x, int y, int r)
	{
		if (r == 3)
			r = 0;
		else
			++r;

		return showShape(x, y, r);
	}


};


// паличка блакитна
class Figure0 : public Shape
{
private:

public:

	Figure0()
	{

		shape[0][0][1] = 11;
		shape[0][1][1] = 11;
		shape[0][2][1] = 11;
		shape[0][3][1] = 11;

		shape[1][1][0] = 11;
		shape[1][1][1] = 11;
		shape[1][1][2] = 11;
		shape[1][1][3] = 11;

		shape[2][0][1] = 11;
		shape[2][1][1] = 11;
		shape[2][2][1] = 11;
		shape[2][3][1] = 11;

		shape[3][1][0] = 11;
		shape[3][1][1] = 11;
		shape[3][1][2] = 11;
		shape[3][1][3] = 11;


	}

};

// гачок направо синій
class Figure1 : public Shape
{
private:

public:

	Figure1()
	{


		shape[0][0][1] = 9;
		shape[0][1][1] = 9;
		shape[0][2][1] = 9;
		shape[0][0][2] = 9;

		shape[1][1][0] = 9;
		shape[1][1][1] = 9;
		shape[1][1][2] = 9;
		shape[1][2][2] = 9;

		shape[2][0][2] = 9;
		shape[2][1][2] = 9;
		shape[2][2][2] = 9;
		shape[2][2][1] = 9;

		shape[3][2][0] = 9;
		shape[3][2][1] = 9;
		shape[3][2][2] = 9;
		shape[3][1][0] = 9;

	}

};

//гачок наліво сірий
class Figure2 : public Shape
{
private:

public:

	Figure2()
	{


		shape[0][0][1] = 8;
		shape[0][1][1] = 8;
		shape[0][2][1] = 8;
		shape[0][2][2] = 8;

		shape[1][1][0] = 8;
		shape[1][1][1] = 8;
		shape[1][1][2] = 8;
		shape[1][2][0] = 8;

		shape[2][0][2] = 8;
		shape[2][1][2] = 8;
		shape[2][2][2] = 8;
		shape[2][0][1] = 8;

		shape[3][2][0] = 8;
		shape[3][2][1] = 8;
		shape[3][2][2] = 8;
		shape[3][1][2] = 8;

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


		shape[0][1][2] = 10;
		shape[0][1][3] = 10;
		shape[0][2][1] = 10;
		shape[0][2][2] = 10;

		shape[1][2][2] = 10;
		shape[1][3][2] = 10;
		shape[1][1][1] = 10;
		shape[1][2][1] = 10;

		shape[2][1][2] = 10;
		shape[2][1][3] = 10;
		shape[2][2][1] = 10;
		shape[2][2][2] = 10;

		shape[3][2][2] = 10;
		shape[3][3][2] = 10;
		shape[3][1][1] = 10;
		shape[3][2][1] = 10;

	}

};

// паличка з відротком посередині рожева
class Figure5 : public Shape
{
private:

public:

	Figure5()
	{


		shape[0][2][1] = 13;
		shape[0][2][2] = 13;
		shape[0][2][3] = 13;
		shape[0][1][2] = 13;

		shape[1][1][2] = 13;
		shape[1][2][2] = 13;
		shape[1][3][2] = 13;
		shape[1][2][3] = 13;

		shape[2][2][1] = 13;
		shape[2][2][2] = 13;
		shape[2][2][3] = 13;
		shape[2][3][2] = 13;

		shape[3][1][2] = 13;
		shape[3][2][2] = 13;
		shape[3][3][2] = 13;
		shape[3][2][1] = 13;

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

public:

	Matrix(int point = 0, int speed = 0)
	{
		point = 0;
		speed = 0;
		timeGame = 0;
	}

	~Matrix()
	{
		//delete[]figure;
	}

	//промальовка рамки для гри
	void frame(char begin, char middle, char end, int width)
	{
		for (int i = 0; i <= width; ++i)
			if (i == 0)
				cout << char(begin);
			else
				if (i == width)
					cout << char(end);
				else
					cout << char(middle);
		cout << endl;
	}

	void move()
	{}

	void rotate()
	{}

	void draw()
	{
		//промальовка ігрового поля
		frame(201, 205, 187, width);
		for (int j = 1; j < 20; ++j)
			frame(186, ' ', 186, width);
		frame(200, 205, 188, width);

		int r = 0;
		int curr, next;
		int x, y;

		r = 0;
		x = 1;
		y = width / 2 - 2;
		int ix = 0;
		int iy = 40;

		for (int r = 0; r < 4; r++)
		{
			for (int f = 0; f < 7; f++)
			{
				figure[f]->showShape(ix, iy, r);
				ix += 4;
			}
			ix = 0;
			iy += 10;
		}
			
		curr = rand() % 7;
		next = rand() % 7;
		gotoxy(1, width);
		cout << "\tNext";
		figure[next]->showShape(3, width + 3, r);
		do
		{
			++timeGame;

			if (timeGame % delay == 0)
			{
				figure[curr]->showShape(x, y, r);
				Sleep(delay);
				figure[curr]->hideShape(x, y, r);
				++x;
				gotoxy(8, width);
				cout << "\tTime " << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60;;
				if (x >= 18)
				{
					figure[curr]->showShape(x, y, r);
					figure[next]->hideShape(3, width + 3, r);
					x = 1;
					y = width / 2 - 2;
					r = 0;
					curr = next;
					next = rand() % 7;
					figure[next]->showShape(3, width + 3, r);
				}
			}

			if (_kbhit())
			{
				switch (_getch())
				{
				case 80: // вниз
					figure[curr]->hideShape(x, y, r);
					++x;
					figure[curr]->showShape(x, y, r);
					break;
				case 75: // вліво
					figure[curr]->hideShape(x, y, r);
					y -= 2;
					figure[curr]->showShape(x, y, r);
					break;
				case 77: // вправо
					figure[curr]->hideShape(x, y, r);
					y += 2;
					figure[curr]->showShape(x, y, r);
					break;
				case 32: // пробіл
					r = figure[curr]->rotate(x, y, r);
					break;
				case 27:
					gotoxy(heigth + 1, 0);
					setColor(RED);
					cout << "\tExit";
					Sleep(500);
					return;
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
		int choose = 0;
		string menuItem[3] = { "* Play game","* Rules and about", "* Exit" };
		gotoxy(X, Y);
		setColor(240);
		cout << menuItem[0];
		setColor();
		gotoxy(X + 1, Y);
		cout << menuItem[1];
		gotoxy(X + 2, Y);
		cout << menuItem[2];
		gotoxy(0, 0);
		for (;;) {
			switch (_getch()) {
			case 72:
				gotoxy(X + choose, Y);
				setColor();
				cout << menuItem[choose];
				--choose;
				if (choose < 0)
					choose = 2;
				gotoxy(X + choose, Y);
				setColor(240);
				cout << menuItem[choose];
				break;
			case 80:
				gotoxy(X + choose, Y);
				setColor();
				cout << menuItem[choose];
				++choose;
				if (choose > 2)
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
		menu();
		system("cls");
		Matrix m;
		m.draw();
	}
		

		
};




int main()
{
	srand(unsigned(time(0)));
	Game g;
	g.start();
	
	//cout << endl;
	//system("pause");
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

