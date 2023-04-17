#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <clocale>
#include <ctime>

using namespace std;

void solveEquation(const vector <double>& coefficients, vector <double>& solution)
{
	double discriminant = pow(coefficients.at(1), 2) - 4 * coefficients.at(0) * coefficients.at(2);

	if (discriminant == 0)
	{
		solution.push_back(-coefficients.at(1) / (2 * coefficients.at(0)));
	}

	else if (discriminant > 0)
	{
		solution.push_back((-coefficients.at(1) + sqrt(discriminant)) / (2 * coefficients.at(0)));
		solution.push_back((-coefficients.at(1) - sqrt(discriminant)) / (2 * coefficients.at(0)));
	}
}

class Student 
{
public:

	Student(string name)
	{
		this->name = name;
	}

	void completeWork(const vector <vector <double>>& equations)
	{
		for (vector <double> coefficients : equations) 
		{
			solutions.push_back(solve(coefficients));
		}
	}

	virtual vector <double> solve(const vector <double>& coefficients)
	{
		vector <double> solution;
		solveEquation(coefficients, solution);
		return solution;
	}
	
	string getName() {return name; }

	vector <double> getSolution(int equationNumber) { return solutions.at(equationNumber); }

private:

	string name;
	vector <vector <double>> solutions;
};

class GoodStudent : public Student
{
public:
	GoodStudent(string name) :Student(name) {}

	vector <double> solve(const vector <double>& coefficients) override
	{
		vector <double> solution;
		int solveAbility = true;
		
		if (!solveAbility)
		{
			solution.push_back(0);
		}
		else
		{
			solveEquation(coefficients, solution);
		}

		return solution;
	}
};

class OrdinaryStudent : public Student 
{
public:
	OrdinaryStudent(string name) :Student(name) {}

	vector <double> solve(const vector <double>& coefficients) override
	{
		vector <double> solution;
		int solveAbility = rand() % 2;

		if (!solveAbility)
		{
			solution.push_back(0);
		}
		else
		{
			solveEquation(coefficients, solution);
		}

		return solution;
	}
};

class BadStudent : public Student 
{
public:
	BadStudent(string name) :Student(name) {}

	vector <double> solve(const vector <double>& coefficients) override
	{
		vector <double> solution;
		int solveAbility = false;

		if (!solveAbility)
		{
			solution.push_back(0);
		}
		else
		{
			solveEquation(coefficients, solution);
		}

		return solution;
	}
};

class Teacher 
{
public:
	void checkWorks(const vector <Student*>& students, const vector <vector <double>>& equations)
	{
		for (Student* student : students) 
		{
			studentsName.push_back(student->getName());
			valueCorrectTask.push_back(0);
			for (int equationNumber = 0; equationNumber < equations.size(); equationNumber++)
			{
				vector <double> rightSolution;
				solveEquation(equations.at(equationNumber), rightSolution);
				if (rightSolution == student->getSolution(equationNumber)) 
				{
					valueCorrectTask.back()++;
				}
				
			}
		}
	}

	void printProgressTable() 
	{
		for (int studentIndex = 0; studentIndex < studentsName.size(); studentIndex++)
		{
			cout << studentsName[studentIndex] << ": " << valueCorrectTask[studentIndex] << endl;
		}
	}

private:
	vector <string> studentsName;
	vector <int> valueCorrectTask;
};

vector <vector <double>> getInputEquations(ifstream& inputEquations)
{
	vector <vector <double>> equations;
	vector <double> equation(3);

	while (!inputEquations.eof())
	{
		inputEquations >> equation.at(0) >> equation.at(1) >> equation.at(2);
		equations.push_back(equation);
	}
	return equations;
}
 

Student* createRandomStudent(string name) 
{
	int studentType = rand() % 3;
	switch (studentType)
	{
	case 0:
		return new GoodStudent(name);
	case 1:
		return new BadStudent(name);
	case 2:
		return new OrdinaryStudent(name);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	vector <Student*> students;

	ifstream inputEquations("equations.txt");
	vector <vector <double>> equations = getInputEquations(inputEquations);

	ifstream inputStudents("students.txt");
	while (!inputStudents.eof()) 
	{
		string name;
		inputStudents >> name;
		students.push_back(createRandomStudent(name));
		students.back()->completeWork(equations);
	}

	Teacher teacher;
	teacher.checkWorks(students, equations);
	teacher.printProgressTable();
}