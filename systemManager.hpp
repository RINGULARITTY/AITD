#pragma once

#include "system.hpp"

#include <vector>
#include <memory>


class SystemManager {
private:
    std::vector<std::unique_ptr<System>> systems;

public:
    template<typename T, typename... Args>
    void AddSystem(Args&&... args) {
        systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void UpdateSystems() {
        for (auto& system : systems) {
            system->UpdateSystem();
        }
    }

    void UpdateRenders() {
        for (auto& system : systems) {
            system->UpdateRender();
        }
    }

    void Renders() {
        for (auto& system : systems) {
            system->Render();
        }
    }
};
