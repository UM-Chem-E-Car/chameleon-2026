class Filter{
  public:
    Filter(int WINDOW_SIZE) 
            : WS(WINDOW_SIZE), index(1), data(new float[WINDOW_SIZE]){}

    float average(float input) {
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
    ~Filter() { delete[] data; }

  private:
      int WS;
      float * data;
      int index;
      float avg;
};

class DDx{
  public:
    DDx(float dxn) : dx(dxn) {}
    float der(float new_value){
       float d = (new_value - last_value)/dx;
       last_value = new_value;
       return d;
    }

    float change(float new_value){
      float d = last_value - new_value;
      last_value = new_value;
      return d;
    }
  private:
      float dx;
      float last_value;
};