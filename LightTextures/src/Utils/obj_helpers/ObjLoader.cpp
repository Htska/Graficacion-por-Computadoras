#include "Utils/obj_helpers/ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <string.h> // Para usar memcmp
#include <map>

struct PackedVertex
{
    int v, t, n;

    bool operator<(const PackedVertex &that) const
    {
        if (v != that.v)
            return v < that.v;
        if (t != that.t)
            return t < that.t;
        return n < that.n;
    }
};

int resolveIndex(int idx, int size)
{
    if (idx > 0)
    {
        return idx - 1;
    }
    else
    {
        return size + idx;
    }
}

ObjLoader::ObjLoader() {}

void ObjLoader::parseOBJ(const char *filePath)
{
    float x, y, z;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream)
    {
        std::cerr << "PROBLEM OPENING THE OBJ FILE" << std::endl;
        return;
    }

    // La llave es el objeto PackedVertex y el valor rl indice
    std::map<PackedVertex, unsigned int> vertexToOutIndex;
    std::string line;

    auto addVertex = [&](const PackedVertex &packed) -> unsigned int
    {
        auto it = vertexToOutIndex.find(packed);
        if (it != vertexToOutIndex.end())
        {
            return it->second;
        }

        // La posicion
        triangleVerts.push_back(vertVals[packed.v * 3]);
        triangleVerts.push_back(vertVals[packed.v * 3 + 1]);
        triangleVerts.push_back(vertVals[packed.v * 3 + 2]);

        // Textura
        if (packed.t >= 0)
        {
            textureCoords.push_back(stVals[packed.t * 2]);
            textureCoords.push_back(stVals[packed.t * 2 + 1]);
        }
        else
        {
            textureCoords.push_back(0.0f);
            textureCoords.push_back(0.0f);
        }

        // Normales
        if (packed.n >= 0)
        {
            normals.push_back(normVals[packed.n * 3]);
            normals.push_back(normVals[packed.n * 3 + 1]);
            normals.push_back(normVals[packed.n * 3 + 2]);
        }
        else
        {
            normals.push_back(0.0f);
            normals.push_back(0.0f);
            normals.push_back(0.0f);
        }

        unsigned int newIndex = (unsigned int)(triangleVerts.size() / 3) - 1;
        vertexToOutIndex[packed] = newIndex;
        return newIndex;
    };

    while (std::getline(fileStream, line))
    {
        if (line.compare(0, 2, "v ") == 0)
        {
            std::stringstream ss(line.substr(2));
            ss >> x >> y >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        else if (line.compare(0, 3, "vt ") == 0)
        {
            std::stringstream ss(line.substr(3));
            ss >> x >> y;
            stVals.push_back(x);
            stVals.push_back(y);
        }
        else if (line.compare(0, 3, "vn ") == 0)
        {
            std::stringstream ss(line.substr(3));
            ss >> x >> y >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        else if (line.compare(0, 2, "f ") == 0)
        {
            std::stringstream ss(line.substr(2));
            std::string oneCorner;
            std::vector<PackedVertex> faceVerts; // guarda los vértices de la cara

            while (ss >> oneCorner)
            {
                std::string v_str, t_str, n_str;
                std::stringstream cornerSS(oneCorner);
                std::getline(cornerSS, v_str, '/');
                std::getline(cornerSS, t_str, '/');
                std::getline(cornerSS, n_str, '/');

                PackedVertex packed;
                packed.v = resolveIndex(std::stoi(v_str), (int)vertVals.size() / 3);
                packed.t = !t_str.empty() ? resolveIndex(std::stoi(t_str), (int)stVals.size() / 2) : -1;
                packed.n = !n_str.empty() ? resolveIndex(std::stoi(n_str), (int)normVals.size() / 3) : -1;

                faceVerts.push_back(packed);
            }

            if (faceVerts.size() == 3)
            {
                // Triángulo directo
                for (const auto &pv : faceVerts)
                {
                    indices.push_back(addVertex(pv));
                }
            }
            else if (faceVerts.size() > 3)
            {

                for (size_t i = 1; i < faceVerts.size() - 1; ++i)
                {
                    indices.push_back(addVertex(faceVerts[0]));
                    indices.push_back(addVertex(faceVerts[i]));
                    indices.push_back(addVertex(faceVerts[i + 1]));
                }
            }
            // Si es línea (2 vértices) o punto (1 vértice) se ignora
        }
    }
    max.push_back(vertVals[0]);
    max.push_back(vertVals[1]);
    max.push_back(vertVals[2]);
    min.push_back(vertVals[0]);
    min.push_back(vertVals[1]);
    min.push_back(vertVals[2]);
    for (int i = 0; i<(int)vertVals.size()-1;i+=3){
        if (vertVals[i] > max[0])
            max[0] = vertVals[i];
        if (vertVals[i+1] > max[1])
            max[1] = vertVals[i+1];
        if (vertVals[i+2] > max[2])
            max[2] = vertVals[i+2];
        if (vertVals[i] < min[0])
            min[0] = vertVals[i];
        if (vertVals[i+1] < min[1])
            min[1] = vertVals[i+1];
        if (vertVals[i+2] < min[2])
            min[2] = vertVals[i+2];  
    }
}

// getters
int ObjLoader::getNumVertices() { return (triangleVerts.size() / 3); }
std::vector<float> ObjLoader::getVertices() { return triangleVerts; }
std::vector<float> ObjLoader::getTextureCoordinates() { return textureCoords; }
std::vector<float> ObjLoader::getNormals() { return normals; }
std::vector<unsigned int> ObjLoader::getIndices() { return indices; }