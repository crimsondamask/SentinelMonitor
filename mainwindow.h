#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
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
#include <limits>

#include "link.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SentinelTableModel : public QAbstractTableModel {
  Q_OBJECT
public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // TableView reimplementations-----------

  explicit SentinelTableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  //---------------------------------------

  void setTableData(SentinelDeviceLink link);
  void setTableData(SentinelInputsLink link);
  void setTableData(SentinelEvalLink link);

private:
  int linkType;
  SentinelDeviceLink deviceLinkData;
  SentinelInputsLink inputsLinkData;
  SentinelEvalLink evalLinkData;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void initRequest();
  void postWriteRequest(int linkId, int tagId, SentinelTagValue value);
  void postTagConfigRequest(int linkId, QByteArray data);
  void writeTagFinished();
  void reconfigTagFinished();
  void reconfigLinksFinished();
  void saveActionClicked();
  void sendConfigActionClicked();
  void aboutActionClicked();
  void tagRowClicked(const QModelIndex &index);
  void parseServerData();
  void selectedLinkChanged();
  void updateView();
  void httpErrorOccurred();
  bool isError();
  QString errorString();
  QByteArray tagReconfigJson(SentinelDeviceTag tag);
  QByteArray jsonFromTag(SentinelInputsTag tag);

private:
  Ui::MainWindow *ui;
  QLabel *statusLabel;
  QLineEdit *linkDetails;
  QLineEdit *linkStatus;
  QPushButton *downloadButton;
  QComboBox *linksList;
  QTimer *pollTimer;
  QTableView *tableView;
  QWidget *centralWidget;
  QMenuBar *mainMenuBar;
  QMenu *fileMenu;
  QMenu *viewMenu;
  QMenu *helpMenu;
  QDialog *evalDialog;

  QString configData;
  int selectedLinkIndex;
  bool error;
  QString serverError;
  std::vector<SentinelLink> linksBuffer;
  qsizetype numLinks;
  SentinelTableModel model;
  QUrl url;
  QNetworkAccessManager qnam;
  QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;
  QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> writeTagReply;
  QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reconfigTagReply;
  QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reconfigLinksReply;
};

#endif // MAINWINDOW_H
