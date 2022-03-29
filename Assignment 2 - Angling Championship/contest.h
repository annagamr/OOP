#ifndef CONTEST_H_INCLUDED
#define CONTEST_H_INCLUDED

#include <fstream>
#include <sstream>
#include <string>


struct Contest
{
    std::string angler;
    std::string contest;

    double average;
};

class contestEnor
{
private:
    std::ifstream _f;
    Contest _cur;
    bool _end;


public:
    enum Error {MissingInputFile};
    contestEnor(const std::string &str);
    void first()
    {
        next();
    }
    void next();
    Contest current() const
    {
        return _cur;
    }
    bool end() const
    {
        return _end;
    }

};


#endif // CONTEST_H_INCLUDED
