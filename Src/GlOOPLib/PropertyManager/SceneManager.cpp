#include "SceneManager.h"

void gloop::SceneManager::popScene(){
	scenes.pop();
	if (scenes.empty())
		exit(0);
	scenes.top()->onLoad();
}

bool gloop::SceneManager::isPaused() const{
	return paused;
}

void gloop::SceneManager::pause(){
	paused = true;
}

void gloop::SceneManager::unPause(){
	paused = false;
}

bool gloop::SceneManager::togglePause(){
	paused = !paused;
	return paused;
}

void gloop::SceneManager::display() const{
	scenes.top()->display();
}

void gloop::SceneManager::update(){
	if (!paused)
		scenes.top()->update();
}
