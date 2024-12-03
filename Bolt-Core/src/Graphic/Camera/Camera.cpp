#include "../../../include/Graphic/Camera/Camera.hpp"
#include "../../../include/Core/Event.hpp"

namespace bolt {
	void Camera::updateCameraVectors() {
		this->vectors.cameraFront = normalize(vec3(cos(radians(this->rotation.yaw)) * cos(radians(this->rotation.pitch)),
			-sin(radians(this->rotation.pitch)),
			sin(radians(this->rotation.yaw) * cos(radians(this->rotation.pitch)))
		));
		this->vectors.cameraRight = normalize(cross(this->vectors.cameraFront, this->worldUp));
		this->vectors.cameraUp = normalize(cross(this->vectors.cameraRight, this->vectors.cameraFront));
		this->m_view = lookAt(this->vectors.cameraPos, this->vectors.cameraPos + this->vectors.cameraFront, this->vectors.cameraUp);
        this->m_viewProj = this->m_proj * this->m_view;
        EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);
	}

	mat4 Camera::getViewProjMatrix() {
        return this->m_viewProj;
	}

	void Camera::moveCamera(vec3 pos) {
		this->vectors.cameraPos += (pos * this->info.speed);
		this->updateCameraVectors();
	}

	void Camera::processMouseMovement(f32 xoffset, f32 yoffset, b8 constrainPitch) {
		xoffset *= this->info.sensitivity;
		yoffset *= this->info.sensitivity;

		this->rotation.yaw += xoffset;
		this->rotation.pitch += yoffset;

		if (constrainPitch) {
			if (this->rotation.pitch > 89)
				this->rotation.pitch = 89;
			if (this->rotation.pitch < -89)
				this->rotation.pitch = -89;
		}

		this->updateCameraVectors();
	}
};
