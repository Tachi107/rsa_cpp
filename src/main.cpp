#include <cmath>
#include <concepts>
#include <vector>
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
auto getCoprime(type number) {
	type divisore {number - 1};
	std::vector<type> primeFactors;
	std::vector<type> primeNotFactors;
	while (number > 1) {
		if (primalityTest(divisore)) {
			if (number % divisore == 0) {
				primeFactors.push_back(divisore);
				number /= divisore;
				std::cout << divisore << '\n';
			}
			else {
				primeNotFactors.push_back(divisore);
				if (divisore > 3) {
					divisore -= 2;
				}
				else {
					--divisore;
				}
			}
		}
		else {
			if (divisore > 3) {
				divisore -= 2;
			}
			else {
				--divisore;
			}
		}
	}
}

int main() {
	std::uint64_t p, q;
	std::cout << "Inserisci il numero primo p\n";
	std::cin >> p;
	std::cout << "Inserisci il numero primo q\n";
	std::cin >> q;

	std::cout << std::boolalpha;
	std::cout << "p e q sono primi?\n" << (primalityTest(p) && primalityTest(q)) << '\n';

	std::uint64_t n {p * q};

	std::cout << "Il coprimo di " << (p - 1) * (q - 1) << '\n';
	getCoprime((p - 1) * (q - 1));
	//std::cout << "e, ovvero il coprimo di " << (p - 1) * (q - 1) << " è " << getCoprime((p - 1) * (q - 1)) << '\n';
}