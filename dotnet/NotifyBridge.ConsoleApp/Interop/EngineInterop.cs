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
            _logger.LogInformation("Dispose handler: {0} (0x{1})", _handler, _handler.ToString("x2"));

            NativeLibrary.Free(_handler);
        }

        public IntPtr GetMememoyAddress()
        {
            return _handler;
        }

        public void InitializeLogger(Action<NativeLogLevel, IntPtr> logCallback)
        {
            var initializeLogger = GetDelegateFromNativeFunction<InitLoggerDelegate>("initializeLogger");

            void OnLogCallback(NativeLogLevel nativeLogLevel, IntPtr logMessage)
            {
                logCallback(nativeLogLevel, logMessage);
            }

            LoggerInfrastructureResult result = initializeLogger(OnLogCallback);

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

        public IntPtr CreateObserver()
        {
            var createObserver = GetDelegateFromNativeFunction<CreateObserverDelegate>("createObserver");

            IntPtr observerPtr = createObserver();

            _logger.LogInformation("Create observer: {0} (0x{1})", observerPtr, observerPtr.ToString("x2"));

            return observerPtr;
        }

        public ApiResult RemoveObserver(IntPtr observer)
        {
            var removeObserver = GetDelegateFromNativeFunction<RemoveObserverDelegate>("removeObserver");

            ApiResult apiResult = removeObserver(observer);

            _logger.LogInformation("Remove observer: {0} (0x{1}) with result: {3}", observer, observer.ToString("x2"), apiResult);

            return apiResult;
        }

        public ApiResult DeleteObserver(IntPtr observer)
        {
            _logger.LogInformation("Trying to delete observer: {0} (0x{1})", observer, observer.ToString("x2"));

            var deleteObserver = GetDelegateFromNativeFunction<DeleteObserverDelegate>("deleteObserver");

            ApiResult apiResult = deleteObserver(observer);

            _logger.LogInformation("Delete observer result: {0}", apiResult);

            return apiResult;
        }
        public ApiResult RegisterObserver(IntPtr observer, Action<float, float, float> notificationCallback)
        {
            var registerObserver = GetDelegateFromNativeFunction<RegisterObserverDelegate>("registerObserver");

            void OnNotificationCallback(float temp, float hum, float press)
            {
                notificationCallback(temp, hum, press);
            }

            ApiResult apiResult = registerObserver(observer, OnNotificationCallback);

            _logger.LogInformation("Registred observer: {0} (0x{1}) with result: {3}", observer, observer.ToString("x2"), apiResult);

            return apiResult;
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