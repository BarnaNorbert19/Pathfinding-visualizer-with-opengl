using Pathfinding.AStar;
using System;

namespace PathfindingAlgorithms.CommonData
{
    public class Vectors
    {
        public struct Vector3
        {
            public float X;
            public float Y;
            public float Z;

            public Vector3(float x, float y, float z)
            {
                X = x;
                Y = y;
                Z = z;
            }
        }

        public struct Vector2
        {
            public float X { get; set; }
            public float Y { get; set; }

            public Vector2(float x, float y)
            {
                X = x;
                Y = y;
            }
        }
    }
}
