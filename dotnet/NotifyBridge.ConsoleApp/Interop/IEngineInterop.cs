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

        public void SetMeasurements(double temp, double hum, double press);

        public IntPtr CreateObserver();

        public ApiResult RemoveObserver(IntPtr observer);

        public ApiResult DeleteObserver(IntPtr observer);

        public ApiResult RegisterObserver(IntPtr observer, Action<float, float, float> notificationCallback);

        #endregion        
    }
}