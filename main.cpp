#include "core/Application.h"
#include "game/Creature.h"
#include "render/Mesh.h"
#include "render/Shader.h"

#include <GLFW/glfw3.h>

#include <vector>

int main() {
    Application app(800, 600, "LearnOpenGL");
    if (!app.isValid()) return -1;

    app.setBackgroundColor(Color(228, 233, 69));

    app.input().onKey([&](int key, int action) {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) app.requestClose();
    });

    std::vector vertices = {
        -0.85f, 0.6f, 0.0f,
        -0.7f, 0.425f, 0.0f,
        -0.85f, 0.3f, 0.0f,
        -0.55f, 0.55f, 0.0f,
        -0.55f, 0.3f, 0.0f,
        -0.85f, 0.0f, 0.0f,
        -0.55f, 0.0f, 0.0f,
        -0.55f, 0.15f, 0.0f,
        -0.55f, -0.35f, 0.0f,
        0.0f, 0.15f, 0.0f,
        0.55f, -0.35f, 0.0f,
        0.55f, 0.15f, 0.0f,
        0.85f, 0.6f, 0.0f,
        0.83f, 0.3f, 0.0f,
        0.58f, 0.45f, 0.0f,
        -0.275f, -0.1f, 0.0f,
        0.275f, -0.1f, 0.0f
    };

    std::vector<unsigned int> indices = {
        0, 1,  2,  3, 2,  4,  2,  5,  6,  2,  6, 4,  7, 8,
                                      9, 10, 11, 9, 11, 13, 14, 14, 12, 13, 9, 15, 16
    };

    std::vector<unsigned int> lineIndices = {0,  1,  1,  2,  2,  0,  3,  2, 2,  4,  3,
                                  4,  2,  5,  5,  6,  6,  4,  7, 8,  8,  9,
                                  9,  7,  9,  10, 10, 11, 11, 9, 11, 13, 13,
                                  12, 12, 14, 11, 14, 15, 16

    };

    Shader shader("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");
    //app.convertToNdc(vertices, 3, 10.0f);
    Mesh cat(vertices, indices, lineIndices);
    Creature creature(1.0f);

    double lastTime = glfwGetTime();

    app.run([&] {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        creature.update(app.input(), dt);

        shader.use();
        shader.setVec2("uOffSet", creature.x(), creature.y());

        shader.setVec3("uColor", 0.1f, 0.6f, 0.2f);
        cat.draw();

        shader.setVec3("uColor", 0.0f, 0.0f, 0.0f);
        cat.drawLine();
    });

    return 0;
}
