using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools._Internal
{
    public static class RTHandler
    {
        public static CPURegisters _Allocate(IntPtr addr)
        {
            return new CPURegisters(addr, null);
        }

        public static void _Free(CPURegisters cpu)
        {

        }
        
        /// <summary>
        /// Suspends all threads in current process except the executing thread.
        /// </summary>
        internal static void SuspendAllThreadsInCurrentProcess()
        {
            var threads = System.Diagnostics.Process.GetCurrentProcess().Threads;
            var cur = GetCurrentThreadId();

            for(int i = 0; i < threads.Count; i++)
            {
                var t = threads[i];

                if (t.Id == cur)
                    continue;

                var handle = OpenThread(2, false, t.Id);
                if(handle != IntPtr.Zero)
                {
                    SuspendThread(handle);
                    CloseHandle(handle);
                }
            }
        }

        /// <summary>
        /// Exits the process.
        /// </summary>
        /// <param name="graceful">Is this graceful exit or should we kill.</param>
        internal static void ExitProcess(bool graceful)
        {
            try
            {
                Main.Shutdown();
            }
            catch
            {

            }

            if (graceful)
                Environment.Exit(0);
            else
                System.Diagnostics.Process.GetCurrentProcess().Kill();
        }

        #region API calls

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool CloseHandle(IntPtr hObject);
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenThread(uint dwDesiredAccess, bool bInheritHandle, int dwThreadId);
        [DllImport("kernel32.dll")]
        private static extern uint SuspendThread(IntPtr hThread);
        [DllImport("kernel32.dll")]
        internal static extern int GetCurrentThreadId();

        #endregion
    }
}
