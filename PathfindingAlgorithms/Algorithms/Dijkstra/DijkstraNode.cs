using PathfindingAlgorithms.Algorithms.Model;
using System.Drawing;

namespace Pathfinding.Dijkstra
{
    public class DijkstraNode : INode
    {
        public ICoordinate Coord { get; set; }
        public INode ParentNode { get; set; }
        public int G { get; set; }

        public DijkstraNode(ICoordinate coord, INode parentNode, int g = 0)
        {
            Coord = coord;
            ParentNode = parentNode;
            G = g;
        }

        
    }
}
