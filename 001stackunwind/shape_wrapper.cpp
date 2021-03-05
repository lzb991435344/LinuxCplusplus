
#include "shape.h"
#include <stdio.h>

class shape_wrapper {
public:
   explicit shape_wrapper(shape* ptr = nullptr):ptr_(ptr) {

    }
    ~shape_wrapper(){
        delete ptr_;
    }
    shape* get() const {
        return ptr_;
    }

private:
    shape* ptr_;
};

void foo() {
    shape_wrapper ptr_wrapper(create_shape(shape_type::circle));
}

int main() {


    foo();
    getchar();
    return 0;
}