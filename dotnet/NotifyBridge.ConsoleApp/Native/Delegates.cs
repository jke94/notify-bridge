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

    public enum ApiResult
    {
        WTF = -1,
        SUCCESS = 0,
        FAILURE = 1,
        FAILURE_ELEMENT_NOT_FOUND = 2,
        FAILURE_ELEMENT_IS_NULL = 3
    };

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate ApiResult InitializeMeasurementTool();

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SetMeasurements(Single temp, Single hum, Single press);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate IntPtr CreateObserverDelegate();

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate ApiResult RemoveObserverDelegate(IntPtr observer);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate ApiResult DeleteObserverDelegate(IntPtr observer);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void NotificationDelegate(Single temp, Single hum, Single press);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate ApiResult RegisterObserverDelegate(IntPtr observer, NotificationDelegate notification);
}