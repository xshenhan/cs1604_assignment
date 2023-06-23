#ifndef UNITS_H_INCLUDED
#define UNITS_H_INCLUDED

#include <string>
#include "field.h"
/* Class for units */
// true for player A, false for player B

class Unit {
public:
    Unit(UnitType u, bool sd) :
        type(u), side(sd) {}
    UnitType getType() const {return type;}
    bool getSide() const {return side;}
private:
    UnitType type;
    bool side;
};

void normal_attack(int row, int col, int direction, bool player, Field& field);
void archer_attack(int row, int col, int direction, bool player, Field& field);
void mage_attack(int row, int col, int direction,int kinds, Field& field);
bool move(int& row, int& col,int direction, bool player, int& energy, Field& field);
int getEnergy(UnitType utype);
#endif // UNITS_H_INCLUDED
