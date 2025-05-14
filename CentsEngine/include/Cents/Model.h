#pragma once
#include <string>
#include "Common.h"
#include "Mesh.h"

class Model
{
public:
    Model(const std::string& modelFile);
    ~Model();

    void Draw();

private:

    void LoadModel(const std::string& filepath);

    std::vector<Mesh*> m_meshes;
};