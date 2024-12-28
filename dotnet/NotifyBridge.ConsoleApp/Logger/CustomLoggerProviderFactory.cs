namespace NotifyBridge.ConsoleApp.Logger
{
    #region using
    
    using Microsoft.Extensions.Configuration;
    using Microsoft.Extensions.Logging;

    #endregion

    public class CustomLoggerProviderFactory : ICustomLoggerProviderFactory
    {
        public ILoggerProvider Create(IConfiguration configuration)
        {
            var loggerProvider = new CustomLoggerProvider(configuration);
            
            return loggerProvider;
        }
    }

}