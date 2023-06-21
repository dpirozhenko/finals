#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Set{
private:
    vector<int> elements;

public:

    Set() {}

    void add_element(int el){
        if(!contains(el)){
            elements.push_back(el);
            sort(elements.begin(), elements.end());
        }
    }

    bool contains(int el){
        return binary_search(elements.begin(), elements.end(), el);
    }

    void remove_element(int el){
        auto it = find(elements.begin(), elements.end(), el);
        elements.erase(it);
    }

    Set operator+(Set& other){
        Set result;

        for(int el : elements){
            result.add_element(el);
        }

        for(int e : other.elements){
            result.add_element(e);
        }

        return result;

    }

    Set operator* (Set& other){
        Set result;

        for(int element : elements){
            if(other.contains(element)){
                result.add_element(element);
            }
        }

        return result;

    }

    Set operator/ (Set& other){
        Set result;

        for(int element : elements){
            if(!other.contains(element)){
                result.add_element(element);
            }
        }

        return result;


    }

    void print(){
        for (int element : elements){
            cout << element << " ";
        }
        cout << endl;
    }

    string get_elements(){
        string ss;
        for(int el : elements){
            ss += to_string(el) + " ";
        }

        return ss;
    }


};

void create_own(){
    Set mySet3;
    bool flag = true;
    int el, choice;
    bool flag1;
    cout << "Lets create our set: " << endl; 

    do{
        cout <<"menu: \n1-> add element\n2-> delete element\n3-> exit"<< endl;   
        cin >> choice;
        if(cin.fail()){
                throw "Please enter int.... bye";        
            }
        if(choice == 1 || choice == 2 || choice == 3 ){
            
        }else{
            throw "You had to enter 1, 2 or 3.... bye";
        }

        switch (choice)
        {
        case 1:
         
            cout << "enter element: ";
            cin >> el;
            if(cin.fail()){
                throw "Please enter int.... bye";        
            }
            mySet3.add_element(el);
            cout << "\nCurrent set: ";
            mySet3.print();
            break;
        case 2:
            cout << "enter element to delete: ";
            cin >> el;
            if(cin.fail()){
                throw "Please enter int....bye";        
            }else if(!mySet3.contains(el)){
                throw "No element to delete, bye";
            }
          
            mySet3.remove_element(el);
            cout << "\nCurrent set: ";
            mySet3.print();
            break;
        case 3:
            flag = false;
            break;
        default:
            break;
        }
    }while(flag);

}

void to_file(Set& myset){
    string filename;
    cout << endl << "Enter filename: ";
    cin >> filename;

    string s = myset.get_elements();

    ofstream file(filename);
    if(file.is_open()){
        file << s;
    }

    file.close();
    cout << "Elements have been written to file " << filename;

}

int main(){

    Set myset1;
    Set myset2;

    myset1.add_element(2);
    myset1.add_element(6);
    myset1.add_element(1);
    myset1.add_element(9);

    myset2.add_element(12);
    myset2.add_element(45);
    myset2.add_element(9);
    myset2.add_element(3);

    cout << "Initial sets: " << endl;
    myset1.print();
    myset2.print();

    Set addSets = myset1 + myset2;
    cout << "Union: " << endl;
    addSets.print();

    Set interSets = myset1 * myset2;
    cout << "Intersection: " << endl;
    interSets.print();

    Set dif1 = myset1 / myset2;
    cout << "Difference1: " << endl;
    dif1.print();

    Set dif2 = myset2 / myset1;
    cout << "Difference1: " << endl;
    dif2.print();

    try{
        create_own();
        to_file(addSets);

    }catch(const char* exception){
        std::cerr << "Error: " << exception << std::endl;
    }

}
