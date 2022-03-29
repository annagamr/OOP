#pragma once

#include "contest.h"
#include <string>

struct Angler
{
    std::string name;
    std::string id;
    int contestWithNoCatches;
};

class AnglerEnor
{
private:
    contestEnor _tt;
    Angler _cur;
    bool _end;
public:
    AnglerEnor(const std::string &str): _tt(str) { }
    void first()
    {
        _tt.first();
        next();
    }
    void next();
    Angler current() const
    {
        return _cur;
    }
    bool end() const
    {
        return _end;
    }
};
