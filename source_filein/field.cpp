#include <string>
#include <cassert>
#include <iomanip>
#include "field.h"
#include "units.h"
#include <Stack.h>
using namespace std;

/* Battle field */

// Constructor
Field::Field(int h, int w)
    : units(h, w), terrains(h, w)
{
    assert (h > 0 && h <=20 && w > 0 && w <= 20);
}

// Get the height of the field
int Field::getHeight() const
{
    return units.numRows();
}

// Get the width of the field
int Field::getWidth() const
{
    return units.numCols();
}

void Field::set_unit(int row, int col, UnitType utype, bool player) {
    if (utype != CLEAR)
        units[row][col] = new Unit(utype, player);
    else
        units[row][col] = nullptr;
}

void Field::set_terrian(int row, int col, Terrain t) {
    terrains[row][col] = t;
}
// Get the terrain of a square
Terrain Field::getTerrain(int row, int col) const
{
    assert (terrains.inBounds(row, col));

    return terrains[row][col];
}

// Get the unit of a square
Unit* Field::getUnit(int row, int col) const
{
    assert (units.inBounds(row, col));

    return units[row][col];
}
// Check if the player wins
bool Field::check_win(bool player) const{
    for (int i = 0; i < units.numRows(); i++){
    for (int j = 0; j < units.numCols(); j++){
        if (units[i][j] != nullptr && units[i][j]->getSide() != player)
            return false;}}
    return true;
}

// Reclaim all the units
Field::~Field()
{
    for (int i = 0; i < units.numRows(); i++)
    for (int j = 0; j < units.numCols(); j++)
        if (units[i][j] != nullptr)
            delete units[i][j];
}



// Display the symbol for terrains
string getTerrainSymbol(Terrain t)
{
    switch (t) {
    case PLAIN:
        return "  ";
    case FOREST:
        return "$ ";
    case MOUNTAIN:
        return "/\\";
    case WATER:return "~~";
    case A:
        return "\\/";
    }

    assert(false);
    return "";
}
// Display the symbol for units
string getUnitSymbol(Unit* u)
{
    if (u == nullptr)
        return "  ";

    if (u->getSide()){
        switch (u->getType()) {
            case FT:
                return "FT";
            case KN:
                return "KN";
            case AR:
                return "AR";
            case MG:
                return "MG";
            default:{}
        }
    }
    else{
        switch (u->getType()) {
            case FT:
                return "ft";
            case KN:
                return "kn";
            case AR:
                return "ar";
            case MG:
                return "mg";
            default:{}
        }
    }

    assert(false);
    return "";
}

// change the direction to location

void direction2location(const int& original_location_row, const int& original_location_col, const int& direction, int& new_location_row, int& new_location_col) {
    switch (direction) {
        case 1:{
            new_location_row = original_location_row - 1;
            new_location_col = original_location_col - 1;
            break;
        }
        case 2:{
            new_location_row = original_location_row - 1;
            new_location_col = original_location_col;
            break;
        }
        case 3:{
            new_location_row = original_location_row - 1;
            new_location_col = original_location_col + 1;
            break;
        }
        case 4:{
            new_location_row = original_location_row;
            new_location_col = original_location_col - 1;
            break;
        }
        case 5:{
            new_location_row = original_location_row;
            new_location_col = original_location_col;
            break;
        }
        case 6:{
            new_location_row = original_location_row;
            new_location_col = original_location_col + 1;
            break;
        }
        case 7:{
            new_location_row = original_location_row + 1;
            new_location_col = original_location_col - 1;
            break;
        }
        case 8:{
            new_location_row = original_location_row + 1;
            new_location_col = original_location_col;
            break;
        }
        case 9:{
            new_location_row = original_location_row + 1;
            new_location_col = original_location_col + 1;
            break;
        }
        default:{}
    }
}
void init_abass(Field& field){
    int m = field.getHeight();
    int n = field.getWidth();
    Stack<pair<int,int>> water_place_to_check;
    for (int i=0; i<m ;i++){
        for (int j=0; j<n; j++){
            if (field.getTerrain(i, j)==WATER)
                water_place_to_check.push({i, j});
        }
    }
    while(!water_place_to_check.isEmpty()){
        pair<int,int> place = water_place_to_check.pop();
        for (int i=1; i<=9;i++){
            int nrow, ncol;
            direction2location(place.first, place.second, i, nrow, ncol);
            if (nrow >=0 && nrow <m && ncol >=0 && ncol <n && field.getTerrain(nrow, ncol) == A){
                field.set_terrian(nrow, ncol, WATER);
                water_place_to_check.push({nrow, ncol});
            }
        }
    }
}
//


// Print the horizontal line
void printHLine(ostream& os, int n)
{
    os << "  ";
    for (int i = 0; i < n; i++)
        os << "+--";
    os << "+" << endl;
}

// Display field
ostream& operator<<(ostream& os, const Field& field)
{
    int height = field.getHeight();
    int width = field.getWidth();

    // Print the x coordinates
    os << "  ";
    for (int i = 0; i < width; i++)
        os << ' ' << setw(2) << i;
    os << endl;

    printHLine(os, width);
    for (int i = 0; i < height; i++) {
        os << setw(2) << i;
        for (int j = 0; j < width; j++) {
            os << '|';
            string ts;
            if (field.getUnit(i,j) == nullptr) {
                ts = getTerrainSymbol(field.getTerrain(i,j));
            }
            else {
                ts = getUnitSymbol(field.getUnit(i,j));
            }
            os << ts;
            }
        os << '|' << endl;
        printHLine(os, width);
    }
    os << endl;
    return os;
}

