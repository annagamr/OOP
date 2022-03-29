#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "set.h"

class Menu
{
  public:
          Menu() {};
          void run();
  private:
          int printMenu();
          void insert();
          void print();
          void remove();
          void empty();
          void contains();
          void random();
          void sum();
          void loadTest();
          Set S;

};



#endif // MENU_H_INCLUDED
