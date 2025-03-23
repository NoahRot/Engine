#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <inttypes.h>
#include <fstream>
#include <stack>

#include "Log/Logger.hpp"
#include "mat/BaseVector.hpp"
#include "mat/Vector.hpp"
#include "mat/Complex.hpp"
#include "mat/Quaternion.hpp"
#include "mat/Matrix.hpp"

namespace ora {

struct DataNode {

    DataNode();

    DataNode(const std::string& content_);

    std::string content;
    std::unordered_map<std::string, DataNode> children;

    bool has_content() const;

    DataNode& operator[](const std::string& name);

    DataNode& operator[](const char* name) ;

    DataNode& operator=(const std::string& str);

    operator std::string();

    DataNode& operator=(int value);

    operator int();

    DataNode& operator=(uint32_t value);

    operator uint32_t();

    DataNode& operator=(float value);

    operator float();

    DataNode& operator=(double value);

    operator double();

    template<typename T, uint32_t N>
    DataNode& operator=(const mat::BaseVector<T,N>& vec);

    template<typename T, uint32_t N>
    operator mat::BaseVector<T,N>();

    template<typename T, uint32_t N>
    operator mat::Vector<T,N>();

    template<typename T>
    operator mat::Complex<T>();

    template<typename T>
    operator mat::Quaternion<T>();

    template<typename T, uint32_t N, uint32_t M>
    DataNode& operator=(const mat::Matrix<T,N,M>& mat);

    template<typename T, uint32_t N, uint32_t M>
    operator mat::Matrix<T,N,M>();

};

class DataFile {
public:
    DataFile();

    DataFile(const DataNode& node);

    DataFile(const std::string& path);

    DataNode& get();

    bool save_txt(const std::string& path);

    bool load_txt(const std::string& path);

private:
    void write_txt(const DataNode& node, int depth, std::fstream& stream);

    void read_txt(std::fstream& stream);

    DataNode m_root;
};



template<typename T, uint32_t N>
DataNode& DataNode::operator=(const mat::BaseVector<T,N>& vec) {
    content = "";
    for (auto i : vec) {
        content += std::to_string(i) + " ";
    }
    return *this;
}

template<typename T, uint32_t N>
DataNode::operator mat::BaseVector<T,N>() {
    mat::BaseVector<T, N> vec;

    std::istringstream iss(content);
    T value;
    uint32_t index = 0;

    // Read values from content and store in the vector
    while (iss >> value && index < N) {
        vec[index] = value;
        index++;
    }

    return vec;
}

template<typename T, uint32_t N>
DataNode::operator mat::Vector<T,N>() {
    mat::BaseVector<T, N> vec;

    std::istringstream iss(content);
    T value;
    uint32_t index = 0;

    // Read values from content and store in the vector
    while (iss >> value && index < N) {
        vec[index] = value;
        index++;
    }

    return vec;
}

template<typename T>
DataNode::operator mat::Complex<T>() {
    mat::Complex<T> vec;

    std::istringstream iss(content);
    T value;
    uint32_t index = 0;

    // Read values from content and store in the vector
    while (iss >> value && index < 2) {
        vec[index] = value;
        index++;
    }

    return vec;
}

template<typename T>
DataNode::operator mat::Quaternion<T>() {
    mat::Quaternion<T> vec;

    std::istringstream iss(content);
    T value;
    uint32_t index = 0;

    // Read values from content and store in the vector
    while (iss >> value && index < 4) {
        vec[index] = value;
        index++;
    }

    return vec;
}

template<typename T, uint32_t N, uint32_t M>
DataNode& DataNode::operator=(const mat::Matrix<T,N,M>& mat) {
    content = "";
    for (auto i : mat) {
        content += std::to_string(i) + " ";
    }
    return *this;
}

template<typename T, uint32_t N, uint32_t M>
DataNode::operator mat::Matrix<T,N,M>() {
    mat::Matrix<T,N,M> mat;

    std::istringstream iss(content);
    T value;
    uint32_t row = 0, col = 0;

    // Read values from content and store in the vector
    while (iss >> value) {
        mat(row, col) = value; // Populate the matrix
        col++;
        if (col == M) { // Move to next row
            col = 0;
            row++;
        }
        if (row == N) break; // Stop if full
    }

    return mat;
}


}