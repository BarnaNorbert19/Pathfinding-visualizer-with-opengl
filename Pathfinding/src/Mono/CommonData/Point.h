#pragma once
struct Point
{
    int X;
    int Y;

    Point(int X = 0, int Y = 0) : X(X), Y(Y)
    { }

    Point& operator=(const Point& a)
    {
        X = a.X;
        Y = a.Y;
        return *this;
    }

    Point operator+(const Point& a) const
    {
        return Point(a.X + X, a.Y + Y);
    }

    bool operator==(const Point& a) const
    {
        return (X == a.X && Y == a.Y);
    }
};