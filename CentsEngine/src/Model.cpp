#include "Model.h"
#include "Common.h"
#include <tiny_obj_loader.h>

Model::Model(const std::string& modelFile)
{
    LoadModel(modelFile);
}

Model::~Model()
{
    for (Mesh* mesh : m_meshes)
    {
        delete mesh;
    }

    m_meshes.clear();
}

void Model::Draw()
{
    for (Mesh* mesh : m_meshes)
    {
        mesh->Draw();
    }
}

void Model::LoadModel(const std::string& filepath)
{
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filepath, reader_config))
    {
        if (!reader.Error().empty())
        {
            printf("TinyObjReader: %s", reader.Error().c_str());
        }

        return;
    }

    if (!reader.Warning().empty())
    {
        printf("TinyObjReader: %s", reader.Warning().c_str());
        return;
    }

    const tinyobj::attrib_t& attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++)
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<uint16> indices;

        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                glm::vec3 vertex
                {
                    attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                    attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                    attrib.vertices[3 * size_t(idx.vertex_index) + 2]
                };
                vertices.push_back(vertex);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    glm::vec3 normal
                    {
                        attrib.normals[3 * size_t(idx.normal_index) + 0],
                        attrib.normals[3 * size_t(idx.normal_index) + 1],
                        attrib.normals[3 * size_t(idx.normal_index) + 2]
                    };
                    normals.push_back(normal);
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    glm::vec2 texCoord
                    {
                        attrib.texcoords[2 * size_t(idx.texcoord_index) + 0],
                        attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]
                    };
                    texCoords.push_back(texCoord);
                }

                indices.push_back((uint16)indices.size());
            }

            index_offset += fv;
        }

        Mesh* mesh = new Mesh(vertices, normals, texCoords, indices);
        m_meshes.push_back(mesh);
    }
}
