#include <Adafruit_AS7341.h>

class Color_Sensor{
public:
    struct Data {
        double v, b, c, g, gy, y, o, r;
        double cl, nir;

        String toString(){
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

        bool operator==(const Data& other) const {
            const double eps = 1e-6;

            return fabs(v - other.v) < eps &&
                fabs(b - other.b) < eps &&
                fabs(c - other.c) < eps &&
                fabs(g - other.g) < eps &&
                fabs(gy - other.gy) < eps &&
                fabs(y - other.y) < eps &&
                fabs(o - other.o) < eps &&
                fabs(r - other.r) < eps &&
                fabs(cl - other.cl) < eps &&
                fabs(nir - other.nir) < eps;
        }

        bool operator!=(const Data& other) const{
            return !operator==(other);
        }

    };

    Color_Sensor(): sensor(), readings(){}

    bool init(int ATIME, int ASTEP) {
        if (!sensor.begin()) {
            Serial.println("Could not find AS7341");
            return false;
        }

        sensor.setATIME(ATIME);
        sensor.setASTEP(ASTEP);
        sensor.setGain(AS7341_GAIN_256X);
        sensor.enableSpectralMeasurement(true);

        return true;
    }

    bool read(){
        if (!sensor.getIsDataReady()) {
            return false;   // No new data yet
        }
        Data ret{};
        if (!sensor.readAllChannels()) {
            Serial.println("Failed to read sensor");
            return false;
        }
        ret.v = (double) sensor.getChannel(AS7341_CHANNEL_415nm_F1) / 65536.0 * 100;
        ret.b = (double) sensor.getChannel(AS7341_CHANNEL_445nm_F2) / 65536.0 * 100;
        ret.c = (double) sensor.getChannel(AS7341_CHANNEL_480nm_F3) / 65536.0 * 100;
        ret.g = (double) sensor.getChannel(AS7341_CHANNEL_515nm_F4) / 65536.0 * 100;
        ret.gy = (double) sensor.getChannel(AS7341_CHANNEL_555nm_F5) / 65536.0 * 100;
        ret.y = (double) sensor.getChannel(AS7341_CHANNEL_590nm_F6) / 65536.0 * 100;
        ret.o = (double) sensor.getChannel(AS7341_CHANNEL_630nm_F7) / 65536.0 * 100;
        ret.r = (double) sensor.getChannel(AS7341_CHANNEL_680nm_F8) / 65536.0 * 100;
        ret.cl = (double) sensor.getChannel(AS7341_CHANNEL_CLEAR) / 65536.0 * 100;
        ret.nir = (double) sensor.getChannel(AS7341_CHANNEL_NIR) / 65536.0 * 100;
        if (ret != readings){
            readings = ret;
            ping();
            return true;
        }
        return false;
    }

    bool ping(){
        Serial.println("TIME: " + String(millis()) + " -> " + readings.toString());
        return true;
    }



    Adafruit_AS7341 sensor;
    Data readings;
};
