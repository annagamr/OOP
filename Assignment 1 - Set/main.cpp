#include <iostream>
#include <cstdlib>
#include "set.h"
#include "menu.h"
#include <time.h>
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE
//#define NORMAL_MODE

int main()
{
std::srand((unsigned)time(0));
cout<<" SET "<<endl;
Menu menu;
menu.run();
return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("empty")
{
  Set TS;
  CHECK(TS.empty());

  int num=1;
  TS.insert(num);
  CHECK(!TS.empty());

  TS.remove(num);
  CHECK(TS.empty());
}

TEST_CASE("remove")
{

     int num=1;

    SECTION("empty set")
    {
        Set TS;
        CHECK_THROWS(TS.remove(num));
    }

  SECTION("set with one element")
    {
        Set TS;
        TS.insert(num);
        CHECK(TS.contains(num));
        TS.remove(num);
        CHECK(!TS.contains(num));
    }

   SECTION("set with more elements")
    {
        int num1=2;
        int num2=3;
        int num3=4;
        int num4=5;
        Set TS;

        TS.insert(num);
        CHECK(TS.contains(num));
        TS.insert(num1);
        CHECK(TS.contains(num1));
        TS.insert(num2);
        CHECK(TS.contains(num2));
        TS.insert(num3);
        CHECK(TS.contains(num3));
        TS.insert(num4);
        CHECK(TS.contains(num4));
        TS.remove(num3);
        CHECK(!TS.contains(num3));
    }
}

TEST_CASE("insert")
{
   int num=1;
  int num1=2;
  int num2=3;
  int num3=4;
  int num4=5;
  Set TS;

   SECTION("set with one element")
	 {
    TS.insert(num);
    CHECK(1==TS.getLength());
    CHECK(TS.contains(num));
  }

  SECTION("set with more elements")
	{
		TS.insert(num);
    TS.insert(num1);
    TS.insert(num2);
    TS.insert(num3);
    TS.insert(num4);
    CHECK(5==TS.getLength());
    CHECK(TS.contains(num));
    CHECK(TS.contains(num1));
    CHECK(TS.contains(num2));
    CHECK(TS.contains(num3));
    CHECK(TS.contains(num4));
  }
}

TEST_CASE("contains")
{
  int num=1;
  int num1=2;
  int num2=3;
  int num3=4;
  int num4=5;
  Set TS;
  SECTION("empty set")
    {

        CHECK(!TS.contains(num));

    }

  SECTION("multiple elements")
    {
      TS.insert(num);
      TS.insert(num1);
      TS.insert(num2);
      TS.insert(num3);
      TS.insert(num4);
      CHECK(TS.contains(num));
      CHECK(TS.contains(num1));
      CHECK(TS.contains(num2));
      CHECK(TS.contains(num3));
      CHECK(TS.contains(num4));
    }

		SECTION("does not contain")
    {
			TS.insert(num);
			CHECK(!TS.contains(num1));
		}
}

TEST_CASE("random")
{
  SECTION("empty set")
  {
        Set TS;
        CHECK_THROWS(TS.random());
  }
  SECTION("One element")
  {
        Set TS;
        int num=1;
        TS.insert(num);
        CHECK(TS.random()==num);
  }
  SECTION("More than one")
  {   Set TS;
      int num=1;
      int num1=2;
      int num2=3;
      int num3=4;
      int num4=5;

      TS.insert(num);
      TS.insert(num1);
      TS.insert(num2);
      TS.insert(num3);
      TS.insert(num4);

			int randNum=TS.random();
            int randNum1=TS.random();
			int randNum2=TS.random();
			int randNum3=TS.random();
			int randNum4=TS.random();

      CHECK(TS.contains(randNum));
      CHECK(TS.contains(randNum1));
      CHECK(TS.contains(randNum2));
      CHECK(TS.contains(randNum3));
      CHECK(TS.contains(randNum4));
  }
}

TEST_CASE("sum")
{
  SECTION("empty set")
  {
        Set TS;
        CHECK(TS.sum()==0);
  }
  SECTION("one element")
  {
      int num=1;
      Set TS;
      TS.insert(num);
      CHECK(TS.sum()==num);

  }
  SECTION("more than one elements")
  {
    Set TS;
    int num=1;
      int num1=2;
      int num2=3;
      int num3=4;
      int num4=5;

      TS.insert(num);
      TS.insert(num1);
      TS.insert(num2);
      TS.insert(num3);
      TS.insert(num4);
      CHECK(TS.sum()==num+num1+num2+num3+num4);
  }
}
#endif
