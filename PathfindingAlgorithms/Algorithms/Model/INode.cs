namespace Pathfinding
{
    /// <summary>
    /// Supports all node types that have a coordinate, G cost and a parent node.
    /// </summary>
    public interface INode
    {
        INode ParentNode { get; set; }
        System.Drawing.Point Coord { get; set; }
        int G { get; set; }
    }
}
