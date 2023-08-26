
#include <glm/glm.hpp>

namespace Engine
{
class OrthgraphicCamera
{
public:
    OrthgraphicCamera(float left, float right, float bottom, float top);

    const glm::mat4& getProjectionMatric() const { return _projectionMatrix; }
    void setProjectionMatrix(glm::mat4 projection) { _projectionMatrix = projection; }

    const glm::mat4& getviewMatrix() const { return _viewMatrix; }
    void setViewMatrix(glm::mat4 view) { _viewMatrix = view; }

    void setPosition(glm::vec3 position) { _position = position; RecalculateViewProjectionMatrix(); }
    const glm::vec3& getPosition() const { return _position; }

    void setRotation(float rotation) { _rotation = rotation; RecalculateViewProjectionMatrix(); }
    const float& getRotation() const { return _rotation; }

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