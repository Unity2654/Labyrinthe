#pragma once

#include <map>
#include <vector>

namespace gloop {
    class KeybordManager {
    private:
        std::map<int, bool> keyState;

    public:
        KeybordManager();

        void addKey(int k);
        void addKeys(const std::vector<int>& keys);

        bool getKeyState(int k) const;

        void setKeyStateTrue(int k);
        void setKeyStateFalse(int k);
    };
}