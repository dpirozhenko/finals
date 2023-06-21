#include <iostream>
#include <string>

using namespace std;

struct Node {
    std::string data;
    Node* next;

    Node(const std::string& value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const std::string& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void printStack() {
        Node* current = top;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void removeDuplicatePairs() {
        if (isEmpty()) {
            return;
        }

        Node* current = top;
        Node* prev = nullptr;

        while (current != nullptr && current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* duplicate1 = current;
                Node* duplicate2 = current->next;

                // Видаляємо обидва повторювані рядки
                if (prev == nullptr) {
                    top = current->next->next;
                } else {
                    prev->next = current->next->next;
                }

                current = current->next->next;
                delete duplicate1;
                delete duplicate2;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
};


void fill_stack(Stack& mystack){
    string line;
    bool flag = true;
    int num;
    cout << "Let's fill stack:" << endl;

    do{
        
        cout << "Enter strign: ";
        cin >> line;
        //getline(cin, line);
        mystack.add_string(line);
        cout << "Countinue? [1-> yes || 2-> no]: ";
        cin >> num;
        if(num == 2){
            flag = false;
        }

    }while(flag);
    
}

int main() {
    Stack stack;
    
    fill_stack(stack);

    stack.printStack();

    stack.removeDuplicatePairs();
    stack.printStack();

    return 0;
}
