#pragma once

class Snapshot {
public:
    Snapshot();
    Snapshot(const Snapshot &that);
    virtual ~Snapshot();

    Snapshot &operator=(const Snapshot &that);
};
