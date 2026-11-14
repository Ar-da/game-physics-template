#include "EulerSimulation.h"
#include <imgui.h>


void EulerSimulation::init()
{
    springSystem = SpringSystem();
    timeStep = 0.005f;
}

void EulerSimulation::simulateStep()
{
    springSystem.eulerStep(timeStep);
}

void EulerSimulation::onDraw(Renderer &renderer)
{
    renderer.drawSphere(springSystem.x[0], 0.1f, glm::vec4(1, 0, 0, 1));
    renderer.drawSphere(springSystem.x[1], 0.1f, glm::vec4(0, 0, 1, 1));
    renderer.drawLine(springSystem.x[0], springSystem.x[1], glm::vec3(1));
}

void EulerSimulation::onGUI()
{
    ImGui::SliderFloat("Time Step", &timeStep, 0.001f, 0.1f);
}