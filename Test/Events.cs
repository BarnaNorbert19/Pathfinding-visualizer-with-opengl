using Pathfinding;
using Pathfinding.AStar;
using PathfindingAlgorithms.CommonData;
using System;
using System.Linq;

namespace PathfindingAlgorithms
{
    public class Events
    {
        public static int ClickCount { get; private set; } = 0;
        private static GridInfo _gridInfo = new GridInfo();

        public void OnSquareClicked(Point square)
        {
            Console.WriteLine("square value: X->" + square.X + " Y->" + square.Y);
            Console.WriteLine("Click count: " + ClickCount);
            //ExternalCalls.ChangeColor(new Point(5, 2), new Vectors.Vector3(0.1f, 0.7f, 1f));

            if (ClickCount == 0)
            {
                _gridInfo.Start = square;
                Console.WriteLine("case 0 hit !");
                Console.WriteLine("Click count: " + ClickCount);
                ClickCount++;
            }
            
            else if (ClickCount == 1)
            {
                _gridInfo.End = square;
                Console.WriteLine("case 1 hit !");
                Console.WriteLine("Click count: " + ClickCount);
                ClickCount++;
            }

            else if (ClickCount == 2)
            {
                Console.WriteLine("case 2 hit !");
                Console.WriteLine("Click count: " + ClickCount);

                AStar aStar = new AStar();

                var test = aStar.FindPathDiagonal(_gridInfo).GetAwaiter().GetResult().Cast<AStarNode>();
                var test1 = new Point[test.Count()];

                int a = 0;
                foreach (var item in test)
                {
                    test1[a] = (Point)item.Coord;
                }
                ClickCount++;
            }

        }
    }
}
