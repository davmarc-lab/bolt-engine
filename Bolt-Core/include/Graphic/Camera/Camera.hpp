#pragma once

#include "../../Core/Utils.hpp"
#include "../../Core/Math.hpp"
#include "../../Core/Structs.hpp"

namespace bolt {
	class Camera {
	private:
		vec3 worldUp = vec3(0, 1, 0);
		camera::CameraVectors vectors;
		camera::CameraInfo info;
		camera::CameraRotation rotation;

        mat4 m_view = mat4(0);
        mat4 m_proj = mat4(0);
        mat4 m_viewProj = mat4(0);

		void updateCameraVectors();

	public:
		mat4 getViewProjMatrix();

        // Updates the Proj * View results BUT it assumes that the scene is 2D.
        inline void updateOrthoProjection(const f32& left, const f32& right, const f32& bot, const f32& top) {
            this->m_proj = glm::ortho(left, right, bot, top);
            this->m_view = mat4(1);
            this->m_viewProj = this->m_proj * this->m_view;
        }

        inline void updatePerspProjection(const f32& fov, const f32& width, const f32& height, const f32& near, const f32& far) {
            this->m_proj = perspective(fov, width / height, near, far);
            this->updateCameraVectors();
        }

		void moveCamera(vec3 position);

		void processMouseMovement(f32 xoffset, f32 yoffset, b8 constrainPitch = true);

		inline void setCameraFront(vec3 vec) { this->vectors.cameraFront = vec; }

		inline vec3 getCameraFront() { return this->vectors.cameraFront; }

		inline vec3 getCameraUp() { return this->vectors.cameraUp; }

		inline void setCameraVelocity(const float velocity) { this->info.speed = velocity; }

		inline float getCameraVelocity() { return this->info.speed; }

		inline vec3 getCameraRight() { return this->vectors.cameraRight; }

		inline vec3 getCameraPosition() { return this->vectors.cameraPos; }

		inline float getMouseSensitivity() { return this->info.sensitivity; }

		inline void setMouseSensitivity(float val) { this->info.sensitivity = val; }

		inline float getCameraZoom() { return this->info.zoom; }

		inline void setCameraZoom(const float zoom) { this->info.zoom = zoom; }

		//inline float getTrackballSpeed() { return this->info.tb_speed; }

		//inline void setTrackballSpeed(const float speed) { this->info.tb_speed = speed; }

		inline vec3 getCameraDirection() { return this->vectors.cameraDirection; }

		inline void setCameraDirection(vec3 dir) { this->vectors.cameraDirection = dir; }

		inline vec3 getCameraTarget() { return this->vectors.cameraTarget; }

		inline void setCameraTarget(vec3 target) { this->vectors.cameraTarget = target; }

		Camera() { this->updateCameraVectors(); }

		~Camera() = default;
	};

	inline Camera standardCamera{};
};
