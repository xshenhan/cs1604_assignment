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
            return 0;
        }
        play(*f, cin, cout);

        delete f;
        return 0;
    }
}
