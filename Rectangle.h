#pragma once
#include <iostream>

using namespace std;

struct Point
{
	double x, y;
	Point(double X = -1, double Y = -1) { x = X; y = Y; }
};

struct Color
{
	short int r, g, b;
	void Enter()
	{
		cout << "R: "; cin >> r;
		cout << "G: "; cin >> g;
		cout << "B: "; cin >> b;
	}
	void Show()
	{
		cout << "RGB(" << r << ", " << g << ", " << b << ")" << endl;
	}
};

enum BorderType
{
	bEMPTY = 1,
	bFILL,
	bDASH,
	bDOT
};

enum FillType
{
	fEMPTY = 1,
	fFILL
};

struct Border
{
	Color color;
	int type;
	int thickness;
};

struct Fill
{
	Color color;
	int type;
};

struct Style
{
	Border border;
	Fill fill;
};

class Rectangle
{
private:
	Point A, B, C, D, center;
	Style style;
	void StyleEnter();
	void StyleShow();
	void NewRectFromDiag(Point, Point);
	friend Rectangle MinRect(Rectangle, Rectangle);
	friend Rectangle InterRect(Rectangle, Rectangle);
public:
	Rectangle(void) {}
	Rectangle(Point, Point);

	void Enter();
	void Show();
	void ChangeSize();
	void Move();

};
