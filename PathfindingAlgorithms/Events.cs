using Pathfinding;
using static PathfindingAlgorithms.CommonData.Vectors;

namespace PathfindingAlgorithms
{
    public class Events
    {
        public static int ClickCount { get; private set; }
        private static GridInfo _gridInfo;

        public void OnSquareClicked(Vector2 square)
        {
            if (ClickCount == 0)
            {
                _gridInfo.Start = square;
                ClickCount++;
                return;
            }

            else if (ClickCount == 1)
            {
                _gridInfo.End = square;
                ClickCount++;
                return;
            }

            ClickCount = 0;
        }
    }
}
