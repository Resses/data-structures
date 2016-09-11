#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>

struct Location  {
    friend std::ostream &operator <<(std::ostream &os, const Location &location) {
        os << "(" << location.x << ", " << location.y << ")";
        return os;
    }
    bool operator ==(const Location &rhs) const {return x == rhs.x && y == rhs.y;}
    bool operator !=(const Location &rhs) const {return !(*this == rhs);}
    operator bool() const {return x >= 0;}
    Location(int x=-1, int y=-1) : x(x), y(y) {}
    int x, y;
};

class Maze;

Maze load(std::string filename);

class Maze {

    friend std::ostream &operator <<(std::ostream &os, const Maze &maze);
    friend Maze load(std::string filename);

public:
    
    Maze(std::vector<std::vector<bool> > spec, const Location &start, const Location &end); //constructor
    bool solve(); //solves maze
    
private:
    
    //functions
    bool solve(Location loc); //For recursive solve
    bool contains(const Location &location) const; //Is this location part of the maze?
    bool isPath(const Location &location) const;
    int height() const {return spec.size();}
    int width() const {return spec[0].size();}
   
    //variables
    std::vector<std::vector<bool> > spec;
    std::vector<std::vector<bool> > was_here; //Made this a member variable because of recursive solve
    const Location start, finish;
    Location current;
    bool solved; //For recursive solve
};

#endif