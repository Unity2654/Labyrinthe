#include "SceneManager.h"

namespace gloop{


    void SceneManager::update(){
        onUpdate();
        ActiveScene.update();
    }

    void SceneManager::display() const{
        onDisplay();
        ActiveScene.display();
    }

    Scene& SceneManager::getActiveScene() const{
        return ActiveScene;
    }

    void run(){
        // TODO
    }
}
