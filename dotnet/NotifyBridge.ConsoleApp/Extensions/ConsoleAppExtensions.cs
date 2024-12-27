namespace NotifyBridge.ConsoleApp.Extensions
{
    #region using

    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.Configuration;
    using NotifyBridge.ConsoleApp.Logger;

    #endregion

    #region Public Methods

    public static class ConsoleAppExtensions
    {
        public static ILoggingBuilder AddFileLogger(this ILoggingBuilder builder, IConfiguration configuration)
        {
            var loggerProvider = new CustomLoggerProvider(configuration);
            loggerProvider.Init();
            
            builder.AddProvider(loggerProvider);

            return builder;
        }
    }

    #endregion
}