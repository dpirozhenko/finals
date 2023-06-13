#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class Stack {
public:
    class Iterator;

    Stack() : top(nullptr) {}

    ~Stack() {
        clear();
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }

        Node<T>* temp = top;
        top = top->next;
        delete temp;
    }

    T& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }

        return top->data;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    class Iterator {
    public:
        Iterator(Node<T>* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        Node<T>* current;
    };

    Iterator begin() const {
        return Iterator(top);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

private:
    Node<T>* top;
};

int main() {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    for (Stack<int>::Iterator it = stack.begin(); it != stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    stack.pop();
    stack.push(4);

    while (!stack.isEmpty()) {
        std::cout << stack.peek() << " ";
        stack.pop();
    }
    std::cout << std::endl;

    return 0;
}
