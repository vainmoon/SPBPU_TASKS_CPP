#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void getInput(ifstream& input, vector <float> &coefficients)
{
	input >> coefficients.at(0) >> coefficients.at(1) >> coefficients.at(2);
}
	
void getOut(ofstream& output, vector <float> solution)
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

 float findDiscriminant(vector <float> coefficients)
{
	 return pow(coefficients.at(1), 2) - 4 * coefficients.at(0) * coefficients.at(2);
}

 void findSolution(vector <float> coefficients, float discriminant, vector <float> &solution)
{
	 if (discriminant == 0)
	 {
		 solution.push_back(-1 * coefficients.at(1) / (2 * coefficients.at(0)));
	 }
	 else if (discriminant > 0)
	 {
		 solution.push_back((-1 * coefficients.at(1) + sqrt(discriminant)) / (2 * coefficients.at(0)));
		 solution.push_back((-1 * coefficients.at(1) - sqrt(discriminant)) / (2 * coefficients.at(0)));
	 }
}

void main()
{
	vector <float> coefficients(3);
	vector <float> solution;
	ifstream input("input.txt");
	ofstream output("output.txt");

	getInput(input, coefficients);

	float discriminant = findDiscriminant(coefficients);
	findSolution(coefficients, discriminant, solution);

	getOut(output, solution);
}
