namespace NotifyBridge.ConsoleApp.Interop
{
    #region using

    #endregion

    public interface IEngineInterop
    {
        #region Public methods

        public bool IsLoadadSharedLibrary();

        public IntPtr GetMememoyAddress();

        #endregion        
    }
}