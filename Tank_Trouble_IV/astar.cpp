#include "astar.h"
#include <queue>
#include <cmath>
#include <algorithm>

struct Node {
    Point point;
    int f, g, h;
    Node* parent;

    Node(Point point, int f, int g, int h, Node* parent)
        : point(point), f(f), g(g), h(h), parent(parent) {}

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

std::vector<Point> findPath(Point start, Point goal, int map[][10], int mapSize) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<Node> closedList;

    openList.push(Node(start, 0, 0, 0, nullptr));

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current.point.x == goal.x && current.point.y == goal.y) {
            std::vector<Point> path;
            for (Node* node = &current; node != nullptr; node = node->parent) {
                path.push_back(node->point);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedList.push_back(current);

        std::vector<Point> neighbors = {
            {current.point.x + 1, current.point.y},
            {current.point.x - 1, current.point.y},
            {current.point.x, current.point.y + 1},
            {current.point.x, current.point.y - 1}
        };

        for (const auto& neighbor : neighbors) {
            if (neighbor.x >= 0 && neighbor.x < mapSize &&
                neighbor.y >= 0 && neighbor.y < mapSize &&
                map[neighbor.x][neighbor.y] == 0) {
                int g = current.g + 1;
                int h = std::abs(neighbor.x - goal.x) + std::abs(neighbor.y - goal.y);
                int f = g + h;

                bool inClosedList = false;
                for (const auto& node : closedList) {
                    if (node.point.x == neighbor.x && node.point.y == neighbor.y) {
                        inClosedList = true;
                        break;
                    }
                }

                if (!inClosedList) {
                    // Check if neighbor is in openList and update if necessary
                    bool inOpenList = false;
                    std::vector<Node> tempBuffer; // Temporary buffer to hold nodes to re-insert

                    while (!openList.empty()) {
                        Node node = openList.top();
                        openList.pop();

                        if (node.point.x == neighbor.x && node.point.y == neighbor.y) {
                            inOpenList = true;
                            if (g < node.g) {
                                node.g = g;
                                node.f = g + node.h;
                                node.parent = &closedList.back();
                            }
                        }

                        tempBuffer.push_back(node);
                    }

                    // Re-insert nodes back into openList
                    for (const auto& node : tempBuffer) {
                        openList.push(node);
                    }

                    if (!inOpenList) {
                        openList.push(Node(neighbor, f, g, h, &closedList.back()));
                    }
                }
            }
        }
    }

    return std::vector<Point>(); // No path found
}
