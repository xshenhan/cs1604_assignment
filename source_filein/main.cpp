#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"
using namespace std;

int main()
{
    {
        Field* f = loadMap(cin);
        if (f == NULL) {
            cout << "Failed to load map!" << endl;
            return -1;
        }
        play(*f, cin, cout);
//        cout << *f << endl;
        delete f;
        return 0;
    }


    // origin
//    Field* f = new Field(11, 11);
//    if (f == NULL) {
//        cout << "Failed to load map!" << endl;
//        return -1;
//    }
//    play(*f, cin, cout);
//
//
//    delete f;
//    return 0;
}
