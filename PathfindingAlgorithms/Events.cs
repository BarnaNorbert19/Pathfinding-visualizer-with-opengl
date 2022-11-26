using Pathfinding;
using Pathfinding.AStar;
using PathfindingAlgorithms.CommonData;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Threading;

namespace PathfindingAlgorithms
{
    public class Events
    {
        public static int ClickCount { get; private set; }
        private static GridInfo _gridInfo = new GridInfo(new List<Point>(), 30, 30);

        public void OnSquareClicked(Point square, bool shiftState)
        {
            if (ClickCount >= 2)
            {
                ExternalCalls.ResetGrid();
                _gridInfo = new GridInfo(new List<Point>(), 30, 30);
                ClickCount = 0;
            }

            if (shiftState)
            {
                if (square.X < 0 || square.Y < 0 || _gridInfo.UnwalkablePos.Contains(square))
                    return;

                _gridInfo.UnwalkablePos.Add(square);
                ExternalCalls.ChangeColor(square, new Vectors.Vector3(0.0f, 0.0f, 0.0f));
                ExternalCalls.ReDraw();
            }

            else if (ClickCount == 0)
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
            path = aStar.FindPathDiagonal(_gridInfo).ToList();
            
            RecolorVisitedNodes(aStar);
            RecolorPath(path);

            ExternalCalls.ReDraw();
        }

        private void RecolorVisitedNodes(PathfindingBase visitedNodes)
        {
            //Don't need to remove end since it can never be part of VisitedNodes
            var visitedNodesFiltered = visitedNodes.VisitedNodes.Where(s => s.Coord != _gridInfo.Start);

            //Recolor squares
            foreach (var item in visitedNodesFiltered)
            {
                ExternalCalls.ChangeColor(item.Coord, new Vectors.Vector3(0.840f, 0.826f, 0.00f));
            }
        }

        private void RecolorPath(List<INode> path)
        {
            //Remove start and end points from the lists, so they won't be recolored
            path.RemoveAt(0);
            path.RemoveAt(path.Count - 1);

            //Recolor squares
            for (int i = 0; i < path.Count; i++)
                ExternalCalls.ChangeColor(path[i].Coord, new Vectors.Vector3(0.0723f, 0.620f, 0.00f));
        }
    }
}
