#include <cmath>
#include <iostream>

double sinx(double x, int n_terms) {
	double sum = 0.0;
	for (int i = 0; i < n_terms; i++) {
		sum += (std::pow((double)-1, (double)i) / std::tgamma((double)(2 * i) + (double)2)) * std::pow(x, (double)(2 * i) + (double)1);
	}
	return sum;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Error: no argument(s) given" << std::endl;
		return 0;
	}
	double x = std::stod(argv[1]);
	int n_terms = std::stoi(argv[2]);
	
	printf("sin(%lf) = %lf, error = %lf\n", x, sinx(x, n_terms), std::abs(sinx(x, n_terms) - sin(x)));
}
