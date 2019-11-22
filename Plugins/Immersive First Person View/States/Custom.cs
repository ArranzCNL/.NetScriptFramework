using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Tools;

namespace IFPV.States
{
    internal sealed class Custom : CameraState
    {
        private Custom()
        {

        }

        internal override int Priority
        {
            get
            {
                return _prio;
            }
        }

        internal override int Group
        {
            get
            {
                return _group;
            }
        }

        internal string Name
        {
            get;
            private set;
        }

        private int _prio = 50;
        private int _group = 0;
        private List<Action<CameraState>> _setters = null;
        private List<Tuple<double, ProfileSettings._ConditionDelegate>> _cond = null;
        private List<Tuple<string, ProfileSettings._ConditionDelegate2>> _cond2 = null;

        internal static Custom LoadFrom(string keyword)
        {
            var settings = new ProfileSettings();
            if (!settings.LoadFrom(Prefix + "." + keyword))
                return null;

            var c = new Custom();
            c._prio = settings.Priority;
            c._group = settings.Group;
            c._setters = settings.setters;
            c._cond = settings.conditions;
            c._cond2 = settings.conditions2;
            c.Name = keyword;

            if(c._group < 0 || c._group >= 32)
                throw new InvalidOperationException(Prefix + "." + keyword + ".config.txt has invalid group setting: " + c._group);

            return c;
        }

        internal static readonly string Prefix = "IFPVProfile";

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            if(this._setters != null)
            {
                foreach(var s in this._setters)
                {
                    if (s != null)
                        s(this);
                }
            }
        }

