#pragma once

class System {
public:
    virtual void UpdateSystem() {}
    virtual void UpdateRender() {}
    virtual void Render() {}
};