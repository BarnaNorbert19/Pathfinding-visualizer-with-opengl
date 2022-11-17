using PathfindingAlgorithms.Algorithms.Model;

namespace Pathfinding.BreadthFirst
{
    public class BFSNode : INode
    {
        public BFSNode(ICoordinate coord, INode parentNode)
        {
            Coord = coord;
            ParentNode = parentNode;
        }

        public ICoordinate Coord { get; set; }
        public INode ParentNode { get; set; }
        public int G { get; set; }
    }
}
