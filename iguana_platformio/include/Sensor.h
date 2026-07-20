#include <Arduino.h>
#include <Adafruit_AS7341.h>

class Color_Sensor {
public:
    struct Data {
        double v,b,c,g,gy,y,o,r;
        double cl,nir;

        String toString() const {
            return "V: " + String(v) +
                   ", B: " + String(b) +
                   ", C: " + String(c) +
                   ", G: " + String(g) +
                   ", GY: " + String(gy) +
                   ", Y: " + String(y) +
                   ", O: " + String(o) +
                   ", R: " + String(r) +
                   ", CL: " + String(cl) +
                   ", NIR: " + String(nir);
        }
        
        Data(
        double v,double b,double c,double g,double gy,
        double y,double o,double r,double cl,double nir
        ) : v(v),b(b),c(c),g(g),gy(gy),y(y),o(o),r(r),cl(cl),nir(nir) {}

        Data() : v(0),b(0),c(0),g(0),gy(0),y(0),o(0),r(0),cl(0),nir(0) {}

        bool operator==(const Data& other) const {
            const double eps = 1e-6;

            return fabs(v-other.v) < eps &&
                   fabs(b-other.b) < eps &&
                   fabs(c-other.c) < eps &&
                   fabs(g-other.g) < eps &&
                   fabs(gy-other.gy) < eps &&
                   fabs(y-other.y) < eps &&
                   fabs(o-other.o) < eps &&
                   fabs(r-other.r) < eps &&
                   fabs(cl-other.cl) < eps &&
                   fabs(nir-other.nir) < eps;
        }

        bool operator!=(const Data& other) const {
            return !(*this == other);
        }
    };

    Color_Sensor(int ATIME_in, int ASTEP_in);
    Color_Sensor(int ATIME_in, int ASTEP_in, double gain_in);
    Color_Sensor();

    void gatherData();

    const Data& getReadings();

    const Data invalid{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};

    double getIntegrationTimeInMiliseconds();
    
    bool ready_to_read;

private:
    int ATIME;
    int ASTEP;
    Adafruit_AS7341 sensor;
    double gain;
    Data readings;


};