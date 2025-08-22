//AbstractGeometry
#include <iostream>
#include<windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

	class Shape
	{
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800;
	protected:

		int start_x;
		int start_y;
		int line_width;
		Color color;		//цвет фигуры
	public:
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		double get_start_x()const
		{
			return start_x;
		}
		double get_start_y()const
		{
			return start_y;
		}
		double get_line_width()const
		{
			return line_width;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		Square(double side, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle :public Shape
	{
		double side_1;
		double side_2;
	public:
		void set_side_1(double side_1)
		{
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
		}
		double get_side_1()const
		{
			return side_1;
		}
		double get_side_2()const
		{
			return side_2;
		}
		double get_area()const override
		{
			return side_1 * side_2;
		}
		double get_perimeter()const override
		{
			return (side_1 + side_2) * 2;
		}
		void draw()const override
		{
			//cout << "Прямоугольник" << endl;
			//1) Прлучаем окно консоли:
			HWND hwnd = GetConsoleWindow();

			//2) Получаем контекст устройства консольного окна:
			HDC hdc = GetDC(hwnd);	//Контекст устройства (DeviceContext) - это то, на чем мы будем рисовать.

			//3) Создаем карандаш:
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Pen рисует контур фигуры
			//PC_SOLID - сплошная линия;
			//1 - толщина линии = 1 pixel;
			// RGB(255,0,0) - линия красного цвета

			//4)Создаем кисть, которая выполняет заливку фигуры:
			HBRUSH hBrush = CreateSolidBrush(color);

			//5) Выбираем, чем и на чем будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Вызываем нужную функцию для рисования фигуры:
			::Rectangle(hdc, start_x, start_y, start_x + side_1, start_y + side_2);
			// :: - Global Scope (Глобальное пространство имен).

			//7) Удаляем карандаш и кисть, поскольку они тоже занимают реурсы:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			//8) Контекст утройства занимает ресурсы, которые нужно освоодить:
			ReleaseDC(hwnd, hdc);
		}
		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Cторона 1: " << get_side_1() << endl;
			cout << "Cторона 2: " << get_side_2() << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};

	class Circle :public Shape
	{
		double diameter;
	public:
		void set_diameter(double diameter)
		{
			this->diameter = diameter;
		}
		double get_diameter()const
		{
			return diameter;
		}
		double get_radius()const
		{
			return diameter / 2;
		}
		double get_area()const override
		{
			return 3.14 * diameter * diameter / 4;
		}
		double get_perimeter()const override
		{
			return 3.14 * diameter;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + diameter, start_y + diameter);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		Circle(double diameter, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_diameter(diameter);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Диаметр: " << get_diameter() << endl;
			cout << "Радиус: " << get_radius() << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
	public:
		virtual double get_hight()const = 0;
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {};
		void info()const override
		{
			cout << "Высота треугольника: " << get_hight() << endl;
			Shape::info();
		}
	};

	class IsoscelesTriangle :public Triangle
	{
		double side;
		double base;
	public:
		void set_side(double side)
		{
			this->side = side;
		}
		void set_base(double base)
		{
			this->base = base;
		}
		double get_side()const
		{
			return side;
		}
		double get_base()const
		{
			return base;
		}
		double get_hight()const override
		{
			return sqrt(side*side-base*base/4);
		}
		double get_area()const override
		{
			return get_hight()*base/2;
		}
		double get_perimeter()const override
		{
			return side*2 + base;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertices[] =
			{
				{start_x, start_y},
				{start_x+base, start_y},
				{start_x+base/2, start_y-get_hight()}
			};
			::Polygon(hdc, vertices, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		IsoscelesTriangle(double side, double base, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_base(base);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Боковая сторона: " << get_side() << endl;
			cout << "Основание: " << get_base() << endl;
			Triangle::info();
		}
	};

	class EquilaterialTriangle :public IsoscelesTriangle
	{
	public:
		EquilaterialTriangle(double side, SHAPE_TAKE_PARAMETERS) : IsoscelesTriangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::Blue);
	/*Geometry::Square square(50, 500, 100, 5, Geometry::Color::Red);
	square.info();
	Geometry::Rectangle rectangle(200, 150, 600, 100, 1, Geometry::Color::Blue);
	rectangle.info();*/
	/*Geometry::Circle circle(50, 100, 200, 1, Geometry::Color::Yellow);
	circle.info();*/
	Geometry::IsoscelesTriangle triangle1(150, 100, 100, 400, 1, Geometry::Color::Green);
	triangle1.info();
	Geometry::EquilaterialTriangle triangle2(100, 300, 400, 1, Geometry::Color::Violet);
	triangle2.info();
}