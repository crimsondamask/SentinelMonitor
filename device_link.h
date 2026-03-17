#ifndef DEVICE_LINK_H
#define DEVICE_LINK_H

#include "config.h"

#include <QAbstractTableModel>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

enum SentinelProtocol {
    ST_MODBUS_TCP,
    ST_MODBUS_SERIAL,
};

enum TagAddressType {
    ST_MODBUS_ADDRESS,
};
struct SentinelTagAddress {
    int type;
    int modbusRegister;
};

class SentinelDeviceTag {
  public:
    // TODO---
    SentinelDeviceTag(qint16 id, QString tk);
    //~SentinelDeviceTag();
    QString displayValue() const;
    QString displayName() const;
    QString displayTk() const;
    QString displayStatus() const;
    QString displayDetails() const;
    bool    isEnabled() const;
    // -------

    qint16             id;
    QString            tk;
    QString            name;
    QString            tagDetails;
    bool               enabled;
    SentinelTagAddress address;
    SentinelTagValue   value;
    QString            status;
};

class SentinelDeviceLink {
  public:
    SentinelDeviceLink(qint16 id, QString tk);
    //~SentinelDeviceLink();

    qint16                         id;
    QString                        tk;
    QString                        name;
    bool                           enable;
    int                            protocol;
    QString                        protocolDetails;
    std::vector<SentinelDeviceTag> tags;
    size_t                         tag_count;
    QString                        last_poll_time;
    QString                        status;

  private:
};

#endif // DEVICE_LINK_H
