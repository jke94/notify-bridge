namespace NotifyBridge.ConsoleApp.Services
{

    #region using

    using System.Runtime.InteropServices;
    using Microsoft.Extensions.Logging;
    using NotifyBridge.ConsoleApp.Interop;
    using NotifyBridge.ConsoleApp.Native;

    #endregion

    public class MainRunnerService : IMainRunnerService
    {
        #region Fields

        private readonly ILogger<MainRunnerService> _logger;
        private readonly IEngineInterop _engineInterop;


        #endregion

        #region Constructor

        public MainRunnerService(
            ILogger<MainRunnerService> logger,
            IEngineInterop engineInterop
        )
        {
            _logger = logger;
            _engineInterop = engineInterop;
        }

        #endregion

        #region Public Methods

        public async Task RunAsync(string[] args)
        {
            // A. Logging entry point.
            _logger.LogInformation("Hello world from NotifyBridge!");
            
            // B. Check if shared library is correctyle lodaded.
            var result = _engineInterop.IsLoadadSharedLibrary();
            
            _logger.LogInformation("Is load shared library? {0}", result);

            // C. Get memory address of shared library handler.
            var memoryAddress = _engineInterop.GetMememoyAddress();
            
            _logger.LogInformation("Memory address {0} (0x{1})", memoryAddress, memoryAddress.ToString("x2"));
            
            // D. Initialize logger of shared library to library's traces.
            _engineInterop.InitializeLogger(LogNativeLoggerCallback);

            //----------------------------------------
            // Playing with bussiness library logic.
            //----------------------------------------
            
            // E. Initialize measurement tool to generate events.
            _engineInterop.InitializeMeasurementTool();
            
            // F. nitialize measurement tool to generate events.
            _engineInterop.SetMeasurements(29.7, 56, 1010.34);

            // G. Create observers to receive events.
            IntPtr observerA = _engineInterop.CreateObserver();
            IntPtr observerB = _engineInterop.CreateObserver();

            // H. Add subcriber (observer) to be notify.
            _engineInterop.RegisterObserver(observerA, ObserverA_OnNotification);
            _engineInterop.RegisterObserver(observerB, ObserverB_OnNotification);

            // I. Create event to notify to the subscribers (observers).
            _engineInterop.SetMeasurements(11.1, 35.2, 1001.10);

            // J. Remove observer of the measurement tool to avoid receive events.
            _engineInterop.RemoveObserver(observerA);

            // K. Delete observers. Free memory.
            _engineInterop.DeleteObserver(observerA);
            _engineInterop.DeleteObserver(observerB);

            await Task.CompletedTask;
        }

        #endregion

        #region Private Methods

        public void ObserverA_OnNotification(float temp, float hum, float press)
        {
            _logger.LogInformation("I am observer A! Notification received: Temperature={0} ºC, Humidity={1} %, Pressure={2} hPa", temp, hum, press);
        }

        public void ObserverB_OnNotification(float temp, float hum, float press)
        {
            var fahrenheitTemp = temp * (9/5) + 32;
            _logger.LogInformation(
                "I am observer B! Notification received: Temperature={0} ºC ({1} ºF), Humidity={2} %, Pressure={3} hPa", 
                temp, fahrenheitTemp, hum, press);
        }        

        private void LogNativeLoggerCallback(NativeLogLevel nativeLogLevel, IntPtr logMessagePtr)
        {
            string? logMessage = Marshal.PtrToStringAuto(logMessagePtr);

            string logLevel = nativeLogLevel switch
            {
                NativeLogLevel.VERBOSE => "VERBOSE",
                NativeLogLevel.INFO => "INFO",
                NativeLogLevel.WARNING => "WARNING",
                NativeLogLevel.ERROR => "ERROR",
                NativeLogLevel.CRITICAL => "CRITICAL",
                _ => "UNKNOWN_LOG_LEVEL",
            };

            _logger.LogInformation($"[NATIVE_CODE][{logLevel}]{logMessage}");
        }

        #endregion
    }
}