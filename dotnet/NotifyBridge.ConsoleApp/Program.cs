namespace NotifyBridge.ConsoleApp
{
    #region using

    using Microsoft.Extensions.Hosting;
    using Microsoft.Extensions.DependencyInjection;
    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.Configuration;
    using NotifyBridge.ConsoleApp.Services;
    using NotifyBridge.ConsoleApp.Logger;

    #endregion

    public class Program
    {
        #region Public methods

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
            .ConfigureServices(services =>
            {
                services.AddInteropServices();
                services.AddTransient<IMainRunnerService, MainRunnerService>();
            })
            .ConfigureLogging((hostBuilderContext, loggingBuilder) =>
            {
                loggingBuilder.ClearProviders();
                loggingBuilder.AddCustomLogger(hostBuilderContext);
            })
            .ConfigureAppConfiguration((hostContext, config) =>
            {
                config.SetBasePath(AppDomain.CurrentDomain.BaseDirectory);
                config.AddJsonFile(
                    "appsettings.json", 
                    optional: false, 
                    reloadOnChange: true);
            });        

        #endregion

        #region Main method

        public static async Task Main(string[] args)
        {
            using var host = CreateHostBuilder(args).Build();
            var mainService = host.Services.GetRequiredService<IMainRunnerService>();

            await mainService.RunAsync(args);            
        }

        #endregion
    }
}
