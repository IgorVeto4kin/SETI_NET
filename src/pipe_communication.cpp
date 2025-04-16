#include <iostream>
#include <cstdio>
#include <string>

#include <regex>

int main() {
   
    struct ipv4{};

    struct ipv6{};

    FILE* pipe = popen("rm -f pipe_communication.cpp", "r");
    

   
    char buffer[128];
    std::string result;

  
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer; 
    }
pclose(pipe);


   
    std::cout << result << std::endl;

    return 0;
}