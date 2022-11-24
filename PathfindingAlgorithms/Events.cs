using Pathfinding;
using Pathfinding.AStar;
using PathfindingAlgorithms.CommonData;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;

namespace PathfindingAlgorithms
{
    public class Events
    {
        public static int ClickCount { get; private set; }
        private static GridInfo _gridInfo = new GridInfo(new List<Point>(), 30, 30);

        public void OnSquareClicked(Point square)
        {
            if (ClickCount >= 2)
            {
                ExternalCalls.ResetGrid();
                ClickCount = 0;
            }

            if (ClickCount == 0)
            {
                _gridInfo.Start = square;
                ExternalCalls.ChangeColor(square, new Vectors.Vector3(0.0f, 0.224f, 0.840f));
                ExternalCalls.ReDraw();
                ClickCount++;
            }
            
            else if (ClickCount == 1)
            {
                _gridInfo.End = square;
                ExternalCalls.ChangeColor(square, new Vectors.Vector3(0.840f, 0.0f, 0.0f));
                ExternalCalls.ReDraw();

                AStar aStar = new AStar();
                IEnumerable<INode> test = null;
                Thread t = new Thread(() => { test = aStar.FindPathDiagonal(_gridInfo); });
                t.Start();

                while (t.IsAlive)
                {
                    
                }

                var pointArray = new Point[test.Count()];

                int a = 0;
                foreach (var item in test)
                {
                    pointArray[a] = item.Coord;
                    a++;
                }

                for (int i = 0; i < pointArray.Length; i++)
                {
                    ExternalCalls.ChangeColor(pointArray[i], new Vectors.Vector3(0.1f, 1.0f, 0.4f));
                }

                ExternalCalls.ReDraw();
                ClickCount++;
            }

        }
    }
}
