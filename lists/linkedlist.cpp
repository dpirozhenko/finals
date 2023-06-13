#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void insertAt(const T& value, int position) {
        if (position <= 0) {
            insertFront(value);
        }
        else if (position >= size()) {
            insertBack(value);
        }
        else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* current = head;
            for (int i = 1; i < position; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void remove(const T& value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            if (current->next == nullptr) {
                tail = current;
            }
            delete temp;
        }
    }

    int getPosition(const T& value) {
        Node<T>* current = head;
        int position = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        return -1;
    }

    int size() const {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

int main() {
    LinkedList<int> list;

    list.insertFront(3);
    list.insertFront(2);
    list.insertFront(1);

    list.insertBack(4);
    list.insertBack(5);
    list.insertBack(6);

    list.insertAt(10, 3);

    for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int position = list.getPosition(4);
    if (position != -1) {
        std::cout << "Element 4 found at position: " << position << std::endl;
    }
    else {
        std::cout << "Element 4 not found in the list" << std::endl;
    }

    list.remove(3);

    for (const auto& element : list) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
