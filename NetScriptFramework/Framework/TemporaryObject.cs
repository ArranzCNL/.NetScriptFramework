using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Temporary object that will clean up resources when disposed.
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    public abstract class TemporaryObject : IDisposable
    {
        /// <summary>
        /// The pinned state.
        /// </summary>
        private int Pinned = 0;

        /// <summary>
        /// Pins this object and prevents it from being freed automatically when the instance is disposed.
        /// </summary>
        public void Pin()
        {
            Interlocked.Increment(ref this.Pinned);
        }

        /// <summary>
        /// Unpins this object and allows the underlying resources to be freed when this instance is disposed.
        /// </summary>
        public void Unpin()
        {
            Interlocked.Decrement(ref this.Pinned);
        }

        /// <summary>
        /// Frees resources.
        /// </summary>
        protected abstract void Free();
        
        #region IDisposable interface

        /// <summary>
        /// Internal value to avoid redundant calls.
        /// </summary>
        private bool disposedValue = false;

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources.
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        private void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                //if (disposing) { }

                if (this.Pinned == 0)
                    this.Free();

                disposedValue = true;
            }
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="TemporaryObject"/> class.
        /// </summary>
        ~TemporaryObject()
        {
            Dispose(false);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion
    }
}
