//
// Created by loban on 10/13/2026.
//

#ifndef LAB1_INPUT_H
#define LAB1_INPUT_H

#include <functional>

struct GLFWwindow;

class Input {
public:
    using KeyCallback = std::function<void(int key, int action)>;

    Input(GLFWwindow* window);
    ~Input();

    bool isKeyDown(int key) const;

    void onKey(KeyCallback callback) { keyCallback_ = callback; }

private:
    static void keyCallbackThunk(GLFWwindow* window, int key, int scancode, int action, int mods);

    GLFWwindow* window_;
    KeyCallback keyCallback_;
};

#endif //LAB1_INPUT_H
