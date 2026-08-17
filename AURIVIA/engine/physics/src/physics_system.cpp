#include "aurivia/physics_system.h"
#include "aurivia/logger.h"
#include <unordered_map>
#include <memory>

namespace Aurivia {

struct RigidBody
{
    uint32_t id;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 scale;
    float mass;
    float linearDamping;
    float angularDamping;
    bool isKinematic;
};

struct PhysicsSystem::PhysicsImpl
{
    std::unordered_map<uint32_t, std::unique_ptr<RigidBody>> bodies;
    uint32_t nextBodyID = 1;
    glm::vec3 gravity;
    float timeStep;
};

PhysicsSystem::PhysicsSystem()
    : m_gravity(0.0f, -9.81f, 0.0f), m_timeStep(1.0f / 60.0f)
{
    m_impl = std::make_unique<PhysicsImpl>();
    m_impl->gravity = m_gravity;
    m_impl->timeStep = m_timeStep;
}

PhysicsSystem::~PhysicsSystem()
{
    Shutdown();
}

bool PhysicsSystem::Initialize()
{
    AV_LOG_INFO("Initializing Physics System (Simulation)");
    return true;
}

void PhysicsSystem::Update(float deltaTime)
{
    if (!m_impl)
        return;
    
    // Simple physics iteration
    for (auto& [id, body] : m_impl->bodies)
    {
        if (body->isKinematic)
            continue;
        
        // Apply gravity
        body->acceleration = m_gravity;
        
        // Apply damping
        body->velocity *= (1.0f - body->linearDamping * deltaTime);
        
        // Integrate velocity
        body->velocity += body->acceleration * deltaTime;
        
        // Integrate position
        body->position += body->velocity * deltaTime;
        
        // Simple ground collision
        if (body->position.y < -5.0f)
        {
            body->position.y = -5.0f;
            body->velocity.y = 0.0f;
        }
    }
}

void PhysicsSystem::Shutdown()
{
    if (m_impl)
    {
        m_impl->bodies.clear();
    }
    AV_LOG_INFO("Physics System shutdown");
}

uint32_t PhysicsSystem::CreateRigidBody(const glm::vec3& position, const glm::vec3& scale, float mass)
{
    if (!m_impl || mass <= 0.0f)
        return 0;
    
    auto body = std::make_unique<RigidBody>();
    body->id = m_impl->nextBodyID++;
    body->position = position;
    body->scale = scale;
    body->mass = mass;
    body->velocity = glm::vec3(0.0f);
    body->acceleration = glm::vec3(0.0f);
    body->linearDamping = 0.01f;
    body->angularDamping = 0.01f;
    body->isKinematic = false;
    
    uint32_t bodyID = body->id;
    m_impl->bodies[bodyID] = std::move(body);
    
    AV_LOG_DEBUG("Created rigid body ID: " + std::to_string(bodyID));
    return bodyID;
}

void PhysicsSystem::DestroyRigidBody(uint32_t bodyID)
{
    if (!m_impl)
        return;
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
    {
        m_impl->bodies.erase(it);
        AV_LOG_DEBUG("Destroyed rigid body ID: " + std::to_string(bodyID));
    }
}

void PhysicsSystem::AddForce(uint32_t bodyID, const glm::vec3& force)
{
    if (!m_impl)
        return;
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
    {
        it->second->acceleration += force / it->second->mass;
    }
}

void PhysicsSystem::SetVelocity(uint32_t bodyID, const glm::vec3& velocity)
{
    if (!m_impl)
        return;
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
    {
        it->second->velocity = velocity;
    }
}

void PhysicsSystem::SetGravity(const glm::vec3& gravity)
{
    m_gravity = gravity;
    if (m_impl)
        m_impl->gravity = gravity;
}

glm::vec3 PhysicsSystem::GetGravity() const
{
    return m_gravity;
}

glm::vec3 PhysicsSystem::GetPosition(uint32_t bodyID) const
{
    if (!m_impl)
        return glm::vec3(0.0f);
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
        return it->second->position;
    
    return glm::vec3(0.0f);
}

glm::vec3 PhysicsSystem::GetVelocity(uint32_t bodyID) const
{
    if (!m_impl)
        return glm::vec3(0.0f);
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
        return it->second->velocity;
    
    return glm::vec3(0.0f);
}

void PhysicsSystem::SetDamping(uint32_t bodyID, float linearDamping, float angularDamping)
{
    if (!m_impl)
        return;
    
    auto it = m_impl->bodies.find(bodyID);
    if (it != m_impl->bodies.end())
    {
        it->second->linearDamping = linearDamping;
        it->second->angularDamping = angularDamping;
    }
}

} // namespace Aurivia
