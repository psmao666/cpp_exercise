#include <bits/stdc++.h>
using namespace std;

class Heap{
public:
    vector<int> arr;
    int sz;

    Heap() {
        arr.push_back(0);
        sz = 0;
    }
    int getfa(const int x) {
        return x >> 1;
    }
    int getleft(const int x) {
        return (x << 1);
    }
    int getright(const int x) {
        return (x << 1 | 1);
    }
    void insert(int key) {
        ++ sz;
        arr.push_back(key);
        
        int now = sz;
        while (getfa(now) > 0 && arr[now] < arr[getfa(now)]) {
            swap(arr[now], arr[getfa(now)]);
            now = getfa(now);
        }
    }
    int getmin() {
        return arr[1];
    }
    void heapify(int i) {
        int l = getleft(i);
        int r = getright(i);
        int nxt = i;
        if (l <= sz && arr[l] < arr[nxt]) {
            nxt = l;
        }
        if (r <= sz && arr[r] < arr[nxt]) {
            nxt = r;
        }
        if (i == nxt) return;
        swap(arr[nxt], arr[i]);
        heapify(nxt);
    }
    void del() {
        swap(arr[sz], arr[1]);
        arr.erase(arr.end()-1, arr.end());
        -- sz;
        heapify(1);
    }
};

int main() {
    Heap t;
    t.insert(1);
    t.insert(2);
    t.del();
    cout << t.getmin() << endl;
    return 0;
}