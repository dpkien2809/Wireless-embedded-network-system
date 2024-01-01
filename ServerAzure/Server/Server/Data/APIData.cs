using Microsoft.EntityFrameworkCore;
using Server.Model;

namespace Server.Data
{
    public class APIData : DbContext
    {
        public APIData(DbContextOptions options) : base(options)
        {
        }
        public DbSet<Weather> weather { get; set; }
        public DbSet<WeatherShow> weatherShow { get; set; }
        public DbSet<Weather1> weather1 { get; set; }
    }
}