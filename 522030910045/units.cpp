#include "units.h"
#include "field.h"
#include <cassert>
#include <Stack.h>
using namespace std;

/* Implementation of Units */
bool move(int& row, int& col, int direction, bool player, int& energy, Field& field){
    int m = field.getHeight();
    int n = field.getWidth();
    int nrow, ncol;
    if (direction == 5)
        return false;
    direction2location(row, col, direction, nrow, ncol);
    if (nrow < 0 || nrow >= m || ncol < 0 || ncol >= n) {
        return false;
    }
    if (field.getUnit(nrow, ncol) != nullptr) {
        return false;
    }
    Terrain t = field.getTerrain(nrow, ncol);
    int needed_energy = 0;
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
        case A:
            return false;
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
    int nrow=-1, ncol=-1;
    if (direction == 5)
        assert(false);
    direction2location(row, col, direction, nrow, ncol);
    if (nrow >=0 && nrow < field.getHeight() && ncol>=0 && ncol < field.getWidth())
        field.set_unit(nrow, ncol, CLEAR, player);
}

void archer_attack(int row, int col, int direction, bool player, Field& field){
    int nrow, ncol;
    int m = field.getHeight();
    int n = field.getWidth();
    direction2location(row, col, direction, nrow, ncol);
    if (nrow >=0 && nrow < m && ncol>=0 && ncol < n && field.getTerrain(nrow, ncol) != MOUNTAIN){
        int nnrow, nncol;
        direction2location(nrow, ncol, direction, nnrow, nncol);
        if (nncol>=0 && nncol < n && nnrow >=0 && nnrow < m)
            field.set_unit(nnrow, nncol, CLEAR, player);
    }
}

void burn_forest(int row, int col,Field& field){
    field.set_terrian(row, col, PLAIN);
    Stack<pair<int, int>> burning_place = {{row, col}};
    while (!burning_place.isEmpty()){
        pair<int, int> p = burning_place.pop();
        for (int i=1; i<=9; i++){
            int nrow, ncol;
            direction2location(p.first, p.second, i, nrow, ncol);
            if (nrow >=0 && nrow < field.getHeight() && ncol>=0 && ncol < field.getWidth() && field.getTerrain(nrow, ncol) == FOREST){
                field.set_terrian(nrow, ncol, PLAIN);
                field.set_unit(nrow, ncol, CLEAR, false);
                burning_place.push({nrow, ncol});
            }
        }
    }
}

void fireball_fly(int row, int col, int direction, Field& field){
    int nrow, ncol;
    int m = field.getHeight();
    int n = field.getWidth();
    direction2location(row, col, direction, nrow, ncol);
    while (nrow >=0 && nrow < m && ncol>=0 && ncol < n && field.getTerrain(nrow, ncol) != MOUNTAIN){
        if (field.getUnit(nrow, ncol) != nullptr){
            field.set_unit(nrow, ncol, CLEAR, false);
            break;
        }
        else if (field.getTerrain(nrow, ncol) == FOREST){
            burn_forest(nrow, ncol, field);
            break;
        }
        else{
            direction2location(nrow, ncol, direction, nrow, ncol);
        }
    }
}

void fireball_attack(int row, int col, int direction, Field& field){
    int m = field.getHeight();
    int n = field.getWidth();
    if (row >=0 && row < m && col>=0 && col < n && field.getTerrain(row, col) != MOUNTAIN){
        fireball_fly(row, col, direction, field);
    }
}

void earthquake__(int row, int col, Field& field){
    int m = field.getHeight();
    int n = field.getWidth();
    if (row >= 0 && row < m && col >= 0 && col < n){
        field.set_unit(row, col, CLEAR, false);
        switch (field.getTerrain(row, col)) {
            case PLAIN:{
                field.set_terrian(row, col, A);
                break;
            }
            case FOREST:{
                field.set_terrian(row, col, A);
                break;
            }
            case MOUNTAIN:{
                field.set_terrian(row, col, PLAIN);
                break;
            }
            case WATER:{
                break;
            }
            case A:{
                break;
            }
        }

        }
    }


void earthquake(int row, int col, Field& field){
    int direction[5] = {2, 4, 6, 8, 5};
    for (int i: direction){
        int nrow, ncol;
        direction2location(row, col, i, nrow, ncol);
        earthquake__(nrow, ncol, field);
    }
    init_abass(field);
}

void earthquake_attack(int row, int col, int direction, Field& field){
    for (int i=0; i<3 ; i++)
        direction2location(row, col, direction, row, col);

    earthquake(row, col, field);
}

void mage_attack(int row, int col, int direction,int kinds, Field& field){
    switch (kinds) {
        case 1:{
            fireball_attack(row, col, direction, field);
            break;
        }
        case 2:{
            earthquake_attack(row, col, direction, field);
            break;
        }
        default:{}
    }
}