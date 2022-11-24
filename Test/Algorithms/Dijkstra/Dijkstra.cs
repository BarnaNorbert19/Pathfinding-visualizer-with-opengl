using PathfindingAlgorithms.Algorithms.Model;
using PathfindingAlgorithms.CommonData;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace Pathfinding.Dijkstra
{
    public class Dijkstra : PathfindingBase
    {
        public override IEnumerable<INode> UnvisitedNodes { get; set; }
        public override IEnumerable<INode> VisitedNodes { get; set; }

        public async override Task<IEnumerable<INode>> FindPathDiagonal(GridInfo meshInfo)
        {
            var visited = new List<DijkstraNode>();
            var unvisited = new List<DijkstraNode>
            {
                new DijkstraNode(meshInfo.Start, null)
            };

            while (unvisited.Count > 0)
            {
                DijkstraNode cur_node = unvisited[unvisited.Count - 1];
                unvisited.Remove(cur_node);
                var neighbours = GetNeighboursDiagonal(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<DijkstraNode>();

                foreach (var node in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == node.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == node.Coord))
                        continue;

                    var targetNode = visited.FirstOrDefault(s => s.Coord == node.Coord);
                    if (!(targetNode is null))
                    {
                        if (cur_node.ParentNode.G > targetNode.G)
                        {
                            cur_node.ParentNode = targetNode;
                            cur_node.G = Distance(cur_node.Coord, cur_node.ParentNode.Coord) + targetNode.G;
                            /*if (MainW.ShowG)
                                await AddGTextToNode(cur_node);*/
                        }
                        continue;
                    }

                    unvisited.Insert(0, node);
                }

                visited.Add(cur_node);

                if (cur_node.Coord == meshInfo.End)
                {
                    UnvisitedNodes = unvisited;
                    VisitedNodes = visited;
                    return CalculatePath(cur_node);
                }
                 
            }

            return null;
        }

        public async override Task<IEnumerable<INode>> FindPathNoDiagonal(GridInfo meshInfo)
        {
            var visited = new List<DijkstraNode>();
            var unvisited = new List<DijkstraNode>
            {
                new DijkstraNode(meshInfo.Start, null)
            };

            while (unvisited.Count > 0)
            {
                DijkstraNode cur_node = unvisited[unvisited.Count - 1];
                unvisited.Remove(cur_node);
                var neighbours = GetNeighbours(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<DijkstraNode>();

                foreach (var node in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == node.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == node.Coord))
                        continue;

                    var targetNode = visited.FirstOrDefault(s => s.Coord == node.Coord);
                    if (!(targetNode is null))
                    {
                        if (cur_node.ParentNode.G > targetNode.G)
                        {
                            cur_node.ParentNode = targetNode;
                            cur_node.G = Distance(cur_node.Coord, cur_node.ParentNode.Coord) + targetNode.G;
                        }
                        continue;
                    }

                    unvisited.Insert(0, node);
                }

                visited.Add(cur_node);

                if (cur_node.Coord == meshInfo.End)
                {
                    UnvisitedNodes = unvisited;
                    VisitedNodes = visited;
                    return CalculatePath(cur_node);
                }
            }

            return null;
        }

        protected override IEnumerable<INode> GetNeighbours(int horizontallenght, int verticallenght, INode mainNode, ICoordinate end)
        {
            List<DijkstraNode> result = new List<DijkstraNode>();
            //Define grid bounds
            int rowMinimum = mainNode.Coord.X - 1 < 0 ? mainNode.Coord.X : mainNode.Coord.X - 1;
            int rowMaximum = mainNode.Coord.X + 1 > horizontallenght ? mainNode.Coord.X : mainNode.Coord.X + 1;
            int columnMinimum = mainNode.Coord.Y - 1 < 0 ? mainNode.Coord.Y : mainNode.Coord.Y - 1;
            int columnMaximum = mainNode.Coord.Y + 1 > verticallenght ? mainNode.Coord.Y : mainNode.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                {
                    var curPoint = new Point(i, j);
                    if ((i != mainNode.Coord.X || j != mainNode.Coord.Y) && (mainNode.Coord.X == curPoint.X || mainNode.Coord.Y == curPoint.Y))
                        result.Add(new DijkstraNode(curPoint, mainNode, Distance(curPoint, mainNode.Coord) + mainNode.G));
                }
            return result;
        }

        protected override IEnumerable<INode> GetNeighboursDiagonal(int horizontallenght, int verticallenght, INode mainNode, ICoordinate end)
        {
            List<DijkstraNode> result = new List<DijkstraNode>();
            //Define grid bounds
            int rowMinimum = mainNode.Coord.X - 1 < 0 ? mainNode.Coord.X : mainNode.Coord.X - 1;
            int rowMaximum = mainNode.Coord.X + 1 > horizontallenght ? mainNode.Coord.X : mainNode.Coord.X + 1;
            int columnMinimum = mainNode.Coord.Y - 1 < 0 ? mainNode.Coord.Y : mainNode.Coord.Y - 1;
            int columnMaximum = mainNode.Coord.Y + 1 > verticallenght ? mainNode.Coord.Y : mainNode.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                    if (i != mainNode.Coord.X || j != mainNode.Coord.Y)
                    {
                        var cur_point = new Point(i, j);
                        result.Add(new DijkstraNode(cur_point, mainNode, Distance(cur_point, mainNode.Coord) + mainNode.G));
                    }
            return result;
        }
    }
}
