#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <glm/glm.hpp>

class ObjLoader{

private: 

    // valores leidos de un OBJ 
    std::vector<float> vertVals; 
    std::vector<float> stVals; 
    std::vector<float> normVals; 

    // valores almacenados para ser usados como vertex attributes 
    std::vector<float> triangleVerts; 
    std::vector<float> textureCoords; 
    std::vector<float> normals;
    std::vector<float> max;
    std::vector<float> min; 

    std::vector<unsigned int> indices; 

public: 

    ObjLoader();
    void parseOBJ(const char *filePath);
    int getNumVertices(); 
    std::vector<float> getVertices(); 
    std::vector<float> getTextureCoordinates(); 
    std::vector<float> getNormals();
    std::vector<unsigned int> getIndices();
    std::vector<float> getMax(){return max;}
    std::vector<float> getMin(){return min;} 
};

#endif