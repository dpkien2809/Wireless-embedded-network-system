using Microsoft.AspNetCore.Mvc;
using Server.Model;
using Microsoft.EntityFrameworkCore;
using Server.Data;
using Microsoft.Data.SqlClient;

namespace Server.Controllers
{
    [ApiController]
    [Route("api/weather")]
    public class WeatherController : Controller
    {
        private readonly APIData dbContext;

        public WeatherController(APIData dbContext)
        {
            this.dbContext = dbContext;
        }
        // get: lấy dữ liệu
        [HttpGet]
        public async Task<IActionResult> Get()
        {
            return Ok(await dbContext.weather.ToListAsync());
        }
        
        [HttpGet]
        [Route("{id:int}")]
        public async Task<IActionResult> GetOne([FromRoute] int id)
        {
            var wea = await dbContext.weather.FindAsync(id);
            if (wea == null) { return NotFound(); }
            return Ok(wea);
        }
        // post: tạo data mới
        [HttpPost]
        public async Task<IActionResult> Add(WeatherRequest request)
        {
            DateTime currentTime = DateTime.Now;
            DateTime newTime = currentTime.AddHours(7);
            var weather1 = new Weather()
            {
                Temp = request.Temp,
                Humidity = request.Humidity,
                Pressure = request.Pressure,
                DayTime = newTime.ToString("dd/MM/yyyy HH:mm:ss"),
                Predict = request.Predict,
        };
            await dbContext.weather.AddAsync(weather1);
            await dbContext.SaveChangesAsync();
            // Thay đổi giá trị trong weatherShow
            var wea = await dbContext.weatherShow.FindAsync(1);
            if (wea != null)
            {
                wea.Temp = request.Temp;
                wea.Pressure = request.Pressure;
                wea.Humidity = request.Humidity;
                wea.DayTime = newTime.ToString("dd/MM/yyyy HH:mm:ss");
                wea.Predict = request.Predict;
                await dbContext.SaveChangesAsync();
            }
            else { return NotFound(); }

            return Ok(weather1);
        }
        [HttpPut]
        [Route("{id:int}")]
        public async Task<IActionResult> Update([FromRoute] int id, WeatherRequest updateRequest)
        {
            DateTime currentTime = DateTime.Now;
            DateTime newTime = currentTime.AddHours(7);
            var wea = await dbContext.weather.FindAsync(id);
            if (wea != null)
            {
                wea.Temp = updateRequest.Temp;
                wea.Pressure = updateRequest.Pressure;
                wea.Humidity = updateRequest.Humidity;
                wea.DayTime = newTime.ToString("dd/MM/yyyy HH:mm:ss");
                wea.Predict = updateRequest.Predict;
                await dbContext.SaveChangesAsync();

                return Ok(wea);
            }
            return NotFound();
        }
    }
}
