namespace Server.Model
{
    public class WeatherShow
    {
        public int ID { get; set; }
        public string? Temp { get; set; }
        public string? Humidity { get; set; }
        public string? Pressure { get; set; }
        public string? DayTime { get; set; }
        public string? Predict { get; set; }
    }
}
