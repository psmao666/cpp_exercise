#include <iostream>
#include <thread>

template<typename T>
class Queue{
    // circular message queue
    T* array;
    int head, len, sizeBound;
    std::mutex mtx;
    std::condition_variable _c;

public:
    Queue() {} // default constructor
    Queue(size_t sz) { // constructor, given fixed size
        array = new T[sz]; 
        head = len = 0;
        sizeBound = sz;
    }
    Queue(const Queue<T>& cQ) {  // copy constructor
        this->array = cQ.array;
        this->head = cQ.head;
        this->len = cQ.len;
    }
    int size() { // return the size of the queue
        return len;
    }
    bool empty() {
        return this->size() == 0;
    }
    void push(T newElement) { // push the new element
        std::unique_lock<std::mutex> mlock(mtx);
        if (len == sizeBound) {
            array[head] = newElement;
            head = (head + 1) % sizeBound; // overlap the head since the queue is full
        }
        else {
            array[(head + len) % sizeBound] = newElement;
            ++ len;
        }
        mlock.unlock();
        _c.notify_all();
    }
    void pop() {// pop the front
        std::unique_lock<std::mutex> mlock(mtx);
        /*try {
            if (len == 0) {
                throw std::runtime_error("queue is empty");
            }
        }catch(std::exception& exc) {
            std::cout << "An exception occured! " << exc.what() << std::endl;
            return;
        }*/
        while (this->empty()) {
            _c.wait(mlock);
        }
        head = (head + 1) % sizeBound;
        len --;
    }
    T front() {
        /*try {
            if (len == 0) {
                throw std::runtime_error("queue is empty");
            }
        }catch(std::exception& exc) {
            std::cout << "An exception occured! " << exc.what() << std::endl;
        }*/
        std::unique_lock<std::mutex> mlock(mtx);
        while (this->empty()) {
            _c.wait(mlock);
        }
        return array[head];
    }
};

Queue<int> q(5);
void func() {
    q.pop();
    for (int i = 1; i <= 5; ++ i) {
        q.push(i);
        std::cout << q.size() << ' ' << q.front() << std::endl;
    }
}

int main() {
    /*
    Queue<int> q(4);
    q.push(1);
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.size() << std::endl;
    std::cout << q.front() << std::endl;
    q.pop();

    std::cout << "------------------\n";
    
    for (int i = 0; i <= 4; ++ i) {
        q.push(i);
    }
    while(!q.empty()) {
        std::cout << q.front() << std::endl;
        q.pop();
    }*/

    std::cout << "------test multithread------\n";
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();

    return 0;
}