#pragma once

#include "coord3d.h"

class Matrix4D {
public:
    Matrix4D();
    Matrix4D(bool identity);

    Coord3D &GetXVector(Coord3D &out) const;
    Coord3D &GetYVector(Coord3D &out) const;
    Coord3D &GetZVector(Coord3D &out) const;
    Coord3D &GetTranslationVector(Coord3D &out) const;
    Matrix4D &SetIdentity();

    float values[16];
};
