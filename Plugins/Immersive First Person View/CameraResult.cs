using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace IFPV
{
    internal sealed class CameraResult : TemporaryObject
    {
        internal CameraResult()
        {
            this.Allocation = Memory.Allocate(MemoryObject.SizeOf<NiTransform>());
            this.Transform = MemoryObject.FromAddress<NiTransform>(this.Allocation.Address);
            this.Transform.Position.X = 0.0f;
            this.Transform.Position.Y = 0.0f;
            this.Transform.Position.Z = 0.0f;
            this.Transform.Rotation.Identity(1.0f);
            this.Transform.Scale = 1.0f;
        }

        private MemoryAllocation Allocation = null;

        internal NiTransform Transform
        {
            get;
            private set;
        }

        protected override void Free()
        {
            if (NetScriptFramework.Main.IsShutdown)
                return;

            this.Transform = null;

            if(this.Allocation != null)
            {
                this.Allocation.Dispose();
                this.Allocation = null;
            }
        }
    }
}
