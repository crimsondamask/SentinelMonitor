#include "link.h"

SentinelLink::SentinelLink(SentinelDeviceLink link)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Device Link")) {

    this->type       = ST_DEVICE;
    this->deviceLink = link;
}
SentinelLink::SentinelLink(SentinelInputsLink link)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Device Link"))

{
    this->type       = ST_INPUTS;
    this->inputsLink = link;
}

SentinelLink::SentinelLink(const SentinelLink &other)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Device Link"))

{

    switch (other.type) {
    case ST_DEVICE:
        this->type       = ST_DEVICE;
        this->deviceLink = other.deviceLink;
        break;
    case ST_INPUTS:
        this->type       = ST_INPUTS;
        this->inputsLink = other.inputsLink;
        break;
    default:
        qDebug() << "Error";
        this->type       = ST_DEVICE;
        this->deviceLink = other.deviceLink;
        break;
    }
}
SentinelLink::~SentinelLink() {}
