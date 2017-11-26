#include "QuadraticFunction.h"

void QuadraticFunction::AutomaticSetRealZeroVariables()
{
	const double FourAC = 4 * m_a * m_c;
	const double BSquaredMinusFourAC = std::sqrt(std::pow(m_b, 2) - FourAC);

	if (BSquaredMinusFourAC > 0)
	{
		// there are two real numbers that satisfy the quadratic equation
		m_AmountOfRealNumberZeros = 2;

	}
	else if (BSquaredMinusFourAC < 0)
	{
		// no real numbers satisfy the quadratic equation.
		m_AmountOfRealNumberZeros = 0;

	}
	else
	{
		// == 0
		// This formula tells us there is only one solution, and it is a real number.
		m_AmountOfRealNumberZeros = 1;
	}
}

void QuadraticFunction::SetTheMaxMinValue(double InNum)
{
	if (m_a < 0)
	{
		// Opens downward (mole hill) max
		m_MaxValueAtXIsEqualTo = InNum;
	}
	else if (m_a < 0)
	{
		m_MinValueAtXIsEqualTo = InNum;
	}
	else
	{
		// this shoudlnt be possible for a quadratic we should
		// have already thrown an exception in the constructor.
	}

}

void QuadraticFunction::PrintFunctionEndBehavior() const
{
	if (m_EndBehavior == EndBehavior::AsXGoesToPosOrNegInfinityFOfXGoesToPosInfinity)
	{
		std::cout << "As X goes to positive or negative infinity f(x) goes to positive infinity\n";
	}
	else if (m_EndBehavior == EndBehavior::AsXGoesToPosOrNegInfinityFOfXGoesToNegInfinity)
	{
		std::cout << "As X goes to positive or negative infinity f(x) goes to negative infinity\n";
	}
	else
	{
		// not implemented...

	}

}

void QuadraticFunction::PrintParabolaOpensDirection() const
{
	if (m_ParabolaOpens == ParabolaOpen::UP)
	{
		std::cout << "The parabola opens up\n";
	}
	else if (m_ParabolaOpens == ParabolaOpen::DOWN)
	{
		std::cout << "The parabola opens down\n";
	}
	else
	{
		// not implemented...

	}
}

void QuadraticFunction::PrintAllZeros() const
{
	std::cout << "Printing all zeros of the function\n";

	for (const auto& zero : m_AllZeros)
	{
		std::cout << zero << std::endl;
	}
	std::cout << "Done printing all zeros\n";

}

void QuadraticFunction::PrintAllRealNumberZeros() const
{
	std::cout << "Printing all real number zeros of the function\n";

	for (const auto& zero : m_RealNumberZeros)
	{
		std::cout << zero << std::endl;
	}
	std::cout << "Done printing all real number zeros\n";


}

void QuadraticFunction::PrintNumberOfRealNumberSoltions() const
{
	std::cout << "The function has " << m_AmountOfRealNumberZeros << " real number solutions\n";
}

void QuadraticFunction::PrintBasicFunctionInfo() const
{
	std::cout << "Starting to print basic function info\n";

	PrintFunctionEndBehavior();
	PrintParabolaOpensDirection();
	std::cout << std::endl;
	PrintAllZeros();
	std::cout << std::endl;
	PrintNumberOfRealNumberSoltions();
	PrintAllRealNumberZeros();
	std::cout << std::endl;

	std::cout << "End of data output\n";
}

std::vector<double> GetZerosQuadraticFormula(QuadraticFunction& QuadraticFunc)
{
	std::tuple<double, double, double> ABC = QuadraticFunc.GetABC();

	double a = std::get<0>(ABC);
	double b = std::get<1>(ABC);
	double c = std::get<2>(ABC);


	std::vector<double> LocalVecOfZeros = GetZerosQuadraticFormula(a, b, c);
	std::vector<double> OutVecRealNumZeros;

	//std::cout << LocalVecOfZeros.size();

	for (int i = 0; i < LocalVecOfZeros.size(); ++i)
	{
		double TermOne, TermTwo, TermThree;

		TermOne = (std::pow(LocalVecOfZeros[i], 2)) * a;
		TermTwo = LocalVecOfZeros[i] * b;
		TermThree = c;

		double ZeroTest = TermOne + TermTwo + TermThree;

		//std::cout << ZeroTest << std::endl;

		if (is_close_to_zero(ZeroTest))
		{
			OutVecRealNumZeros.push_back(LocalVecOfZeros[i]);
		}
	}


	QuadraticFunc.SetAllZeroVec(LocalVecOfZeros);
	QuadraticFunc.SetRealNumberZeroVec(OutVecRealNumZeros);

	// Line of symmetry is between the two zeros.
	QuadraticFunc.SetLineOfSymmetry(LocalVecOfZeros[1] / LocalVecOfZeros[0]);
	QuadraticFunc.SetTheMaxMinValue(LocalVecOfZeros[1] / LocalVecOfZeros[0]);


	// dont really need to return it but whatever...
	return OutVecRealNumZeros;

}

std::vector<double> GetZerosQuadraticFormula(const double& a, const double& b, const double& c)
{

	std::vector<double> OutVec;

	const double NegativeB = -1 * b;
	const double FourAC = 4 * a * c;
	const double BSquaredMinusFourAC = std::sqrt(std::pow(b, 2) - FourAC);
	const double TwoA = 2 * a;

	double FirstZero = ((NegativeB + BSquaredMinusFourAC) / TwoA);
	double SecondZero = ((NegativeB - BSquaredMinusFourAC) / TwoA);

	// TODO: Separate these into real zeros from all zeros later
	OutVec.push_back(FirstZero);
	OutVec.push_back(SecondZero);


	return OutVec;
}