#include <iostream>
using namespace std;

class Animal
{
	//Астрактный класс
public:
	virtual void Sound() = 0;
};
class Cat :public Animal
{
	//Астрактный класс
};
class Lion :public Cat
{
	//Конкретный класс
public:
	void Sound()override
	{
		cout << "Pppppp" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal animal;		//E0322, C2259
	//Cat cat;
	Lion lion;
}