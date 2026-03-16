#ifndef INPUTS_LINK_H
#define INPUTS_LINK_H
#include "config.h"
#include <QString>

class SentinelInputsTag {
  public:
    SentinelInputsTag(qint16 id, QString tk);
    QString displayValue() const;
    QString displayName() const;
    QString displayTk() const;
    bool    isEnabled() const;

    qint16           id;
    QString          tk;
    QString          name;
    bool             enabled;
    SentinelTagValue value;
};

class SentinelInputsLink {
  public:
    SentinelInputsLink(qint16 id, QString tk);
    qint16                         id;
    QString                        tk;
    QString                        name;
    std::vector<SentinelInputsTag> tags;
    size_t                         tag_count;
};

#endif // INPUTS_LINK_H
