#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace Aurivia {

/**
 * @brief Physics system for rigid body dynamics and collision detection
 * Current implementation: Simple particle-based physics simulation
 * Future: Integration with Rapier3D or Bullet3 for advanced features
 */
class PhysicsSystem
{
public:
    PhysicsSystem();
    ~PhysicsSystem();
    
    bool Initialize();
    void Update(float deltaTime);
    void Shutdown();
    
    // Rigid body management
    uint32_t CreateRigidBody(const glm::vec3& position, const glm::vec3& scale, float mass);
    void DestroyRigidBody(uint32_t bodyID);
    
    // Physics manipulation
    void AddForce(uint32_t bodyID, const glm::vec3& force);
    void SetVelocity(uint32_t bodyID, const glm::vec3& velocity);
    void SetDamping(uint32_t bodyID, float linearDamping, float angularDamping);
    
    // Physics queries
    void SetGravity(const glm::vec3& gravity);
    glm::vec3 GetGravity() const;
    glm::vec3 GetPosition(uint32_t bodyID) const;
    glm::vec3 GetVelocity(uint32_t bodyID) const;
    
    // Raycasting (future)
    // RaycastHit Raycast(const glm::vec3& origin, const glm::vec3& direction, float distance);
    
    // Collision callbacks (future)
    // void OnCollisionEnter(Callback callback);

private:
    struct PhysicsImpl;
    std::unique_ptr<PhysicsImpl> m_impl;
    
    glm::vec3 m_gravity;
    float m_timeStep;
};

} // namespace Aurivia
