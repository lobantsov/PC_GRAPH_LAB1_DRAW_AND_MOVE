#ifndef LAB1_MESH_H
#define LAB1_MESH_H

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;

private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
    int indexCount_ = 0;
};

#endif //LAB1_MESH_H