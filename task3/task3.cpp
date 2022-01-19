#include <iostream>
#include <glm/glm.hpp>

static constexpr int NVERTS = 4;

glm::vec3 calculateNormal(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
    auto vecA = p1 - p2;
    auto vecB = p3 - p2;
    return glm::cross(vecA, vecB);
}

//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
void calc_mesh_normals(glm::vec3* normals, const glm::vec3* verts, const int* faces, int nverts, int nfaces) {
    for (int i = 0; i < nfaces; i = i + 3) {
        auto indA = faces[i];
        auto indB = faces[i + 1];
        auto indC = faces[i + 2];

        auto normal = calculateNormal(verts[indA], verts[indB], verts[indC]);
        normals[indA] += normal;
        normals[indB] += normal;
        normals[indC] += normal;
    }

    for (int i = 0; i < nverts; ++i) {
        normals[i] = glm::normalize(normals[i]);
    }
}

int main() {
    glm::vec3 normals[NVERTS] = {glm::vec3(0, 0, 0),
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 0, 0)};
    glm::vec3 verts[NVERTS];

    verts[0] = glm::vec3(0, 0, 5);
    verts[1] = glm::vec3(-5, 0, 0);
    verts[2] = glm::vec3(0, 5, 0);
    verts[3] = glm::vec3(5, 0, 0);

    int faces[NVERTS * 3];
    faces[0] = 0;
    faces[1] = 1;
    faces[2] = 2;

    faces[3] = 0;
    faces[4] = 2;
    faces[5] = 3;

    faces[6] = 0;
    faces[7] = 1;
    faces[8] = 3;

    faces[9] = 1;
    faces[10] = 2;
    faces[11] = 3;

    calc_mesh_normals(normals, verts, faces, 4, 12);

    for (int i = 0; i < NVERTS; ++i) {
        std::cout << normals[i].x << ' '<< normals[i].y << ' ' << normals[i].z << '\n';
    }
    return 0;
}
