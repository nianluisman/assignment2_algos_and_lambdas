//
// Created by Saxion on 10/12/2018.
//
#include <string>
#include <iostream>
#include "algorithm"

int main(){
    std::vector<std::string> names {"nian", "bob", "camiel", "julia", "nian"};
    std::string check = "nian";

    std::transform(names.begin(), names.end(), names.begin(),
                   [&](std::string &s) -> std::string { if(s == check){
                    s.clear();
                   } return s; });



    std::for_each(names.begin(), names.end(), [](const std::string& n){std::cout << " " << n << std::endl; });


}
