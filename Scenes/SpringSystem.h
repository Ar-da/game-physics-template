#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <iomanip>

struct SpringSystem
{
    std::vector<glm::vec3> x = {{0, 0, 0}, {0, 2, 0}};  
    std::vector<glm::vec3> v = {{-1, 0, 0}, {1, 0, 0}}; 
    std::vector<glm::ivec2> springs = {{0, 1}};         
    float m = 10.0;
    float L = 1.0;
    float k = 40.0;
    glm::vec3 gravity = glm::vec3(0); // off by default, so Euler/Midpoint scenes are unaffected

    std::vector<glm::vec3> computeAccelerations(const std::vector<glm::vec3> &pos)
    {
        std::vector<glm::vec3> a(pos.size(), gravity);
        for (glm::ivec2 s : springs)
        {
            glm::vec3 d = pos[s.x] - pos[s.y];
            float l = glm::length(d);
            glm::vec3 f = -k * (l - L) * (d / l);
            a[s.x] += f / m;
            a[s.y] -= f / m;
        }
        return a;
    }

    void eulerStep(float timeStep)
    {
        std::vector<glm::vec3> a = computeAccelerations(x);
        for (size_t i = 0; i < x.size(); i++)
        {
            x[i] += timeStep * v[i];
            v[i] += timeStep * a[i];
        }
    }

    void midpointStep(float timeStep)
    {
        std::vector<glm::vec3> a = computeAccelerations(x);

        std::vector<glm::vec3> midx = x;
        std::vector<glm::vec3> midv = v;
        for (size_t i = 0; i < x.size(); i++)
        {
            midx[i] += 0.5f * timeStep * v[i];
            midv[i] += 0.5f * timeStep * a[i];
        }

        std::vector<glm::vec3> midA = computeAccelerations(midx);
        for (size_t i = 0; i < x.size(); i++)
        {
            x[i] += timeStep * midv[i];
            v[i] += timeStep * midA[i];
        }
    }

    void print()
    {
        for (size_t i = 0; i < x.size(); i++)
        {
            std::cout << "Masspoint " << i << std::endl;
            std::cout << "position: vec3(" << std::fixed << std::setprecision(6) << x[i].x << ", " << x[i].y << ", " << x[i].z << ")" << std::endl;
            std::cout << "velocity: vec3(" << std::fixed << std::setprecision(6) << v[i].x << ", " << v[i].y << ", " << v[i].z << ")" << std::endl;
        }
        std::cout << std::endl;
    }
};
