#include "set.h"
#include <cstdlib>



void Set::insert(int num)
{

    for(int i=0; i<_vec.size(); i++)
    {
        if (_vec[i]==num) throw WrongInput;


    } _vec.push_back(num);
            Sum+=num;

}

void Set::print()
{
  for(int i=0; i<_vec.size(); i++)
  {
    std::cout << _vec[i] << " ";
  }
	std::cout << std::endl;
}


void Set::remove(int num)
{

    if(_vec.size()==0) throw EmptyVec;
  for(int i=0; i<_vec.size(); i++)
  {
    if(_vec[i]==num)
    {
        _vec.erase(_vec.begin() + i);
        Sum-=num;
        return;
    }
  } throw WrongInput;

}

bool Set::empty() const
{
  if(_vec.size()==0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool Set::contains(int num)
{
  for(int i=0; i<_vec.size(); i++)
  {
    if(_vec[i]==num)
    {
      return 1; //true
    }
	}
	return 0;

}

int Set::random()
{

	if (_vec.size() == 0) throw EmptyVec;


  int randIndex= rand() % _vec.size();

  return _vec[randIndex];
}

int Set::sum()
{
   return Sum;
}

int Set::getLength()
{
  int size=_vec.size();
  return size;
}

