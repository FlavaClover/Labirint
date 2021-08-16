//
// Created by Заурбек Тедеев on 06.08.2021.
//

#ifndef LAB_LABIRINT_H
#define LAB_LABIRINT_H

#include "Cell.h"
#include <vector>
#include <stack>
#include <algorithm>


class Labirint {
private:
    //структура которая представляет какую-то позицию в либирите
    struct Position {
        int x, y;
        //конструктор стандартный(пустой)
        Position() = default;
        //конструктор с параметрами(принимает координаты ячейки)
        Position(int x, int y): x(x), y(y) {}

        /*
         *  5 5
         *  -> 5 6 -> 0 1
         *  <- 5 4 -> 0 -1
         *  ^ 4 5 -> -1 0
         *  . 6 5 -> 1 0
        */

        //конструктор с смещением
        Position(Position pos, Position direction): x(pos.x + direction.x), y(pos.y + direction.y) {}

        //перегрузка оператора сравнения
        bool operator==(Position other) const {
            return this->x == other.x && this->y == other.y;
        }
    };

    //лабиринт
    Cell** labirint;
    int height, width;
    Position start;
    Position end;

    //направления
    const std::vector<Position> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    //проверка на посещение
    bool is_visited(Position pos) {
        return pos.x < 0 || pos.x >= height ||
               pos.y < 0 || pos.y >= width ||
               labirint[pos.x][pos.y].is_visited();
    }

    //ставим посещение
    void set_visited(Position pos) {
        labirint[pos.x][pos.y].set_visited();
    }

    //убираем стену
    void unset_wall(Position pos){
        labirint[pos.x][pos.y].unset_wall();
    }

    //проверяем стена ли ячейка
    bool is_wall(Position pos){
        if(pos.x < 0 || pos.x >= width) return true;
        if(pos.y < 0 || pos.y >= height) return true;
        return labirint[pos.x][pos.y].is_wall();
    }

    //убираем все посещения в лабиринте
    void remove_visited(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(!labirint[i][j].is_wall()) labirint[i][j].unset_visited();
            }
        }
    }

    //построение лабиринта
    bool dfs(Position pos) { // начальная позиция
        set_visited(pos); //отмечаем ее как посещенную

        //если позиция совпала с концом лабиринта
        if (pos == end) {
            return true; //вернем истину, как знак того, что успешно дошли
        } else {//в ином случае
            int delta = rand() % directions.size(); // берем рандомное смещение
            for (int i = 0; i < directions.size(); i++) { //проходимся по всем направлениям
                //берем следующую позицию, на которую пойдем(учитывая смещение)
                Position next(pos, directions[(delta + i) % directions.size()]);
                if (!is_visited(next)) { // если эта позиция не посещена
                    if (dfs(next)) { // то проверяем дфс от этой позиции. Если он успешен, значит тупика нет и
                        unset_wall(next); // мы убираем стенку
                        return true;
                    }
                }
            }

            return false; // если произошел тупик, т.е никуда не можем попасть, то вернем ложь
        }
    }

    //дфс для решения лабиринта
    bool dfs_solve(Position pos){
        set_visited(pos); // ставит отметку о посещении

        if (pos == end) { // если совпала текущая позиция с концом
            return false; // то вернем ложь, как знак того, что нужно прекратить обход
        } else { // в ином случае
            //берем смещение
            int delta = rand() % directions.size();
            for (int i = 0; i < directions.size(); i++) {//проходимся по всем направлениям
                //берем следующую позицию, на которую пойдем(учитывая смещение)
                Position next(pos, directions[(delta + i) % directions.size()]);
                if (!is_visited(next) && !is_wall(next)) { // если след. позиция не посещена и не является стеной
                    if (dfs(next)) { // то проверяем дфс от этой позиции
                        return true; //и если он успешен, то вернем тру
                    }
                }
            }

            return false; // если зашли в тупик, то вернем ложь
        }
    }

    //запуск построения лабиринта
    void generate(){
        unset_wall(start);
        dfs(start);
        labirint[start.x][start.y].set_start();
        labirint[end.x][end.y].set_end();
    }

public:
    // конструктор класса
    Labirint(int height, int width, int x_start, int y_start, int x_end, int y_end){
        //сохраняем размеры лабиринта
        this->height = height;
        this->width = width;

        //сохраняем начальную позицию
        start.x = x_start;
        start.y = y_start;

        //сохраняем конечную позицию
        end.x = x_end;
        end.y = y_end;

        //создаем начальный лабиринт(сетку)
        labirint = new Cell*[height];
        for(int i = 0; i < height; i++){
            labirint[i] = new Cell[width];
            for(int j = 0; j < width; j++){
                if(i % 2 == 0 || j % 2 == 0){
                    labirint[i][j].set_wall();
                }
            }
        }

        //генерируем лабиринт
        generate();

        //убираем посещения
        remove_visited();
    }

    int get_rows() const{
        return height;
    }

    int get_cols() const{
        return width;
    }

    void print_labirint(){
        for(int i = 0; i < get_rows(); i++){
            for(int j = 0; j < get_cols(); j++){
                std::cout << labirint[i][j];
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }



    void solve(){
        dfs_solve(start);
    }
};


#endif //LAB_LABIRINT_H
