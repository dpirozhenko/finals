#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> 

using namespace std;

class FullName{
private:
    string surname;
    string name;
    string second_name;
    string f_name;
    
public:
    FullName(){
        name = "";
        second_name = "";
        surname = "";
    }

    FullName(string n){
        f_name = n;
        stringstream line(n);
        line >> surname >> name >> second_name;
    }

    string info(){
        string ss = " " + surname + " " + name + " " + second_name + " ";
        return ss;
    }

};

class Date{
private:
    int day;
    int month;
    int year;
public:
    Date() : day(0), month(0), year(0) {}

    Date(string d){
        sscanf(d.c_str(), "%d.%d.%d", &day, &month, &year);
    }

    string info(){
        return (to_string(day) + "." + to_string(month) + "." + to_string(year));
    }

    int get_year(){
        return year;
    }

};

class Client{
private:
    char full_name[100];
    char city[100];
    char phone[100];
    char date[20];
    
public:
    Client() : full_name(""), city(""), phone(""), date("") {}

    Client(string fname, string c, string num, string d) {
        strcpy(full_name, fname.c_str());
        strcpy(city, c.c_str());
        strcpy(phone, num.c_str());
        strcpy(date, d.c_str());
    }

    string get_name(){
        return string(full_name);
    }

    string get_city(){
        return string(city);
    }

    string get_phone(){
        return string(phone);
    }

    string get_date(){
        return string(date);
    }


};

class Abonent{
private:
    FullName name;
    Date date;
    string address;
    string phone;

public:

    Abonent() : address(""), phone("") {}
    Abonent(string n, string a, string p, string d) : name(n), address(a), phone(p), date(d) {}

    void info(){
        cout << name.info() << " " << address << " " << phone << endl;
    }

    void info2(){
        cout << name.info() << " " << address << " " << phone << " " << date.info() << endl;
    }

    int get_year(){
        return date.get_year();
    }

    string get_address(){
        return address;
    }

};

class Phone_book{
private:
    Abonent abonents[100];
    int size;
public:
    Phone_book() : size(0) {}

    Phone_book(int s) : size(s) {}

    ~Phone_book(){
        delete[] abonents;
    }

    void set_size(int s){
        size = s;
    }

    void fill_phone_book(string filename){
        ifstream f(filename, ios::binary); 
        Client obj;
        
        for(int i = 0; i < size; i++){
            f.read((char*)&obj, sizeof(obj));
            string nn, aa, pp, dd;
            nn = obj.get_name();
            aa = obj.get_city();
            pp = obj.get_phone();
            dd = obj.get_date();


            Abonent a(nn, aa, pp, dd);
            abonents[i] = a;

        }
        f.close();
    }

    void print(){
        cout << "Phone book:" << endl;
        for(int i = 0; i < size; i++){
            abonents[i].info();
        }
    }

    void check_city(string name){
        int num = 0;
        for(int i = 0; i < size; i++){
            if(abonents[i].get_address() == name){
                num++;
            }
        }
        cout << "Number of people, who live in the same town: " << num << endl;
    }

};

class Node{
public:
    Abonent ab;
    Node* next;


    Node(Abonent a) : ab(a), next(nullptr) {}

};


class List{
private:
    Node* head;
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        void operator*() {
            return current->ab.info2();
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        int year(){
            return current->ab.get_year();
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Abonent get_current(){
            return current->ab;
        }
    };

    void operator<<(Abonent& a){
        Node* newNode = new Node(a);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    
    }
    
    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

};

List check_year(List& initial, int year){
    List temp;

    for (List::Iterator it = initial.begin(); it != initial.end(); ++it) {
        if(it.year() == 2023){
            Abonent a = it.get_current();
            temp << a;
        }
        
    }

    return temp;
}


void create(Client obj, string filename){
    ofstream f(filename, ios::binary | ios::app);
    f.write((char*)&obj, sizeof(obj));
    f.close();
}

int generate_data(string filename){
    ofstream f(filename, ios::binary | ios::out);
    f.close();
    string full_name, city, phone, date, text;
    bool flag = true;
    int count = 0;

    while(flag){

        cout << "Enter full name: ";
        cin.ignore();
        getline(cin, full_name);

        cout << "Enter city: ";
        
        getline(cin, city);

        cout << "Enter phone number ";
        getline(cin, phone);

        cout << "Enter date: ";
        getline(cin, date);



        Client a(full_name, city, phone, date);
        create(a, filename);
        count++;

        cout << "To stop enter 'ff': ";
        getline(cin, text);        
        if(text == "ff"){
            flag = false;
        }      
    }
    return count;
    
}


int main(){
    string filename, city;
    cout << "Enter the name of the file: ";
    cin >> filename;

    int num = generate_data(filename);
    Phone_book pbook(num);
    pbook.fill_phone_book(filename);
    pbook.print();

    cout << "\nEnter name of the city: ";
    cin >> city;
    pbook.check_city(city);

    List ll;
    Abonent a1("Samuel L Jacson","NewYork","0664376332","12.12.2020");
    Abonent a2("Robert Downey Jr","Kyiv","0664345390","24.7.2023");
    Abonent a3("Peter B Parker","NewYork","0662389664","10.10.2023");
    Abonent a4("John David Washington","NewYork","0685633994","30.11.2021");

    ll << a1;
    ll << a2;
    ll << a3;
    ll << a4;

    cout << "\nInitial list: " << endl;
    for (List::Iterator it = ll.begin(); it != ll.end(); ++it) {
        *it;
    }


    cout << "\nList with abonents of this year: " << endl;
    for (List::Iterator it = ll.begin(); it != ll.end(); ++it) {
        if (it.year() == 2023) {
            *it;
        }
   
    }


}
