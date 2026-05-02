#include "KeybordManager.h"
#include <functional>

namespace gloop {

    KeybordManager::KeybordManager(){}

    void KeybordManager::addKey(int k) {
        keyState[k] = false;
    }

    void KeybordManager::addKeys(const std::vector<int>& keys) {
        for (int k : keys) {
            addKey(k);
        }
    }

    void KeybordManager::registerCallback(int k, std::function<void(bool)> callback){
        auto& find = callbacks.find(k);
        if (find == callbacks.end()) {
            callbacks[k] = {};
        }
        callbacks[k].push_back(callback);
    }

    bool KeybordManager::getKeyState(int k) const {
        auto& find = keyState.find(k);
        if (find != keyState.end()) {
            return find->second;
        }
        return false;
    }

    void KeybordManager::setKeyStateTrue(int k) {
        keyState[k] = true;
        auto& find = callbacks.find(k);
        if (find != callbacks.end()) {
            for (auto& callback : find->second)
                callback(true);
        }
    }

    void KeybordManager::setKeyStateFalse(int k) {
        keyState[k] = false;
        auto& find = callbacks.find(k);
        if (find != callbacks.end()) {
            for (auto& callback : find->second)
                callback(false);
        }
    }

}