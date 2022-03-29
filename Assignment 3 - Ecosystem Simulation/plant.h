#ifndef PLANT_H_INCLUDED
#define PLANT_H_INCLUDED



#include <string>
#include "radiation.h"


class Plant
{


protected:

    std::string _name; //name of a plant
    int _nutrientLevel; //nutritient level of a plant which defines if its alive or not
    Plant (const std::string &str, int e = 0) :_name(str), _nutrientLevel(e) {}


public:
    bool alive() const
    {
        return _nutrientLevel > 0;
    }
    std::string name() const
    {
        return _name;
    }
    void changeLevel(int e)
    {
        _nutrientLevel+= e;
    }
    virtual void nextDay(Radiation* &radiation)=0;
    virtual ~Plant () {}
    int nutrientLevel() const
    {
        return _nutrientLevel;
    }
    void die()
    {
        _nutrientLevel=0;
    }
};


class Wombleroot : public Plant
{
public:
    Wombleroot(const std::string &str, int e = 0) : Plant(str, e) {}
    void nextDay(Radiation* &radiation) override
    {
        radiation=radiation->nextDay(this);
    }
};

class Wittentoot : public Plant
{
public:
    Wittentoot(const std::string &str, int e = 0) : Plant(str, e) {}
    void nextDay(Radiation* &radiation) override
    {
        radiation=radiation->nextDay(this);

    }
};

class Woreroot : public Plant
{
public:
    Woreroot(const std::string &str, int e = 0) : Plant(str, e) {}
    void nextDay(Radiation* &radiation) override
    {
        radiation=radiation->nextDay(this);
    }
};






#endif // PLANT_H_INCLUDED
