using System.Collections.Generic;
using Draw = System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System;
using PathfindingAlgorithms.Algorithms.Model;
using PathfindingAlgorithms.CommonData;

namespace Pathfinding.DepthFirst
{
    public class DFS : PathfindingBase
    {
        public override IEnumerable<INode> UnvisitedNodes { get; set; }
        public override IEnumerable<INode> VisitedNodes { get; set; }

        public async override Task<IEnumerable<INode>> FindPathDiagonal(Stopwatch timer, GridInfo meshInfo, int delay, Action<INode> UnvisitedPathChanged, Action<INode> VisitedPathChanged, CancellationToken cToken)
        {
            timer.Start();

            List<DFSNode> visited = new List<DFSNode>();
            Stack<DFSNode> unvisited = new Stack<DFSNode>();

            unvisited.Push(new DFSNode(meshInfo.Start, null));

            while (unvisited.Count > 0)
            {
                var cur_node = unvisited.Pop();

                if (cur_node.Coord == meshInfo.End)
                {
                    UnvisitedNodes = unvisited;
                    VisitedNodes = visited;
                    return CalculatePath(cur_node);
                }

                timer.Stop();

                timer.Start();
                var neighbours = GetNeighboursDiagonal(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<DFSNode>();

                foreach (var neighbour in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == neighbour.Coord))
                        continue;

                    if (visited.Any(s => s.Coord == neighbour.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == neighbour.Coord))
                        continue;

                    unvisited.Push(neighbour);
                    timer.Stop();
                    await Task.Run(() => UnvisitedPathChanged(neighbour), cToken);
                    timer.Start();
                }

                visited.Add(cur_node);

                timer.Stop();
                await Task.Run(() => VisitedPathChanged(cur_node), cToken);

                await Task.Delay(delay, cToken);

                timer.Start();
            }

            return null;
        }

        public async override Task<IEnumerable<INode>> FindPathNoDiagonal(Stopwatch timer, GridInfo meshInfo, int delay, Action<INode> UnvisitedPathChanged, Action<INode> VisitedPathChanged, CancellationToken cToken)
        {
            timer.Start();

            List<DFSNode> visited = new List<DFSNode>();
            Stack<DFSNode> unvisited = new Stack<DFSNode>();

            unvisited.Push(new DFSNode(meshInfo.Start, null));

            while (unvisited.Count > 0)
            {
                var cur_node = unvisited.Pop();

                if (cur_node.Coord == meshInfo.End)
                {
                    UnvisitedNodes = unvisited;
                    VisitedNodes = visited;
                    return CalculatePath(cur_node);
                }

                var neighbours = GetNeighbours(meshInfo.HorizontalLenght - 1, meshInfo.VerticalLenght - 1, cur_node, meshInfo.End).Cast<DFSNode>();

                foreach (var neighbour in neighbours)
                {
                    if (meshInfo.UnwalkablePos.Any(s => s == neighbour.Coord))
                        continue;

                    if (visited.Any(s => s.Coord == neighbour.Coord))
                        continue;

                    if (unvisited.Any(s => s.Coord == neighbour.Coord))
                        continue;

                    unvisited.Push(neighbour);
                    timer.Stop();
                    await Task.Run(() => UnvisitedPathChanged(neighbour), cToken);
                    timer.Start();
                }


                visited.Add(cur_node);

                timer.Stop();
                await Task.Run(() => VisitedPathChanged(cur_node), cToken);

                await Task.Delay(delay, cToken);

                timer.Start();
            }

            return null;
        }

        protected override IEnumerable<INode> GetNeighbours(int horizontallenght, int verticallenght, INode main_node, ICoordinate end)
        {
            List<DFSNode> result = new List<DFSNode>();
            //Define grid bounds
            int rowMinimum = main_node.Coord.X - 1 < 0 ? main_node.Coord.X : main_node.Coord.X - 1;
            int rowMaximum = main_node.Coord.X + 1 > horizontallenght ? main_node.Coord.X : main_node.Coord.X + 1;
            int columnMinimum = main_node.Coord.Y - 1 < 0 ? main_node.Coord.Y : main_node.Coord.Y - 1;
            int columnMaximum = main_node.Coord.Y + 1 > verticallenght ? main_node.Coord.Y : main_node.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                {
                    ICoordinate cur_point = new Vectors.Vector2(i, j);
                    if ((i != main_node.Coord.X || j != main_node.Coord.Y) && (main_node.Coord.X == cur_point.X || main_node.Coord.Y == cur_point.Y))
                        result.Add(new DFSNode(cur_point, main_node));
                }
            return result;
        }

        protected override IEnumerable<INode> GetNeighboursDiagonal(int horizontallenght, int verticallenght, INode main_node, ICoordinate end)
        {
            List<DFSNode> result = new List<DFSNode>();
            //Define grid bounds
            int rowMinimum = main_node.Coord.X - 1 < 0 ? main_node.Coord.X : main_node.Coord.X - 1;
            int rowMaximum = main_node.Coord.X + 1 > horizontallenght ? main_node.Coord.X : main_node.Coord.X + 1;
            int columnMinimum = main_node.Coord.Y - 1 < 0 ? main_node.Coord.Y : main_node.Coord.Y - 1;
            int columnMaximum = main_node.Coord.Y + 1 > verticallenght ? main_node.Coord.Y : main_node.Coord.Y + 1;

            for (int i = rowMinimum; i <= rowMaximum; i++)
                for (int j = columnMinimum; j <= columnMaximum; j++)
                    if (i != main_node.Coord.X || j != main_node.Coord.Y)
                    {
                        var cur_point = new Vectors.Vector2(i, j);
                        result.Add(new DFSNode(cur_point, main_node));
                    }
            return result;
        }
    }
}
