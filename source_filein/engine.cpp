#include <sstream>
#include <iomanip>
#include <cassert>
#include <Queue.h>
#include "engine.h"
#include "units.h"
using namespace std;

bool NOERROR = true;

// Main loop for playing the game
void play(Field& field, istream& is, ostream& os)
{
    int end = 0;
    bool side = true;
    int numTurns = 1;
    while (is)
    {
        // Print the new map
        os << field << endl;
        // Check if the game is over
        if (field.check_win(true)){
            end = 1;
        }
        else if (field.check_win(false)){
            end = 2;}
        switch (end) {
            case 1 :{
                cout << "Winner is Player A!" << endl;
                return;
            }
            case 2 :{
                cout << "Winner is Player B!" << endl;
                return;
            }
        }
        string player;
        if (side)
            player = "Player A";
        else
            player = "Player B";

        os << "Turn " << numTurns << " (" << player << ")" << endl;
        // get the command
        string line;
        if (!getline(is, line)) break;
        stringstream ss(line);

        int row, col;
        ss>> row >> col;
        if (row>= 0 && row < field.getHeight() && col >= 0 && col < field.getWidth() && field.getUnit(row, col) != nullptr){
        if (field.getUnit(row, col)->getSide() == side){
        // move
        int energy = getEnergy(field.getUnit(row, col)->getType());
        int command;
        ss >> command;
        while((command>=1 && command<=9) && ss){
            move(row, col, command, side, energy, field);
            ss >> command;
        }
        // attack
        if (ss && command == 0){
            int direction;
            ss >> direction;
            switch (field.getUnit(row, col)->getType()) {
                case FT:{
                    normal_attack(row, col, direction, side, field);
                    break;
                }
                case KN:{
                    normal_attack(row, col, direction, side, field);
                    break;
                }
                case AR:{
                    archer_attack(row, col, direction, side, field);
                    break;
                }
                default:{}
            }

        }
        else if (ss && command == 10){
            int direction, range;
            ss >> direction >> range;
            mage_attack(row, col, direction, range, field);
        }



        }}
        side = !side;
        numTurns++;
    }
}

Field* loadMap(std::istream& is){
    int m, n, nt, nu;
    string commandline;
    getline(is, commandline);
    stringstream ss(commandline);
    ss >> m >> n >> nt >> nu;
    if (m > 20 || n > 20){
        cout << "Failed to load map!" << endl; NOERROR = false;
        return nullptr;
    }
    Field* newMap = new Field(m, n);
    for (int i=0; i<nt ; i++){
        getline(is, commandline);
        stringstream ss(commandline);
        int r, c;
        char T;
        ss >> r >> c >> T;
        switch (T) {
            case 'W': newMap->set_terrian(r, c, WATER); break;
            case 'M': newMap->set_terrian(r, c, MOUNTAIN); break;
            case 'F': newMap->set_terrian(r, c, FOREST); break;
            case 'A': newMap->set_terrian(r, c, A);break;
            default: cout << "Failed to load map!" << endl; NOERROR = false; return nullptr;
        }
    }
    init_abass(*newMap);
    for (int i=0; i<nu ;i++){
        getline(is, commandline);
        stringstream ss(commandline);
        int r, c;
        char s;
        string u;
        ss >> r >> c >> s >> u;
        bool player;
        if (s == 'A') player = true;
        else player = false;
        switch (u[0]) {
            case 'F': newMap->set_unit(r, c, FT, player); break;
            case 'K': newMap->set_unit(r, c, KN, player); break;
            case 'A': newMap->set_unit(r, c, AR, player); break;
            case 'M': newMap->set_unit(r, c, MG, player); break;
            default: cout << "Failed to load map!" << endl; NOERROR = false; return nullptr;
        }
    }
    return newMap;
}

