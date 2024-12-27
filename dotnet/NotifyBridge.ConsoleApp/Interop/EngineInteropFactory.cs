namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    using System.Runtime.InteropServices;
    using Microsoft.Extensions.Logging;
    using Microsoft.Extensions.DependencyInjection;

    #endregion

    public class EngineInteropFactory : IEngineInteropFactory
    {
        #region Public Methods

        public IEngineInterop Create(string nativeLibraryName, IServiceCollection services)
        {
            // A. Load shared library.
            var handlerEntryPoint = NativeLibrary.Load(
                nativeLibraryName,
                typeof(EngineInterop).Assembly,
                DllImportSearchPath.AssemblyDirectory
            );

            // B. Build service provider.
            var serviceProvider = services.BuildServiceProvider();

            var logger = serviceProvider.GetRequiredService<ILogger<EngineInterop>>();

            // C. Build engine interop.
            var engineInterop = new EngineInterop(logger, handlerEntryPoint);

            return engineInterop;
        }

        #endregion

    }
}