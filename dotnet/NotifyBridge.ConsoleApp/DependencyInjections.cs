namespace NotifyBridge.ConsoleApp
{
    #region using

    using Microsoft.Extensions.DependencyInjection;
    using NotifyBridge.ConsoleApp.Interop;

    #endregion

    public static class DependencyInjections
    {
        #region Private Fields

        private const string SharedLibraryName = "libnotify_bridge";

        #endregion

        #region Public methods 

        public static IServiceCollection AddInteropServices(this IServiceCollection services)
        {
            services.AddTransient<IEngineInteropFactory , EngineInteropFactory>();
            services.AddSingleton(provider =>
            {
                var factory = provider.GetRequiredService<IEngineInteropFactory>();

                return factory.Create(SharedLibraryName, services);
            });

            return services;
        }

        #endregion
    }
}