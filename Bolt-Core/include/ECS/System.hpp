#pragma once

#include "../Application/Application.hpp"

#include "../Core/Math.hpp"
#include "../Core/RenderApi.hpp"
#include "../Core/Utils.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"

#include "../Core/Scene.hpp"
#include "../Graphic/Camera/Camera.hpp"

#include "../../../Bolt-Graphics/include/glad/glad.h"

namespace bolt {
	namespace systems {
		namespace transform {
			void updateEntityPosition(u32 id, const vec3 &pos);

			void updateEntityRotation(u32 id, const vec3 &rot);

			void updateModelMatrix(u32 id);

			void updateAllModelMatrix();
		} // namespace transform

		namespace render {
			void drawElement(u32 id);

			void drawElementIndexed(u32 id);

			void drawAllMeshes();
		} // namespace render
	} // namespace systems
} // namespace bolt
