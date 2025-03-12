#include <cmath>
#include <iostream>

float sinx(float x, int n_terms) {
	float sum = 0.0;
	for (int i = 0; i < n_terms; i++) {
		sum += (std::pow((float)-1, (float)i) / std::tgamma((float)(2 * i) + (float)2)) * std::pow(x, (float)(2 * i) + (float)1);
	}
	return sum;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Error: no argument(s) given" << std::endl;
		return 0;
	}
	float x = std::stof(argv[1]);
	int n_terms = std::stoi(argv[2]);
	
	printf("sin(%lf) = %lf, error = %lf\n", x, sinx(x, n_terms), std::abs(sinx(x, n_terms) - sin(x)));
}
