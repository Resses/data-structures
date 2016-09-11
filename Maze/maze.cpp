#include "maze.h"
#include <stack>
#include <fstream>



std::ostream &operator <<(std::ostream &os, const Maze &maze){
    os << std::endl;
    for(int i = 0 ; i < maze.height(); i++){
        for (int j = 0; j < maze.width(); j++){
            Location temp(i,j);
            if(temp == maze.current)
                os << 'O';
            else if (temp == maze.start)
                os << 'S';
            else if(temp == maze.finish)
                os << 'F';
            else if(maze.spec[i][j])
                os << '*';
            else if((i==0 && j==0)  ||  (i==0 && j==maze.width()-1)  ||
                    (i==maze.height()-1 && j==0) || (i==maze.height()-1 && j==maze.width()-1))
                os << '+'; //corners
            else if(i==0 || i==maze.height()-1)
                os << '-';  //top and bottom
            else if(j==0 || j==maze.width()-1)
                os<< '|';  //sides
            else
                os << ' ';
        
        }
        os << std::endl;
    }
    return os;
}



//confirm that line is in form +-------+
bool confirm_line (std::string& line){
    if(line[0] == '+' && line.back()== '+'){
        for (int i = 1; i<line.length()-1; i++){
            if (line[i] != '-') return false;
        }
        return true;
    }
    return false;
}



Maze load(std::string filename){
    //open input file
    std::ifstream infile;
    infile.open(filename);
    if(!infile)
        throw "file does not exist";
    
    //vector of strings holds each row of the maze as a string
    std::vector< std::string > lines;
    std::string line;
    while (!infile.eof()){
        getline(infile, line);
        lines.push_back(line);
    }
    infile.close();
    
    //Check that first and last line are in form +----+
    if (! confirm_line(lines[0]) || ! confirm_line(lines[lines.size()-1]))
        throw "did not read first and last line properly";
    
    //Check that all lines are the same length, and start and end with |
    int line_length = lines[0].size();
    for(int i = 0; i < lines.size(); i++){
        if(lines[i].size() != line_length)
            throw "Lines are not the same length";
        if( (lines[i][0]!='|' || lines[i][line_length-1]!='|') && i!=0 && i!=lines.size()-1)
            throw "Invalid Line. Does not start and end with '|' ";
    }
    
    std::vector<std::vector<bool> > spec (lines.size(), std::vector<bool>(lines[0].size(), false));
    Location start, finish;
    
    for(int x = 1; x < lines.size()-1; x++){
        for(int y = 1; y < lines[x].size()-1; y++){
            if (lines[x][y] == '*')
                spec[x][y] = true;
            else if(lines[x][y] == 'S' || lines[x][y] == 's'){
                spec[x][y] = true;
                start.x = x;
                start.y = y;
            }
            else if(lines[x][y] == 'F' || lines[x][y] == 'f'){
                spec[x][y] = true;
                finish.x = x;
                finish.y = y;
            }
            else
                spec[x][y] = false;
        }
    }
    Maze maze(spec, start, finish);
    return maze;
}



//constructor
Maze::Maze(std::vector<std::vector<bool> > spec, const Location &start, const Location &end) : spec(spec), start(start), finish(end), current(start), solved(false){
    //make was_here the same size as spec and initialize all to false
    was_here = spec;
    for(int i = 0; i < was_here.size(); i++)
        for(int j = 0; j< was_here[0].size(); j++)
            was_here[i][j] = false;
}



//*  RECURSIVE SOLVE
bool Maze::solve(){
    return solve(start);
}

bool Maze::solve(Location loc){
    current = loc;
    was_here[current.x][current.y] = true;
    std::cout << *this;
        
    if(current == finish){
        std::cout << "Finished!" << std::endl;
        solved=true;
    }
    
    Location down((current.x)+1, current.y);
    Location up((current.x)-1, current.y);
    Location right(current.x, (current.y)+1);
    Location left(current.x, (current.y)-1);
    
    if(isPath(up) && !was_here[up.x][up.y] && !solved){
        solve(up);
    }
    if(isPath(down) && !was_here[down.x][down.y] && !solved){
        solve(down);
    }
    if(isPath(right) && !was_here[right.x][right.y] && !solved){
        solve(right);
    }
    if(isPath(left) && !was_here[left.x][left.y] && !solved){
        solve(left);
    }
    return solved;
}
//*/



/*
//STACK SOLVE
bool Maze::solve(){
    std::stack<Location> s;
    s.push(start);
    
   // std::vector<std::vector<bool> > was_here (spec.size(), std::vector<bool> (spec[0].size(),false));
   // Made this a member function for recursion
    
    while(!s.empty()){
        current = s.top();
        s.pop();
        was_here[current.x][current.y] = true;
        std::cout<<*this;
        
        if(current == finish){
            std::cout<< "Finished!"<< std::endl;
            return true; //Maze solved
        }

        Location down((current.x)+1, current.y);
        Location up((current.x)-1, current.y);
        Location right(current.x, (current.y)+1);
        Location left(current.x, (current.y)-1);
        
        if(isPath(up) && !was_here[up.x][up.y]){
            s.push(up);
        }
        if(isPath(down) && !was_here[down.x][down.y]){
            s.push(down);
        }
        if(isPath(right) && !was_here[right.x][right.y]){
            s.push(right);
        }
        if(isPath(left) && !was_here[left.x][left.y]){
            s.push(left);
        }
    }
    return false; //Maze cannot be solved
}
//*/



//PRIVATE FUNCTIONS
bool Maze::contains(const Location &location) const{
    if(location.x<1 || location.x>=spec.size()-1)
        return false;
    if(location.y<1 || location.y>=spec[0].size()-1)
        return false;
    return true;
}



bool Maze::isPath(const Location &location) const{
    if(contains(location) && spec[location.x][location.y])
        return true;
    else
        return false;
}



