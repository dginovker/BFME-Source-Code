#pragma once

class Coord3D {
public:
    ~Coord3D();

    void zero();
    Coord3D &SetZero();

    float x;
    float y;
    float z;
};
