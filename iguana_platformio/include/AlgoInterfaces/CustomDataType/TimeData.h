#pragma once

struct TimeData {
    double time_reaction_end;

    TimeData() : time_reaction_end(-1){};
    bool operator==(const TimeData& rhs) const {
        if (time_reaction_end != rhs.time_reaction_end)
            return false;
        return true;
    }
};

struct ValueDiff {
    double diff;

    ValueDiff() : diff(-1){};
    bool operator==(const ValueDiff& rhs) const {
        if (diff != rhs.diff)
            return false;
        return true;
    }
};