#pragma once

#include <string>
#include "Component.hpp"
#include "PrimitivesManager.hpp"

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
					break;
				}
				case LIGHT_POINT: {
					this->m_light = CreateShared<PointLight>(helper);
					break;
				}
				case LIGHT_SPOT: {
					this->m_light = CreateShared<SpotLight>(helper);
					break;
				}
				default: {
					std::cerr << "Invalid Light type.\n";
					break;
				}
			}
		}

		u32 getCasterId() const { return this->m_caster; }
		
		EntityLight() = delete;
		~EntityLight() override = default;

	private:
		Shared<Light> m_light{};
		u32 m_caster{};
	};
} // namespace bolt
