#include <iostream>
#include <sstream>

int main ()
{
    std::string s = "hello";
    std::string s1 = "\t";
    std::string s2 = "world";
    std::stringstream ss(s + s1 + s2);

    for (int i = 0; i < 2; i++)
    {

    ss >> s;
    std::cout << s << std::endl;
    }
}