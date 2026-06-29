#pragma once

class Snapshot;

class Xfer {
public:
    Xfer();
    virtual ~Xfer();

    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
};
