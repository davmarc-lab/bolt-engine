#pragma once

#include "../Component/Component.hpp"

#include "../../includes/Math.hpp"

#include <set>
#include <type_traits>

class Entity {
  private:
    unsigned int m_id;

    std::set<Component> m_components;

    EntityInfo m_info;

  public:
    inline void setId(const int &id) { this->m_id = id; }

    inline const unsigned int &getId() { return this->m_id; }

    inline void setPosition(const glm::vec3 &pos) { this->m_info.position = pos; }

    inline const glm::vec3 &getPosition() const { return this->m_info.position; }

    inline void setScale(const glm::vec3 &scale) { this->m_info.scale = scale; }

    inline const glm::vec3 &getScale() const { return this->m_info.scale; }

    inline void setRotation(const glm::vec3 &rotation) { this->m_info.rotation = rotation; }

    inline const glm::vec3 &getRotation() const { return this->m_info.rotation; }

    void addComponent(const Component &component);

    template <typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type * = nullptr> bool removeComponent();

    template <typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type * = nullptr> const T &getSingleComponent() const;

    const std::set<Component> &getAllComponents() const { return this->m_components; }
};
