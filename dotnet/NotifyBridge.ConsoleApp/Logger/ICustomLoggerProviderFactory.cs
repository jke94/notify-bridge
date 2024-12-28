namespace NotifyBridge.ConsoleApp.Logger
{
    #region using
    
    using Microsoft.Extensions.Configuration;
    using Microsoft.Extensions.Logging;

    #endregion

    public interface ICustomLoggerProviderFactory
    {
        public ILoggerProvider Create(IConfiguration configuration);
    }
}