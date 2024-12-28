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
            
            // D, Initialize logger of shared library to library's traces.
            _engineInterop.InitializeLogger(LogNativeLoggerCallback);

            // E. Playing with busssiness logic of the library. Initialize measurement tool to generate events.
            _engineInterop.InitializeMeasurementTool();
            
            // F. Playing with busssiness logic of the library. Initialize measurement tool to generate events.
            _engineInterop.SetMeasurements(29.7, 56, 1010.34);

            // G. Playing with busssiness logic of the library. Create observer to receive events.
            IntPtr observerA = _engineInterop.CreateObserver();

            // H. Playing with busssiness logic of the library. Add subcriber (observer) to be notify.

            _engineInterop.RegisterObserver(observerA, ObserverA_OnNotification);

            // I. Playing with busssiness logic of the library. Create event to notify to the subscribers (observers).
            _engineInterop.SetMeasurements(11.1, 35.2, 1001.10);

            _engineInterop.DeleteObserver(observerA);

            await Task.CompletedTask;
        }

        #endregion

        #region Private Methods

        public void ObserverA_OnNotification(float temp, float hum, float press)
        {
            _logger.LogInformation("I am observer A! Notification received: Temperature={0}, Humidity={1}, Pressure={2}", temp, hum, press);
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