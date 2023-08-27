#pragma once

#include <glm/glm.hpp>

namespace Engine
{
class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void setPosition(glm::vec3 position) { _position = position; RecalculateViewProjectionMatrix(); }
    const glm::vec3& getPosition() const { return _position; }

    void setRotation(float rotation) { _rotation = rotation; RecalculateViewProjectionMatrix(); }
    const float& getRotation() const { return _rotation; }

    const glm::mat4& getViewProjectionMatrix() const { return _pvMatrix; }
    const glm::mat4& getviewMatrix() const { return _viewMatrix; }
private:
    void RecalculateViewProjectionMatrix();
private:
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;
    glm::mat4 _pvMatrix;

    glm::vec3 _position;
    float _rotation{0.0f};
};

}