
#include <stdio.h>
#include <iostream>

using namespace std;
//栈展开
class Obj  {
public:
    Obj(){
        puts("Obj()");
    }
    ~Obj(){
        puts("~Obj()");
    }

private:
};

void foo(int n){
    Obj obj;
    if(n == 42) {
        throw "function err!";
    }
}

int main(){
    try
    {
        foo(41);
        foo(42);
    }
    catch(const char* s)
    {
        puts(s);
    }
    
    getchar();
    return 0;
}
/*
Obj()
~Obj()
Obj()
~Obj()
function err!

栈展开：无论是否发生异常，析构函数都会被执行到


*/