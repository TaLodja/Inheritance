#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n--------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 10;
	static const int LAST_NAME_WIDTH = 16;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 3;
	static int count;			//Static member declaration
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//		Constructors
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}

	//		Methods
	virtual std::ostream& info(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age;
		os.width(TYPE_WIDTH);
		os << std::left;
		//os << strchr(typeid(*this).name(), ' ')+1 << ":";
		os << std::string(typeid(*this).name() + 6) + ":";	//убираем из строки слово 'class'
		os.width(LAST_NAME_WIDTH);
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}
	virtual std::istream& scan(std::istream& is)
	{
		return is >> last_name >> first_name >> age;
	}
};
//Static member definition
int Human::count = 0;		//Статические переменные класса инициализируют вне класса

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
	//return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age();
}

std::istream& operator>>(std::istream& is, Human& obj)
{
	return obj.scan(is);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance


class Student :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 5;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//		Constructors
	Student
	(
		HUMAN_TAKE_PARAMETERS,
		STUDENT_TAKE_PARAMETERS
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//		Methods
	std::ostream& info(std::ostream& os)const override
	{
		/*Human::info(os) << " ";
		return os << speciality << " " << group << " " << rating << " " << attendance;*/
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(RATING_WIDTH);
		os << attendance;
		return os;
	}

	std::istream& scan(std::istream& is)override
	{
		//return Human::scan(is) >> speciality >> group >> rating >> attendance;
		Human::scan(is);
		char buffer[SPECIALITY_WIDTH + 1]{};
		is.read(buffer, SPECIALITY_WIDTH);
		int i = 0;
		while (buffer[i] == ' ')
		{
			for (int j = 0; j < SPECIALITY_WIDTH + 1; j++)
				buffer[j] = buffer[j + 1];
			i++;
		}
		speciality = buffer;
		is >> group >> rating >> attendance;
		return is;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 3;
	std::string speciality;
	int experience;
public:
	const std::string get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//		Constructors
	Teacher
	(
		HUMAN_TAKE_PARAMETERS,
		TEACHER_TAKE_PARAMETERS
	) : Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//		Methods
	std::ostream& info(std::ostream& os)const override
	{
		/*Human::info(os) << " ";
		return os << speciality << " " << experience;*/
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
	}
	std::istream& scan(std::istream& is)override
	{
		//return Human::scan(is) >> speciality >> experience;
		Human::scan(is);
		char buffer[SPECIALITY_WIDTH + 1]{};
		is.read(buffer, SPECIALITY_WIDTH);
		int i = 0;
		while (buffer[i] == ' ')
		{
			for (int j = 0; j < SPECIALITY_WIDTH + 1; j++)
				buffer[j] = buffer[j + 1];
			i++;
		}
		speciality = buffer;
		is >> experience;
		return is;
	}
};

class Graduate : public Student
{
	std::string subject;	//Тема дипломного проекта
public:
	const std::string get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		this->subject = subject;
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//Methods
	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os) << " ";
		return os << subject;
	}
	std::istream& scan(std::istream& is)override
	{
		return std::getline(Student::scan(is), subject);
	}
};

void Print(Human* group[], const int n)
{
	cout << typeid(group).name() << endl;
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *group[i] << endl;
	}
	cout << delimiter << endl;
	cout << "Количество людей: " << Human::get_count() << endl;
}
void Save(Human** group, const int n, const char filename[])
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	system((std::string("start notepad ") + filename).c_str());
}

Human* HumanFactory(std::string& type)
{
	Human* human = nullptr;
	//if (type[0] == '\n')type = type.c_str() + 1;
	if (strstr(type.c_str(), "Human")) human = new Human("", "", 0);
	if (strstr(type.c_str(), "Student")) human = new Student("", "", 0, "", "", 0, 0);
	if (strstr(type.c_str(), "Graduate")) human = new Graduate("", "", 0, "", "", 0, 0, "");
	if (strstr(type.c_str(), "Teacher")) human = new Teacher("", "", 0, "", 0);
	return human;
}

Human** Load(const char filename[])
{
	int n = 0;		//количнство объектов, хранящихся в файле
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Посчитать количество объектов в файле для того, чтобы выделить память:
		std::string buffer;
		while (!fin.eof())
		{
			std::getline(fin, buffer);
			if (buffer.size() == 0) continue;
			//break - прерывает текущую итерацию, и все последующие;
			//continue - прерывает текущую итерацию и переходит к следующей;
			n++;
		}
		cout << "File position: " << fin.tellg() << endl;;
		cout << "Количество объектов: " << n << endl;
		//2) Выделяем память под массив объектоа:
		group = new Human * [n] {};
		//3) Возвращаемся в начало файла для того, чтобы считать объекты:
		fin.clear();
		fin.seekg(0);
		cout << "File position: " << fin.tellg() << endl;
		//4) Считываем объекты из файла:
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, buffer, ':');
			cout << buffer << endl;
			group[i] = HumanFactory(buffer);
			//std::getline(fin, buffer);
			fin >> *group[i];
		}
	}
	fin.close();
	return group;
}

void Clear(Human** group, const int n)
{
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}

//#define INHERITANCE
//#define POLYMORPHISM
//#define WRITE_TO_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE
	Human human("Montana", "Antonio", 25);
	human.info();

	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99);
	student.info();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.info();

	Graduate graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg");
	graduate.info();
#endif // INHERITANCE

#ifdef POLYMORPHISM
	Human* group[] =
	{
		//приведение дочернего объекта к базовому типу называют Upcast
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Graduate("Targarian", "Daineris", 22, "Flight", "GoT", 91, 92, "How to make smoke"),
		new Teacher("Schwartzenegger", "Arnold", 85, "HeavyMetal", 60)
	};
	char filename[] = "group.txt";
	std::ofstream fout(filename);
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << *group[i] << endl;
		fout << *group[i] << endl;
		cout << delimiter << endl;
	}
	fout.close();
	//char cmd[FILENAME_MAX] = "notepad ";
	//system(strcat(cmd, filename));
	system((std::string("start notepad ") + filename).c_str());
	cout << "Количество людей: " << group[0]->get_count() << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
	cout << "Количество людей: " << Human::get_count() << endl;
#endif // POLYMORPHISM

#ifdef WRITE_TO_FILE
	Human* group[] =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Graduate("Targarian", "Daineris", 22, "Flight", "GoT", 91, 92, "How to make smoke"),
		new Teacher("Schwartzenegger", "Arnold", 85, "HeavyMetal", 60)
	};
	cout << typeid(group).name() << endl;
	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif // WRITE_TO_FILE

	Human** group = Load("group.txt");
	cout << "\n==========================================================\n" << endl;
	Print(group, 8);

}