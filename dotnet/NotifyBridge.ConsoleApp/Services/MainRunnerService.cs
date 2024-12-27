namespace NotifyBridge.ConsoleApp.Services
{
    #region using

    using System.Runtime.InteropServices;
    using Microsoft.Extensions.Logging;
    using NotifyBridge.ConsoleApp.Native;
    // using InteropDotnetBridge.InteropService.Engine;
    // using InteropDotnetBridge.InteropService.InteropDelegates;
    // using InteropDotnetBridge.InteropService.Logger;

    #endregion

    public class MainRunnerService : IMainRunnerService
    {
        #region Fields

        private readonly ILogger<MainRunnerService> _logger;
        // private readonly IEngineInterop _engineInterop;

        #endregion

        #region Constructor

        public MainRunnerService(
            ILogger<MainRunnerService> logger
            // IEngineInterop engineInterop
        )
        {
            _logger = logger;
            // _engineInterop = engineInterop;
        }

        #endregion

        #region Public Methods

        public async Task RunAsync(string[] args)
        {
            _logger.LogInformation("Hello world from NotifyBridge!");
            
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