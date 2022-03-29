#include <iostream>
#include "menu.h"
#include "read.hpp"
#include <sstream>
#define INT_MAX 2147483647
#define INT_MIN -2147483647 - 1
#define menuCount 7 // 7 items on menu

using namespace std;


bool check(int a) {return a>=0 && a<=menuCount;}
inline bool valid(int a) {return true;}

void Menu::run()
{
  int k;
  do{
    k=printMenu();
    switch(k)
    {
      case 1:
            insert();
            print();
            break;
      case 2:
            print();
            break;
      case 3:
            remove();
            print();
            break;
      case 4:
            empty();
            print();
            break;
      case 5:
            contains();
            print();
            break;
      case 6:
            random();
            print();
            break;
      case 7:
            sum();
            print();
            break;
      default:
            cout<<"\nGoodbye!\n";
    }
 } while(k!=0);

}

int Menu::printMenu()
{
  int number;
  cout<<"\n***********************************\n";
  cout<<"0. Exit\n";
  cout<<"1. Insert\n";
  cout<<"2. Print\n";
  cout<<"3. Remove\n";
  cout<<"4. isEmpty\n";
  cout<<"5. Contains\n";
  cout<<"6. Random\n";
  cout<<"7. Sum\n";
  cout<<"\n***********************************\n";
  //Error message if the number is out of our range
    ostringstream s;
    s << "Number should be between 0 and " << menuCount << endl;
    string errorMessage = s.str();
    number = read<int>(">>>", errorMessage, check);


  return number;
}

void Menu::insert()
{

  int num;
  num=read<int>("Number: ", "Wrong! Input Integer Number:\n", valid);

    bool error=false;
  try {
    S.insert(num);
  } catch(Set::Exception err)
  {
    error=true;
    if(err==Set::WrongInput)
    {
      cerr<<"The number is already in the set!\n";

    }

  }
  if(!error) cout<<"The number inserted is: "<<num<<endl;


}

void Menu::print()
{
  S.print();
}

void Menu::remove()
{
  int num;
  num=read<int>("Please Enter a Number to Remove: ", "Wrong! Input Integer Number:\n", valid);

  bool error=false;
  try {
    S.remove(num);
  } catch(Set::Exception err)
  {
    error=true;
    if(err==Set::EmptyVec)
    {
      cerr<<"Can Not Remove. The Set is Empty\n";

    }
    else if(err==Set::WrongInput)
    {
      cerr<<"Can Not Remove. Wrong Input\n";
    }

    else {
        cerr<<"Unknown Error\n";
      }
  }
  if(!error) cout<<"The number removed is:\n"<<num<<endl;
}

void Menu::empty()
{
  if(S.empty()==1) {
    cout<<"The set is empty\n";
  }
  else
  {
    cout<<"The set is not empty\n";
  }
}

void Menu::contains()
{
  int num;
  num=read<int>("Please Enter a Number: \n", "Wrong! Input Integer Number:\n", valid);
  if(S.contains(num)==1)
  {
    cout<<"The set contains the number\n";
  }
  else
  {
    cout<<"The set does not contain the number\n";
  }
}

void Menu::random()
{
  int num=0;
  bool error=false;
  try {
    num=S.random();
  } catch(Set::Exception err)
  {
    error=true;
    if(err==Set::EmptyVec)
    {
      cerr<<"The Set is Empty. No Random Number Generated!\n";
    }

    else {
        cerr<<"Unknown Error\n";
      }
  }
  if(!error) cout<<"Random Number From the Set:\n"<<num<<endl;
}

void Menu::sum()
{
  cout<<"The Sum of the Set is: "<<S.sum()<<endl;

}

void Menu::loadTest()
{
  const int size=1000000000;
  Set S;
  cout<<"Follow the current size of the set: \n";
  try{
    for(int i=1; i<size; i++)
    {
      if(i%1000000)
      {
        cout<<i<<endl;
        S.insert(int(i));
      }
    }
  } catch(...)
  {
    cerr<<"Run Out of Memory\n";
    cerr<<"The size of the vector: "<<S.getLength()<<endl;

  }
}
