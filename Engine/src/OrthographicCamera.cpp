#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

Engine::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
    , _viewMatrix(1.0f)
{
    _pvMatrix = _projectionMatrix * _viewMatrix;
}

void Engine::OrthographicCamera::RecalculateViewProjectionMatrix()
{
    //TODO: what's best for performance here?
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) * 
                          glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3(0, 0, 1));

    // We invert here as we are going to be apply a transform from the camera back to the world view 
    // frame so need to go in reverse. If we didn't, we'd be going from world to camera.
    _viewMatrix = glm::inverse(transform);
    _pvMatrix =  _projectionMatrix * _viewMatrix;
}
