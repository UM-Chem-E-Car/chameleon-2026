#include <Arduino.h>
#include <Adafruit_AS7341.h>

class Color_Sensor {
public:
    Color_Sensor(): ready_to_read(false), sensor(), readings() {}

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

    bool init(int ATIME, int ASTEP){

        if(!sensor.begin()){
            Serial.println("AS7341 not detected");
            return false;
        }

        sensor.setATIME(ATIME);
        sensor.setASTEP(ASTEP);
        sensor.setGain(AS7341_GAIN_256X);

        sensor.enableSpectralMeasurement(true);

        return true;
    }

    void gatherData(){

        if(!sensor.getIsDataReady())
            return;

        Data ret{};

        if(!sensor.readAllChannels()){
            Serial.println("Sensor read failed");
            return;
        }

        ret.v  = sensor.getChannel(AS7341_CHANNEL_415nm_F1) / 65536.0 * 100;
        ret.b  = sensor.getChannel(AS7341_CHANNEL_445nm_F2) / 65536.0 * 100;
        ret.c  = sensor.getChannel(AS7341_CHANNEL_480nm_F3) / 65536.0 * 100;
        ret.g  = sensor.getChannel(AS7341_CHANNEL_515nm_F4) / 65536.0 * 100;
        ret.gy = sensor.getChannel(AS7341_CHANNEL_555nm_F5) / 65536.0 * 100;
        ret.y  = sensor.getChannel(AS7341_CHANNEL_590nm_F6) / 65536.0 * 100;
        ret.o  = sensor.getChannel(AS7341_CHANNEL_630nm_F7) / 65536.0 * 100;
        ret.r  = sensor.getChannel(AS7341_CHANNEL_680nm_F8) / 65536.0 * 100;
        ret.cl = sensor.getChannel(AS7341_CHANNEL_CLEAR) / 65536.0 * 100;
        ret.nir= sensor.getChannel(AS7341_CHANNEL_NIR) / 65536.0 * 100;

        if(ret != readings){
            readings = ret;
            ready_to_read = true;
            return;
        }
    }

    const Data& getReadings() {
        if (!ready_to_read){
            Serial.println("NOT READY");
            return invalid;
        }
        ready_to_read = false;
        return readings;
    }

    const Data invalid{NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN};

    bool ready_to_read;

private:
    Adafruit_AS7341 sensor;
    Data readings;
};