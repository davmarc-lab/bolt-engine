#pragma once

#include "../../Bolt-Core/include/Engine.hpp"

#include <string>

struct InfoEntity {
	bolt::vec3 pos{};
	bolt::vec3 scale{};
	bolt::vec3 rot{};
};

struct InfoMesh {
	std::vector<bolt::vec3> vertex{};
	std::vector<u32> index{};
	std::vector<bolt::vec4> colors{};
	std::vector<bolt::vec3> normals{};
	std::vector<bolt::vec2> texCoords{};
    bolt::RenderHelper render{};
};

class MeshParser {
public:
	static constexpr char FILE_NEW_ENTITY_SEP = '$';
	inline static const std::string FILE_POS = "pos";
	inline static const std::string FILE_SCL = "scale";
	inline static const std::string FILE_ROT = "rot";
	inline static const std::string FILE_MESH_VERT = "vertex";
	inline static const std::string FILE_MESH_IDX = "indices";
	inline static const std::string FILE_MESH_COLOR = "colors";
	inline static const std::string FILE_MESH_NORM = "normals";  // TODO
	inline static const std::string FILE_MESH_TEX = "texCoords"; // TODO
    inline static const std::string FILE_RENDER = "render";

	static void readMeshFromFile(const std::string &path);

	static void saveMeshToFile(const std::string &path = "config.txt");

private:
	static std::vector<std::string> removeSpaces(const std::string &content);
	
	static InfoEntity parseEntityInfo(const std::string &content);

	static InfoMesh unpackBuffer(const std::vector<std::string>& buffer);
};
