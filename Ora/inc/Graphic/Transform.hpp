#pragma once 

#include "mat/Math.hpp"

namespace ora {

struct Transform2D {
    mat::Vec3f position;
    mat::Vec3f centre;
    float rotation;
    float scale;
};

mat::Mat4f model_matrix(const Transform2D& tra) {
    return mat::dot(mat::translate3<float>(tra.position), mat::dot(mat::rotateZ<float>(tra.rotation), mat::translate3<float>(-tra.centre)));
}

}