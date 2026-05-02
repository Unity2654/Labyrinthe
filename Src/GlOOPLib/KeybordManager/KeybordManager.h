#pragma once

#include <map>
#include <vector>
#include <functional>

namespace gloop {
    class KeybordManager {
    private:
        std::map<int, bool> keyState;
        std::map<int, std::vector<std::function<void(bool)>>> callbacks;

    public:
        KeybordManager();

        void addKey(int k);
        void addKeys(const std::vector<int>& keys);

        void registerCallback(int k, std::function<void(bool)> callback);

        bool getKeyState(int k) const;

        void setKeyStateTrue(int k);
        void setKeyStateFalse(int k);
    };
}