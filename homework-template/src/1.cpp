#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
private:
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

public:
    Polynomial() : capacity(8), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() {
        delete[] termArray;
    }

    void addTerm(float c, int e) {
        if (c == 0) return;
        if (terms == capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            copy(termArray, termArray + terms, temp);
            delete[] termArray;
            termArray = temp;
        }
        termArray[terms].coef = c;
        termArray[terms++].exp = e;
    }

    Polynomial operator+(const Polynomial& rhs) const {
        Polynomial result;
        int i = 0, j = 0;
        while (i < terms && j < rhs.terms) {
            if (termArray[i].exp == rhs.termArray[j].exp) {
                float sum = termArray[i].coef + rhs.termArray[j].coef;
                if (sum != 0) result.addTerm(sum, termArray[i].exp);
                i++; j++;
            } else if (termArray[i].exp > rhs.termArray[j].exp) {
                result.addTerm(termArray[i].coef, termArray[i].exp);
                i++;
            } else {
                result.addTerm(rhs.termArray[j].coef, rhs.termArray[j].exp);
                j++;
            }
        }
        while (i < terms) result.addTerm(termArray[i].coef, termArray[i].exp), i++;
        while (j < rhs.terms) result.addTerm(rhs.termArray[j].coef, rhs.termArray[j].exp), j++;
        return result;
    }

    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < rhs.terms; j++) {
                float c = termArray[i].coef * rhs.termArray[j].coef;
                int e = termArray[i].exp + rhs.termArray[j].exp;
                bool merged = false;
                for (int k = 0; k < result.terms; k++) {
                    if (result.termArray[k].exp == e) {
                        result.termArray[k].coef += c;
                        merged = true;
                        break;
                    }
                }
                if (!merged) result.addTerm(c, e);
            }
        }
        sort(result.termArray, result.termArray + result.terms,
             const Term& a, const Term& b { return a.exp > b.exp; });
        return result;
    }

    float operator()(float x) const {
        float sum = 0;
        for (int i = 0; i < terms; i++)
            sum += termArray[i].coef * pow(x, termArray[i].exp);
        return sum;
    }

    friend istream& operator>>(istream& in, Polynomial& poly) {
        int n;
        in >> n;
        for (int i = 0; i < n; i++) {
            float c; int e;
            in >> c >> e;
            poly.addTerm(c, e);
        }
        return in;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.terms == 0) return os << "0";
        for (int i = 0; i < poly.terms; i++) {
            if (i > 0 && poly.termArray[i].coef > 0) os << " + ";
            os << poly.termArray[i].coef;
            if (poly.termArray[i].exp != 0) os << "x^" << poly.termArray[i].exp;
        }
        return os;
    }
};

int main() {
    Polynomial a, b;
    cout << "輸入多項式 a(x): 項數及每項(係數 指數)\n";
    cin >> a;
    cout << "輸入多項式 b(x): 項數及每項(係數 指數)\n";
    cin >> b;

    cout << "\na(x) = " << a << "\n";
    cout << "b(x) = " << b << "\n";

    cout << "\na + b = " << (a + b) << "\n";
    cout << "a * b = " << (a * b) << "\n";

    float x;
    cout << "\n請輸入 x 的值: ";
    cin >> x;
    cout << "a(" << x << ") = " << a(x) << "\n";
    cout << "b(" << x << ") = " << b(x) << "\n";

    return 0;
}
