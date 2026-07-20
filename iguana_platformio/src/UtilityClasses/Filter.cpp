#include "Filter.h"
#include "ConfigVariables.h"

Filter::Filter(int WINDOW_SIZE) 
: WS(WINDOW_SIZE), index(1), data(new float[WINDOW_SIZE]){
  for (int i = 0; i < WINDOW_SIZE; i++){
    data[i] = 0;
  }
}

Filter::Filter() : Filter(CONFIG.FILTER.WINDOW_SIZE){}

float Filter::newAverage(float input) {
  int windex = index % WS;
  if (index < WS) {
    data[windex] = input;
    avg += input / WS;
    float ret = (data[index - 1] + input) / index;
    index += 1;
    return ret;
  } else {
    avg += (input / WS) - (data[windex] / WS);
    data[windex] = input;
    index += 1;
    return avg;
  }
}




DDx::DDx(float dxn) : dx(dxn) {}

DDx::DDx() : DDx(CONFIG.RUNTIME.DT){}

float DDx::der(float new_value){
    float d = (new_value - last_value)/dx;
    last_value = new_value;
    return d;
}

float DDx::change(float new_value){
  float d = last_value - new_value;
  last_value = new_value;
  return d;
}
