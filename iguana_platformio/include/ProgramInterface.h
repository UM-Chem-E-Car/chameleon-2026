#pragma once

class Program {
public:

    virtual ~Program() = default;

    // Initialize Hardware Here
    virtual void hardware_setup_impl() = 0;

    // Initialize Software Here
    virtual void software_setup_impl() = 0;

    // Called every time after valve opened
    virtual void spin_once() = 0;


};
