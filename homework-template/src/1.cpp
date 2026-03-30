#include <iostream>
#include <stdexcept>
using namespace std;

// ===== 抽象類別：Min Priority Queue =====
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;   // 判斷是否為空
    virtual const T& Top() const = 0;   // 取得最小值
    virtual void Push(const T&) = 0;    // 插入元素
    virtual void Pop() = 0;             // 刪除最小值
};

// ===== MinHeap 實作 =====
template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;        // 儲存 heap 的陣列（從 index 1 開始）
    int capacity;   // 陣列容量
    int size;       // 目前元素數量

    // 擴充陣列大小（容量*2）
    void ChangeSize() {
        T* oldheap = heap;
        capacity *= 2;
        heap = new T[capacity + 1];

        // 複製原本資料
        for (int i = 1; i <= size; i++) {
            heap[i] = oldheap[i];
        }
        delete[] oldheap;
    }

public:
    // 建構子
    MinHeap(int Capacity = 10) {
        capacity = Capacity;
        heap = new T[capacity + 1]; // index 從 1 開始
        size = 0;
    }

    // 解構子
    ~MinHeap() {
        delete[] heap;
    }

    // 判斷是否為空
    bool IsEmpty() const {
        return size == 0;
    }

    // 取得最小元素（root）
    const T& Top() const {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        return heap[1]; // root 在 index 1
    }

    // 插入元素（heapify up）
    void Push(const T& e) {
        // 若容量不夠就擴充
        if (size + 1 == capacity) {
            ChangeSize();
        }

        int index = ++size;

        // 向上調整（維持 min heap）
        while (index != 1 && heap[index / 2] > e) {
            heap[index] = heap[index / 2]; // 父節點往下
            index /= 2;
        }
        heap[index] = e;
    }

    // 刪除最小元素（heapify down）
    void Pop() {
        if (IsEmpty()) throw runtime_error("Heap is empty");

        T lastE = heap[size--]; // 取最後一個元素

        int currentNode = 1;
        int child = 2;

        // 向下調整
        while (child <= size) {
            // 找較小的子節點
            if (child < size && heap[child] > heap[child + 1])
                child++;

            // 如果已經符合 heap 條件就停止
            if (lastE <= heap[child]) break;

            // 子節點往上移
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }

        // 放入最後元素
        heap[currentNode] = lastE;
    }

    // 印出 heap（陣列形式）
    void print() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

// ===== 主程式 =====
int main() {
    MinHeap<int> myheap;
    int n, e;

    cout << "輸入個數: ";
    cin >> n;

    // 輸入資料並插入 heap
    for (int i = 0; i < n; i++) {
        cout << "輸入第 " << i + 1 << " 個元素: ";
        cin >> e;
        myheap.Push(e);
    }

    cout << "MinHeap內容: ";
    myheap.print();

    // 顯示最小值
    cout << "Top: " << myheap.Top() << endl;

    // 刪除最小值後再印
    myheap.Pop();
    cout << "Pop後: ";
    myheap.print();

    return 0;
}
