namespace NotifyBridge.ConsoleApp.Native
{
    #region using

    using System;
    using System.Runtime.InteropServices;

    #endregion

    public enum LoggerInfrastructureResult
    {
        /** Something was wrong, contact with the logger author. */
        WTF = -1,

        /** OK, logger callback has initialize correctly. */
        OK = 0,

        /** Failure, You've already initialized the logger! */
        FAILURE_HEY_YOU_HAVE_ALREADY_INITIALIZE_THE_LOGGER = 1,

        /** Failure, callback logger is null! */
        FAILURE_CALLBACK_LOGGER_IS_NULL = 2,

        /** Failure, you are trying configure log minimun level log callback before to initialize! */
        FAILURE_CALLBACK_IS_NULL_PLEASE_INITIALIZE_FIRST_THE_CALLBACK_BEFORE_TO_SET_MIN_LOGGER_LEVEL = 3,
    };

    public enum NativeLogLevel
    {
        VERBOSE = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4
    };

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LogCallback(NativeLogLevel nativeLogLevel, IntPtr logMessagePtr);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate LoggerInfrastructureResult InitLoggerDelegate(LogCallback logCallback);
}