#include "Scene.h"
#include <map>

#include "SingleStep.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"

using SceneCreator = std::function<std::unique_ptr<Scene>()>;

template <typename T>
SceneCreator creator()
{
    return []()
    { return std::make_unique<T>(); };
}

std::map<std::string, SceneCreator> scenesCreators = {
    {"Single Step", creator<SingleStep>()},
    {"Scene 2", creator<Scene2>()},
    {"Scene 3", creator<Scene3>()},
    {"Scene 4", creator<Scene4>()},
    // add more Scene types here
};
