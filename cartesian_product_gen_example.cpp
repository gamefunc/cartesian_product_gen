/* gamefunc
qq: 32686647
home_page: https://www.gamefunc.top:9029

MIT; 

The copyright belongs to gamefunc; free to use, 
but you need to keep the above information; */

#include <iostream>
#include <string>
#include <vector>

// from CppCoro:
#include "generator.hpp"

// gen:
cppcoro::generator<std::vector<std::string>> cartesian_product_gen(
        std::vector<std::vector<std::string>> src){
    std::vector<std::string> result;
    if(src.empty()){
        result.clear();
        co_yield result;
    }else {
        for(const std::string& s : src[0]){
            for (const std::vector<std::string>& r : 
                    cartesian_product_gen(
                        std::vector<std::vector<std::string>>(
                            src.begin() + 1, src.end()))){
                result.push_back(s);
                result.insert(
                    result.end(), r.begin(), r.end());
                co_yield result;
                result.clear();
            }// for r in cartesian_product()
        }// for s: src[0]
    }// if src.empty()
}// cartesian_product_gen()


// normal:
std::vector<std::vector<std::string>> cartesian_product(
        std::vector<std::vector<std::string>> src) {
    std::vector<std::vector<std::string>> result;
    if(src.empty()){
        result.push_back({});
    }else{
        for(const std::string& s : src[0]){
            for(const std::vector<std::string>& r : 
                cartesian_product(
                    std::vector<std::vector<std::string>>(
                        src.begin() + 1, src.end()))){
                result.push_back({s});
                result.back().insert(
                    result.back().end(), 
                    r.begin(), r.end());
            }// for r : cartesian_product()
        }// for s : src[0]
    }// if else src.empty()
    return result;
}// cartesian_product()



int main(){
    std::vector<std::string> s1{"ab", "cd", "ef"};
    std::vector<std::string> s2{"gh", "hi", "jk"};
    std::vector<std::string> s3{"lm", "n"};

    for(auto l: cartesian_product_gen({s1, s2, s3})){
        std::cout << "[";
        for(auto l1: l){
            std::cout << l1 << ", ";
        }
        std::cout << "\b\b],\n";
    }
  return 0;
}// main()
           
           
