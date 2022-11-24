using System.Drawing;

namespace Pathfinding.DepthFirst
{
    public class DFSNode : INode
    {
        public Point Coord { get; set; }
        public INode ParentNode { get; set; }
        public int G { get; set; }

        public DFSNode(Point coord, INode parentNode)
        {
            Coord = coord;
            ParentNode = parentNode;
        }
    }
}