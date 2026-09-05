#pragma once

class Program {
public:

    virtual ~Program() = default;

    // Initialize Hardware Here
    virtual void setup_impl() = 0;

    // Called every time after valve opened
    virtual void loop_impl() = 0;


};
