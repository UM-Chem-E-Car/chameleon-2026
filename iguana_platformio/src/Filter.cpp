class Filter{
  public:
    Filter(int WINDOW_SIZE) 
            : WS(WINDOW_SIZE), index(1), data(new float[WINDOW_SIZE]){
              for (int i = 0; i < WINDOW_SIZE; i++){
                data[i] = 0;
              }
            }

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
      int index;
      float avg;
      float * data;
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

class RunningMedian {
private:
    static const int MAX = 5;

    double buffer[MAX];   // circular buffer
    double sorted[MAX];   // sorted copy

    int size = 0;
    int head = 0;

public:

    void add(double n) {

        // remove oldest if full
        if (size == MAX) {

            double old = buffer[head];

            int i = 0;
            while (sorted[i] != old) i++;

            for (; i < size - 1; i++)
                sorted[i] = sorted[i + 1];

            size--;
        }

        buffer[head] = n;
        head = (head + 1) % MAX;

        int i = size - 1;

        while (i >= 0 && sorted[i] > n) {
            sorted[i + 1] = sorted[i];
            i--;
        }

        sorted[i + 1] = n;
        size++;
    }

    double median() {

        if (size == 0)
            return 0;

        if (size % 2)
            return sorted[size/2];

        return (sorted[size/2 - 1] + sorted[size/2]) / 2.0;
    }
};