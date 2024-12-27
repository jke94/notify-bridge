namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    using System;
    using System.Runtime.InteropServices;
    using Microsoft.Extensions.Logging;
    using NotifyBridge.ConsoleApp.Native;

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

        public void InitializeLogger(Action<NativeLogLevel, IntPtr> logCallback)
        {
            var nativeDelegate = GetDelegateFromNativeFunction<InitLoggerDelegate>("initializeLogger");

            void logCallback_(NativeLogLevel nativeLogLevel, IntPtr logMessage)
            {
                logCallback(nativeLogLevel, logMessage);
            }

            LoggerInfrastructureResult result = nativeDelegate(logCallback_);

            _logger.LogInformation("Native logger initialization result {0}", result);
        }

        #endregion


        #region Private Methods

        private TDelegate GetDelegateFromNativeFunction<TDelegate>(string functionNativeName) 
            where TDelegate : Delegate
        {
            if (NativeLibrary.TryGetExport(_handler, functionNativeName, out IntPtr handle))
            {
                return Marshal.GetDelegateForFunctionPointer<TDelegate>(handle);
            }

            throw new EntryPointNotFoundException(functionNativeName);
        }

        #endregion
    }
}