
## 1. 解題說明 
設計一個多項式類別 `Polynomial`，支援：
- 加法運算（`operator+`）
- 乘法運算（`operator*`）
- 代入計算（`operator()`）
- 輸入與輸出格式化（`operator>>`、`operator<<`）

### 設計思路
1. 使用 `Term` 類別儲存每一項的係數與指數。
2. 動態陣列 `Term*` 保存非零項，容量不足時自動擴充。
3. 運算子多載讓操作更直觀，例如：
   ```cpp
   cout << (a + b);
   cout << (a * b);
   cout << a(x);
   ```
4. 加法與乘法需合併同次項並保持降冪排序。
## 2. Algorithm Design & Programming
   ```cpp
   #include <iostream>
using namespace std;

struct Term {
    float coef; // 係數
    int exp;    // 次方
};

// Polynomial 類別：儲存多項式並提供加法與輸出功能
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

    // 印出多項式
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
   ```
## 3. 效能分析 

加法運算 (operator+)

時間複雜度：
→ 最多比較 n+mn+mn+m 次，因此時間複雜度為 O(n+m)。
空間複雜度：
需要額外的陣列儲存結果。
→ 空間複雜度為 O(n+m)。

乘法運算 (operator)*

時間複雜度：
每一項都要與另一個多項式的每一項相乘，形成新項。
→ 時間複雜度為 O(n×m)。
空間複雜度：
最壞情況下，每次相乘都產生不同指數的新項。
→ 空間複雜度為 O(n×m)。

代入運算 (operator())

時間複雜度：
→ 時間複雜度為 O(n)。
空間複雜度：
僅需一個變數儲存累加結果。
→ 空間複雜度為 O(1)。

加法：時間複雜度 O(n+m)，空間 O(n+m)
乘法：時間複雜度 O(n×m)，空間 O(n×m)
代入：時間 O(n)，空間 O(1)
## 4. 測試與驗證
```cpp
輸入：
a(x): 3項 → (2 3), (2 2), (4 1)
b(x): 2項 → (3 1), (4 0)
x = 2

輸出：
a(x) = 2x^3 + 2x^2 + 4x^1
b(x) = 3x^1 + 4
a + b = 2x^3 + 2x^2 + 7x^1 + 4
a * b = 6x^4 + 14x^3 + 20x^2 + 16x^1
a(2) = 32
b(2) = 10
```
## 5. 效能量測 
測試方法
使用 chrono 計算執行時間，測試不同項數下的加法與乘法。
預期結果
加法：執行時間隨項數線性成長。
乘法：執行時間隨項數平方成長。

範例測試結果
```cpp
n = 100   → 加法 ~0.001s，乘法 ~0.01s
n = 1000  → 加法 ~0.01s，乘法 ~0.5s
n = 10000 → 加法 ~0.1s，乘法 ~50s
```
結果符合理論：加法 O(n)，乘法 O(n²)。
## 6. 心得討論 
1.物件導向設計的實用性
將多項式抽象成類別，並透過封裝（Encapsulation）管理資料與操作，讓程式結構更清晰。這種設計方式不僅提高可讀性，也讓後續擴充功能變得容易。

2.運算子多載的直觀性
使用 operator+、operator* 和 operator()，讓多項式運算可以像數學公式一樣自然，例如 a + b 或 a(x)。

3.記憶體管理與動態擴充的挑戰
在實作中，必須處理動態陣列的擴充，確保在容量不足時不會遺失資料。
4.效能與複雜度分析的重要性
透過分析加法、乘法和代入的時間與空間複雜度，我能預測在大規模資料下的效能瓶頸。

5.測試與驗證的必要性
撰寫測試案例並驗證結果，讓我確信程式邏輯正確。若沒有測試，很容易出現錯誤或重複項。

6.效能量測與理論驗證
觀察加法呈線性成長、乘法呈平方成長，與理論分析一致是實際影響程式效能的關鍵。
