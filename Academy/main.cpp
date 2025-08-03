#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n--------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
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
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//		Methods
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}

	virtual std::ostream& out(std::ostream& os)const
	{
		cout << last_name << " " << first_name << " " << age;
		return os;
	}

	virtual void InFile(std::ofstream& fout)const
	{
		fout << last_name << " " << first_name << " " << age;
	}

	//Не закончено (применительно к READ_FROM_FILE
	/*virtual void FromFile(std::ifstream& fin, char sz_buffer[])
	{
		const char delimiters[] = { ' ' };
		char parameters[3] = {};
		int n = 0;
		for (char* pch = strtok(sz_buffer, delimiters); pch && n < 3; pch = strtok(NULL, delimiters))
			parameters[n++] = *pch;
		this->last_name = parameters[0];
		this->first_name = parameters[1];
		this->age = atoi(parameters[2]);
	}*/
};

std::ostream& operator<<(std::ostream& os, const Human& human)
{
	return human.out(os);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance


class Student :public Human
{
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
	void info()const override
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}

	std::ostream& out(std::ostream& os)const override
	{
		Human::out(os); cout << endl;
		cout << speciality << " " << group << " " << rating << " " << attendance;
		return os;
	}

	void InFile(std::ofstream& fout)const override
	{
		Human::InFile(fout); fout << endl;
		fout << speciality << " " << group << " " << rating << " " << attendance;
	}
};

//std::ostream& operator<<(std::ostream& os, const Student& student)
//{
//	return student.out(os);
//}

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
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
	void info()const override
	{
		Human::info();
		cout << speciality << " " << experience << endl;
	}

	std::ostream& out(std::ostream& os)const override
	{
		Human::out(os); cout << endl;
		cout << speciality << " " << experience;
		return os;
	}

	void InFile(std::ofstream& fout)const override
	{
		Human::InFile(fout); fout << endl;
		fout << speciality << " " << experience;
	}
};

//std::ostream& operator<<(std::ostream& os, const Teacher& teacher)
//{
//	return teacher.out(os);
//}

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
	void info()const override
	{
		Student::info();
		cout << subject << endl;
	}

	std::ostream& out(std::ostream& os) const override
	{
		Student::out(os); cout << endl;
		cout << subject;
		return os;
	}

	void InFile(std::ofstream& fout)const override
	{
		Student::InFile(fout); fout << endl;
		fout << subject;
	}
};

//std::ostream& operator<<(std::ostream& os, const Graduate& graduate)
//{
//	return graduate.out(os);
//}

std::ofstream& operator<<(std::ofstream& ofs, const Human* group)
{
	group->InFile(ofs);
	return ofs;
}

//#define INHERITANCE
//#define POLYMORPHISM
//#define OSTFREAM_OPERATOR
#define WRITE_TO_FILE
//#define READ_FROM_FILE		//Не закончено

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
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << delimiter << endl;
	}
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
#endif // POLYMORPHISM

#ifdef OSTFREAM_OPERATOR
	Human human("Montana", "Antonio", 25);
	cout << human << endl;

	Student student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99);
	cout << student << endl;

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	cout << teacher << endl;

	Graduate graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg");
	cout << graduate << endl;
#endif // OSTFREAM_OPERATOR

#ifdef WRITE_TO_FILE
	Human* group[] =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	std::ofstream fout;
	fout.open("group.txt");
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		fout << group[i] << endl;
		fout << delimiter << endl;
	}
	fout.close();
	system("notepad group.txt");

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
#endif // WRITE_TO_FILE

//Не закончено
#ifdef READ_FROM_FILE
	std::ifstream fin("group.txt");
	if (fin.is_open())
	{
		const int QUANTITY = 30;
		const int ROWS_IN_FILE = 5 * 30;
		const int COLS = 3;
		std::string temp[QUANTITY][COLS] = {};
		int RowsInMembers[QUANTITY] = {};
		//char* temp = new char[SIZE_GROUP] {};
		int number = 0;
		while (!fin.eof())
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			fin.getline(sz_buffer, SIZE);
			int i = 0;
			/*while (sz_buffer != delimiter || sz_buffer != 0)
			{
				temp[number][i++] = sz_buffer;
			}
				RowsInMembers[number] = i;*/

			if (sz_buffer != delimiter || sz_buffer != 0)
			{
				temp[number][i] = sz_buffer;
				RowsInMembers[number] = i;
			}
			else break;
		}
		fin.close();
		cout << number << endl;
		for (int i = 0; i < number; i++)
			cout << &temp[i] << endl;
		delete[] temp;
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // READ_FROM_FILE

}