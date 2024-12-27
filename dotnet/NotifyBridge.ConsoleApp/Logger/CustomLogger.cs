namespace NotifyBridge.ConsoleApp.Logger
{
    #region using
    
    using System;
    using System.Globalization;
    using System.IO;
    using Microsoft.Extensions.Logging;

    #endregion

    public class CustomLogger : ILogger
    {
        #region Fields

        private readonly string _logFilePath;

        #endregion

        #region Constructor

        public CustomLogger(string logFilePath)
        {
            _logFilePath = logFilePath ?? throw new ArgumentNullException(nameof(logFilePath));
        }

        #endregion

        #region Public Methods

        public IDisposable BeginScope<TState>(TState state) where TState : notnull
        {
            return default!;
        }

        public bool IsEnabled(LogLevel logLevel)
        {
            return logLevel != LogLevel.None;
        }

        public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)
        {
            if (!IsEnabled(logLevel))
            {
                return;
            }

            var logMessage = $"[{CustomFormatDate()}][{logLevel}] {formatter(state, exception)}";

            try
            {
                WriteLogToFile(logMessage);
            }
            catch (IOException ioEx)
            {
                Console.Error.WriteLine($"Failed to write log to file: {ioEx.Message}");
            }
        }

        #endregion

        #region Private Methods

        private void WriteLogToFile(string message)
        {
            using (var writer = new StreamWriter(_logFilePath, append: true))
            {
                writer.WriteLine(message);
            }
        }

        private string CustomFormatDate() => $"{DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff", CultureInfo.InvariantCulture)}";

        #endregion
    }
}