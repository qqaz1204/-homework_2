#include <iostream>
using namespace std;

struct Term {
    float coef; // 係數
    int exp;    // 次方
};

class Polynomial {
public:
    Term termArray[100]; // 固定大小陣列，存放多項式項目
    int terms;           // 非零項數

    // 建構子：初始化項數為 0
    Polynomial() {
        terms = 0;
    }

    // 新增一項到多項式
    void newTerm(float coef, int exp) {
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++;
    }

    // 多項式加法：將當前多項式與另一個多項式 b 相加
    Polynomial Add(Polynomial b) {
        Polynomial c; // 儲存結果
        int aPos = 0, bPos = 0;

        // 同時遍歷兩個多項式，根據指數大小合併
        while ((aPos < terms) && (bPos < b.terms)) {
            if (termArray[aPos].exp == b.termArray[bPos].exp) {
                // 如果指數相同，係數相加
                float t = termArray[aPos].coef + b.termArray[bPos].coef;
                if (t != 0)
                    c.newTerm(t, termArray[aPos].exp);
                aPos++;
                bPos++;
            }
            else if (termArray[aPos].exp < b.termArray[bPos].exp) {
                // b 的指數較大，先加入 b 的項
                c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                bPos++;
            }
            else { // a 的指數較大
                c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
        }

        // 將剩餘的項加入結果
        for (; aPos < terms; aPos++)
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

        for (; bPos < b.terms; bPos++)
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

        return c;
    }

    // 印出多項式（格式：coefX^exp）
    void print() {
        for (int i = 0; i < terms; i++) {
            cout << termArray[i].coef << "X^" << termArray[i].exp;
            if (i != terms - 1)
                cout << " + ";
        }
        cout << endl;
    }
};

int main() {
    Polynomial a, b, c;
    int n, m;
    float coef;
    int exp;

    // 輸入多項式 A
    cin >> n; // A 的項數
    for (int i = 0; i < n; i++) {
        cin >> coef >> exp; // 輸入係數與指數
        a.newTerm(coef, exp);
    }

    // 輸入多項式 B
    cin >> m; // B 的項數
    for (int i = 0; i < m; i++) {
        cin >> coef >> exp;
        b.newTerm(coef, exp);
    }

    // 計算 A + B 並輸出結果
    c = a.Add(b);
    c.print();

    return 0;
}
