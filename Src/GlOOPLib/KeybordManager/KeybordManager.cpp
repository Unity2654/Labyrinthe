#include "KeybordManager.h"
#include <functional>
#include <iostream>

namespace gloop {

    KeyboardManager::KeyboardManager(){}

    void KeyboardManager::addKey(int k) {
        keyState[k] = false;
    }

    void KeyboardManager::addKeys(const std::vector<int>& keys) {
        for (int k : keys) {
            addKey(k);
        }
    }

    void KeyboardManager::registerCallback(int k, std::function<void(bool)> callback){
        auto find = callbacks.find(k);
        if (find == callbacks.end()) {
            callbacks[k] = {};
        }
        callbacks[k].push_back(callback);
    }

    void KeyboardManager::clearCallbacks(int k){
        auto find = callbacks.find(k);
        if (find != callbacks.end()) {
            callbacks[k].clear();
        }
    }

    bool KeyboardManager::getKeyState(int k) const {
        auto find = keyState.find(k);
        if (find != keyState.end()) {
            return find->second;
        }
        return false;
    }

    void KeyboardManager::setKeyStateTrue(int k) {
        keyState[k] = true;
        auto find = callbacks.find(k);
        if (find != callbacks.end()) {
            for (auto& callback : find->second)
                callback(true);
        }
    }

    void KeyboardManager::setKeyStateFalse(int k) {
        keyState[k] = false;
        auto find = callbacks.find(k);
        if (find != callbacks.end()) {
            for (auto& callback : find->second)
                callback(false);
        }
    }

}