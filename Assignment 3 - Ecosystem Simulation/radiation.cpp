#include "radiation.h"
#include "plant.h"
#include <iostream>

using namespace std;

// implementation of Radiation
void Radiation::updateDemand(const bool is_alpha_demand, const int demand)
{

    if(is_alpha_demand)
    {
        _alphaDemand+=demand;
    }
    else
    {
        _deltaDemand+=demand;
    }

}

void Radiation::resetRadiation()
{
    Radiation::_alphaDemand=0;
    Radiation::_deltaDemand=0;
}


Radiation* Radiation::determineRadiation()
{
    cout<<_alphaDemand<<" "<<_deltaDemand<<endl;
    if(_alphaDemand>_deltaDemand && (_alphaDemand - _deltaDemand) >= 3)
    {
        return Alpha::instance();
    }
    else if(_deltaDemand>_alphaDemand && (_deltaDemand-_alphaDemand) >= 3)
    {
        return Delta::instance();
    }
    else
    {
        return noRad::instance();
    }


}

// implementation of class Alpha
Alpha* Alpha::_instance = nullptr;
Alpha* Alpha::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Alpha();
    }
    return _instance;
}
void Alpha::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* Alpha::nextDay(Wombleroot *p)
{
    if(p->alive())
    {
        p->changeLevel(2);
    }

    if(p->nutrientLevel()>10)
    {
        p->die();
    }
    if(p->alive())
    {
        updateDemand(true, 10);
    }
    return this;
}

Radiation* Alpha::nextDay(Wittentoot *p)
{
    if(p->alive())
    {
        p->changeLevel(-3);
    }
    if(p->alive() && p->nutrientLevel() < 5)
    {
        updateDemand(false,4);
    }
    else if (p->nutrientLevel()>=5 && p->nutrientLevel()<=10)
    {
        updateDemand(false,1);
    }
    return this;
}

Radiation* Alpha::nextDay(Woreroot *p)
{
    if(p->alive())
    {
        p->changeLevel(1);
    }
    return this;
}

// implementation of class Delta
Delta* Delta::_instance = nullptr;
Delta* Delta::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Delta();
    }
    return _instance;
}
void Delta::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* Delta::nextDay(Wombleroot *p)
{
    if(p->alive())
    {
        p->changeLevel(-2);
    }

    if(p->nutrientLevel()>10)
    {
        p->die();
    }
    if(p->alive())
    {
        updateDemand(true, 10);
    }
    return this;
}

Radiation* Delta::nextDay(Wittentoot *p)
{
    if(p->alive())
    {
        p->changeLevel(4);
    }

    if(p->alive() && p->nutrientLevel() < 5)
    {
        updateDemand(false,4);
    }
    else if (p->nutrientLevel()>=5 && p->nutrientLevel()<=10)
    {
        updateDemand(false,1);
    }
    return this;
}

Radiation* Delta::nextDay(Woreroot *p)
{
    if(p->alive())
    {
        p->changeLevel(1);
    }

    return this;
}

// implementation of class noRad
noRad* noRad::_instance = nullptr;
noRad* noRad::instance()
{
    if(_instance == nullptr)
    {
        _instance = new noRad();
    }
    return _instance;
}
void noRad::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

Radiation* noRad::nextDay(Wombleroot *p)
{
    if(p->alive())
    {
        p->changeLevel(-1);
    }

    if(p->nutrientLevel()>10)
    {
        p->die();
    }
    if(p->alive())
    {
        updateDemand(true, 10);
    }
    return this;
}

Radiation* noRad::nextDay(Wittentoot *p)
{
    if(p->alive())
    {
        p->changeLevel(-1);
    }

    if(p->alive() && p->nutrientLevel() < 5)
    {
        updateDemand(false,4);
    }
    else if (p->nutrientLevel()>=5 && p->nutrientLevel()<=10)
    {
        updateDemand(false,1);
    }
    return this;
}

Radiation* noRad::nextDay(Woreroot *p)
{
    if(p->alive())
    {
        p->changeLevel(-1);
    }

    return this;
}

