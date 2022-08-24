#include <iostream>

using namespace std;

class class1 {
protected:
    //define operators
public:
    class1(){
        //default constructor
    }
    
    class1(/*parameters*/){
        //constructir with parameters
    }
    
    class1(const class1 other){
        //copy constructor
    }
    
    ~class1(){
        //destructor
    }
    
    class1& operator=(const class1 other){
        //operator =
    }
    
    
    void getsmth() const {
        //getter
    }
    
    void setsmth(/*parameters*/){
        //setter
    }
};

class class2 : class1 {
    //contrucktors destructors getters setter and all the other stuff
    
};

int main(){

    int* number = new int;
    char* str = new char[5];
    cout << "Hello World!" << endl;

    delete number;
    delete[] str;

    return 0;
    
}
