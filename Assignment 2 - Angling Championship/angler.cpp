#include "angler.h"

using namespace std;

//next() method for the second task
//Task: 	Reading the next angler with his ability
//Input:    ContestEnor tt  - the enumerator of contests
//Output:   Angler _cur     - the next angler
//          bool _end       - the end of the enumeration
//Activity:
void AnglerEnor::next()
{

    if( !(_end = _tt.end()) )
    {
        _cur.name = _tt.current().angler;
        _cur.contestWithNoCatches= 0;
        for( ; !_tt.end() && _tt.current().angler == _cur.name; _tt.next() )
        {
            if(_tt.current().average==0)
            {
                _cur.contestWithNoCatches++;
            }

        }
    }
}
