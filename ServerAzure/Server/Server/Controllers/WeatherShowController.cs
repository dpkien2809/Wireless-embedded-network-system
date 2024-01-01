using Microsoft.AspNetCore.Mvc;
using Server.Model;
using Microsoft.EntityFrameworkCore;
using Server.Data;
using Microsoft.Data.SqlClient;

namespace Server.Controllers
{
    [ApiController]
    [Route("api/weatherShow")]
    public class WeatherShowController : Controller
    {
        private readonly APIData dbContext;

        public WeatherShowController(APIData dbContext)
        {
            this.dbContext = dbContext;
        }
        // get: lấy dữ liệu
        [HttpGet]
        public async Task<IActionResult> Get()
        {
            return Ok(await dbContext.weatherShow.ToListAsync());
        }

        [HttpGet]
        [Route("{id:int}")]
        public async Task<IActionResult> GetOne([FromRoute] int id)
        {
            var wea = await dbContext.weatherShow.FindAsync(id);
            if (wea == null) { return NotFound(); }
            return Ok(wea);
        }
        // post: tạo data mới
        [HttpPost]
        public async Task<IActionResult> Add(WeatherRequest request)
        {
            var weather1 = new WeatherShow()
            {

                Temp = request.Temp,
                Humidity = request.Humidity,
                Pressure = request.Pressure,
                DayTime = DateTime.Now.ToString("dd/MM/yyyy HH:mm:ss"),
                Predict = request.Predict,
        };
            await dbContext.weatherShow.AddAsync(weather1);
            await dbContext.SaveChangesAsync();
            return Ok(weather1);
        }
        // Thay đổi giá trị ( cập nhật giá trị thời tiết)
        [HttpPut]
        [Route("{id:int}")]
        public async Task<IActionResult> Update([FromRoute] int id, WeatherRequest updateRequest)
        {
            var wea = await dbContext.weatherShow.FindAsync(id);
            DateTime currentTime = DateTime.Now;
            if (wea != null)
            {
                wea.Temp = updateRequest.Temp;
                wea.Pressure = updateRequest.Pressure;
                wea.Humidity = updateRequest.Humidity;
                wea.DayTime = currentTime.ToString("dd/MM/yyyy HH:mm:ss");
                wea.Predict = updateRequest.Predict;

                await dbContext.SaveChangesAsync();

                return Ok(wea);
            }
            return NotFound();
        }
    }
}

