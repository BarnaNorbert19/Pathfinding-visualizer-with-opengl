using Pathfinding.AStar;
using PathfindingAlgorithms.Algorithms.Model;
using System;

namespace PathfindingAlgorithms.CommonData
{
    public class Vectors
    {
        public class Vector3
        {
            public float X;
            public float Y;
            public float Z;
        }

        public class Vector2 : ICoordinate
        {
            public int X { get; set; }
            public int Y { get; set; }

            public Vector2(int x, int y)
            {
                X = x;
                Y = y;
            }
        }
    }
}
