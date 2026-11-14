#include "ComplexSimulation.h"
#include <imgui.h>
#include <cmath>

void ComplexSimulation::init()
{
    timeStep = 0.005f;
    method = 1;
    setupRing();
}

void ComplexSimulation::setupRing()
{
    springSystem = SpringSystem();
    springSystem.x.clear();
    springSystem.v.clear();
    springSystem.springs.clear();

    for (int i = 0; i < 10; i++)
    {
        float angle = 2.0f * 3.14159265f * i / 10;
        springSystem.x.push_back({std::cos(angle), 0, 1 + std::sin(angle)}); // ring in the xz-plane, centre at z = 1
        springSystem.v.push_back({0, 0, 0});
        springSystem.springs.push_back({i, (i + 1) % 10});
    }

    springSystem.L = 0.5f;
    springSystem.gravity = glm::vec3(0, 0, -9.81f);
    springSystem.v[0] = {0, 2, 0}; // small push out of the plane
}

void ComplexSimulation::simulateStep()
{
    applyMouseForce();

    if (method == 0)
        springSystem.eulerStep(timeStep);
    else
        springSystem.midpointStep(timeStep);

    handleCollisions();
}

void ComplexSimulation::applyMouseForce()
{
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Right) || ImGui::GetIO().WantCaptureMouse)
        return;

    ImVec2 drag = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);

    glm::vec3 dir = Renderer::camera.right() * drag.x
                  - Renderer::camera.up() * drag.y; // screen y points down, world up points up

    for (glm::vec3 &v : springSystem.v)
        v += mouseStrength * dir * timeStep;
}

void ComplexSimulation::handleCollisions()
{
    for (size_t i = 0; i < springSystem.x.size(); i++)
    {
        glm::vec3 &x = springSystem.x[i];
        glm::vec3 &v = springSystem.v[i];

        if (x.z < floorZ) // point went through the floor
        {
            x.z = floorZ;            // put it back on the floor
            v.z = -bounce * v.z;     // reverse vertical velocity and apply bounce factor
        }
    }
}

void ComplexSimulation::onDraw(Renderer &renderer)
{
    renderer.drawWireCube(glm::vec3(0, 0, floorZ), glm::vec3(4, 4, 0), glm::vec3(1)); // flat square = floor

    for (glm::vec3 p : springSystem.x)
        renderer.drawSphere(p, 0.05f, glm::vec4(1, 0, 0, 1));
    for (glm::ivec2 s : springSystem.springs)
        renderer.drawLine(springSystem.x[s.x], springSystem.x[s.y], glm::vec3(1));
}

void ComplexSimulation::onGUI()
{
    ImGui::RadioButton("Euler", &method, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Midpoint", &method, 1);

    ImGui::SliderFloat("Time Step", &timeStep, 0.001f, 0.1f);
    ImGui::SliderFloat("Gravity", &springSystem.gravity.z, -20.0f, 0.0f);
    ImGui::SliderFloat("Bounce", &bounce, 0.0f, 1.0f);
    ImGui::SliderFloat("Mouse Strength", &mouseStrength, 0.0f, 1.0f);
    ImGui::Text("Right-click + drag to push the ring");

    if (ImGui::Button("Reset"))
        setupRing();
}
