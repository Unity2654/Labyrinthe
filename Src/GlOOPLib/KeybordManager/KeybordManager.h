#pragma once

#include <map>
#include <vector>
#include <functional>

namespace gloop {

    // Class handling the user keyboard inputs, allowing to check if a key is pressed or not
    // The key have to be explicitely added to the manager for them to be monitored
    // The key have to be explicitely added to the manager for them to be monitored
    // Also includes callbacks, called when a key is pressed
    class KeyboardManager {
    private:
        // State of the key (pressed or not)
        std::map<int, bool> keyState;
        // Map of the callbacks
        std::map<int, std::vector<std::function<void(bool)>>> callbacks;

    public:
        KeyboardManager();

        // Add a single key to be monitored by the manager
        void addKey(int k);
        // Adds a set of keys to be monitored by the manager
        void addKeys(const std::vector<int>& keys);

        // Adds a callback to the manager
        // The callback is a method taking a boolean as an input, that states wether the callback has been called when the key was pressed or released
        void registerCallback(int k, std::function<void(bool)> callback);
        // Removes all the callbacks added for a given key
        void clearCallbacks(int k);

        // Checks wether the key is pressed or not
        bool getKeyState(int k) const;

        // Sets the state of a key to pressed
        // Should only be called in a glut callback
        void setKeyStateTrue(int k);
        // Sets the state of a key to not pressed
        // Should only be called in a glut callback
        void setKeyStateFalse(int k);
    };
}