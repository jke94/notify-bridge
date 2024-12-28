namespace NotifyBridge.ConsoleApp.Logger
{
    #region using

    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.DependencyInjection;
    using Microsoft.Extensions.Hosting;

    #endregion

    #region Public Methods

    public static class LoggerAppExtensions
    {
        public static ILoggingBuilder AddCustomLogger(this ILoggingBuilder loggingBuilder, HostBuilderContext hostBuilderContext)
        {
            loggingBuilder.Services.AddTransient<CustomLoggerProvider>();
            loggingBuilder.Services.AddTransient<ICustomLoggerProviderFactory, CustomLoggerProviderFactory>();

            loggingBuilder.Services.AddSingleton(loggerProvider =>
            {
                var factory = loggerProvider.GetRequiredService<ICustomLoggerProviderFactory>();
                var configuration = hostBuilderContext.Configuration;

                return factory.Create(configuration);
            });

            var serviceProvider = loggingBuilder.Services.BuildServiceProvider();

            var loggerProvider = serviceProvider.GetRequiredService<CustomLoggerProvider>();
            loggerProvider.Init();

            return loggingBuilder;
        }
    }

    #endregion
}