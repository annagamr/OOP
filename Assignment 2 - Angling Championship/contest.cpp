#include "contest.h"

using namespace std;

contestEnor::contestEnor(const std::string &str)
{
    _f.open(str);
    if(_f.fail()) throw MissingInputFile;
}

//Task: 	Reading the next row of the input file
//Input:    ifstream _f  - the test file
//Output:   Contest _cur - the next contest
//          bool _end    - the end of the enumeration
//Activity:
void contestEnor::next()
{
    string line;
    getline(_f , line, '\n');
    if( !(_end = _f.fail()) )
    {
        istringstream is(line);
        is >> _cur.angler >> _cur.contest;
        _cur.average = 0;
        string fish;
        int size;

        double counterFish=0;
        double sum=0;
        for( is >> fish >> size ; !is.fail(); is >> fish >> size ){
            sum+=size;
            counterFish++;
        }
        if (counterFish == 0)
        {
            _cur.average = 0;

        }
        else{
            _cur.average=sum/counterFish;

        }
    }
}
