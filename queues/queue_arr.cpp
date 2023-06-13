#include <iostream>
//на базі масиву

template<typename T>
class Queue {
private:
    T* elements;  // Масив для зберігання елементів черги
    int capacity; // Розмір масиву
    int size;     // Поточний розмір черги
    int front;    // Індекс першого елемента черги
    int rear;     // Індекс наступного вільного слоту

public:
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const {
            return *ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };

    Queue(int capacity) : capacity(capacity), size(0), front(0), rear(0) {
        elements = new T[capacity];
    }

    ~Queue() {
        delete[] elements;
    }

    void enqueue(const T& item) {
        if (size == capacity) {
            std::cout << "Queue is full. Cannot enqueue element.\n";
            return;
        }

        elements[rear] = item;
        rear = (rear + 1) % capacity;
        ++size;
    }

    void dequeue() {
        if (size == 0) {
            std::cout << "Queue is empty. Cannot dequeue element.\n";
            return;
        }

        front = (front + 1) % capacity;
        --size;
    }

    int getPosition(const T& item) const {
        int index = front;
        for (int count = 0; count < size; ++count) {
            if (elements[index] == item) {
                return count;
            }
            index = (index + 1) % capacity;
        }
        return -1; // Елемент не знайдено
    }

    void clear() {
        size = 0;
        front = 0;
        rear = 0;
    }

    Iterator begin() const {
        return Iterator(elements + front);
    }

    Iterator end() const {
        return Iterator(elements + rear);
    }

    int getSize() const {
        return size;
    }
};

int main() {
    Queue<int> queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    std::cout << "Queue elements: ";
    for (typename Queue<int>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    queue.dequeue();

    std::cout << "Queue elements after dequeue: ";
    for (typename Queue<int>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    int searchItem = 20;
    int position = queue.getPosition(searchItem);
    if (position != -1) {
        std::cout << "Position of " << searchItem << " in the queue: " << position << "\n";
    } else {
        std::cout << searchItem << " not found in the queue.\n";
    }

    queue.clear();
    std::cout << "Queue cleared. Size: " << queue.getSize() << "\n";

    return 0;
}
