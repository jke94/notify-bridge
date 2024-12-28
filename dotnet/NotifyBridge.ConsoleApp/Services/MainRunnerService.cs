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
            _logger.LogInformation("Hello world from NotifyBridge!");
            
            var result = _engineInterop.IsLoadadSharedLibrary();
            _logger.LogInformation("Is load shared library? {0}", result);

            var memoryAddress = _engineInterop.GetMememoyAddress();
            _logger.LogInformation("Memory address {0} (0x{1})", memoryAddress, memoryAddress.ToString("x2"));
            
            _engineInterop.InitializeLogger(LogNativeLoggerCallback);

            _engineInterop.InitializeMeasurementTool();
            
            _engineInterop.SetMeasurements(29.7, 56, 1010.34);

            await Task.CompletedTask;
        }

        #endregion

        #region Private Methods

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