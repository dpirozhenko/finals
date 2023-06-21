#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> 

// Створити клас для представлення автомобіля з атрибутами марка, року виготовлення та максимальної швидкості. 
// Створити структуру даних список, що містить  об’єкти класу автомобіль та підтримує операції пошуку, 
// знаходження максимального і мінімального елемента за різними атрибутами і виведення списку у консоль. 
// Ввести задану кількість автомобілів, внести їх у список і знайти автомобіль з максимальною швидкістю і автомобіль з найпізнішою датою виходу, 
// порівняти їх між собою. Створити новий список з усіма автомобілями, що вийшли в той же рік, що й автомобіль з найбільшою швидкістю.

using namespace std;

class Avto {
private:
    string mark;
    int year;
    int speed;

public:
    Avto() : mark(""), year(0), speed(0) {}

    Avto(string m, int y, int s) : mark(m), year(y), speed(s) {}

    void info() {
        cout << "Mark is " << mark << "; Issue date: " << year << "; The maximum spreed: " << speed << " km;" << endl;
    }

    int get_year() {
        return year;
    }

    int get_speed() {
        return speed;
    }

};

class Node {
public:
    Avto av;
    Node* next;

    Node(Avto& a) : av(a), next(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;
    int size;

public:

    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void isert(Avto& a) {
        Node* new_node = new Node(a);
        if (head == nullptr) {
            head = tail = new_node;
        }
        else {
            new_node->next = head;
            head = new_node;
        }
    }

    int find_biggest_year() {
        Node* current = head;
        int c_year = current->av.get_year();

        while (current != nullptr) {
            if (c_year < current->next->av.get_year()) {
                c_year = current->next->av.get_year();
            }
            current = current->next;

        }

        return c_year;
    }

    int find_smalest_year() {
        Node* current = head;
        int c_year = current->av.get_year();

        while (current != nullptr) {
            if (c_year > current->next->av.get_year()) {
                c_year = current->next->av.get_year();
            }
            current = current->next;

        }

        return c_year;
    }

    int find_biggest_speed() {
        Node* current = head;

        int c_speed = current->av.get_speed();

        while (current != nullptr) {
            if (c_speed < current->next->av.get_speed()) {
                c_speed = current->next->av.get_speed();
            }
            current = current->next;

        }

        return c_speed;

    }

    int find_smallest_speed() {
        Node* current = head;

        int c_speed = current->av.get_speed();

        while (current != nullptr) {
            if (c_speed > current->next->av.get_speed()) {
                c_speed = current->next->av.get_speed();
            }
            current = current->next;

        }

        return c_speed;

    }

    void show_by_speed(int speed) {
        Node* current = head;
        int pos = 0;
        while (current != nullptr) {
            if (current->av.get_speed() == speed) {
                this->show_element(pos);
            }
            current = current->next;
            pos++;
        }

    }

    void show_by_year(int year) {
        Node* current = head;
        int pos = 0;
        while (current != nullptr) {
            if (current->av.get_year() == year) {
                this->show_element(pos);
            }
            current = current->next;
            pos++;
        }

    }

    void show_element(int position) {
        Node* current = head;

        for (int i = 0; i < position; i++) {
            current = current->next;
        }

        current->av.info();

    }

    List create_same_year(int year){



    }


    void print() {
        Node* current = head;

        while (current != nullptr) {
            current->av.info();
            current = current->next;
        }

    }

};

void create_list(List* ll) {
    int num, year, speed;
    string mark;
    cout << "Enter size of the list: ";
    cin >> num;

    for (int i = 0; i < num; i++) {

        cout << "\n[" << i + 1 << "] - Enter mark of the car: ";
        cin.ignore();
        getline(cin, mark);

        cout << "Enter the issue date: ";
        cin >> year;

        cout << "Enter the max speed: ";
        cin >> speed;

        Avto a(mark, year, speed);
        ll->isert(a);

    }

}


int main() {
    List* ll = new List;

    create_list(ll);

    cout << "\nCurrent list:" << endl;
    ll->print();

    int biggest_year = ll->find_biggest_year();
    int biggest_speed = ll->find_biggest_speed();

    cout << "Car with the biggest speed:";
    ll->show_by_speed(biggest_speed);

    cout << "Car with the biggest year:";
    ll->show_by_year(biggest_speed);




}
