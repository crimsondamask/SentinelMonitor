#ifndef LINK_H
#define LINK_H

#include "config.h"
#include "device_link.h"
#include "inputs_link.h"

enum SentinelLinkType {
    ST_DEVICE,
    ST_INPUTS,
    ST_EVALS,
};

class SentinelLink {
  public:
    SentinelLink(SentinelDeviceLink link);
    SentinelLink(SentinelInputsLink link);
    SentinelLink(const SentinelLink &other);
    ~SentinelLink();

    int                type;
    SentinelDeviceLink deviceLink;
    SentinelInputsLink inputsLink;
};

#endif // LINK_H
