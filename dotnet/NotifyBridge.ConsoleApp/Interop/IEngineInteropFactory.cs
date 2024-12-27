namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    using Microsoft.Extensions.DependencyInjection;
    
    #endregion

    public interface IEngineInteropFactory
    {
        #region Public Methods

        IEngineInterop Create(string nativeLibraryName, IServiceCollection services);

        #endregion
    }
}