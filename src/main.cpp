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
 * in quanto è un mcm tra due numeri pari, essendo
 * derivati da un numero primo -1.
 * Mentre scompongo per fattori primi
 * mi metto da parte i numeri primi che trovo
 * ma che non sono fattori del numero che sto scomponendo;
 * questo perché un coprimo di un numero può
 * essere ottenuto dal prodotto di numeri primi
 * non appartenenti alla scomposizione in fattori
 * del numero.
 * In questa funzione scelgo il coprimo più grande
 * minore del numero ottenuto come input.
 * Se dovessi fare un unit test su questa funzione,
 * potrei testare che
 * il numero di output sia minore dell'input,
 * e che il numero di output sia coprimo dell'input,
 * in quanto l'output dev'essere
 * un coprimo minore dell'input.
 */

template<std::integral type>
type getSmallerCoprime(const type number) {
	if (number < 3) {
		throw std::domain_error("number must be bigger than 2");
	}
	type temp {number};
	type divider {number - 1};
	std::vector<type> primeNotFactors;
	while (temp > 1) {
		if (primalityTest(divider)) {
			if (temp % divider == 0) {
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
	for (std::size_t i {0}; i < primeNotFactors.size() && coprime < number - primeNotFactors[primeNotFactors.size() - (primeNotFactors.size() - 1)]; ++i) {
		coprime *= primeNotFactors[i];
	}
	return coprime;
}

/*
 * x[i+1] = x[i-1] % x[i]
 */
template<std::integral type>
type computee(type φn, type d) {
	std::vector<type> x(3);
	x[0] = φn;
	x[1] = d;

	std::vector<type> a;
	std::vector<type> b;

	for (std::size_t i {2}; x[i] != 0; ++i) {
		x.resize(x.size() + 1);
		x[i + 1] = x[i - 1] % x[i];

		x[i] = (a[i] * x[0]) + (b[i] * x[1]);
		a[i] = (x[i] - b[i] * x[1]) / x[0];
		b[i] = (x[i] - a[i] * x[0]) / x[1];

		a[i] = (x[i] - ((x[i] - a[i] * x[0]) / x[1]) * x[1]) / x[0];
		
	}
	std::gcd(x[0], x[1]) = x[x.size() - 1];
	if (std::gcd(x[0], x[1]) != x[x.size() - 1]) {
		throw std::logic_error("Qualcosa non va");
	}
}

int main() {
	std::uint64_t p, q;
	std::cout << "Inserisci il numero primo p: ";
	std::cin >> p;
	std::cout << "Inserisci il numero primo q: ";
	std::cin >> q;
	if (!(primalityTest(p) && primalityTest(q))) {
		std::cerr << "p e q devono essere numeri primi\n";
		return EXIT_FAILURE;
	}

	std::uint64_t n {p * q};
	std::cout << "n, ovvero il prodotto tra p e q, vale " << n << '\n';

	//std::uint64_t λn {std::lcm(p - 1, q - 1)};
	//std::cout << "λ(n) vale " << λn << '\n';
	std::uint64_t φn {(p - 1) * (q - 1)};
	std::cout << "φ(n) vale " << φn << '\n';

	std::uint64_t d;
	try {
		d = getSmallerCoprime(φn);
		std::cout << "d, ovvero il coprimo di " << φn << ", è " << d << '\n';
	} catch (std::domain_error& exception) {
		std::cerr << exception.what() << '\n';
		return EXIT_FAILURE;
	} d = 157;

	std::cout << std::gcd(φn, d) << '\n';

	std::uint64_t x0 {φn};
	std::uint64_t x1 {d};
}
