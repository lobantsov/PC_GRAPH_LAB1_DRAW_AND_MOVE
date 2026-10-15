#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& indicesLine) {
    indexCount_ = static_cast<int>(indices.size());
    lineIndexCount_ = static_cast<int>(indicesLine.size());

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glGenBuffers(1, &eboLines_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboLines_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLine.size() * sizeof(unsigned int), indicesLine.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (ebo_) glDeleteBuffers(1, &ebo_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (eboLines_) glDeleteVertexArrays(1, &eboLines_);
}

void Mesh::draw() const {
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, nullptr);
}

void Mesh::drawLine() const {
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboLines_);
    glDrawElements(GL_LINES, lineIndexCount_, GL_UNSIGNED_INT, nullptr);
}
