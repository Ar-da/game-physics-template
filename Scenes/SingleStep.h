#include "Scene.h"
#include "SpringSystem.h"

class SingleStep : public Scene
{
    void init() override;

    SpringSystem springSystem;
};