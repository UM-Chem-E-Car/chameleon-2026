#pragma once

class Filter {
public:
    Filter(int WINDOW_SIZE);

    Filter();

    float newAverage(float input);

    ~Filter() { delete[] data; }

private:
    int WS;
    int index;
    float avg;
    float* data;
};

class DDx {
public:
    DDx(float dxn);
    DDx();

    float der(float new_value);
    

    float change(float new_value);

private:
    float dx;
    float last_value;
};


//Unused
/*
class RunningMedian {
public:
    void add(double n) {
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
            return sorted[size / 2];

        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }

private:
    static const int MAX = 5;

    double buffer[MAX];
    double sorted[MAX];

    int size = 0;
    int head = 0;
};
*/
