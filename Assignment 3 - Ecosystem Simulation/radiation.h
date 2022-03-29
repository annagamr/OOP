#ifndef RADIATION_H_INCLUDED
#define RADIATION_H_INCLUDED



#include <string>

class Wombleroot;
class Wittentoot;
class Woreroot;


class Radiation
{
public:

    virtual Radiation* nextDay(Wombleroot *p) = 0;
    virtual Radiation* nextDay(Wittentoot *p) = 0;
    virtual Radiation* nextDay(Woreroot   *p) = 0;
    virtual ~Radiation() {} /

    Radiation* determineRadiation();
    void updateDemand(const bool is_alpha_demand, const int demand);
    void resetRadiation();

private:
    int _alphaDemand = 0;
    int _deltaDemand = 0;
};


// class of alpha radiation
class Alpha : public Radiation
{
public:
    static Alpha* instance();
    Radiation* nextDay(Wombleroot *p) override;
    Radiation* nextDay(Wittentoot *p) override;
    Radiation* nextDay(Woreroot   *p) override;
    static void destroy() ;
protected:
    Alpha() {}
private:
    static Alpha* _instance;
};

// class of Delta radiation
class Delta : public Radiation
{
public:
    static Delta* instance();
    Radiation* nextDay(Wombleroot *p) override;
    Radiation* nextDay(Wittentoot *p) override;
    Radiation* nextDay(Woreroot   *p) override;
    static void destroy() ;
protected:
    Delta() {}
private:
    static Delta* _instance;
};

// class of no radiation
class noRad : public Radiation
{
public:
    static noRad* instance();
    Radiation* nextDay(Wombleroot *p) override;
    Radiation* nextDay(Wittentoot *p) override;
    Radiation* nextDay(Woreroot   *p) override;
    static void destroy() ;
protected:
    noRad() {}
private:
    static noRad* _instance;
};


#endif // RADIATION_H_INCLUDED
