#include "KeybordManager.h"

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

    bool KeybordManager::getKeyState(int k) const {
        auto find = keyState.find(k);
        if (find != keyState.end()) {
            return find->second;
        }
        return false;
    }

    void KeybordManager::setKeyStateTrue(int k) {
        keyState[k] = true;
    }

    void KeybordManager::setKeyStateFalse(int k) {
        keyState[k] = false;
    }

}