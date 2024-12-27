namespace NotifyBridge.ConsoleApp.Services
{
    public interface IMainRunnerService
    {
        #region Public Methods

        public Task RunAsync(string[] args);

        #endregion
    }    
}