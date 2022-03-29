#include <iostream>
#include "contest.h"
#include "angler.h"
using namespace std;


///conditional summation
bool first_search(const string &name)
{
    contestEnor t(name);
    bool l=false;
    for(t.first(); !t.end(); t.next())
    {
        if(t.current().average > 3.0)
        {
            l=true;
            cout<<"Name:"<<t.current().angler<<" , ";
            cout<<"ID: "<<t.current().contest<<" , ";
            cout<<"Average:"<<t.current().average<<endl;
        }
    }
    return l;
}


bool second_search(const string &name, string &person)
{
    Angler elem;
    AnglerEnor t(name);
    bool l = false;
    int max=0;
    for(t.first(); !t.end(); t.next())
    {
        if(t.current().contestWithNoCatches > max)
        {
            max=t.current().contestWithNoCatches;
            elem = t.current();
            l=true;
        }
    }
    if (l)
        person = elem.name;
    return l;
}

#define NORMAL_MODE
#ifdef NORMAL_MODE2

int main()
{

    string filename;
    cout<<"Enter the name of the input file, please: ";
    cin>>filename;

    //First task
    cout<<"---First  task---\n\n";
    try
    {
        if(first_search(filename)==false)
        {
            cout<<"There was no angler with average more than 3.0\n\n";
        }

    }
    catch(contestEnor::Error err)
    {
        cerr<<"Can't find input file "<<filename<<"!"<<endl;
    }


//Second task
    cout<<"\n---Second task---\n\n";

    try
    {
        string name;
        if(second_search(filename, name))
        {
            cout << name << " has not Caught Anything in the Most Competitions";
        }
        else
        {
            cout<<"We Could not Find Such Angler\n";
        }

    }
    catch(contestEnor::Error err)
    {
        cerr<<"Can't find the input file:"<<filename<<endl;
    }
    return 0;
}


#else
#define CATCH_CONFIG_MAIN
#include "catch.h"


//conditional summation first part

TEST_CASE("first task empty file, no angler to find", "t0.txt")
{

    CHECK_FALSE(first_search("t0.txt"));
}

TEST_CASE("first task 1 angler, more than 3.0", "t2.txt")
{


    CHECK_FALSE(first_search("t2.txt"));
}


// average = summation/counting

TEST_CASE("1 angler,no catch", "t8.txt")
{
    contestEnor tt("t8.txt");
    tt.first();
    CHECK(tt.current().average == 0);
}

TEST_CASE("1 catch", "t3.txt")
{
    contestEnor tt("t3.txt");
    tt.first();
    int expected_average = 45;
    CHECK(tt.current().average == expected_average);
}

// conditional maximum search second part

TEST_CASE("empty file", "t0.txt")
{
    string name;
    CHECK_FALSE(second_search("t0.txt", name));
}

TEST_CASE("2 angler, Peter didn't catch anything", "t1.txt")
{
    string name;
    CHECK(second_search("t1.txt", name));
    CHECK(name=="Peter");
}

// conditional maximum search

TEST_CASE("no contest", "t0.txt")
{
    AnglerEnor t("t0.txt");
    t.first();
    CHECK(t.current().contestWithNoCatches);
}

TEST_CASE("1 angler 1 contest with catch", "t2.txt")
{
    AnglerEnor t("t2.txt");
    t.first();

    CHECK(t.current().contestWithNoCatches);
}


#endif
