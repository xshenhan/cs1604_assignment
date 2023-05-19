#include "units.h"
#include "field.h"
#include <cassert>
using namespace std;

/* Implementation of Units */
bool move(int& row, int& col, int direction, bool player, int& energy, Field& field){
    int m = field.getHeight();
    int n = field.getWidth();
    int nrow, ncol;
    direction2location(row, col, direction, nrow, ncol);
    if (nrow < 0 || nrow >= m || ncol < 0 || ncol >= n) {
        return false;
    }
    if (field.getUnit(nrow, ncol) != nullptr) {
        return false;
    }
    Terrain t = field.getTerrain(nrow, ncol);
    int needed_energy;
    switch (t) {
        case PLAIN:{
            needed_energy = 1;
            break;
        }
        case FOREST:{
            needed_energy = 2;
            break;
        }
        case MOUNTAIN:{
            return false;
        }
        case WATER:{
            return false;
        }
    }
    if (energy < needed_energy) {
        return false;
    }
    else{
        energy-=needed_energy;
        field.set_unit(nrow, ncol,field.getUnit(row,col)->getType(), player);
        field.set_unit(row, col, CLEAR, player);
        row = nrow;
        col = ncol;
    }
    return true;
}

int getEnergy(UnitType utype){
    switch (utype) {
        case FT:{
            return 4;
        }
        case KN:{
            return 5;
        }
        case AR:{
            return 3;
        }
        case MG:{
            return 2;
        }
        default:{
            return -1;
        }
    }
}

void normal_attack(int row, int col, int direction, bool player, Field& field){
    int nrow, ncol;
    direction2location(row, col, direction, nrow, ncol);
    if (nrow >=0 && nrow < field.getHeight() && ncol>=0 && ncol < field.getWidth())
        field.set_unit(nrow, ncol, CLEAR, player);
}