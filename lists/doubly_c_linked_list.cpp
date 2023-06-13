#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
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

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
            head->next = tail;
            tail->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        size++;
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
            head->next = tail;
            tail->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAt(const T& value, int position) {
        if (position < 0 || position > size) {
            std::cout << "Invalid position!\n";
            return;
        }
        if (position == 0) {
            insertFront(value);
            return;
        }
        if (position == size) {
            insertBack(value);
            return;
        }

        Node<T>* newNode = new Node<T>(value);
        Node<T>* temp = head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }

    void remove(const T& value) {
        if (isEmpty()) {
            std::cout << "List is empty!\n";
            return;
        }

        Node<T>* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Element not found!\n";
            return;
        }

        if (current == head && current == tail) {
            delete current;
            head = nullptr;
            tail = nullptr;
        } else if (current == head) {
            head = current->next;
            head->prev = tail;
            tail->next = head;
            delete current;
        } else if (current == tail) {
            tail = current->prev;
            tail->next = head;
            head->prev = tail;
            delete current;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;
    }

    int find(const T& value) const {
        if (isEmpty()) {
            std::cout << "List is empty!\n";
            return -1;
        }

        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }

        std::cout << "Element not found!\n";
        return -1;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

int main() {
    DoublyLinkedList<int> myList;
    myList.insertFront(3);
    myList.insertFront(2);
    myList.insertFront(1);
    myList.insertBack(4);
    myList.insertBack(5);
    myList.insertAt(6, 3);

    std::cout << "List size: " << myList.getSize() << std::endl;

    std::cout << "List elements: ";
    int k = 0;
    for (DoublyLinkedList<int>::Iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
        if(k == myList.getSize()){
            break;
        }
        k++;
    }
    std::cout << std::endl;

    int position = myList.find(4);
    if (position != -1) {
        std::cout << "Element 4 found at position " << position << std::endl;
    }

    myList.remove(2);
    myList.remove(6);

    std::cout << "List size after removals: " << myList.getSize() << std::endl;

    std::cout << "List elements after removals: ";
    k = 0;
    for (DoublyLinkedList<int>::Iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
        if(k == myList.getSize()){
            break;
        }
        k++;
    }
    std::cout << std::endl;

    myList.clear();

    std::cout << "List size after clearing: " << myList.getSize() << std::endl;

    return 0;
}
