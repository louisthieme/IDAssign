#include "IDAssign.h"

int main()
{
	std::string NumericalID{};
	std::string AlphabeticalID{};
	std::string AlphaNumericalID{};

	IDA::ID IDA;

	NumericalID = IDA.GetNewID(8, "10000000", IDA.NUMERICAL_SEED);
	AlphabeticalID = IDA.GetNewID(4, "aaaa", IDA.LOWER_ALPHABET_EN_SEED);
	AlphaNumericalID = IDA.GetNewID(5, "aA77b", IDA.MIXED_ALPHA_NUMERICAL_EN_SEED);

	std::cout << "Num: " << NumericalID << "\n";
	std::cout << "Alhpa: " << AlphabeticalID << "\n";
	std::cout << "Alpha Num: " << AlphaNumericalID << "\n";

	return 0;
}