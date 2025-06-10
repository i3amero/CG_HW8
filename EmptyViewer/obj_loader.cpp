#include "obj_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

bool loadObj(const std::string& filename,
    std::vector<float>& out_vertices,
    std::vector<float>& out_normals,
    std::vector<unsigned int>& out_indices) {
    std::ifstream in(filename);
    if (!in) return false;

    std::vector<float> temp_vertices;
    std::vector<float> temp_normals;
    std::vector<unsigned int> temp_indices;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            temp_vertices.push_back(x);
            temp_vertices.push_back(y);
            temp_vertices.push_back(z);
        }
        else if (type == "vn") {
            float nx, ny, nz;
            ss >> nx >> ny >> nz;
            temp_normals.push_back(nx);
            temp_normals.push_back(ny);
            temp_normals.push_back(nz);
        }
        else if (type == "f") {
            std::string v1, v2, v3;
            ss >> v1 >> v2 >> v3;
            for (const auto& v : { v1, v2, v3 }) {
                int v_idx = 0, n_idx = 0;
                sscanf(v.c_str(), "%d//%d", &v_idx, &n_idx);
                out_vertices.push_back(temp_vertices[(v_idx - 1) * 3 + 0]);
                out_vertices.push_back(temp_vertices[(v_idx - 1) * 3 + 1]);
                out_vertices.push_back(temp_vertices[(v_idx - 1) * 3 + 2]);

                out_normals.push_back(temp_normals[(n_idx - 1) * 3 + 0]);
                out_normals.push_back(temp_normals[(n_idx - 1) * 3 + 1]);
                out_normals.push_back(temp_normals[(n_idx - 1) * 3 + 2]);

                out_indices.push_back(out_indices.size());
            }
        }
    }

    return true;
}
