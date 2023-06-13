#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Date{
private:
    int day;
    int month;
public:
    Date() : day(0), month(0) {}

    Date(int d, int m) : day(d), month(m) {}

    Date(string d){
        sscanf(d.c_str(), "%d.%d", &day, &month);
    }

    int get_d(){
        return day;
    }

    int get_m(){
        return month;
    }

    string info(){
        string ss = to_string(day) + "." + to_string(month);
        return ss;
    }   

};


class Meeting{
private:
    string title;
    Date date;

public:
    Meeting(){
        title = ""; 
    }

    Meeting(string t, string d) : title(t), date(d){}


    int get_day(){
        return date.get_d();
    }

    int get_month(){
        return date.get_m();
    }

    int get_time(){
        int t = (date.get_m()*100) + date.get_d();
        return t;
    }

    void info(){
        cout << title << " " << date.info() << endl;
    }

};

class List{
private:
    Meeting meetings[100];
    int size;
public:
    List() : size(0) {}

    List operator&(Meeting& meet){
        meetings[size] = meet;
        size++;
        return *this;
    }

    void print_list(){
        for(int i = 0; i < size; i++){
            meetings[i].info();
        }
    }

    void sort(){
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (meetings[j].get_time() > meetings[j+1].get_time()) {
                    Meeting temp = meetings[j];
                    meetings[j] = meetings[j+1];
                    meetings[j+1] = temp;
                }
            }
        }
    }


};

List fill_list(Meeting * meetings, int size){
        List temp;
        for(int i = 0; i<size; i++){
            temp & meetings[i];
        }

        return temp;
}

void fill_meetings(Meeting * meetings){  
    fstream file;
    string date, tt, mm;
    int i = 0;

    file.open("conferences.txt", ios::in);

        if (file.is_open()) {
            while (getline(file, date)) {
                istringstream line(date);
                line >> tt >> mm;  
                Meeting a(tt, mm);
                meetings[i] = a;
                i++;
            }
            
        file.close();
        }

}

void sort_meetings(Meeting * meetings, int size){
    for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (meetings[j].get_time() > meetings[j+1].get_time()) {
                    Meeting temp = meetings[j];
                    meetings[j] = meetings[j+1];
                    meetings[j+1] = temp;
                }
            }
    }
}

void show_first(Meeting * meetings, int size){
    sort_meetings(meetings, size);
    cout << "First meeting: ";
    meetings[0].info();
}

int generate_data(){
    string title, date, text;
    int dat, mon, count;
    bool flag = true;

    ofstream file("conferences.txt");

    count = 0;
    while(flag){

        cout << "Enter title: ";
        cin >> title;
        cout << "Enter date (format DD.MM): ";
        cin.ignore();
        getline(cin, date);
        file << title << " " << date << endl;
        cout << "To stop enter 'ff': ";
        getline(cin, text);
        if(text == "ff"){
            flag = false;
        }
        count++;

    }
    file.close();

    cout << "Input has been written to file" << endl;
    return count;

};


int main(){

    List ll;
    Meeting * meetings = new Meeting[100];

    int size = generate_data();
    fill_meetings(meetings);
    ll = fill_list(meetings, size);

    show_first(meetings, size);

    cout << "\nInitial list:" << endl;
    ll.print_list();

    cout << "\nList after sorting:" << endl;
    ll.sort();
    ll.print_list();

}
