#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool quadraticTest(const vector <float> &coefficients)
{
	return coefficients.at(0) != 0 ? 1 : 0;
}

void equationError(ofstream& output)
{
	output << "Ошибка: введено не квадратное уравнение";
}

void getInput(ifstream& input, vector <float> &coefficients)
{
	input >> coefficients.at(0) >> coefficients.at(1) >> coefficients.at(2);
}
	
void getOut(ofstream& output, const vector <float> &solution)
{
	int number_solutions = solution.size();
	switch (number_solutions)
	{
	case 1:
		output << "Уравнение имеет только одно решение:\n" << solution.at(0);
		break;
	case 2:
		output << "Уравнение имеет два решения:\n" << solution.at(0) << endl << solution.at(1);
		break;
	default:
		output << "Уравнение не имеет вещественных корней";
		break;
	}
}

 float findDiscriminant(const vector <float> &coefficients)
{
	 return pow(coefficients.at(1), 2) - 4 * coefficients.at(0) * coefficients.at(2);
}

 void findSolution(const vector <float> &coefficients, const float &discriminant, vector <float> &solution)
{
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

void main()
{
	vector <float> coefficients(3);
	vector <float> solution;
	ifstream input("input.txt");
	ofstream output("output.txt");

	getInput(input, coefficients);
	
	if (quadraticTest(coefficients))
	{
		float discriminant = findDiscriminant(coefficients);
		findSolution(coefficients, discriminant, solution);

		getOut(output, solution);
	}
	else
	{
		equationError(output);
	}
}
