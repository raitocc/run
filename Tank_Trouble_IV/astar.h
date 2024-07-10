#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

std::vector<Point> findPath(Point start, Point goal, int map[][10], int mapSize);

#endif // ASTAR_H
