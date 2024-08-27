#pragma once

#include "../Component/Component.hpp"

#include "../../includes/Math.hpp"

#include <memory>
#include <set>
#include <type_traits>

class Entity {
  private:
    const unsigned int m_id;

    // TODO : Check if is correct to use unique_ptr 
    std::set<std::unique_ptr<Component>> m_components;

    EntityInfo m_info;

  public:
    Entity(const int& id) : m_id(id) {}
    
    inline const unsigned int &getId() { return this->m_id; }

    inline void setPosition(const glm::vec3 &pos) { this->m_info.position = pos; }

    inline const glm::vec3 &getPosition() const { return this->m_info.position; }

    inline void setScale(const glm::vec3 &scale) { this->m_info.scale = scale; }

    inline const glm::vec3 &getScale() const { return this->m_info.scale; }

    inline void setRotation(const glm::vec3 &rotation) { this->m_info.rotation = rotation; }

    inline const glm::vec3 &getRotation() const { return this->m_info.rotation; }

    void addComponent(const Component &component);

    template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>> * = nullptr> bool removeComponent() {}
    
    template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>> * = nullptr> const T &getSingleComponent() const {}

    const std::set<std::unique_ptr<Component>> &getAllComponents() const { return this->m_components; }

    // TODO : Change destructor
    ~Entity() = default;
};
