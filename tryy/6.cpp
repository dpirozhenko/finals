#include <iostream>

//Створити клас для представлення банківського рахунку TBankAccount, визначити у ньому атрибути ім’я власника рахунку, кількості грошей та методи для списання та нарахування коштів. 
//Створити два класи нащадки для представлення гривневих та доларових рахунків, визначити у кожному класі як мінімум один конструктор, гетери, а також методи для конвертації з однієї валюти у іншу. 
//Створити гривневий та доларовий рахунок за введеними значеннями, після чого конвертувати на одному з рахунків частину валюти і перевести на інший рахунок. 
///Після цього визначити на якому з рахунків більше грошей (з урахуванням валюти).

using namespace std;

class TbankAccount{
private:

    string name;
    int sum;

public:
    TbankAccount(): name(""), sum(0) {}

    TbankAccount(string n, int s) : name(n), sum(s) {}

    string get_name(){
        return name;
    }

    int get_sum(){
        return sum;
    }

    virtual void show_balance() = 0;


    void add_money(int num){
        sum += num;
    }

    int take_money(int num){
        sum -= num;
        return num;
    }


};


class GrivnaTbankAccount : public TbankAccount{
public: 
    GrivnaTbankAccount(string n, int s) : TbankAccount(n, s) {}

    void show_balance(){
        cout << "The current balance of " << this->get_name() << " is " << this->get_sum() << " hrivnas" << endl;
    }

    void add_dollars(int num){
        int c = num * 35;
        this->add_money(c);
    }

};

class DolarTbankAccount : public TbankAccount{
public: 

    DolarTbankAccount(string n, int s) : TbankAccount(n, s) {}

    void show_balance(){
        cout << "The current balance of " << this->get_name() << " is " << this->get_sum() << " dolars" << endl;
    }

    void add_hrivna(int num){
        int c = num*0.027;
        this->add_money(c);
    }


};


int main(){
    GrivnaTbankAccount a1("Nate", 10000);
    DolarTbankAccount a2("Sam", 1000);

    a1.show_balance();
    a2.show_balance();

    int m1 = a1.take_money(3703);
    a2.add_hrivna(m1);
    cout << "After converting..." << endl;


    a1.show_balance();
    a2.show_balance();


}
