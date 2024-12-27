namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    using NotifyBridge.ConsoleApp.Native;

    #endregion

    public interface IEngineInterop
    {
        #region Public methods

        public bool IsLoadadSharedLibrary();

        public IntPtr GetMememoyAddress();

        public void InitializeLogger(Action<NativeLogLevel, IntPtr> logCallback);

        public ApiResult InitializeMeasurementTool();

        #endregion        
    }
}