using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    internal sealed class CameraStack
    {
        internal CameraStack(CameraMain cameraMain)
        {
            if (cameraMain == null)
                throw new ArgumentNullException("cameraMain");

            this.CameraMain = cameraMain;

            var types = System.Reflection.Assembly.GetExecutingAssembly().GetTypes();
            foreach(var t in types)
            {
                if (t.IsAbstract || !t.IsSubclassOf(typeof(CameraState)))
                    continue;

                if (t == typeof(States.Custom) || t.IsSubclassOf(typeof(States.Custom)))
                    continue;

                var cis = t.GetConstructors(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
                System.Reflection.ConstructorInfo ci = null;
                foreach(var c in cis)
                {
                    if (c.GetParameters().Length == 0)
                        ci = c;
                }

                if(ci != null)
                {
                    CameraState state = (CameraState)ci.Invoke(new object[0]);
                    if(state != null)
                    {
                        state._init(this);
                        this._states.Add(state);

                        int grp = state.Group;
                        if (grp > MaxGroup)
                            MaxGroup = grp;
                    }
                }
            }

            this.LoadCustomProfiles();

            if (this._states.Count > 1)
                this._states.Sort((u, v) => u.Priority.CompareTo(v.Priority));

            MaxGroup = MaxGroup + 1;
            this._temp = new CameraState[MaxGroup];

            foreach (var s in this._states)
                s.Initialize();
        }

        private void LoadCustomProfiles()
        {
            var dir = new System.IO.DirectoryInfo("Data/NetScriptFramework/Plugins");
            if (!dir.Exists)
                return;

            var files = dir.GetFiles();
            string prefix = IFPV.States.Custom.Prefix + ".";
            string suffix = ".config.txt";
            foreach(var f in files)
            {
                if (!f.Name.StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
                    continue;
                if (!f.Name.EndsWith(suffix, StringComparison.OrdinalIgnoreCase))
                    continue;

                string n = f.Name;
                n = n.Substring(prefix.Length);
                n = n.Substring(0, n.Length - suffix.Length);

                if (n.Length == 0)
                    continue;

                var state = IFPV.States.Custom.LoadFrom(n);
                if (state == null)
                    continue;

                state._init(this);
                this._states.Add(state);

                int grp = state.Group;
                if (grp > MaxGroup)
                    MaxGroup = grp;
            }
        }

        internal readonly CameraMain CameraMain;
        
        internal IReadOnlyList<CameraState> States
        {
            get
            {
                return this._states;
            }
        }
        private readonly List<CameraState> _states = new List<CameraState>();
        private readonly CameraState[] _temp;
        internal int MaxGroup
        {
            get;
            private set;
        }
        private bool Warned = false;

        internal void Check(CameraUpdate update)
        {
            foreach(var s in this.States)
            {
                int grp = s.Group;
                if (grp < 0 || grp >= MaxGroup)
                {
                    if(!Warned)
                    {
                        Warned = true;
                        NetScriptFramework.Main.Log.AppendLine("IFPV: State " + s.GetType().Name + " has invalid group " + grp + "!");
                    }
                    continue;
                }

                bool isActive = s.Check(update);
                bool wasActive = s.IsActive;
                s.__wActivate = isActive;
                if (!isActive || grp == 0)
                    continue;

                var p = this._temp[grp];
                this._temp[grp] = s;

                if (p != null)
                    p.__wActivate = false;
            }

            for (int i = 0; i < MaxGroup; i++)
                this._temp[i] = null;

            foreach (var s in this.States)
            {
                bool a = s.__wActivate;
                if (a != s.IsActive)
                {
                    s._set(a);
                    if (a)
                        s.OnEntering(update);
                    else
                        s.OnLeaving(update);
                }
            }
        }

        internal void DisableAll(CameraUpdate update)
        {
            foreach(var s in this.States)
            {
                if(s.IsActive)
                {
                    s._set(false);
                    s.OnLeaving(update);
                }
            }
        }

        internal void Update(CameraUpdate update)
        {
            foreach(var s in this.States)
            {
                if (s.IsActive)
                    s.Update(update);
            }
        }
    }
}
