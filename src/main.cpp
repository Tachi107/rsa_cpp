#include <cmath>
#include <concepts>
#include <vector>
#include <numeric>
#include <iostream>

bool primalityTest(const std::integral auto number) {
	if (number == 2 || number == 1) {
		return true;
	}
	else if (number <= 0) {
		return false;
	}
	else {
		for (std::uint64_t count {static_cast<std::uint64_t>(std::ceil(std::sqrt(number)))}; count >= 2; --count) {
			if (number % count == 0) {
				return false;
			}
		}
		return true;
	}
}

/*
 * a, b coprimi se ax + by = 1
 * 
 * Per trovare il coprimo di un numero devo
 * scomporre in fattori primi quel numero. 
 * Per farlo devo dividerlo per numeri primi
 * a partire dal più grande minore del numero
 * da scomporre. Per trovare i primi parto 
 * dal numero stesso, controllo se è primo,
 * se lo è lo aggiungo alla lista dei fattori primi
 * e divido il numero per il fattore,
 * se non lo è lo decremento e ripeto il controllo.
 * Il numero del quale trovare il coprimo sarà sempre pari,
 * in quanto è un prodotto tra due numeri pari, essendo
 * derivati da un numero primo -1.
 * 
 * Oppure, coglione che sono, potrei implementare questa:
 * https://en.wikipedia.org/wiki/Euler%27s_totient_function
 */

template<std::integral type>
type getSmallerCoprime(const type number) {
	if (number < 3) {
		throw std::domain_error("number must be bigger than 2");
	}
	type temp {number};
	type divider {number - 1};
	std::vector<type> primeFactors;
	std::vector<type> primeNotFactors;
	while (temp > 1) {
		if (primalityTest(divider)) {
			if (temp % divider == 0) {
				primeFactors.push_back(divider);
				temp /= divider;
			}
			else {
				primeNotFactors.push_back(divider);
				if (divider > 3) {
					divider -= 2;
				}
				else {
					--divider;
				}
			}
		}
		else {
			if (divider > 3) {
				divider -= 2;
			}
			else {
				--divider;
			}
		}
	}
	type coprime {1};
	for (std::size_t i {0}; i < primeNotFactors.size() && coprime < number - primeNotFactors[primeNotFactors.size() - (primeNotFactors.size() - 1) ]; ++i) {
		coprime *= primeNotFactors[i];
	}
	return coprime;
}

int main() {
	std::uint64_t p, q;
	std::cout << "Inserisci il numero primo p\n";
	std::cin >> p;
	std::cout << "Inserisci il numero primo q\n";
	std::cin >> q;

	p == 3 ? q == 3 ? std::cerr << false : std::cerr << true : std::cerr << true;

	std::cout << std::boolalpha;
	std::cout << "p e q sono primi? " << (primalityTest(p) && primalityTest(q)) << '\n';

	std::uint64_t n {p * q};
	std::cout << "n, ovvero il prodotto tra p e q, vale " << n << '\n';

	std::uint64_t λn {std::lcm(p - 1, q - 1)};
	std::cout << "λ(n) vale " << λn << '\n';

	try {
		std::uint64_t e {getSmallerCoprime(λn)};
		std::cout << "e, ovvero il coprimo di " << λn << ", è " << e << '\n';
	} catch (std::domain_error& exception) {
		std::cerr << exception.what() << '\n';
		return EXIT_FAILURE;
	}
}