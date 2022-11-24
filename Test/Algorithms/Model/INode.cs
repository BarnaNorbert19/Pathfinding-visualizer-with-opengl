using PathfindingAlgorithms.Algorithms.Model;

namespace Pathfinding
{
    /// <summary>
    /// Supports all node types that have a coordinate, G cost and a parent node.
    /// </summary>
    public interface INode
    {
        INode ParentNode { get; set; }
        ICoordinate Coord { get; set; }
        int G { get; set; }
    }
}
