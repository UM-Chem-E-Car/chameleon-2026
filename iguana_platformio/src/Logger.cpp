#include <Arduino.h>
#include <fcntl.h>



class Logger {
    public:
    
        Logger* instance(){
            if (logger == nullptr){
                logger = new Logger();
            }
            return this;
        }

        Logger::~Logger(){
            delete logger;
        }
        
        //Requires valid string args
        //Logger passes args to terminal
        void Logger::log_to_terminal(String args){
            Serial.print(args);
            
        }
        
        //
        //
        void Logger::log_to_file(String args){
            
            //input_file
        }

        //
        //
        void Logger::export_file(){
            
        }

        //
        //
        void Logger::open_file(/*fstream & file*/){
            // file.open(___); //need input file name? Pass as an arg or 
            // if(file.!is_open()){
            //     in_file_open = false;
            // }
            // else{
            //     out_file_open = true;
            // }
        }



    private:
    

    Logger(){

    }

    Logger* logger = nullptr;
    
    bool is_logging;
    bool in_file_open;
    bool out_file_open;
    // std::ifstream input_file;
    // std::ofstream output_file;
};
