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

#define GRAY 3 //2 dark green
#define DBLUE 9
#define GREEN 10
#define BLUE 11 //11 ligth blue
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


	void showShape(int x, int y, int r = 0)
	{
		Point p;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (shape[r][i][j] != 0)
					p.setPoint(i + x, j * 2 + y, shape[r][i][j]);
			}
			
		}
	}

	void hideShape(int x, int y, int r)
	{
		Point p;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (shape[r][i][j] != 0)
					p.setPoint(i + x, j * 2 + y, 0);
			}

		}

	}

	int getShape()
	{
		return shape[4][4][4];
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


};

// гачок направо синій
class Figure1 : public Shape
{
private:

public:

	Figure1()
	{


		shape[0][0][1] = DBLUE;
		shape[0][1][1] = DBLUE;
		shape[0][2][1] = DBLUE;
		shape[0][0][2] = DBLUE;

		shape[1][1][0] = DBLUE;
		shape[1][1][1] = DBLUE;
		shape[1][1][2] = DBLUE;
		shape[1][2][2] = DBLUE;

		shape[2][0][2] = DBLUE;
		shape[2][1][2] = DBLUE;
		shape[2][2][2] = DBLUE;
		shape[2][2][1] = DBLUE;

		shape[3][2][0] = DBLUE;
		shape[3][2][1] = DBLUE;
		shape[3][2][2] = DBLUE;
		shape[3][1][0] = DBLUE;

	}

};

//гачок наліво сірий
class Figure2 : public Shape
{
private:

public:

	Figure2()
	{


		shape[0][0][1] = GRAY;
		shape[0][1][1] = GRAY;
		shape[0][2][1] = GRAY;
		shape[0][2][2] = GRAY;

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
	int matrix[height][width] = {};

public:

	Matrix(int point = 0, int speed = 0)
	{
		setPoint(0);
		setSpeed(0);
		timeGame = 0;
		
			for (size_t j = 0; j < height; j++)
			{
				matrix[j][0] = 1;
				matrix[j][width - 1] = 1;
			}
			for (size_t i = 0; i < width; i++)
			{
				matrix[height - 1][i] = 1;
			}
	}

	~Matrix()
	{
		//delete[]figure;
	}

	// тимчасова промальовка
	void showMatrix()
	{
		gotoxy(0, 0);
		for (size_t i = 0; i < height; i++) 
		{
			for (size_t j = 0; j < width; j++)
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
			frame(186, ' ', 186, width);
		frame(200, 205, 188, width);
	}


	// перевірка чи досягнула фігура дна або інших фігур
	bool audit(int x, int y, int r, int curr)
	{
		int shape[4][4][4];
		shape[4][4][4] = figure[curr]->getShape();
		int xpos = 10;
		gotoxy(xpos, 50);
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
				cout << shape[r][i][j];
			gotoxy(xpos + i, 50);
		}

		for (size_t i = 3; i >=0 ; i--)
		{
			for (size_t j = 3; j >= 0; j--)
			{
				if (shape[r][i][j] != 0 && matrix[x + i + 1][y + j * 2 + 1] != 0 )
					return true;
				gotoxy(5, 50);
				cout << "[" << i << "][" << j << "] = " << shape[r][i][j];
			}
		}
		return false;
	}

	bool auditRows()
	{
		return true;
	}

	// інфо про гру
	void score()
	{
		int pos = 8;
		gotoxy(pos, width);
		cout << "\tTime:\t" << (timeGame / 1000) / 60 << ":" << setfill('0') << setw(2) << (timeGame / 1000) % 60;
		gotoxy(pos + 2, width);
		cout << "\tScore:\t" << getPoint();
		gotoxy(pos + 4, width);
		cout << "\tLevel:\t" << getSpeed() / 100;	

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
		//
		//if (y <= 0 || y >= width - 1)
		//{
		//	/*if (y <= 0)
		//		y = 1;*/
		//}
		//else
		//{
		//	figure[curr]->hideShape(x, y, r);
		//		y += leftrigth;
		//	figure[curr]->showShape(x, y, r);
		//}

		figure[curr]->hideShape(x, y, r);
		y += leftrigth;
		figure[curr]->showShape(x, y, r);
		return y;
	}

	// прискорення падіння фігури
	int fall(int x, int y, int r, int curr)
	{
		if (x > 18)
		{
			field(0, 0, height, width);
		}
		else
		{
			figure[curr]->hideShape(x, y, r);
			++x;
			figure[curr]->showShape(x, y, r);
		}
		return x;
	}

	void draw()
	{
		
		field(0, 0, height, width);

		int r = 0;
		int curr, next;
		int x, y;

		r = 0;
		x = 1;
		y = width / 2 - 4;

		// тимчасова промальовка усіх фігур у всіх позиціях для загального перегляду
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
		// end
			
		curr = rand() % 7;
		next = rand() % 7;
		gotoxy(1, width);
		cout << "\tNext";
		gotoxy(14, width);
		cout << "\tEsc - Exit\n";
		figure[next]->showShape(3, width + 3, 0);
		do
		{
			++timeGame;

			if (timeGame % (delay - speed) == 0)
			{
				figure[curr]->showShape(x, y, r);
				Sleep(delay - speed);
				figure[curr]->hideShape(x, y, r);
				++x;
				score();
				if (audit(x, y, r, curr))
				{
					//if (x >= 18)
					{
						setPoint(getPoint() + 1);
						figure[curr]->showShape(x, y, r);
						figure[next]->hideShape(3, width + 3, 0);
						x = 1;
						y = width / 2 - 4;
						r = 0;
						curr = next;
						next = rand() % 7;
						figure[next]->showShape(3, width + 3, 0);
					}
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
					gotoxy(height + 1, 0);
					setColor(RED);
					cout << "\tExit";
					Sleep(500);
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
		int choose = 0;
		string menuItem[3] = { "* Play game","* Rules and about", "* Exit" };
		gotoxy(X, Y); //переробити менюшку на кілька пунктів меню!!!
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

	void load()
	{}

	void save()
	{}

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

