﻿using System.Drawing;

namespace Pathfinding.Dijkstra
{
    public class DijkstraNode : INode
    {
        public Point Coord { get; set; }
        public INode ParentNode { get; set; }
        public int G { get; set; }

        public DijkstraNode(Point coord, INode parentNode, int g = 0)
        {
            Coord = coord;
            ParentNode = parentNode;
            G = g;
        }

        
    }
}
