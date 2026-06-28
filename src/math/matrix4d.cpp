#include "matrix4d.h"

Matrix4D::Matrix4D()
{
}

Matrix4D::Matrix4D(bool identity)
{
    unsigned int zero = 0;

    if (identity) {
        unsigned int one = 0x3f800000;

        ((unsigned int *)values)[0] = one;
        ((unsigned int *)values)[1] = zero;
        ((unsigned int *)values)[2] = zero;
        ((unsigned int *)values)[3] = zero;
        ((unsigned int *)values)[4] = zero;
        ((unsigned int *)values)[5] = one;
        ((unsigned int *)values)[6] = zero;
        ((unsigned int *)values)[7] = zero;
        ((unsigned int *)values)[8] = zero;
        ((unsigned int *)values)[9] = zero;
        ((unsigned int *)values)[10] = one;
        ((unsigned int *)values)[11] = zero;
        ((unsigned int *)values)[12] = zero;
        ((unsigned int *)values)[13] = zero;
        ((unsigned int *)values)[14] = zero;
        ((unsigned int *)values)[15] = one;
    }
}

Coord3D &Matrix4D::GetXVector(Coord3D &out) const
{
    out.x = values[0];
    out.y = values[4];
    out.z = values[8];
    return out;
}

Coord3D &Matrix4D::GetYVector(Coord3D &out) const
{
    out.x = values[1];
    out.y = values[5];
    out.z = values[9];
    return out;
}

Coord3D &Matrix4D::GetZVector(Coord3D &out) const
{
    out.x = values[2];
    out.y = values[6];
    out.z = values[10];
    return out;
}

Coord3D &Matrix4D::GetTranslationVector(Coord3D &out) const
{
    out.x = values[3];
    out.y = values[7];
    out.z = values[11];
    return out;
}

Matrix4D &Matrix4D::SetIdentity()
{
    unsigned int zero = 0;
    unsigned int one = 0x3f800000;

    ((unsigned int *)values)[0] = one;
    ((unsigned int *)values)[1] = zero;
    ((unsigned int *)values)[2] = zero;
    ((unsigned int *)values)[3] = zero;
    ((unsigned int *)values)[4] = zero;
    ((unsigned int *)values)[5] = one;
    ((unsigned int *)values)[6] = zero;
    ((unsigned int *)values)[7] = zero;
    ((unsigned int *)values)[8] = zero;
    ((unsigned int *)values)[9] = zero;
    ((unsigned int *)values)[10] = one;
    ((unsigned int *)values)[11] = zero;
    ((unsigned int *)values)[12] = zero;
    ((unsigned int *)values)[13] = zero;
    ((unsigned int *)values)[14] = zero;
    ((unsigned int *)values)[15] = one;
    return *this;
}
