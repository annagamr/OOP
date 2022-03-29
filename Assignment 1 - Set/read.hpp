#ifndef READ_H
#define READ_H
#include <iostream>
#include <vector>
#include <string>

template <typename T>
T read(const std::string &msg, const std::string &err, bool valid(T))

{
    T n;
    bool wrong;
    do {
        std::cout << msg;
        std::cin >> n;
        if ((wrong = std::cin.fail())) std::cin.clear();
        std::string tmp;
        getline(std::cin, tmp);
        wrong = wrong || tmp.size() != 0 || !valid(n);
        if (wrong) std::cout << err << std::endl;
    } while (wrong);
    return n;
}

#endif
