#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <ostream>
#include <Grid.h>

/* Terrains */
enum Terrain {PLAIN, FOREST, MOUNTAIN, WATER};
/* Type of Units */
enum UnitType {FT, KN, AR, MG, CLEAR};
// Forward declaration of the class of units
class Unit;

/* Battle field */
class Field {
public:
    // Constructor
    Field(int h, int w);

    // Get the height and width of the field
    int getHeight() const;
    int getWidth() const;

    // Get the terrain
    Terrain getTerrain(int row, int col) const;
    Unit* getUnit(int row, int col) const;
    void set_unit(int row, int col, UnitType utype, bool player);

    void set_terrian(int row, int col, Terrain t);

    bool check_win(bool player) const;
    // Destructor
    ~Field();

private:
    // Store the units
    Grid<Unit*> units;
    // Store the terrain
    Grid<Terrain> terrains;
};
// Convert a direction to a location
void direction2location(const int& original_location_row, const int& original_location_col, const int& direction, int& new_location_row, int& new_location_col);

// Display the field on the out stream os
std::ostream& operator<<(std::ostream& os, const Field& field);

#endif // FIELD_H_INCLUDED
