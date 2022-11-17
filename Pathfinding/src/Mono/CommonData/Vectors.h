#pragma once
class Vectors
{
public:
    struct Vector2
    {
        float X;
        float Y;

        Vector2(float X = 0, float Y = 0) : X(X), Y(Y)
        { }

        Vector2& operator=(const Vector2& a)
        {
            X = a.X;
            Y = a.Y;
            return *this;
        }

        Vector2 operator+(const Vector2& a) const
        {
            return Vector2(a.X + X, a.Y + Y);
        }

        bool operator==(const Vector2& a) const
        {
            return (X == a.X && Y == a.Y);
        }
    };

    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3(float X = 0, float Y = 0, float Z = 0) : X(X), Y(Y), Z(Z)
        { }

        Vector3& operator=(const Vector3& a)
        {
            X = a.X;
            Y = a.Y;
            Z = a.Z;
            return *this;
        }

        Vector3 operator+(const Vector3& a) const
        {
            return Vector3(a.X + X, a.Y + Y, a.Z + Z);
        }

        bool operator==(const Vector3& a) const
        {
            return (X == a.X && Y == a.Y && Z == a.Z);
        }
    };
};

