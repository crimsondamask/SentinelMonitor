#ifndef EVAL_LINK_H
#define EVAL_LINK_H

#include "config.h"
#include <QString>

class SentinelEvalTag {
  public:
    SentinelEvalTag(qint16 id, QString tk);
    QString displayValue() const;
    QString displayName() const;
    QString displayTk() const;
    QString displayStatus() const;
    QString displayFormula() const;
    QString displayType() const;
    bool    isEnabled() const;

    qint16           id;
    QString          tk;
    QString          name;
    QString          formula;
    bool             enabled;
    SentinelTagValue value;
    QString          status;
};

class SentinelEvalLink {
  public:
    SentinelEvalLink(qint16 id, QString tk);
    qint16                       id;
    QString                      tk;
    QString                      name;
    std::vector<SentinelEvalTag> tags;
    size_t                       tag_count;
};
#endif // EVAL_LINK_H
