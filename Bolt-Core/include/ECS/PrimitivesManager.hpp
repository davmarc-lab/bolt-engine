#pragma once

#include "../Core/Enums.hpp"

#include "../Graphic/Buffer/VertexArray.hpp"
#include "Component.hpp"

namespace bolt {
    namespace factory {
        namespace primitive {
            u32 createCube();

            u32 createSquare();
        }
    }
    
	class SimplePrimitive {
	public:
		PrimitiveType m_type;
		VertexArray m_vao;
		VertexBuffer m_vbog;
		VertexBuffer m_vbot;
		VertexBuffer m_vbon;

		Transform m_transform;
        RenderComponent m_render;
        
        ~SimplePrimitive() = default;
	};

} // namespace bolt
