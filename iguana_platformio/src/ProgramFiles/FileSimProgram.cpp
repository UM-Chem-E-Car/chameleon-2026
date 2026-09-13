#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#inlcude 

struct DataPoint {
    double time;
    double value;
};

class TimeValueReader {
public:
    explicit TimeValueReader(const std::string& filepath) : file(filepath) {
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filepath);
        }
        // Skip the "Time, Value" header row.
        std::string header;
        std::getline(file, header);
    }
 
    // Fills 'out' with the next pair and returns true, or returns false
    // once the file is exhausted (out is left unchanged in that case).
    bool next(DataPoint& out) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
 
            std::stringstream ss(line);
            std::string timeStr, valueStr;
            if (!std::getline(ss, timeStr, ',')) continue;
            if (!std::getline(ss, valueStr, ',')) continue;
 
            try {
                out.time = std::stod(timeStr);
                out.value = std::stod(valueStr);
            } catch (const std::exception&) {
                continue; // skip a malformed row rather than crash
            }
            return true;
        }
        return false; // end of file
    }
 
    bool isOpen() const { return file.is_open(); }
 
private:
    std::ifstream file;
};


int main(int argc, char* argv[]) {
    std::string path = "data/Reaction1A.csv";
 
    TimeValueReader reader(path);
    DataPoint dp;
    
    while (reader.next(dp)) {
        
        double value = dp.value;
        //double avg_value = valueFilter.newAverage(value);
        double delta_value = derivative.change(value);
        double avg_delta_value = derFilter.newAverage(delta_value);

        if (abs(avg_delta_value) < TRIGGER_VALUE){
            triggers_hit++;
            // Logger::instance().log("TRIGGER HITS: " + String(triggers_hit));
            if (triggers_hit >= TRIGGER_COUNT){
                STORED_REACTION_DATA.time_reaction_end = time;
                return true;
            }
        }
        return false;
    }



    long count = 0;
    while (reader.next(dp)) {
        std::cout << dp.time << ", " << dp.value << "\n";
        count++;
    }
 
    return 0;
}
