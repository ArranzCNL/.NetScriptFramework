using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools
{
    /// <summary>
    /// Unique ID generator.
    /// </summary>
    internal sealed class UIDGenerator
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="UIDGenerator"/> class.
        /// </summary>
        internal UIDGenerator()
        {
            var now = DateTime.UtcNow;
            var min = new DateTime(1990, 1, 1);
            ulong high = 0;
            if (now >= min)
            {
                high = unchecked((ulong)((now - min).TotalSeconds));
                if (high > (ulong)int.MaxValue)
                    high = 0;
            }
            if(high == 0)
                high = (ulong)Randomizer.NextInt(1, int.MaxValue);

            this.HighPart = high << 32;
        }

        /// <summary>
        /// The high part for unique IDs. This is generated from timestamp.
        /// </summary>
        private readonly ulong HighPart = 0;

        /// <summary>
        /// The low part for unique IDs. This is a counter.
        /// </summary>
        private int LowPart = 0;

        /// <summary>
        /// Generates a unique ID.
        /// </summary>
        /// <returns></returns>
        internal long Generate()
        {
            ulong result = this.HighPart;
            int low = System.Threading.Interlocked.Increment(ref this.LowPart);
            if (low == 0)
            {
                Main.CriticalException("UIDGenerator encountered an overflow! Too many IDs were generated.", true);
                return 0;
            }
            result |= unchecked((uint)low);
            return unchecked((long)result);
        }
    }
}