        internal override bool Check(CameraUpdate update)
        {
            if (_cond == null || _cond.Count == 0)
                return true;

            foreach(var t in this._cond)
            {
                if (t.Item2 != null && !t.Item2(update, t.Item1))
                    return false;
            }

            foreach (var t in this._cond2)
            {
                if (t.Item2 != null && !t.Item2(update, t.Item1))
                    return false;
            }

            return true;
        }
    }

    internal sealed class ProfileSettings
    {
        internal int Priority
        {
            get;
            set;
        } = 50;

        internal int Group
        {
            get;
            set;
        } = 0;

        internal List<Action<CameraState>> setters = new List<Action<CameraState>>(16);
        internal List<Tuple<double, _ConditionDelegate>> conditions = new List<Tuple<double, _ConditionDelegate>>(8);
        internal List<Tuple<string, _ConditionDelegate2>> conditions2 = new List<Tuple<string, _ConditionDelegate2>>(2);

        private List<CameraValueBase> GetCameraValues(string keyword)
        {
            List<CameraValueBase> ls = null;

            if (_cv_map.TryGetValue(keyword, out ls))
                return ls;

            var map = IFPVPlugin.Instance.CameraMain.Values;
            ls = new List<CameraValueBase>();

            //switch(keyword)
            
            return ls;
        }

        private double GetCameraValueAmount(string keyword, double amount)
        {
            if (keyword.Equals("StabilizeHistoryDuration", StringComparison.OrdinalIgnoreCase))
                return amount * 1000.0;

            return amount;
        }

        private void AddSetter(string keyword, double value, CameraValueModifier.ModifierTypes type, long removeDelay)
        {
            value = this.GetCameraValueAmount(keyword, value);
            var ls = this.GetCameraValues(keyword);

            foreach(var v in ls)
            {
                this.setters.Add(state =>
                {
                    v.AddModifier(state, type, value, true, removeDelay);
                });
            }
        }
        
        internal bool LoadFrom(string keyword)
        {
            init_cv();

            var type = typeof(Settings).GetType();
            var fields = type.GetFields(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            var props = type.GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);

            var cf = new ConfigFile(keyword);
            cf.AddSetting("Priority", new Value((int)50), "Priority", "The priority of profile. Higher value means profile is loaded later and will overwrite others.");
            cf.AddSetting("Group", new Value((int)0), "Group", "The group of profile. Multiple profiles with same group ID can not be active at the same time. Only one profile (highest priority) from same group will be active (or none).");

            var cf2 = new ConfigFile(keyword);

            if (!cf2.Load())
                return false;

            List<Tuple<ConfigEntry, System.Reflection.FieldInfo, System.Reflection.PropertyInfo>> valid = new List<Tuple<ConfigEntry, System.Reflection.FieldInfo, System.Reflection.PropertyInfo>>();

            foreach (var f in fields)
            {
                var attrs = f.GetCustomAttributes(typeof(ConfigValueAttribute), true);
                if (attrs == null || attrs.Length == 0)
                    continue;

                var a = attrs[0] as ConfigValueAttribute;
                if (a == null)
                    continue;

                if (cf2.GetValue(a.Keyword) == null)
                    continue;

                var val = ToValue(f.FieldType, f.GetValue(Settings.Instance));
                var setting = cf.AddSetting(a.Keyword, val, a.Name, a.Description, a.Flags);
                valid.Add(new Tuple<ConfigEntry, System.Reflection.FieldInfo, System.Reflection.PropertyInfo>(setting, f, null));
            }

            foreach (var p in props)
            {
                var attrs = p.GetCustomAttributes(typeof(ConfigValueAttribute), true);
                if (attrs == null || attrs.Length == 0)
                    continue;

                var a = attrs[0] as ConfigValueAttribute;
                if (a == null)
                    continue;

                if (p.GetMethod == null || p.SetMethod == null)
                    continue;

                if (cf2.GetValue(a.Keyword) == null)
                    continue;

                var val = ToValue(p.PropertyType, p.GetValue(Settings.Instance));
                var setting = cf.AddSetting(a.Keyword, val, a.Name, a.Description, a.Flags);
                valid.Add(new Tuple<ConfigEntry, System.Reflection.FieldInfo, System.Reflection.PropertyInfo>(setting, null, p));
            }

            if (valid.Count == 0)
                return false;

            if (!cf.Load())
                return false;
            
            foreach (var t in valid)
            {
                var val = t.Item1.CurrentValue;
                if (val == null)
                    continue;

                double dv = 0.0;
                if (!val.TryToDouble(out dv))
                    continue;

                var t2 = cf2.GetValue(t.Item1.Keyword + "_Type");
                CameraValueModifier.ModifierTypes settype = CameraValueModifier.ModifierTypes.Set;
                if(t2 != null)
                {
                    string tx = t2.ToString().ToLowerInvariant().Trim();
                    switch(tx)
                    {
                        case "set": settype = CameraValueModifier.ModifierTypes.Set; break;
                        case "add": settype = CameraValueModifier.ModifierTypes.Add; break;
                        case "multiply": settype = CameraValueModifier.ModifierTypes.Multiply; break;
                        case "force": settype = CameraValueModifier.ModifierTypes.Force; break;
                        case "setifpreviousishigherthanthis": settype = CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis; break;
                        case "setifpreviousislowerthanthis": settype = CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis; break;
                    }
                }

                long removeDelay = 0;
                t2 = cf2.GetValue(t.Item1.Keyword + "_RemoveDelay");
                if(t2 != null)
                {
                    long nx = 0;
                    if (t2.TryToInt64(out nx) && nx >= 0)
                        removeDelay = nx;
                }

                this.AddSetter(t.Item1.Keyword, dv, settype, removeDelay);
            }

            foreach(var pair in _cond_map)
            {
                string kw = "Condition_" + pair.Key;
                var val = cf2.GetValue(kw);
                if (val == null)
                    continue;

                double amt = 0.0;
                if (!val.TryToDouble(out amt))
                    continue;

                this.conditions.Add(new Tuple<double, _ConditionDelegate>(amt, pair.Value));
            }

            foreach (var pair in _cond_map2)
            {
                string kw = "Condition_" + pair.Key;
                var val = cf2.GetValue(kw);
                if (val == null)
                    continue;

                string amt = val.ToString();
                this.conditions2.Add(new Tuple<string, _ConditionDelegate2>(amt, pair.Value));
            }

            return true;
        }

        /// <summary>
        /// Convert from base object to our value.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentException">Unhandled type in configuration class ( + type.Name + )!;type</exception>
        private static Value ToValue(Type type, object value)
        {
            if (type == typeof(bool))
                return new Value((bool)value);
            if (type == typeof(sbyte))
                return new Value((sbyte)value);
            if (type == typeof(byte))
                return new Value((byte)value);
            if (type == typeof(short))
                return new Value((short)value);
            if (type == typeof(ushort))
                return new Value((ushort)value);
            if (type == typeof(int))
                return new Value((int)value);
            if (type == typeof(uint))
                return new Value((uint)value);
            if (type == typeof(long))
                return new Value((long)value);
            if (type == typeof(ulong))
                return new Value((ulong)value);
            if (type == typeof(float))
                return new Value((float)value);
            if (type == typeof(double))
                return new Value((double)value);
            if (type == typeof(decimal))
                return new Value((decimal)value);
            if (type == typeof(DateTime))
                return new Value((DateTime)value);
            if (type == typeof(string))
                return new Value((string)value);

            throw new ArgumentException("Unhandled type in configuration class (" + type.Name + ")!", "type");
        }

        private static Dictionary<string, List<CameraValueBase>> _cv_map = null;
        private static Dictionary<string, _ConditionDelegate> _cond_map = null;
        private static Dictionary<string, _ConditionDelegate2> _cond_map2 = null;

        private static void init_cv()
        {
            if (_cv_map != null)
                return;

            init_cond();

            var map = IFPVPlugin.Instance.CameraMain.Values;
            _cv_map = new Dictionary<string, List<CameraValueBase>>(StringComparer.OrdinalIgnoreCase);

            Dictionary<string, CameraValueBase> auto_map = new Dictionary<string, CameraValueBase>();
            var t = typeof(CameraValueMap);
            var fields = t.GetFields(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            foreach(var f in fields)
            {
                if (f.FieldType != typeof(CameraValueBase) && !f.FieldType.IsSubclassOf(typeof(CameraValueBase)))
                    continue;

                auto_map[f.Name] = (CameraValueBase)f.GetValue(map);
            }
            var props = t.GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            foreach(var p in props)
            {
                if (p.PropertyType != typeof(CameraValueBase) && !p.PropertyType.IsSubclassOf(typeof(CameraValueBase)))
                    continue;

                if (p.GetMethod == null)
                    continue;

                var pv = (CameraValueBase)p.GetValue(map);
                if(pv != null)
                    auto_map[p.Name] = pv;
            }

            foreach(var pair in auto_map)
            {
                if (pair.Value == null)
                    continue;

                _cv_map[pair.Key] = new List<CameraValueBase>
                {
                    pair.Value
                };
            }
        }

        internal delegate bool _ConditionDelegate(CameraUpdate update, double value);
        internal delegate bool _ConditionDelegate2(CameraUpdate update, string value);

        private static void init_cond()
        {
            _cond_map = new Dictionary<string, _ConditionDelegate>(StringComparer.OrdinalIgnoreCase);
            _cond_map2 = new Dictionary<string, _ConditionDelegate2>(StringComparer.OrdinalIgnoreCase);

            var methods = typeof(ProfileSettings).GetMethods(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Static);
            foreach(var m in methods)
            {
                if (!m.Name.StartsWith("Cond_"))
                    continue;

                var pr = m.GetParameters();
                if (pr.Length != 2 || pr[0].ParameterType != typeof(CameraUpdate))
                    continue;

                if (m.ReturnType != typeof(bool))
                    continue;

                string name = m.Name.Substring("Cond_".Length);

                if(pr[1].ParameterType == typeof(double))
                    _cond_map[name] = (_ConditionDelegate)m.CreateDelegate(typeof(_ConditionDelegate));
                else if(pr[1].ParameterType == typeof(string))
                    _cond_map2[name] = (_ConditionDelegate2)m.CreateDelegate(typeof(_ConditionDelegate2));
            }
        }

        private static bool Cond_Enabled(CameraUpdate update, double amt)
        {
            bool must = amt >= 0.5;
            bool isen = update.CameraMain.IsEnabled;
            return isen == must;
        }

        private static bool Cond_Race(CameraUpdate update, string amt)
        {
            if (string.IsNullOrEmpty(amt))
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            var race = actor.Race;
            if (race == null)
                return false;

            string n = race.Name;
            if (!string.IsNullOrEmpty(n) && n.IndexOf(amt, StringComparison.OrdinalIgnoreCase) >= 0)
                return true;

            n = race.EditorId;
            if (!string.IsNullOrEmpty(n) && n.IndexOf(amt, StringComparison.OrdinalIgnoreCase) >= 0)
                return true;

            return false;
        }

        private static bool Cond_Mounted(CameraUpdate update, double amt)
        {
            bool must = amt >= 0.5;
            bool isen = update.CachedMounted;
            return must == isen;
        }

        private static bool Cond_Keyword(CameraUpdate update, string amt)
        {
            if (string.IsNullOrEmpty(amt))
                return false;

            var obj = update.Target.Object;
            if (obj == null)
                return false;

            return obj.HasKeywordText(amt);
        }

        private static bool Cond_Profile(CameraUpdate update, string amt)
        {
            if (string.IsNullOrEmpty(amt))
                return false;

            foreach(var s in update.CameraMain.Stack.States)
            {
                if(s is Custom)
                {
                    var cs = (Custom)s;
                    if (cs.Name != null && amt.Equals(cs.Name, StringComparison.OrdinalIgnoreCase))
                        return cs.IsActive;
                    continue;
                }

                var t = s.GetType();
                if (t.Name.Equals(amt, StringComparison.OrdinalIgnoreCase))
                    return s.IsActive;
            }

            return false;
        }

        private static bool Cond_NotProfile(CameraUpdate update, string amt)
        {
            if (string.IsNullOrEmpty(amt))
                return false;

            return !Cond_Profile(update, amt);
        }
    }
}
