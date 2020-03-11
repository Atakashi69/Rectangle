#include "Rectangle.h"

Rectangle::Rectangle(Point p1, Point p2)
{
	NewRectFromDiag(p1, p2);
}

void Rectangle::NewRectFromDiag(Point p1, Point p2)
{
	if ((p1.x > p2.x) && (p1.y > p2.y))
		swap(p1, p2);
	else if ((p1.x > p2.x) && (p1.y < p2.y))
		swap(p1, p2);

	if ((p1.x < p2.x) && (p1.y < p2.y))
	{
		A = p1;
		C = p2;
		B = { A.x, C.y };
		D = { C.x, A.y };
	}
	else if ((p1.x < p2.x) && (p1.y > p2.y))
	{
		B = p1;
		D = p2;
		A = { B.x, D.y };
		C = { D.x, B.y };
	}
}

void Rectangle::StyleEnter()
{
	cout << "Выберите тип обводки:" << endl;
	cout << "1. Без обводки" << endl;
	cout << "2. Заливкой" << endl;
	cout << "3. Пунктиром" << endl;
	cout << "4. Точками" << endl;
	cin >> style.border.type;

	if (style.border.type != bEMPTY)
	{
		cout << "Введите цвет обводки:" << endl;
		style.border.color.Enter();

		cout << "Введите толщину обводки: ";
		cin >> style.border.thickness;
	}

	cout << "Выберите тип заливки:" << endl;
	cout << "1. Не заливать" << endl;
	cout << "2. Заливать" << endl;
	cin >> style.fill.type;

	if (style.fill.type != fEMPTY)
	{
		cout << "Введите цвет заливки:" << endl;
		style.fill.color.Enter();
	}
}

void Rectangle::Enter()
{
	double x1, y1, x2, y2;
	cout << "Введите координаты начала диагонали: ";
	cin >> x1 >> y1;
	cout << "Введите координаты конца диагонали: ";
	cin >> x2 >> y2;

	NewRectFromDiag({ x1, y1 }, { x2, y2 });

	StyleEnter();
}

void Rectangle::StyleShow()
{
	cout << "Обводка: " << endl;

	if (style.border.type == bEMPTY)
	{
		cout << "Без обводки" << endl;
	}
	else
	{
		style.border.color.Show();

		if (style.border.type == bFILL)
			cout << "Заливкой" << endl;
		else if (style.border.type == bDASH)
			cout << "Пунктиром" << endl;
		else if (style.border.type == bDOT)
			cout << "Точками" << endl;

		cout << "толщина: " << style.border.thickness << endl;
	}

	cout << "Цвет прямоугольника: ";

	if (style.fill.type == fEMPTY)
	{
		cout << "Прозрачный" << endl;
	}
	else
	{
		style.fill.color.Show();
	}
}

void Rectangle::Show()
{
	cout << "Координаты прямоугольника: ("
		<< A.x << ", " << A.y << "), ("
		<< B.x << ", " << B.y << "), ("
		<< C.x << ", " << C.y << "), ("
		<< D.x << ", " << D.y << ")\n";

	StyleShow();
}

void Rectangle::ChangeSize()
{
	cout << "Во сколько раз увеличить прямоугольник: ";
	int k;
	cin >> k;

	double a = D.x - A.x;
	double b = B.y - A.y;

	A.x = center.x - (a / 2 * k);
	A.y = center.y - (b / 2 * k);

	C.x = center.x + (a / 2 * k);
	C.y = center.y + (b / 2 * k);

	NewRectFromDiag(A, C);
}

void Rectangle::Move()
{
	cout << "Куда вы хотите переместить прямоугольник ?" << endl;
	cout << "1. Вверх" << endl;
	cout << "2. Вниз" << endl;
	cout << "3. Вправо" << endl;
	cout << "4. Влево" << endl;
	int input;
l1: cin >> input;

	cout << "Переместить на: ";
	double k;
	cin >> k;

	switch (input)
	{
	case 1:
		A.y += k;
		B.y += k;
		C.y += k;
		D.y += k;
		center.y += k;
		break;
	case 2:
		A.y -= k;
		B.y -= k;
		C.y -= k;
		D.y -= k;
		center.y -= k;
		break;
	case 3:
		A.x += k;
		B.x += k;
		C.x += k;
		D.x += k;
		center.x += k;
		break;
	case 4:
		A.x -= k;
		B.x -= k;
		C.x -= k;
		D.x -= k;
		center.x -= k;
		break;
	default:
		cout << "Wrong input!" << endl;
		goto l1;
		break;
	}
}

Rectangle MinRect(Rectangle rect1, Rectangle rect2)
{
	Rectangle left, right;

	if (rect1.A.x < rect2.A.x && rect1.C.x < rect2.C.x)
		left = rect1, right = rect2;
	else
		left = rect2, right = rect1;

	Rectangle temp;
	temp.A = left.A;
	temp.C = right.C;
	temp.NewRectFromDiag(temp.A, temp.C);

	return temp;
}

Rectangle InterRect(Rectangle rect1, Rectangle rect2)
{
	Rectangle left, right;

	if (rect1.A.x < rect2.A.x && rect1.C.x < rect2.C.x)
		left = rect1, right = rect2;
	else
		left = rect2, right = rect1;

	bool intersection = (right.A.x - left.C.x < 0 && right.A.y - left.C.y < 0) ? true : false;

	Rectangle temp;
	
	if ((left.D.y <= right.D.y) && intersection)
	{
		temp.A = right.A;
		temp.C = left.C;
		temp.NewRectFromDiag(temp.A, temp.C);
	}
	else if ((left.D.y >= right.D.y) && intersection)
	{
		temp.B = right.B;
		temp.D = left.D;
		temp.NewRectFromDiag(temp.B, temp.D);
	}
	else
		cout << "Прямоугольники не пересекаются" << endl;

	return temp;
}
