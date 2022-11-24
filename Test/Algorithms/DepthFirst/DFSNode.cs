using PathfindingAlgorithms.Algorithms.Model;
using System.Drawing;

namespace Pathfinding.DepthFirst
{
    public class DFSNode : INode
    {
        public ICoordinate Coord { get; set; }
        public INode ParentNode { get; set; }
        public int G { get; set; }

        public DFSNode(ICoordinate coord, INode parentNode)
        {
            Coord = coord;
            ParentNode = parentNode;
        }
    }
}