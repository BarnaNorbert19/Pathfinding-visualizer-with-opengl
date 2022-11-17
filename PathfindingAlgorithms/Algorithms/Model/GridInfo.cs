using PathfindingAlgorithms.Algorithms.Model;
using System.Collections.Generic;

namespace Pathfinding
{
    /// <summary>
    /// Contains all the information needed for pathfinding.
    /// Running the algorithms without providing these values, might lead to exceptions !
    /// </summary>
    public class GridInfo
    {
        public ICoordinate Start { get; set; }
        public ICoordinate End { get; set; }
        public int HorizontalLenght { get; set; }
        public int VerticalLenght { get; set; }
        public IList<ICoordinate> UnwalkablePos { get; set; }
        public IList<INode> Path { get; set; }
        public IEnumerable<INode> UnvisitedNodes { get; set; }
        public IEnumerable<INode> VisitedNodes { get; set; }
    }
}
