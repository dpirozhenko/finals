#include <iostream>
// (на базі зв'язного списку)

template <typename T>
struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedListQueue {
public:
    class Iterator {
    private:
        Node<T>* current;

    public:
        explicit Iterator(Node<T>* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    LinkedListQueue() : head(nullptr), tail(nullptr) {}

    ~LinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {//вставка елементу вкінець черги
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {//видалення елементу з початку черги
        if (isEmpty()) {
            std::cout << "Queue is empty. Unable to dequeue.\n";
            return;
        }

        Node<T>* temp = head;
        head = head->next;
        delete temp;

        if (isEmpty()) {
            tail = nullptr;
        }
    }

    T& front() const {
        if (isEmpty()) {
            std::cout << "Queue is empty. No front element.\n";
            throw;
        }

        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator find(const T& value) const {
        Node<T>* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                return Iterator(currentNode);
            }
            currentNode = currentNode->next;
        }
        return Iterator(nullptr);
    }

    int getPosition(const T& value) const {
        int position = 0;
        Node<T>* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                return position;
            }
            currentNode = currentNode->next;
            position++;
        }
        return -1; // If element not found
    }

private:
    Node<T>* head;
    Node<T>* tail;
};

int main() {
    LinkedListQueue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    // Using iterator to access queue elements
    LinkedListQueue<int>::Iterator it = queue.begin();
    while (it != queue.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";

    // Finding an element
    LinkedListQueue<int>::Iterator found = queue.find(20);
    if (found != queue.end()) {
        std::cout << "Element found at position: " << queue.getPosition(*found) << "\n";
    } else {
        std::cout << "Element not found.\n";
    }

    queue.dequeue();
    it = queue.begin();
    while (it != queue.end()) {
        std::cout << *it << " ";
        ++it;
    }

    return 0;
}
