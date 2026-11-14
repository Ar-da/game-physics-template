#include "Scene.h"
#include "SpringSystem.h"

class EulerSimulation : public Scene
{
    void init() override;
    void simulateStep() override;
    void onDraw(Renderer &renderer) override;
    void onGUI() override;
    SpringSystem springSystem;
    float timeStep;
};