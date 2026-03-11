#pragma once
#include "Scenes.h"

namespace gloop{

    class SceneManager{
    private :
        // Attributes
        Scene& ActiveScene;
        bool propertyChanged = true;

        // Methods
        void update();
        void display() const;


    protected :
        // Methods
        virtual void onDisplay() const {}
        virtual void onUpdate() {}


    public :
        // Attributes

        // Constructors
        SceneManager() = delete;
        SceneManager(Scene& InitialScene) : ActiveScene(InitialScene) {}

        // Methods
        Scene& getActiveScene() const;

        void run();
    };
}
