using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace IFPV
{
    internal sealed class CameraUpdate
    {
        internal CameraUpdate(CameraMain main, CameraResult result, CameraTarget target, PlayerCamera camera, NiAVObject cameraNode, TESCameraState state, CameraValueMap values)
        {
            if (main == null)
                throw new ArgumentNullException("main");

            if (result == null)
                throw new ArgumentNullException("result");

            if (target == null)
                throw new ArgumentNullException("target");

            if (camera == null)
                throw new ArgumentNullException("camera");

            if (cameraNode == null)
                throw new ArgumentNullException("cameraNode");

            if (state == null)
                throw new ArgumentNullException("state");

            if (values == null)
                throw new ArgumentNullException("values");

            this.CameraMain = main;
            this.Result = result;
            this.Target = target;
            this.GameCamera = camera;
            this.GameCameraNode = cameraNode;
            this.GameCameraState = state;
            this.Values = values;
            this.CachedMounted = target.Actor != null && (target.Actor.IsOnMount || target.Actor.IsOnFlyingMount);
        }

        internal readonly CameraMain CameraMain;

        internal readonly CameraResult Result;

        internal readonly CameraTarget Target;

        internal readonly PlayerCamera GameCamera;

        internal readonly NiAVObject GameCameraNode;

        internal readonly TESCameraState GameCameraState;

        internal readonly CameraValueMap Values;

        internal readonly bool CachedMounted;
    }
}
