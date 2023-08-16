#pragma once

#include "ground.hpp"
#include "waypoint.hpp"
#include <vector>
#include <iostream>

class Map {
public:
    Map(const std::vector<Ground>& grounds):
        grounds { grounds },
        waypoints{} {
    
        //updateWay();
    }

    void updateWay() {
        waypoints.clear();

        // Find start
        for (Ground& g : grounds) {
            if (g.type == Ground::Type::START) {
                waypoints.push_back(Waypoint(g.xPos, g.yPos));
                std::cout << "Found Start(" << g.xPos << "," << g.yPos << ")" << std::endl;
                break;
            }
        }

        // Find first path to get vector then follow to direction. Stops when finding END way
        sf::Vector2i direction{};
        bool endFound = false, foundDirection = false;
        while (true) {
            const Waypoint& w = waypoints[waypoints.size() - 1];
            for (int y = -1; y < 2; ++y) {
                for (int x = -1; x < 2; ++x) {
                    if ((x != 0 && y != 0) || (x == 0 && y == 0))
                        continue;

                    // Dont go back
                    if ((direction.x != 0 || direction.y != 0) && (direction.x == -x && direction.y == -y))
                        continue;

                    Ground* g = getGround(w.x + x, w.y + y);
                    if (!g)
                        continue;

                    if (g->type == Ground::Type::END) {
                        waypoints.push_back(Waypoint(g->xPos, g->yPos));
                        std::cout << "Found End(" << g->xPos << "," << g->yPos << ")" << std::endl;
                        endFound = true;
                        break;
                    }

                    else if (g->type == Ground::Type::WAY) {
                        direction = sf::Vector2i(x, y);
                        std::cout << "Found new Direction (" << w.x << "," << w.y << ") + Vect(" << x << "," << y << ")" << std::endl;
                        foundDirection = true;
                        break;
                    }
                }
                if (endFound || foundDirection) {
                    foundDirection = false;
                    break;
                }
            }
            if (endFound)
                break;

            int x = w.x;
            int y = w.y;
            while (true) {
                x += direction.x;
                y += direction.y;

                Ground* g = getGround(x, y);
                if (!g || (g->type != Ground::Type::WAY && g->type != Ground::Type::END)) {
                    Ground* oldG = getGround(x - direction.x, y - direction.y);
                    waypoints.push_back(Waypoint(oldG->xPos, oldG->yPos));
                    std::cout << "Found new Corner(" << oldG->xPos << "," << oldG->yPos << ")" << std::endl;
                    break;
                }
                if (g->type == Ground::Type::END) {
                    waypoints.push_back(Waypoint(g->xPos, g->yPos));
                    std::cout << "Found END(" << g->xPos << "," << g->yPos << ")" << std::endl;
                    endFound = true;
                    break;
                }
            }

            if (endFound)
                break;
        }
    }

    Ground* getGround(int x, int y) {
        for (Ground& g : grounds) {
            if (g.xPos == x && g.yPos == y)
                return &g;
        }
        return nullptr;
    }

    void debugImGUI() {
        if (ImGui::Button("refresh waypoints"))
            updateWay();

        if (ImGui::TreeNode(("grounds (" + std::to_string(grounds.size()) + ")").c_str())) {
            ImGui::SliderFloat("size", &Ground::size, 25, 75);
            for (int i = 0; i < grounds.size(); ++i) {
                if (ImGui::TreeNode(std::to_string(i).c_str())) {
                    grounds[i].debugImGUI();
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode(("waypoints (" + std::to_string(waypoints.size()) + ")").c_str())) {
            for (int i = 0; i < waypoints.size(); ++i) {
                if (ImGui::TreeNode(std::to_string(i).c_str())) {
                    waypoints[i].debugImGUI();
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }

    void render(sf::RenderWindow& w) {
        for (Ground& g : grounds)
            g.render(w);
        for (Waypoint& wp : waypoints)
            wp.render(w);
    }

    std::vector<Ground> grounds;
    std::vector<Waypoint> waypoints;
};