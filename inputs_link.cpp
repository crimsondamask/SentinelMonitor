#include "inputs_link.h"

SentinelInputsTag::SentinelInputsTag(qint16 id, QString tk) {
    this->id      = id;
    this->tk      = QString("%1:%2").arg(tk).arg(id);
    this->name    = QString("TAG_%1").arg(id);
    this->enabled = false;
    this->value   = SentinelTagValue{
          .type = 0, .real_value = 0.0, .int_value = 0, .bit_value = 0};
}

QString SentinelInputsTag::displayName() const {
    return QString("%1").arg(this->name);
}

QString SentinelInputsTag::displayTk() const {
    return QString("%1").arg(this->tk);
}

bool SentinelInputsTag::isEnabled() const { return this->enabled; }

QString SentinelInputsTag::displayValue() const {
    switch (this->value.type) {
    case ST_INT_VALUE:
        return QString("%1").arg(this->value.int_value);
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
SentinelInputsLink::SentinelInputsLink(qint16 id, QString tk) {
    this->id   = id;
    this->tk   = tk;
    this->name = QString("%1%2").arg(tk).arg(id);
    this->tags.reserve(N_CHANNELS);
    for (size_t i = 0; i < N_CHANNELS; i++) {
        SentinelInputsTag tag = SentinelInputsTag(i, tk);
        this->tags.push_back(tag);
    }
    this->tag_count = N_CHANNELS;
}
