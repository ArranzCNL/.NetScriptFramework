using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV
{
    internal sealed partial class CameraValueMap
    {
        internal CameraValueMap(CameraMain cameraMain)
        {
            if (cameraMain == null)
                throw new ArgumentNullException("cameraMain");

            this.CameraMain = cameraMain;

            var fields = this.GetType().GetFields(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            foreach(var f in fields)
            {
                var ft = f.FieldType;
                if (ft != typeof(CameraValueBase) && !ft.IsSubclassOf(typeof(CameraValueBase)))
                    continue;

                var val = f.GetValue(this) as CameraValueBase;
                if (val != null)
                    this.values.Add(val);
            }
        }

        internal readonly CameraMain CameraMain;

        private readonly List<CameraValueBase> values = new List<CameraValueBase>();

        internal void Reset()
        {
            foreach (var v in this.values)
                v.Reset();
        }

        internal void Update(long now, bool enabled)
        {
            foreach (var v in this.values)
                v.Update(now, enabled);
        }
    }
}
