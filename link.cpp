#include "link.h"

SentinelLink::SentinelLink(SentinelDeviceLink link)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Inputs Link")), evalLink(0, QString("Eval Link")) {
  this->type = ST_DEVICE;
  this->deviceLink = link;
}
SentinelLink::SentinelLink(SentinelInputsLink link)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Inputs Link")), evalLink(0, QString("Eval Link"))

{
  this->type = ST_INPUTS;
  this->inputsLink = link;
}
SentinelLink::SentinelLink(SentinelEvalLink link)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Inputs Link")), evalLink(0, QString("Eval Link"))

{
  this->type = ST_EVALS;
  this->evalLink = link;
}

SentinelLink::SentinelLink(const SentinelLink &other)
    : deviceLink(0, QString("Device Link")),
      inputsLink(0, QString("Input Link")), evalLink(0, QString("Eval Link"))

{
  switch (other.type) {
  case ST_DEVICE:
    this->type = ST_DEVICE;
    this->deviceLink = other.deviceLink;
    break;
  case ST_INPUTS:
    this->type = ST_INPUTS;
    this->inputsLink = other.inputsLink;
    break;
  case ST_EVALS:
    this->type = ST_EVALS;
    this->evalLink = other.evalLink;
    break;
  default:
    qDebug() << "Error";
    this->type = ST_DEVICE;
    this->deviceLink = other.deviceLink;
    break;
  }
}
SentinelLink::~SentinelLink() {}
