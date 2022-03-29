#include <iostream>

#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"

using namespace std;


// TASK:
//      In a sequential input file we will have angler name, contest ID, fish's name, fish's size.
//      Find the angler's with average more than 3.0. - find average with summation(dont need cond just like in practice)
//      put the condition in next instead of writing conditional summation because u must only open the file once
//      Find the angler who has caught nothing in most of the competitions. - lin search counting max search



struct Result
            {
               int sum;
               int count;

               Result() {};
               Result(int s, int c) : sum(s), count(c) {}

            };



struct Angler
{
    string name;
    string contest;
    double avr;
    bool caught;

    friend istream& operator>>(istream& is, Angler &ang);
};

struct Contest
{
  string fish;
  int size;
  friend istream& operator>>(istream& is, Contest &cont)
  {
      is >> cont.fish >> cont.size;
      return is;
  }
};

class Average : public Summation<Contest, Result>
{
    protected:

        Result func(const Contest& e) const override { return Result(e.size,1); }

        Result neutral() const override { return Result(0,0); }

        Result add(const Result& a, const Result& b) const override
        {
         return Result(a.sum + b.sum, a.count + b.count);
        }
};


class noCatch : public LinSearch<Angler,false>
{
    bool cond(const Angler& e) const override { return e.avr == 0;}
};



istream& operator>>(istream& inp, Angler &s)
{
    string line;
    getline(inp, line , '\n');
    stringstream is(line);
    is >> s.name >> s.contest;

    Average pr;
    StringStreamEnumerator<Contest> enor(is);
    pr.addEnumerator(&enor);

    pr.run();

    if(pr.result().count > 0)
    {
        s.avr= (double (pr.result().sum) / pr.result().count );

    }
    else
    {
        s.avr=0;
    }

     return inp;


}


class SecondSearch: public Counting<Angler>
{
private:
    string _name;
public:
    SecondSearch(const string &AnglerName) : _name(AnglerName) {}
protected:
    bool cond(const Angler& e) const override {
         if(e.avr>3.0)
        { cout<<"The Angler's Name and Competition ID: "<< e.name <<"  "<< e.contest<<" | Average: "<< e.avr<<endl; }

         return e.avr==0;}
    bool whileCond(const Angler& e) const override { return e.name == _name; }
    void first() override {}

};



struct Final
{
    string name;
    int noOfZero;
};


class FinalEnumerator : public Enumerator<Final>
{

private:
    SeqInFileEnumerator<Angler>* _f;
    Final _final;
    bool _end;

public:
    FinalEnumerator(const string &fname) {  _f=new SeqInFileEnumerator<Angler>(fname); }
    ~FinalEnumerator() { delete _f;}
     void first() override { _f->first(); next(); }
     void next() override;
     Final current() const override { return _final;  }
     bool end() const override { return _end; }


};

void FinalEnumerator::next()
{
    if((_end = _f->end())) return;
    _final.name = _f->current().name;
    SecondSearch pr(_final.name);
    pr.addEnumerator(_f);
    pr.run();
    _final.noOfZero=pr.result();


}

class maxNoCaught : public MaxSearch<Final,int,Greater<int>>
{

    virtual int func(const Final& e) const override { return e.noOfZero;}
};

int main()
{

    try
      {

        maxNoCaught pr2;
        FinalEnumerator notpr2("input.txt");
        pr2.addEnumerator(&notpr2);
        pr2.run();
        if(pr2.opt()==0)
        {
            cout<<"No Such Anglers to Show"<<endl;
        }
        else{cout<<"The Angler With Max Number of No Catches is: "<<pr2.optElem().name<<" , Number of Contests Where He/She Didn't Catch anything is: "<<pr2.opt()<<endl;}


      } catch (SeqInFileEnumerator<Angler>::Exceptions exc)

            {
                cout<<"File Does Not Exist";
                return 1;
            }



    return 0;
}
