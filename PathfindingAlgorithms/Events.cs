using Pathfinding;
using Pathfinding.AStar;
using Pathfinding.BreadthFirst;
using Pathfinding.DepthFirst;
using Pathfinding.Dijkstra;
using PathfindingAlgorithms.CommonData;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;

namespace PathfindingAlgorithms
{
    public class Events
    {
        public static int ClickCount { get; private set; }
        private static GridInfo _gridInfo = new GridInfo(new List<Point>(), 30, 30);

        public void OnSquareClicked(Point square, bool shiftState, AlgoType algoType)
        {
            //if pathfinding already done -> clicked twice, hence there is some path on screen
            if (ClickCount >= 2)
            {
                //reset screen and basic info
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


                PathFinding(algoType);
                ClickCount++;
            }

        }

        private void PathFinding(AlgoType type)
        {
            List<INode> path;
            PathfindingBase algoArgs;
            switch (type)
            {
                case AlgoType.AStar:
                    {
                        algoArgs = new AStar();
                        path = algoArgs.FindPathDiagonal(_gridInfo).ToList();
                        break;
                    }
                case AlgoType.Dijkstra:
                    {
                        algoArgs = new Dijkstra();
                        path = algoArgs.FindPathDiagonal(_gridInfo).ToList();
                        break;
                    }
                case AlgoType.DepthFirst:
                    {
                        algoArgs = new DFS();
                        path = algoArgs.FindPathDiagonal(_gridInfo).ToList();
                        break;
                    }
                case AlgoType.BreadthFirst:
                    {
                        algoArgs = new BFS();
                        path = algoArgs.FindPathDiagonal(_gridInfo).ToList();
                        break;
                    }
                default:
                    {
                        algoArgs = new AStar();
                        path = algoArgs.FindPathDiagonal(_gridInfo).ToList();
                    }
                    break;
            }

            RecolorVisitedNodes(algoArgs);
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
