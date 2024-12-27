namespace NotifyBridge.ConsoleApp.Logger
{
    #region using

    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.Configuration;

    #endregion

    public class CustomLoggerProvider : ILoggerProvider
    {
        private readonly IConfiguration _configuration;
        private readonly string _logFilePath;

        public CustomLoggerProvider(IConfiguration configuration)
        {
            _configuration = configuration;

            _logFilePath = _configuration["Logging:FilePath"] ?? "logs/application.log";

            // Asegurar que el directorio existe
            var logDirectory = Path.GetDirectoryName(_logFilePath);
            if (!string.IsNullOrWhiteSpace(logDirectory) && !Directory.Exists(logDirectory))
            {
                Directory.CreateDirectory(logDirectory);
            }
        }

        public ILogger CreateLogger(string categoryName)
        {
            return new CustomLogger(_logFilePath);
        }

        public void Dispose()
        {
            // No se necesita limpiar recursos específicos
        }

        #region Public Methods

        public void Init()
        {
            // Opcional: inicialización adicional si fuera necesario
        }

        #endregion
    }
}
