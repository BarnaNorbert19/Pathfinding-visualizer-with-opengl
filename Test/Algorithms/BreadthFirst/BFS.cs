using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System;
using PathfindingAlgorithms.Algorithms.Model;
using PathfindingAlgorithms.CommonData;

namespace Pathfinding.BreadthFirst
{
    public class BFS : PathfindingBase
    {
        public override IEnumerable<INode> UnvisitedNodes { get; set; }
        public override IEnumerable<INode> VisitedNodes { get; set; }

        public async override Task<IEnumerable<INode>> FindPathDiagonal(GridInfo meshInfo)
        {
            var visited = new List<BFSNode>();
            var unvisited = new Queue<BFSNode>();
            unvisited.Enqueue(new BFSNode(meshInfo.Start, null));

            while (unvisited.Count > 0)
            {
                BFSNode cur_node = unvisited.Dequeue();

                if (cur_node.Coord == meshInfo.End)
                {
                    UnvisitedNodes = unvisited;
                    VisitedNodes = visited;
                    return CalculatePath(cur_node);
                }

                var neighbours = GetNeighboursDiagonal(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<BFSNode>();

                foreach (var node in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == node.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == node.Coord))
                        continue;

                    if (visited.Any(s => s.Coord == node.Coord))
                        continue;

                    unvisited.Enqueue(node);
                }

                visited.Add(cur_node);
            }

            return null;
        }

        public async override Task<IEnumerable<INode>> FindPathNoDiagonal(GridInfo meshInfo)
        {
            var visited = new List<BFSNode>();
            var unvisited = new Queue<BFSNode>();
            unvisited.Enqueue(new BFSNode(meshInfo.Start, null));

            while (unvisited.Count > 0)
            {
                BFSNode cur_node = unvisited.Dequeue();

                if (cur_node.Coord == meshInfo.End)
                {
                    VisitedNodes = visited;
                    UnvisitedNodes = unvisited;
                    return CalculatePath(cur_node);
                }

                var neighbours = GetNeighbours(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<BFSNode>();

                foreach (var node in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == node.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == node.Coord))
                        continue;

                    if (visited.Any(s => s.Coord == node.Coord))
                        continue;

                    unvisited.Enqueue(node);
                }

                visited.Add(cur_node);
            }

            return null;
        }

        protected override IEnumerable<INode> GetNeighbours(int horizontallenght, int verticallenght, INode main_node, ICoordinate end)
        {
            List<BFSNode> result = new List<BFSNode>();
            //Define grid bounds
            int rowMinimum = main_node.Coord.X - 1 < 0 ? main_node.Coord.X : main_node.Coord.X - 1;
            int rowMaximum = main_node.Coord.X + 1 > horizontallenght ? main_node.Coord.X : main_node.Coord.X + 1;
            int columnMinimum = main_node.Coord.Y - 1 < 0 ? main_node.Coord.Y : main_node.Coord.Y - 1;
            int columnMaximum = main_node.Coord.Y + 1 > verticallenght ? main_node.Coord.Y : main_node.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                {
                    ICoordinate cur_point = new Point(i, j);
                    if ((i != main_node.Coord.X || j != main_node.Coord.Y) && (main_node.Coord.X == cur_point.X || main_node.Coord.Y == cur_point.Y))
                        result.Add(new BFSNode(cur_point, main_node));
                }
            return result;
        }

        protected override IEnumerable<INode> GetNeighboursDiagonal(int horizontallenght, int verticallenght, INode main_node, ICoordinate end)
        {
            List<BFSNode> result = new List<BFSNode>();
            //Define grid bounds
            int rowMinimum = main_node.Coord.X - 1 < 0 ? main_node.Coord.X : main_node.Coord.X - 1;
            int rowMaximum = main_node.Coord.X + 1 > horizontallenght ? main_node.Coord.X : main_node.Coord.X + 1;
            int columnMinimum = main_node.Coord.Y - 1 < 0 ? main_node.Coord.Y : main_node.Coord.Y - 1;
            int columnMaximum = main_node.Coord.Y + 1 > verticallenght ? main_node.Coord.Y : main_node.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                    if (i != main_node.Coord.X || j != main_node.Coord.Y)
                    {
                        ICoordinate cur_point = new Point(i, j);
                        result.Add(new BFSNode(cur_point, main_node));
                    }
            return result;
        }
    }
}
