using Pathfinding;
using Pathfinding.AStar;
using PathfindingAlgorithms.CommonData;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Threading;

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


                PathFinding();
                ClickCount++;
            }

        }

        private void PathFinding()
        {
            AStar aStar = new AStar();
            List<INode> path = null;
            Thread t = new Thread(() => { path = aStar.FindPathDiagonal(_gridInfo).ToList(); });
            t.Start();

            while (t.IsAlive)
            {

            }
            path.RemoveAt(0);
            path.RemoveAt(path.Count - 1);

            foreach (var item in aStar.VisitedNodes)
            {
                ExternalCalls.ChangeColor(item.Coord, new Vectors.Vector3(0.840f, 0.826f, 0.00f));
            }

            for (int i = 0; i < path.Count; i++)
                ExternalCalls.ChangeColor(path[i].Coord, new Vectors.Vector3(0.0723f, 0.620f, 0.00f));

            ExternalCalls.ReDraw();
        }
    }
}
