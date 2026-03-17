#include "link.h"

SentinelDeviceTag::SentinelDeviceTag(qint16 id, QString tk) {
    this->id      = id;
    this->tk      = QString("%1:%2").arg(tk).arg(id);
    this->name    = QString("TAG_%1").arg(id);
    this->enabled = false;
    this->address = SentinelTagAddress{.type = 0, .modbusRegister = 0};
    this->value   = SentinelTagValue{
          .type = 0, .real_value = 0.0, .int_value = 0, .bit_value = 0};
    this->status = QString("Initialized.");
}

QString SentinelDeviceTag::displayName() const {
    return QString("%1").arg(this->name);
}

QString SentinelDeviceTag::displayTk() const {
    return QString("%1").arg(this->tk);
}

QString SentinelDeviceTag::displayStatus() const {
    return QString("%1").arg(this->status);
}
QString SentinelDeviceTag::displayDetails() const {
    return QString("%1").arg(this->tagDetails);
}

bool SentinelDeviceTag::isEnabled() const { return this->enabled; }

QString SentinelDeviceTag::displayValue() const {
    switch (this->value.type) {
    case ST_INT_VALUE:
        return QString("%1").number(this->value.int_value);
        break;
    case ST_REAL_VALUE:
        return QString("%1").number(this->value.real_value, 'f', 5);
        break;
    case ST_BIT_VALUE:
        return QString("%1").arg(this->value.bit_value);
        break;

    default:
        return QString("%1").arg(this->value.int_value);
        break;
    }
}

SentinelDeviceLink::SentinelDeviceLink(qint16 id, QString tk,
                                       SentinelConfig config)
    : config(config) {

    this->id       = id;
    this->tk       = tk;
    this->name     = QString("%1%2").arg(tk).arg(id);
    this->enable   = true;
    this->protocol = ST_MODBUS_TCP;
    this->tags.reserve(N_CHANNELS);
    for (size_t i = 0; i < N_CHANNELS; i++) {
        SentinelDeviceTag tag = SentinelDeviceTag(i, tk);
        this->tags.push_back(tag);
    }
    this->tag_count      = N_CHANNELS;
    this->status         = QString("Link is disconnected");
    this->last_poll_time = QString("N/A");
}

SentinelDeviceLink::SentinelDeviceLink(qint16 id, QString tk)
    : config(SentinelModbusTcp("192.168.0.1", 502)) {

    this->id       = id;
    this->tk       = tk;
    this->name     = QString("%1%2").arg(tk).arg(id);
    this->enable   = true;
    this->protocol = ST_MODBUS_TCP;
    this->tags.reserve(N_CHANNELS);
    for (size_t i = 0; i < N_CHANNELS; i++) {
        SentinelDeviceTag tag = SentinelDeviceTag(i, tk);
        this->tags.push_back(tag);
    }
    this->tag_count      = N_CHANNELS;
    this->status         = QString("Link is disconnected");
    this->last_poll_time = QString("N/A");
}

void SentinelDeviceLink::setConfig(SentinelModbusTcp config) {
    this->config.modbusTcp = config;
    this->config.protocol  = ST_MODBUS_TCP;
}
void SentinelDeviceLink::setConfig(SentinelModbusSerial config) {
    this->config.modbusSerial = config;
    this->config.protocol     = ST_MODBUS_SERIAL;
}

SentinelConfig::SentinelConfig(SentinelModbusTcp config)
    : modbusTcp(config), modbusSerial("COM1", 9600, 1) {}
SentinelConfig::SentinelConfig(SentinelModbusSerial config)
    : modbusTcp("192.168.0.1", 502), modbusSerial(config) {}

SentinelModbusTcp::SentinelModbusTcp(QString ip, int port)
    : ip(ip), port(port) {}

SentinelModbusSerial::SentinelModbusSerial(QString comPort, int baudrate,
                                           int slave, int parity)
    : comPort(comPort), baudrate(baudrate), slave(slave), parity(parity) {}
SentinelModbusSerial::SentinelModbusSerial(QString comPort, int baudrate,
                                           int slave)
    : comPort(comPort), baudrate(baudrate) {}
