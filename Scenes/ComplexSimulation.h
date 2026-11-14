#pragma once
#include "Scene.h"
#include "SpringSystem.h"

class ComplexSimulation : public Scene
{
    void init() override;
    void simulateStep() override;
    void onDraw(Renderer &renderer) override;
    void onGUI() override;

    void setupRing();
    void handleCollisions();
    void applyMouseForce();

    SpringSystem springSystem;
    float timeStep;
    int method; // 0 = Euler, 1 = Midpoint

    float floorZ = -1.0f;
    float bounce = 0.5f;  // 0 = no bounce, 1 = perfectly elastic
    float mouseStrength = 0.2f;
};
