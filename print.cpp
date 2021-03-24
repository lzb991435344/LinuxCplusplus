#include <iostream>
#include <vector>

int main(){
    std::vector<int> v;
    //v.emplace_back(1);
    //v.emplace_back(2);
    v.push_back(1);

    for (std::vector<int>::iterator it = v.begin(); it!= v.end(); ++it) {
        std::cout<<*it<<std::endl;
    }
    int i = 0;
   // for(i = 0; i <10; ++i){
   //     std::cout<< i <<std::endl;
   // }
   // std::cout<< "999999" <<std::endl;
    return 0;
}