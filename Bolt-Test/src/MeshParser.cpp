#include "../../Bolt-Core/include/Engine.hpp"

#include "../include/MeshParser.hpp"

#include <fstream>
#include <iostream>

std::vector<std::string> MeshParser::removeSpaces(const std::string &content) {
	std::vector<std::string> res{};
	std::string copy{content};
	std::string buff{};
	size_t index{};
	while ((index = copy.find({" "})) != std::string::npos) {
		buff = copy.substr(0, index);
		copy = copy.substr(index + 1);
		res.push_back(buff);
	}
	if (!copy.empty())
		res.push_back(copy);
	return res;
}

InfoEntity MeshParser::parseEntityInfo(const std::string &content) {
	const size_t posIndex = content.find(FILE_POS);
	const size_t sclIndex = content.find(FILE_SCL);
	const size_t rotIndex = content.find(FILE_ROT);

	auto posString = content.substr(posIndex + FILE_POS.length() + 1, sclIndex - (posIndex + FILE_POS.length() + 1));
	auto sclString = content.substr(sclIndex + FILE_SCL.length() + 1, rotIndex - (sclIndex + FILE_SCL.length() + 1));
	auto rotString = content.substr(rotIndex + FILE_ROT.length() + 1);

	InfoEntity ent{};
	{
		const auto vals = removeSpaces(posString);
		BT_ASSERT(vals.size() == 3);
		ent.pos.x = std::stof(vals.at(0));
		ent.pos.y = std::stof(vals.at(1));
		ent.pos.z = std::stof(vals.at(2));
	}
	{
		const auto vals = removeSpaces(sclString);
		BT_ASSERT(vals.size() == 3);
		ent.scale.x = std::stof(vals.at(0));
		ent.scale.y = std::stof(vals.at(1));
		ent.scale.z = std::stof(vals.at(2));
	}
	{
		const auto vals = removeSpaces(rotString);
		BT_ASSERT(vals.size() == 3);
		ent.rot.x = std::stof(vals.at(0));
		ent.rot.y = std::stof(vals.at(1));
		ent.rot.z = std::stof(vals.at(2));
	}
	return ent;
}

InfoMesh MeshParser::unpackBuffer(const std::vector<std::string> &buffer) {
	InfoMesh res{};

	auto vert = std::ranges::find(buffer, FILE_MESH_VERT);
	if (vert != buffer.end()) {
		for (int i = 1; i <= std::atoi((vert + 1)->data()); i++) {
			auto content = removeSpaces(*(vert + 1 + i));
			BT_ASSERT(content.size() == 3);
			res.vertex.emplace_back(std::stof(content.at(0)), std::stof(content.at(1)), std::stof(content.at(2)));
		}
	}

	auto color = std::ranges::find(buffer, FILE_MESH_COLOR);
	if (color != buffer.end()) {
		for (int i = 1; i <= std::atoi((color + 1)->data()); i++) {
			auto content = removeSpaces(*(color + 1 + i));
			BT_ASSERT(content.size() == 4);
			res.colors.emplace_back(std::stof(content.at(0)), std::stof(content.at(1)), std::stof(content.at(2)), std::stof(content.at(3)));
		}
	}
	
	auto index = std::ranges::find(buffer, FILE_MESH_IDX);
	if (index != buffer.end()) {
		for (int i = 1; i <= std::atoi((index + 1)->data()); i++) {
			auto content = removeSpaces(*(index + 1 + i));
			BT_ASSERT(content.size() == 1);
			res.index.emplace_back(std::atoi(content.at(0).c_str()));
		}
	}
	
	auto normal = std::ranges::find(buffer, FILE_MESH_NORM);
	if (normal != buffer.end()) {
		for (int i = 1; i <= std::atoi((normal + 1)->data()); i++) {
			auto content = removeSpaces(*(normal + 1 + i));
			BT_ASSERT(content.size() == 3);
			res.normals.emplace_back(std::stof(content.at(0)), std::stof(content.at(1)), std::stof(content.at(2)));
		}
	}
	
	return res;
}

enum State {
	READ_ENTITY,
	READ_INFO,
	READ_MESH,
};

void MeshParser::readMeshFromFile(const std::string &path) {
	{
		std::ifstream file(path);
		std::string content{};
		auto state = READ_ENTITY;

		std::vector<std::string> mesh{};
		while (std::getline(file, content)) {
			switch (state) {
				case READ_ENTITY: {
					std::cout << "New Entity: " << content << "\n";
					state = READ_INFO;
					break;
				}
				case READ_INFO: {
					auto info = MeshParser::parseEntityInfo(content);
					state = READ_MESH;
					break;
				}
				case READ_MESH: {
					if (content == "\0") {
						// parse all the vertices
						auto buff = unpackBuffer(mesh);
						std::cout << buff.colors.size() << "\n";
						state = READ_ENTITY;
						break;
					}
					mesh.push_back(content);
					break;
				}
			}
		}
	}
}

void MeshParser::saveMeshToFile(const std::string &path) {
	// create file
	{
		std::ofstream file("config.txt");
		int index = 0;
		for (auto id : bolt::EntityManager::instance()->getEntitiesFromComponent<bolt::Mesh>()) {
			file << FILE_NEW_ENTITY_SEP << index << "\n";
			auto t = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(id);
			auto m = bolt::EntityManager::instance()->getEntityComponent<bolt::Mesh>(id);
			auto pos = t->getPosition();
			auto scale = t->getScale();
			auto rot = t->getRotation();

			// model info
			file << FILE_POS << " " << pos.x << " " << pos.y << " " << pos.z << " ";
			file << FILE_SCL << " " << scale.x << " " << scale.y << " " << scale.z << " ";
			file << FILE_ROT << " " << rot.x << " " << rot.y << " " << rot.z << "\n";

			// vertex info
			if (!m->vertices.empty()) {
				file << FILE_MESH_VERT << "\n";
				file << m->vertices.size() << "\n";
				for (auto v : m->vertices) {
					file << "\t" << v.x << " " << v.y << " " << v.z << "\n";
				}
			}

			if (!m->colorComponent.colors.empty()) {
				file << FILE_MESH_COLOR << "\n";
				file << m->colorComponent.colors.size() << "\n";
				for (auto v : m->colorComponent.colors) {
					file << "\t" << v.x << " " << v.y << " " << v.z << " " << v.a << "\n";
				}
			}

			if (!m->indices.empty()) {
				file << FILE_MESH_IDX << "\n";
				file << m->indices.size() << "\n";
				for (auto v : m->indices) {
					file << "\t" << v << "\n";
				}
			}

			file << "\n";
			index++;
		}
		file.close();
	}
}
