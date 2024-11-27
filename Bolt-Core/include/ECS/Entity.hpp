#pragma once

#include <string>
#include "Component.hpp"

namespace bolt {
	class Entity {
	protected:
		std::string m_name;

	public:
		explicit Entity(std::string name = "Entity") :
			m_name(std::move(name)) {}

		virtual ~Entity() = default;

		std::string getName() const { return this->m_name; }

		void setName(const std::string &name) { this->m_name = name; }
	};

	class EntityLight final : public Entity {
	public:
		Shared<Light> getLight() const { return this->m_light; }

		EntityLight(const LightHelper &helper) :
			Entity(helper.name) {
			switch (helper.type) {
				case LIGHT_DIRECTIONAL: {
                    this->m_light = CreateShared<DirectionalLight>(helper);
				}
				case LIGHT_POINT: {
                    this->m_light = CreateShared<PointLight>(helper);
				}
				case LIGHT_SPOT: {
                    this->m_light = CreateShared<SpotLight>(helper);
				}
				default: {
					std::cerr << "Invalid Light type.\n";
					break;
				}
			}
		}

		EntityLight() = delete;
		~EntityLight() override = default;

	private:
		Shared<Light> m_light{};
	};
} // namespace bolt
