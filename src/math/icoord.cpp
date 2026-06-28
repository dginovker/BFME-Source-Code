#include "icoord.h"

ICoord2DBase &ICoord2DBase::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

ICoord2D::ICoord2D()
{
}

ICoord2D::ICoord2D(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
}

ICoord2D::ICoord2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

ICoord2D &ICoord2D::operator=(const ICoord2D &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

ICoord2D &ICoord2D::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

bool ICoord2D::operator==(const ICoord2DBase &that) const
{
    return x == that.x && y == that.y;
}

bool ICoord2D::operator!=(const ICoord2DBase &that) const
{
    return x != that.x || y != that.y;
}

ICoord3D::ICoord3D()
{
}

ICoord3D::ICoord3D(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void ICoord3D::zero()
{
    x = 0;
    y = 0;
    z = 0;
}
