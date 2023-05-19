#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"
using namespace std;

int main(int argc, char* argv[])
{
    {
        string filename = "map.txt";
        ifstream ifs;
        ifs.open(filename.c_str());
        if (!ifs) {
            cout << "Cannot open the file: " << filename << endl;
            return -1;
        }
        Field* f = loadMap(ifs);
        if (f == NULL) {
            cout << "Failed to load map!" << endl;
            return -1;
        }
        play(*f, cin, cout);
//        cout << *f << endl;
        delete f;
        ifs.close();
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
