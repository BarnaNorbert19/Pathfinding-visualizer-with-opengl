using PathfindingAlgorithms.Algorithms.Model;

namespace PathfindingAlgorithms.CommonData
{
    public struct Point : ICoordinate
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
}
