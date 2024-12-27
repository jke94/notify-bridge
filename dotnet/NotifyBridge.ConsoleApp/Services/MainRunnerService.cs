namespace NotifyBridge.ConsoleApp.Services
{
    #region using

    using Microsoft.Extensions.Logging;
    using NotifyBridge.ConsoleApp.Interop;

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
            
            await Task.CompletedTask;
        }

        #endregion

        #region Private Methods

        // private void logNativeLoggerCallback(NativeLogLevel nativeLogLevel, IntPtr logMessagePtr)
        // {
        //     string logMessage = Marshal.PtrToStringAuto(logMessagePtr);

        //     string logLevel = nativeLogLevel switch
        //     {
        //         NativeLogLevel.VERBOSE => "VERBOSE",
        //         NativeLogLevel.INFO => "INFO",
        //         NativeLogLevel.WARNING => "WARNING",
        //         NativeLogLevel.ERROR => "ERROR",
        //         NativeLogLevel.CRITICAL => "CRITICAL",
        //         _ => "UNKNOWN_LOG_LEVEL",
        //     };

        //     _logger.LogNativeCode($"[NATIVE_CODE][{logLevel}] {logMessage}");
        // }

        #endregion
    }
}