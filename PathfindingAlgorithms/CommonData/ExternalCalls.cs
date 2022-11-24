using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace PathfindingAlgorithms.CommonData
{
    public static class ExternalCalls
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void ChangeColor(Point square, Vectors.Vector3 color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void ReDraw();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void ResetGrid();
    }
}
