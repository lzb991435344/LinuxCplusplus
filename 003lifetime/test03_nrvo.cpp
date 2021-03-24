#include <iostream>
#include <utility>

using namespace std;


class Obj {
public:
    Obj(){
        cout<<("Obj()")<<endl;
    }
    ~Obj(){
        cout<<("~obj()")<<endl;
    }
    Obj(const Obj& obj){
        cout<<("Obj(const Obj&)")<<endl;
    }

    Obj(Obj&& obj){
        cout<<("Obj(Obj&&)")<<endl;
    }
private:

};

Obj simple(){
    Obj obj;
    return obj;
}

Obj simpleWithMove(){
    Obj obj;
    return std::move(obj);
}

Obj complicate(int n){
    Obj obj1;
    Obj obj2;

    if (n % 2 == 0) {
        return obj1;
    }else{
        return obj2;
    }
}


int main() {
    cout << "*** 1 ***" << endl;
    auto obj1 = simple();
    cout << "*** 2 ***" << endl;
    auto obj2 = simpleWithMove();
    cout << "*** 3 ***" << endl;
    auto obj3 = complicate(42);

}