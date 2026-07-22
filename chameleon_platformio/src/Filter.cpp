class Filter {
public:
    Filter(int window)
        : WS(window),
          index(0),
          count(0),
          sum(0.0f),
          data(new float[window])
    {
        for (int i = 0; i < WS; i++)
            data[i] = 0.0f;
    }

    float average(float input)
    {
        int windex = index % WS;

        if (count < WS)
        {
            // Still filling the buffer
            data[windex] = input;
            sum += input;
            count++;
        }
        else
        {
            // Replace oldest sample
            sum += input - data[windex];
            data[windex] = input;
        }

        index++;

        return sum / count;
    }

    ~Filter()
    {
        delete[] data;
    }

private:
    int WS;
    int index;
    int count;
    float sum;
    float* data;
};

class DDx {
public:
    DDx(float dxn)
        : dx(dxn),
          last_value(0.0f),
          first(true)
    {}

    float der(float new_value)
    {
        if (first)
        {
            first = false;
            last_value = new_value;
            return 0.0f;
        }

        float d = (new_value - last_value) / dx;
        last_value = new_value;
        return d;
    }

    float change(float new_value)
    {
        if (first)
        {
            first = false;
            last_value = new_value;
            return 0.0f;
        }

        float d = last_value - new_value;
        last_value = new_value;
        return d;
    }

private:
    float dx;
    float last_value;
    bool first;
};

class RunningMedian {
private:
    static const int MAX = 5;

    double buffer[MAX];
    double sorted[MAX];

    int size = 0;
    int head = 0;

public:
    void add(double n)
    {
        if (size == MAX)
        {
            double old = buffer[head];

            int i = 0;
            while (i < size && sorted[i] != old)
                i++;

            for (; i < size - 1; i++)
                sorted[i] = sorted[i + 1];

            size--;
        }

        buffer[head] = n;
        head = (head + 1) % MAX;

        int i = size - 1;
        while (i >= 0 && sorted[i] > n)
        {
            sorted[i + 1] = sorted[i];
            i--;
        }

        sorted[i + 1] = n;
        size++;
    }

    double median() const
    {
        if (size == 0)
            return 0.0;

        if (size % 2 == 1)
            return sorted[size / 2];

        return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    }
};