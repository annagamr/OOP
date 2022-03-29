#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "plant.h"
#include "radiation.h"

using namespace std;

void printPlant(Plant* plant)
{
    cout << plant->name() << " ";
    cout << plant->nutrientLevel() << " ";
    cout << endl;
}

void printRadiation(Radiation* radiations)
{
    if (radiations == Alpha::instance())
    {
        cout << "The radiation is Alpha";
    }
    else if (radiations == Delta::instance() )
    {
        cout << "The radiation is Delta";
    }
    else if  (radiations == noRad::instance() )
    {
        cout<< "No Radiation on This Beautiful Day";
    }
    cout << endl;
}



//Task:          Filling the vector of creatures and the racetrack from a file of a given name
//Input:         string str	- name of the text file
//Output:        vector<Creature*> &creatures  - vector of pointers of the creatures
//               vector<Ground*> &track - vector of the grounds of the racetrack
//Activity:      creating the creatures and their pointers
//               filling the vector of creatures
//               filling the vector of the racetrack
void create(string fileName,vector<Plant*> &plant, vector<Radiation*> &radiations, int &days)
{


    ifstream f(fileName);
    if(f.fail())
    {
        throw 1;
    }


    int n;
    f >> n;
    plant.resize(n);
    for( int i=0; i<n; ++i )
    {
        string name;
        string type;
        int level;
        f >> name >> type >> level;

        if (type=="wom")
        {
            plant[i] = new Wombleroot(name, level);
        }
        else if (type=="wit")
        {
            plant[i] = new Wittentoot(name, level);
        }
        else if (type=="wor")
        {
            plant[i] = new  Woreroot(name, level);
        }
    }


    f >> days;
    radiations.clear();
    radiations.push_back(noRad::instance());
    return;
}


//Task:       The ecosystem
//Input:      vector<Plant*> &plant  - vector of pointers of the plants
//            vector<Radiation*> &radiations - vector of the radiations of days
//Output:     vector<Plant*> &plant  - vector of pointers of the plants
//            vector<Radiation*> &radiations - vector of the radiations of days
//            vector<string> alive - names of the alive plants after n days
//            collects the names of the alive creatures
void ecosystem(vector<Plant*> &plant, vector<Radiation*> &radiations, vector<string>& alive, int days)
{
    alive.clear();
    try
    {
        for (int day = 0; day < days; ++day)
        {
            cout << "Day: " << day + 1 << endl; // DEBUG
            printRadiation(radiations[day]); // DEBUG
            radiations[day]->resetRadiation();
            for(unsigned int i = 0; i < plant.size(); ++i)
            {
                plant[i]->nextDay(radiations[day]);
                printPlant(plant[i]); // DEBUG
            }
            //determine the radiation for next day and add that to radiation vector
            radiations.push_back(radiations[day]->determineRadiation());
            cout << "Next Day Radiation will be: ";
            printRadiation(radiations[day + 1]);// DEBUG
            cout << endl << endl; // DEBUG
        }
        //loop over each plant check if its alive add that plant name to alive vector
        for(unsigned int i=0; i<plant.size(); ++i)
        {
            int maxLevel=0;
            if(plant[i]->alive() && plant[i]->nutrientLevel()>maxLevel )
            {
                alive.clear();
                maxLevel=plant[i]->nutrientLevel();
                alive.push_back(plant[i]->name());
            }
        }

    }
    catch(exception &e)
    {
        cout << e.what() << endl;
    }
}


//Activity:   destroys every dinamically allocated radiation
void destroy(vector<Plant*> &plant)
{
    for(int i=0; i<(int)plant.size(); ++i) delete plant[i];
}


//Activity:   destroys every dinamically allocated radiation
void destroyRadiations()
{
    Alpha::destroy();
    Delta::destroy();
    noRad::destroy();
}

#define NORMAL_MODE
#ifdef NORMAL_MODE
#define NORMAL_MODE

int main()
{


    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    string fileName;
    cout<<"name of an input file: ";
    cin>>fileName;
    try
    {
        create(fileName, plants, radiations, days);

    }
    catch(int i)
    {
        if (i == 1)
        {
            cerr << "Wrong file name!\n";
            exit(1);
        }
    }
    catch (...)
    {
        cerr << "Unknown Error Ocurred\n";
    }
    vector<string> alive;
    ecosystem(plants, radiations, alive, days);

    if(alive.empty())
    {
        cout<<"No Plants Survived after " << days << " days." <<endl;
    }
    else
    {
        for(unsigned int k=0; k<alive.size(); ++k)
        {
            cout<<"The Strongest Plant is: ";
            cout<<alive[k]<<" "<<endl;
        }
    }
    destroy(plants);
    destroyRadiations();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.h"


TEST_CASE("1", "empty.txt")
{
    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    vector<string> alive;


    create("empty.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive.size() == 0);
    destroy(plants);



    create("k.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive.size() == 1);
    destroy(plants);

    create("t.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive.size() == 1);
    destroy(plants);

    create("k.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive[0] == "Great");
    destroy(plants);

    create("t.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive[0] == "Big");
    destroy(plants);

    destroyRadiations();
}


TEST_CASE("2", "")
{
    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    vector<string> alive;

    plants.clear();
    radiations.clear();
    create("t.txt",plants, radiations, days);
    ecosystem(plants, radiations, alive, days);
    CHECK(alive[0] == "Big");
    destroy(plants);

    destroyRadiations();
}



TEST_CASE("3", "")
{

    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    vector<string> alive;

    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("big", 5));
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("lele", 7));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRad::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRad::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Wittentoot("great", 7));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRad::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRad::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Woreroot("cute", 10));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRad::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRad::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Woreroot("nope", -5));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    radiations.push_back(noRad::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());
    CHECK(radiations[2] == noRad::instance());

    destroy(plants);

    destroyRadiations();
}





TEST_CASE("4", "")
{

    vector<Plant*> plants;
    vector<Radiation*> radiations;
    int days;
    vector<string> alive;

    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("bug", 1));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());

    destroy(plants);


    plants.clear();
    radiations.clear();
    plants.push_back(new Wombleroot("nin", -5));
    radiations.push_back(Alpha::instance());
    radiations.push_back(Delta::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == false);
    CHECK(radiations[0] == Alpha::instance());
    CHECK(radiations[1] == Delta::instance());

    destroy(plants);

    plants.clear();
    radiations.clear();
    plants.push_back(new Wittentoot("jack", 10));
    radiations.push_back(noRad::instance());
    radiations.push_back(Delta::instance());
    //ecosystem(plants, radiations, alive, days);

    CHECK(plants[0]->alive() == true);
    CHECK(radiations[0] == noRad::instance());
    CHECK(radiations[1] == Delta::instance());


    destroyRadiations();
}


#endif // NORMAL_MODE
