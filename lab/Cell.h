//
// Created by Заурбек Тедеев on 06.08.2021.
//

#ifndef LAB_CELL_H
#define LAB_CELL_H
#include <iostream>

class Cell {
private:
    bool wall;
    bool visited;
    bool is_start;
    bool is_end;
public:
    Cell(){
        visited = false;
        wall = false;
    }

    bool is_wall() const{
        return wall;
    }

    bool is_visited() const{
        return visited;
    }

    void set_visited(){
        visited = true;
    }

    void unset_visited(){
        visited = false;
    }

    void set_wall(){
        wall = true;
    }

    void unset_wall(){
        wall = false;
    }

    void set_start(){
        unset_wall();
        unset_visited();
        is_start = true;
    }

    void set_end(){
        unset_wall();
        unset_visited();
        is_end = true;
    }


    friend std::ostream& operator<< (std::ostream& out, Cell& c);

};

std::ostream& operator<< (std::ostream& out, Cell& c){
    if(c.is_start){
        out << "S";
    }
    else if(c.is_end){
        out << "E";
    }
    else if(c.is_wall()){
        out << "▓";
    }
    else{
        if(!c.is_visited()){
            out << ".";
        }
        else{
            out << "*";
        }
    }

    return out;
}

#endif //LAB_CELL_H
