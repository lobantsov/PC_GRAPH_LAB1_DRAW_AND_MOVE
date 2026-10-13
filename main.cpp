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

    std::vector<float> vertices = {

    };

    std::vector<unsigned int> indices = {

    };

    Shader shader("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");
    app.convertToNdc(vertices, 3, 10.0f);
    Mesh cat(vertices, indices);
    Creature creature(0.5f);

    double lastTime = glfwGetTime();

    app.run([&] {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        creature.update(app.input(), dt);

        shader.use();
        shader.setVec3("uColor", 0.1f, 0.6f, 0.2f);
        shader.setVec2("uOffSet", creature.x(), creature.y());
        cat.draw();
    });

    return 0;
}
