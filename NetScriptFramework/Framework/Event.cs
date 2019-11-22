using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Contains information about a single event registration.
    /// </summary>
    internal sealed class EventRegistration
    {
        /// <summary>
        /// The unique identifier of registration.
        /// </summary>
        internal long Guid;

        /// <summary>
        /// The handler method.
        /// </summary>
        internal Delegate Handler;

        /// <summary>
        /// The priority of method.
        /// </summary>
        internal int Priority;
        
        /// <summary>
        /// The options for registration.
        /// </summary>
        internal EventRegistrationFlags Flags;

        /// <summary>
        /// The total count to run this before automatically removing.
        /// </summary>
        internal int TotalCount;

        /// <summary>
        /// The current count.
        /// </summary>
        internal int CurrentCount;

        /// <summary>
        /// The plugin that installed the event.
        /// </summary>
        internal string PluginKey = null;

        /// <summary>
        /// The plugin version that installed the event.
        /// </summary>
        internal int PluginVer = 0;
    }

    /// <summary>
    /// Options for an event registration.
    /// </summary>
    [Flags]
    public enum EventRegistrationFlags : uint
    {
        /// <summary>
        /// No flags are set.
        /// </summary>
        None = 0,

        /// <summary>
        /// Skip adding handler to invocation list if it already exists there.
        /// </summary>
        Distinct = 1,
    }

    /// <summary>
    /// The base class for accessing events.
    /// </summary>
    public abstract class EventBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="EventBase"/> class.
        /// </summary>
        /// <param name="key">Unique key of event.</param>
        /// <param name="delegateType">Type of the delegate.</param>
        internal protected EventBase(string key, Type delegateType)
        {
#if DEBUG
            if (string.IsNullOrEmpty(key))
                throw new ArgumentOutOfRangeException("key");
#endif

            this.Key = key;
            this.DelegateType = delegateType;
        }
        
        /// <summary>
        /// The key of event. This is the name of field or property usually.
        /// </summary>
        public readonly string Key;

        /// <summary>
        /// The delegate type, used for loading.
        /// </summary>
        private readonly Type DelegateType;
        
        /// <summary>
        /// The locker for thread safety.
        /// </summary>
        internal readonly object Locker = new object();

        /// <summary>
        /// Gets the handler. This will trigger a recalculation if it's needed. Returns null if no handlers are registered, otherwise
        /// may return a delegate or multi-cast delegate.
        /// </summary>
        /// <returns></returns>
        internal protected Delegate _GetHandler()
        {
            return this.Handler;
        }

        /// <summary>
        /// The current handler.
        /// </summary>
        private Delegate Handler = null;

        /// <summary>
        /// The registrations.
        /// </summary>
        private readonly List<EventRegistration> Registrations = new List<EventRegistration>(32);
        
        /// <summary>
        /// Reduce counts of registrations.
        /// </summary>
        /// <param name="amount">The amount.</param>
        internal protected bool _ReduceCounts(int amount)
        {
            bool removed = false;
            for (int i = this.Registrations.Count - 1; i >= 0; i--)
            {
                var reg = this.Registrations[i];
                if (reg.TotalCount <= 0)
                    continue;
                
                reg.CurrentCount -= amount;
                if (reg.CurrentCount <= 0)
                {
                    if(this._UnregisterByIndex(i))
                        removed = true;
                }
            }

            return removed;
        }

        /// <summary>
        /// Register a new event handler.
        /// </summary>
        /// <param name="handler">The handler.</param>
        /// <param name="priority">The priority.</param>
        /// <param name="totalCount">The total count.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="fromPluginKey">The plugin.</param>
        /// <param name="fromPluginVersion">The plugin version.</param>
        /// <returns></returns>
        internal protected long _Register(Delegate handler, int priority, int totalCount, EventRegistrationFlags flags, string fromPluginKey, int fromPluginVersion)
        {
            var registration = new EventRegistration();
            registration.Guid = Main.GenerateGuid();
            registration.Handler = handler;
            registration.Priority = priority;
            registration.TotalCount = totalCount;
            registration.CurrentCount = totalCount;
            registration.Flags = flags;
            if (fromPluginKey != null)
            {
                registration.PluginKey = fromPluginKey;
                registration.PluginVer = fromPluginVersion;
            }
            else
            {
                registration.PluginKey = null;
                registration.PluginVer = 0;
            }
            this._Register(registration);
            this._Recalculate();
            return registration.Guid;
        }

        /// <summary>
        /// Register a new event handler.
        /// </summary>
        /// <param name="registration">The registration.</param>
        internal void _Register(EventRegistration registration)
        {
            int index = 0;
            for (; index < this.Registrations.Count; index++)
            {
                if (this.Registrations[index].Priority > registration.Priority)
                    break;
            }

            this.Registrations.Insert(index, registration);
        }

        /// <summary>
        /// Unregister an event handler by its unique identifier.
        /// </summary>
        /// <param name="guid">The unique identifier.</param>
        /// <returns></returns>
        internal protected bool _Unregister(long guid)
        {
            for (int i = 0; i < this.Registrations.Count; i++)
            {
                if (this.Registrations[i].Guid == guid)
                {
                    if(this._UnregisterByIndex(i))
                        this._Recalculate();
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Unregister an event handler by its index.
        /// </summary>
        /// <param name="index">The index.</param>
        private bool _UnregisterByIndex(int index)
        {
            var registration = this.Registrations[index];
            this.Registrations.RemoveAt(index);

            return true;
        }

        /// <summary>
        /// Forces a recalculation of the event handler delegate.
        /// </summary>
        internal protected void _Recalculate()
        {
            bool had = this.Handler != null;
            this.Handler = null;

            if (this.Registrations.Count != 0)
            {
                List<Delegate> list = new List<Delegate>();

                for (int i = 0; i < this.Registrations.Count; i++)
                {
                    var reg = this.Registrations[i];

                    if (reg.Handler == null)
                        continue;

                    if ((reg.Flags & EventRegistrationFlags.Distinct) != EventRegistrationFlags.None && list.Contains(reg.Handler))
                        continue;

                    list.Add(reg.Handler);
                }

                if (list.Count == 0)
                    this.Handler = null;
                else if (list.Count == 1)
                    this.Handler = list[0];
                else
                    this.Handler = Delegate.Combine(list.ToArray());
            }
        }
    }

    /// <summary>
    /// Implement event handler.
    /// </summary>
    /// <typeparam name="T">Type of event arguments.</typeparam>
    public class Event<T> : EventBase where T : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Event{T}"/> class.
        /// </summary>
        public Event(string key) : base(key, typeof(EventHandler))
        {

        }

        /// <summary>
        /// Registers the specified handler. Returns handle to registration which can be used in Unregister method.
        /// </summary>
        /// <param name="handler">The handler function. This can be null if only suppression is required.</param>
        /// <param name="priority">The priority where higher priority gets called last.</param>
        /// <param name="count">The count. Set zero or negative for infinite, otherwise the handler is called this many times before automatically removed.</param>
        /// <param name="flags">The flags of registration.</param>
        /// <returns></returns>
        public long Register(EventHandler handler, int priority = 0, int count = 0, EventRegistrationFlags flags = EventRegistrationFlags.None)
        {
            string pluginKey = null;
            int pluginVer = 0;
            var assembly = System.Reflection.Assembly.GetCallingAssembly();
            if(assembly != null)
            {
                if(assembly == Main.FrameworkAssembly)
                {
                    pluginKey = string.Empty;
                    pluginVer = Main.FrameworkVersion;
                }
                else
                {
                    var plugin = PluginManager.GetPlugin(assembly);
                    if(plugin != null)
                    {
                        pluginKey = plugin.InternalKey;
                        pluginVer = plugin.InternalVersion;
                    }
                }
            }
            lock (this.Locker)
            {
                return this._Register(handler, priority, count, flags, pluginKey, pluginVer);
            }
        }

        /// <summary>
        /// Unregisters the specified event handler.
        /// </summary>
        /// <param name="guid">The unique identifier of registration.</param>
        /// <returns></returns>
        public bool Unregister(long guid)
        {
            lock (this.Locker)
            {
                return this._Unregister(guid);
            }
        }

        /// <summary>
        /// Raises the event with specified argument initializer. This initialize is only called if event has handlers registered.
        /// Returns the arguments after raising event, if no handlers were registered then null is returned.
        /// </summary>
        /// <param name="initArgs">The initialize arguments function.</param>
        /// <returns></returns>
        public virtual T Raise(Func<T> initArgs)
        {
            lock (this.Locker)
            {
                var handlerBase = this._GetHandler();
                if (handlerBase == null)
                    return null;

                EventHandler handler = (EventHandler)handlerBase;
                var args = initArgs();
                handler(args);
                if (this._ReduceCounts(1))
                    this._Recalculate();
                return args;
            }
        }

        /// <summary>
        /// The event handler delegate.
        /// </summary>
        /// <param name="args">The arguments.</param>
        public delegate void EventHandler(T args);
    }

    /// <summary>
    /// Base event arguments for hooked event.
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class HookedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the context.
        /// </summary>
        /// <value>
        /// The context.
        /// </value>
        public CPURegisters Context
        {
            get;
            internal set;
        }
    }

    /// <summary>
    /// One hooked event registration parameters.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public sealed class EventHookParameters<T> where T : HookedEventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="EventHookParameters{T}"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="replaceLength">Length of the replace.</param>
        /// <param name="includeLength">Length of the include.</param>
        /// <param name="argFunc">The argument function.</param>
        /// <param name="afterFunc">The after function.</param>
        public EventHookParameters(IntPtr address, int replaceLength, int includeLength, Func<CPURegisters, T> argFunc, Action<CPURegisters, T> afterFunc)
        {
            this.Address = address;
            this.ReplaceLength = replaceLength;
            this.IncludeLength = includeLength;
            this.ArgFunc = argFunc;
            this.AfterFunc = afterFunc;
        }

        /// <summary>
        /// Gets or sets the address.
        /// </summary>
        /// <value>
        /// The address.
        /// </value>
        public IntPtr Address
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the length of the replaced code.
        /// </summary>
        /// <value>
        /// The length of the replace.
        /// </value>
        public int ReplaceLength
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the length of the included code.
        /// </summary>
        /// <value>
        /// The length of the include.
        /// </value>
        public int IncludeLength
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the argument function.
        /// </summary>
        /// <value>
        /// The argument function.
        /// </value>
        public Func<CPURegisters, T> ArgFunc
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the after function.
        /// </summary>
        /// <value>
        /// The after function.
        /// </value>
        public Action<CPURegisters, T> AfterFunc
        {
            get;
            internal set;
        }
    }

    /// <summary>
    /// Options for event hook.
    /// </summary>
    [Flags]
    public enum EventHookFlags : uint
    {
        None = 0,

        AlwaysRun = 1,
    }

    /// <summary>
    /// Implement event handler that is also a code hook.
    /// </summary>
    /// <typeparam name="T">Type of event arguments.</typeparam>
    public sealed class EventHook<T> : Event<T> where T : HookedEventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="EventHook{T}" /> class.
        /// </summary>
        /// <param name="flags">Options.</param>
        /// <param name="key">The key.</param>
        /// <param name="args">The arguments.</param>
        /// <exception cref="System.ArgumentNullException">argFunc</exception>
        public EventHook(EventHookFlags flags, string key, params EventHookParameters<T>[] args) : base(key)
        {
            if (args == null)
                throw new ArgumentNullException("args");
            if (args.Any(q => q.ArgFunc == null))
                throw new ArgumentNullException("args[].ArgFunc");

            this.HookFlags = flags;

            this.Arguments = args.ToArray();
            for (int i = 0; i < this.Arguments.Length; i++)
            {
                var a = this.Arguments[i];

                var p = new HookParameters();
                p.Address = a.Address;
                int ix = i;
                int incl = a.IncludeLength;
                if (incl >= 0)
                    p.Before = cpu => EventHook_Action(cpu, ix);
                else
                    p.After = cpu => EventHook_Action(cpu, ix);
                p.IncludeLength = Math.Abs(a.IncludeLength);
                p.ReplaceLength = a.ReplaceLength;

                Memory.WriteHook(p);
            }
        }

        /// <summary>
        /// The arguments.
        /// </summary>
        private readonly EventHookParameters<T>[] Arguments;

        /// <summary>
        /// The hook flags.
        /// </summary>
        private readonly EventHookFlags HookFlags;
        
        /// <summary>
        /// The action to run in the hook, this will invoke the event.
        /// </summary>
        /// <param name="ctx">The context of action.</param>
        /// <param name="index">The index.</param>
        private void EventHook_Action(CPURegisters ctx, int index)
        {
            var a = this.Arguments[index];
            lock (this.Locker)
            {
                bool valid = true;
                var handlerBase = this._GetHandler();
                if (handlerBase == null)
                {
                    if((this.HookFlags & EventHookFlags.AlwaysRun) == EventHookFlags.None)
                        return;
                    valid = false;
                }

                EventHandler handler = valid ? (EventHandler)handlerBase : null;
                var args = a.ArgFunc(ctx);
                if (args != null)
                {
                    args.Context = ctx;
                    if(valid)
                        handler(args);
                    if (a.AfterFunc != null)
                        a.AfterFunc(ctx, args);
                    if (valid && this._ReduceCounts(1))
                        this._Recalculate();
                }
            }
        }

        /// <summary>
        /// Raises the event with specified argument initializer. This initialize is only called if event has handlers registered.
        /// Returns the arguments after raising event, if no handlers were registered then null is returned.
        /// </summary>
        /// <param name="initArgs">The initialize arguments function.</param>
        /// <returns></returns>
        /// <exception cref="System.InvalidOperationException">Manually invoking hooked event is not allowed!</exception>
        public override T Raise(Func<T> initArgs)
        {
            throw new InvalidOperationException("Manually invoking hooked event is not allowed!");
        }
    }
}
