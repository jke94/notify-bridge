namespace NotifyBridge.ConsoleApp.Logger
{
    #region using

    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.Configuration;

    #endregion

    public static class LoggerExtensions
    {
        public static void LogNativeCode(this ILogger logger, string message)
        {
            logger.LogInformation("{0}", message);
        }
    }
}