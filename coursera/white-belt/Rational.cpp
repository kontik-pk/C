#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <exception>
using namespace std;

class Rational {
public:
	Rational() {
		num = 0;
		denom = 1;
	}
	Rational(int numerator, int denominator) {
		num = numerator;
		denom = denominator;
		if (denom < 0) {
			if (num < 0) {
				denom = abs(denom);
				num = abs(denom);
			}
			else {
				denom = abs(denom);
				num = (-1) * num;
			}
		}
		if (num == 0) {
			denom = 1;
		}
		int n = gcd(abs(num), abs(denom));
		//if (denom == 0) {
			//throw invalid_argument("invalid_argument");
		//}
		//if (num == 0) {
			//throw domain_error("domain_error");
		//}
		num = num / n;
		denom = denom / n;

	}

	int Numerator() const {
		return num;
	}
	int Denominator() const {
		return denom;
	}
private:
	int num;
	int denom;
	int gcd(int a, int b) { 
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		} //while
		return a + b;
	}
};

bool operator==(Rational a, Rational b) {
	int n1 = a.Numerator();
	int d1 = a.Denominator();
	int n2 = b.Numerator();
	int d2 = b.Denominator();
	return ((n1 == n2) && (d1 == d2));
}

Rational operator+(Rational a, Rational b) {
	int n1 = a.Numerator();
	int d1 = a.Denominator();
	int n2 = b.Numerator();
	int d2 = b.Denominator();
	int new_denum = d1 * d2;
	int new_num1 = (new_denum / d1) * n1;
	int new_num2 = (new_denum / d2) * n2;
	int new_num = new_num1 + new_num2;
	if (new_num == new_denum) {
		return Rational(1, 1);
	}
	if (new_num % new_denum == 0) {
		return Rational(new_num / new_denum, 1);
	}
	return Rational(new_num, new_denum);
}

Rational operator-(Rational a, Rational b) {
	int n1 = a.Numerator();
	int d1 = a.Denominator();
	int n2 = b.Numerator();
	int d2 = b.Denominator();
	int new_denum = d1 * d2;
	int new_num1 = (new_denum / d1) * n1;
	int new_num2 = (new_denum / d2) * n2;
	int new_num = new_num1 - new_num2;
	if (new_num == new_denum) {
		return Rational(1, 1);
	}
	if (new_num % new_denum == 0) {
		return Rational(new_num / new_denum, 1);
	}
	return Rational(new_num, new_denum);
}

Rational operator*(Rational a, Rational b) {
	int n1 = a.Numerator();
	int d1 = a.Denominator();
	int n2 = b.Numerator();
	int d2 = b.Denominator();
	return Rational(n1 * n2, d1 * d2);
}

Rational operator/(Rational a, Rational b) {
	int n1 = a.Numerator();
	int d1 = a.Denominator();
	int n2 = b.Numerator();
	int d2 = b.Denominator();
	return Rational(n1 * d2, d1 * n2);
}

istream& operator >> (istream& is, Rational& r) {
	int n, d;
	char c;
	is >> n >> c >> d;
	if (is && c == '/') {
		r = Rational(n, d);
	}
	return is;
}

ostream& operator << (ostream& stream, const Rational& r) {
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}

bool operator > (Rational a, Rational b) {
	return (a.Numerator() / (double)a.Denominator()) > double(b.Numerator() / (double)b.Denominator());
}
bool operator < (Rational a, Rational b) { 
	return (a.Numerator() / (double)a.Denominator()) < (b.Numerator() / (double)b.Denominator());
}

Rational ParseString(char x, Rational a, Rational b) {
	if (x == '+') {
		return a + b;
	}
	else if (x == '-') {
		return a - b;
	}
	else if (x == '/') {
		return a/b;
	}
	else if (x == '*') {
		return a*b;
	}
}

int main() {
	int n1, n2, d1, d2;
	char m,k,x;
	cin >> n1 >> m >> d1 >> x >> n2 >> k >> d2;
	if (d1 == 0 || d2 == 0) {
		cout << "Invalid argument";
	}
	else {
		Rational a = Rational(n1, d1);
		Rational b = Rational(n2, d2);
		Rational result = ParseString(x, a, b);
		if (result.Denominator() == 0) {
			cout << "Division by zero";
		}
		else {
			cout << result;
		}
	}
	return 0;
}