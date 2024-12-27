namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    using System;
    using System.Runtime.InteropServices;
    using Microsoft.Extensions.Logging;

    #endregion

    public class EngineInterop : IEngineInterop, IDisposable
    {

        #region Fields

        private readonly ILogger<IEngineInterop> _logger;
        private readonly IntPtr _handler = IntPtr.Zero;

        #endregion

        #region Constructor

        public EngineInterop(
            ILogger<IEngineInterop> logger,
            IntPtr handlerEntryPoint
        )
        {
            _logger = logger;
            _handler = handlerEntryPoint;
        }

        #endregion

        #region Public methods

        public bool IsLoadadSharedLibrary()
        {
            return _handler != IntPtr.Zero;
        }

        public void Dispose()
        {
            NativeLibrary.Free(_handler);
        }

        public IntPtr GetMememoyAddress()
        {
            return _handler;
        }

        #endregion
    }
}