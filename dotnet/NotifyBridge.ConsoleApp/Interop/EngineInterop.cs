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
            var initializeLogger = GetDelegateFromNativeFunction<InitLoggerDelegate>("initializeLogger");

            void logCallback_(NativeLogLevel nativeLogLevel, IntPtr logMessage)
            {
                logCallback(nativeLogLevel, logMessage);
            }

            LoggerInfrastructureResult result = initializeLogger(logCallback_);

            _logger.LogInformation("Native logger initialization result {0}", result);
        }

        public ApiResult InitializeMeasurementTool()
        {
            var initializeMeasurementTool = GetDelegateFromNativeFunction<InitializeMeasurementTool>("initializeMeasurementTool");

            ApiResult apiResult = initializeMeasurementTool();

            _logger.LogInformation("Initialization measurement tool result {0}", apiResult);

            return apiResult;
        }

        public void SetMeasurements(double temp, double hum, double press)
        {
            _logger.LogInformation("Set measurements. Temperature: {0}, Humidity: {1}, Pressure: {2}", temp, hum, press);

            var setMeasurements = GetDelegateFromNativeFunction<SetMeasurements>("setMeasurements");

            setMeasurements((float)temp, (float)hum, (float)press);
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