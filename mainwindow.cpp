#include "mainwindow.h"

#include <QPlainTextEdit>
#include <QWidget>
#include <QtGlobal>
#include <QtNetwork/QtNetwork>
#include <cfloat>
#include <vector>

#include "./ui_mainwindow.h"
#include "device_link.h"
#include "eval_link.h"
#include "link.h"

SentinelTableModel::SentinelTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      deviceLinkData(SentinelDeviceLink(0, QString("LINK1"))),
      evalLinkData(1, QString("EVALS")),
      inputsLinkData(SentinelInputsLink(2, QString("INPUTS"))) {}

int SentinelTableModel::rowCount(const QModelIndex &parent) const {
  return N_CHANNELS;
}

int SentinelTableModel::columnCount(const QModelIndex &parent) const {
  return 8;
}

void SentinelTableModel::setTableData(SentinelDeviceLink link) {
  this->deviceLinkData = link;
  this->linkType = ST_DEVICE;
  QModelIndex topLeft = createIndex(0, 0);
  QModelIndex bottomRight = createIndex(8, N_CHANNELS - 1);
  emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

void SentinelTableModel::setTableData(SentinelEvalLink link) {
  this->evalLinkData = link;
  this->linkType = ST_EVALS;
  QModelIndex topLeft = createIndex(0, 0);
  QModelIndex bottomRight = createIndex(8, N_CHANNELS - 1);
  emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

void SentinelTableModel::setTableData(SentinelInputsLink link) {
  this->inputsLinkData = link;
  this->linkType = ST_INPUTS;
  QModelIndex topLeft = createIndex(0, 0);
  QModelIndex bottomRight = createIndex(8, N_CHANNELS - 1);
  emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

Qt::ItemFlags SentinelTableModel::flags(const QModelIndex &index) const {
  return QAbstractTableModel::flags(index) & ~Qt::ItemIsUserCheckable;
}

QVariant SentinelTableModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return QString("TK");
    case 1:
      return QString("NAME");
    case 2:
      return QString("VALUE");
    case 3:
      return QString("TYPE");
    case 4:
      return QString("UNIT");
    case 5:
      return QString("ADDRESS");
    case 6:
      return QString("STATUS");
    case 7:
      return QString("DESCRIPTION");
    default:
      break;
    }
  }

  if (orientation == Qt::Vertical) {
    return QString("%1").arg(section);
  }
  return QVariant();
}

QVariant SentinelTableModel::data(const QModelIndex &index, int role) const {
  switch (this->linkType) {
  case ST_DEVICE:
    for (size_t i = 0; i < N_CHANNELS; i++) {
      if (index.row() == i) {
        if (role == Qt::DisplayRole && index.column() == 0) {
          return QString("%1").arg(deviceLinkData.tags[i].displayTk());
        }
        if (role == Qt::DisplayRole && index.column() == 1) {
          return QString("%1").arg(deviceLinkData.tags[i].displayName());
        }
        if (role == Qt::DisplayRole && index.column() == 2) {
          if (!deviceLinkData.tags[i].isEnabled()) {
            return QString("DISABLED");
          } else {
            return QString("%1").arg(deviceLinkData.tags[i].displayValue());
          }
        }
        if (role == Qt::DisplayRole && index.column() == 3) {
          return QString("%1").arg(deviceLinkData.tags[i].displayType());
        }
        if (role == Qt::DisplayRole && index.column() == 4) {
          return QString("%1").arg(deviceLinkData.tags[i].unit);
        }
        if (role == Qt::DisplayRole && index.column() == 5) {
          return QString("%1").arg(deviceLinkData.tags[i].displayAddress());
        }
        if (role == Qt::DisplayRole && index.column() == 6) {
          return QString("%1").arg(deviceLinkData.tags[i].displayStatus());
        }
        if (role == Qt::DisplayRole && index.column() == 7) {
          return QString("%1").arg(deviceLinkData.tags[i].description);
        }
      }
    }
    break;
  case ST_EVALS:
    for (size_t i = 0; i < N_CHANNELS; i++) {
      if (index.row() == i) {
        if (role == Qt::DisplayRole && index.column() == 0) {
          return QString("%1").arg(evalLinkData.tags[i].displayTk());
        }
        if (role == Qt::DisplayRole && index.column() == 1) {
          return QString("%1").arg(evalLinkData.tags[i].displayName());
        }
        if (role == Qt::DisplayRole && index.column() == 2) {
          if (!evalLinkData.tags[i].isEnabled()) {
            return QString("DISABLED");
          } else {
            return QString("%1").arg(evalLinkData.tags[i].displayValue());
          }
        }
        if (role == Qt::DisplayRole && index.column() == 3) {
          return QString("%1").arg(evalLinkData.tags[i].displayType());
        }
        if (role == Qt::DisplayRole && index.column() == 4) {
          return QString("%1").arg(evalLinkData.tags[i].unit);
        }
        if (role == Qt::DisplayRole && index.column() == 5) {
          return QString("%1").arg(evalLinkData.tags[i].displayFormula());
        }
        if (role == Qt::DisplayRole && index.column() == 6) {
          return QString("%1").arg(evalLinkData.tags[i].displayStatus());
        }
        if (role == Qt::DisplayRole && index.column() == 7) {
          return QString("%1").arg(evalLinkData.tags[i].description);
        }
      }
    }
    break;
  case ST_INPUTS:
    for (size_t i = 0; i < N_CHANNELS; i++) {
      if (index.row() == i) {
        if (role == Qt::DisplayRole && index.column() == 0) {
          return QString("%1").arg(inputsLinkData.tags[i].displayTk());
        }
        if (role == Qt::DisplayRole && index.column() == 1) {
          return QString("%1").arg(inputsLinkData.tags[i].displayName());
        }
        if (role == Qt::DisplayRole && index.column() == 2) {
          if (!inputsLinkData.tags[i].isEnabled()) {
            return QString("DISABLED");
          } else {
            return QString("%1").arg(inputsLinkData.tags[i].displayValue());
          }
        }
        if (role == Qt::DisplayRole && index.column() == 3) {
          return QString("%1").arg(inputsLinkData.tags[i].displayType());
        }
        if (role == Qt::DisplayRole && index.column() == 4) {
          return QString("%1").arg(inputsLinkData.tags[i].unit);
        }
        if (role == Qt::DisplayRole && index.column() == 7) {
          return QString("%1").arg(inputsLinkData.tags[i].description);
        }
      }
    }
    break;
  default:
    break;
  }

  return QVariant();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      statusLabel(new QLabel("Disconnected.")), downloadButton(new QPushButton),
      pollTimer(new QTimer(this)), centralWidget(new QWidget(this)),
      linkDetails(new QLineEdit("N/A")),
      linkDetailsButton(new QPushButton("Edit", this)),
      linkStatus(new QLineEdit("N/A")), tableView(new QTableView),
      selectedLinkIndex(0), selectedEvalBuffer(SentinelEvalTag(0, "Hello")) {
  ui->setupUi(this);

  QLocale::setDefault(QLocale::c());
  mainMenuBar = this->menuBar();
  this->fileMenu = this->mainMenuBar->addMenu(tr("&File"));

  QAction *saveAction = new QAction(tr("&Save"), this);
  QAction *sendConfigAction = new QAction(tr("&Send Config"), this);
  QAction *exitAction = new QAction(tr("&Exit"), this);
  exitAction->setShortcuts(QKeySequence::Quit);

  fileMenu->addAction(saveAction);
  fileMenu->addAction(sendConfigAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  this->helpMenu = this->mainMenuBar->addMenu(tr("&Help"));
  QAction *aboutAction = new QAction(tr("&About"), this);
  helpMenu->addAction(aboutAction);

  connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
  connect(saveAction, &QAction::triggered, this,
          &MainWindow::saveActionClicked);
  connect(sendConfigAction, &QAction::triggered, this,
          &MainWindow::sendConfigActionClicked);
  connect(aboutAction, &QAction::triggered, this,
          &MainWindow::aboutActionClicked);

  linkStatus->setReadOnly(true);
  linkStatus->setFixedWidth(300);

  linkDetails->setReadOnly(true);
  linkDetails->setFixedWidth(300);

  url = QUrl::fromUserInput(QString(POLL_URL).trimmed());

  setWindowTitle("Sentinel Monitor V1.0");

  connect(pollTimer, &QTimer::timeout, this, &MainWindow::initRequest);

  pollTimer->start(1000);
  // Repeating timer
  pollTimer->setSingleShot(false);
  linksList = new QComboBox();

  linksList->setFixedWidth(300);
  linksList->setDisabled(true);

  for (size_t i = 0; i < N_LINKS; i++) {
    linksList->addItem(QString("DISABLED LINK %1").arg(i));
  }

  connect(linksList, &QComboBox::currentIndexChanged, this,
          &MainWindow::selectedLinkChanged);
  QFormLayout *formLayout = new QFormLayout;
  formLayout->setFormAlignment(Qt::AlignLeft);
  formLayout->setLabelAlignment(Qt::AlignLeft);
  formLayout->addRow(QString("Link:"), linksList);

  QGridLayout *linkDetailsGrid = new QGridLayout();
  linkDetailsGrid->addWidget(linkDetails, 0, 0);
  linkDetailsGrid->addWidget(linkDetailsButton, 0, 1);

  connect(this->linkDetailsButton, &QPushButton::clicked, this,
          &MainWindow::linkEditClicked);

  formLayout->addRow(QString("Protocol Details:"), linkDetailsGrid);
  formLayout->addRow(QString("Status:"), statusLabel);
  // formLayout->addRow(QString("Link Details:"), linkDetails);
  // formLayout->addRow(QString(""), linkDetailsButton);

  formLayout->addRow(QString("Link Status:"), linkStatus);

  tableView->setModel(&model);
  tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  connect(tableView, &QTableView::doubleClicked, this,
          &MainWindow::tagRowClicked);
  for (size_t i = 0; i < N_CHANNELS; i++) {
    this->tableView->setRowHeight(i, 7);
  }

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(formLayout);
  mainLayout->addWidget(tableView, 1);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::isError() { return this->error; }

QString MainWindow::errorString() { return this->serverError; }

void MainWindow::postWriteRequest(int linkId, int tagId,
                                  SentinelTagValue value) {
  QJsonObject tagWriteData{};
  QJsonObject tagInfo = {};
  QJsonObject tagValueData{};

  tagInfo["link_id"] = linkId;
  tagInfo["tag_id"] = tagId;
  tagWriteData["tag_info"] = tagInfo;

  switch (value.type) {
  case ST_INT_VALUE:
    tagValueData["Int"] = value.int_value;
    break;
  case ST_REAL_VALUE:
    tagValueData["Real"] = value.real_value;
    break;
  case ST_BIT_VALUE:
    tagValueData["Bit"] = value.bit_value;
    break;
  default:
    break;
  }

  tagWriteData["tag_value"] = tagValueData;

  QJsonDocument tagWriteJsonDoc = QJsonDocument(tagWriteData);

  QByteArray bytes = tagWriteJsonDoc.toJson();
  QUrl writeUrl = QUrl(QString(WRITE_TAG_URL));
  QNetworkRequest postRequest = QNetworkRequest(writeUrl);
  postRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                        QString("application/json"));
  writeTagReply.reset(qnam.post(postRequest, bytes));

  connect(this->writeTagReply.get(), &QNetworkReply::finished, this,
          &MainWindow::writeTagFinished);
}

void MainWindow::linkEditFinished() {
  if (this->reconfigLinksReply->error() ==
      QNetworkReply::NetworkError::NoError) {
    int statusCode =
        reconfigLinksReply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
            .toInt();
    if (statusCode == 200) {
      QMessageBox::information(this, "Success",
                               "Configuration sent successfully.");
    } else {
      QMessageBox::critical(this, "Server Error",
                            "Could not send the configuration to the server.");
    }
  } else {
    QString errorMsg = QString("Could not reconfigure the server. %1")
                           .arg(reconfigLinksReply->errorString());
    QMessageBox::critical(this, "Reconfigure Error", errorMsg);
  }
}

void MainWindow::linkEditClicked() {
  if (this->linksBuffer[this->selectedLinkIndex].type != ST_DEVICE) {
    return;
  }
  bool ok{};
  QString stringInput = QInputDialog::getText(
      this, QString("Link Protocol Details"), QString("Details"),
      QLineEdit::Normal, this->linkDetails->text(), &ok);

  if (ok) {
    QJsonDocument doc{};
    QJsonObject jsonObject{};
    jsonObject["link_id"] = this->selectedLinkIndex;
    jsonObject["protocol"] = stringInput;
    doc.setObject(jsonObject);
    QUrl configUrl = QUrl(QString(RECONFIG_DEVICE_PROTOCOL));
    QNetworkRequest postRequest = QNetworkRequest(configUrl);
    postRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                          QString("application/json"));
    reconfigLinksReply.reset(qnam.post(postRequest, doc.toJson()));
    connect(this->reconfigLinksReply.get(), &QNetworkReply::finished, this,
            &MainWindow::linkEditFinished);
  }
}

void MainWindow::writeTagFinished() {
  if (this->writeTagReply->error() == QNetworkReply::NetworkError::NoError) {
    int statusCode =
        writeTagReply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
            .toInt();
    if (statusCode == 200) {
      // QMessageBox::information(this, "Success", "Tag write was
      // successfull.");
    } else {
      QMessageBox::critical(this, "Server Error",
                            "The server could not write the tag successfully.");
    }
  } else {
    QString errorMsg = QString("Could not write tag. %1")
                           .arg(this->writeTagReply->errorString());
    QMessageBox::critical(this, "Write Error", errorMsg);
  }
}

void MainWindow::tagRowClicked(const QModelIndex &index) {
  if (!index.isValid()) {
    return;
  }
  if (index.row() > N_CHANNELS) {
    return;
  }

  if (this->linksBuffer.empty()) {
    return;
  }

  int clickedRow = index.row();
  int clickedColumn = index.column();

  bool ok{};
  int intInput = 0;
  float realInput{};
  int bitInput{};
  SentinelTagValue tagValue;

  if (this->linksBuffer[selectedLinkIndex].type == ST_DEVICE) {
    SentinelDeviceTag selectedTag =
        this->linksBuffer[selectedLinkIndex].deviceLink.tags[clickedRow];

    if (clickedColumn == 2) {
      switch (selectedTag.value.type) {
      case ST_INT_VALUE:
        intInput = QInputDialog::getInt(
            this,
            QString("%1:%2 INT Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write INT Value:"), selectedTag.value.int_value, INT_MIN,
            INT_MAX, 1, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_INT_VALUE,
                                      .real_value = 0.0,
                                      .int_value = intInput,
                                      .bit_value = 0};
        }
        break;
      case ST_REAL_VALUE:

        realInput = QInputDialog::getDouble(
            this,
            QString("%1:%2 REAL Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write REAL Value:"), selectedTag.value.real_value, FLT_MIN,
            FLT_MAX, 5, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_REAL_VALUE,
                                      .real_value = realInput,
                                      .int_value = 0,
                                      .bit_value = 0};
        }
        break;
      case ST_BIT_VALUE:
        bitInput = QInputDialog::getInt(
            this,
            QString("%1:%2 Bit Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write BIT Value:"), selectedTag.value.bit_value, 0, 1, 1, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_BIT_VALUE,
                                      .real_value = 0.0,
                                      .int_value = 0,
                                      .bit_value = bitInput};
        }
        break;
      default:
        break;
      }
    } else if (clickedColumn == 0) {
      int enabled = {};
      enabled = QInputDialog::getInt(
          this,
          QString("%1:%2 Enable Tag")
              .arg(selectedTag.displayTk(), selectedTag.displayName()),
          tr("Enable Tag:"), (int)selectedTag.enabled, 0, 1, 1, &ok);
      if (ok) {
        selectedTag.enabled = enabled;
        this->postTagConfigRequest(selectedTag.id,
                                   this->tagReconfigJson(selectedTag));
        return;
      }
    } else if (clickedColumn == 1) {
      QString name = {};
      name = QInputDialog::getText(
          this,
          QString("%1:%2 Tag Name")
              .arg(selectedTag.displayTk(), selectedTag.displayName()),
          tr("Tag Name"), QLineEdit::Normal, selectedTag.name, &ok);
      if (ok) {
        selectedTag.name = name;
        this->postTagConfigRequest(selectedTag.id,
                                   this->tagReconfigJson(selectedTag));
        return;
      }

    } else if (clickedColumn == 4) {
      QString unit = {};
      unit = QInputDialog::getText(
          this,
          QString("%1:%2 Tag Unit")
              .arg(selectedTag.displayTk(), selectedTag.displayName()),
          tr("Tag Unit"), QLineEdit::Normal, selectedTag.unit, &ok);
      if (ok) {
        selectedTag.unit = unit;
        this->postTagConfigRequest(selectedTag.id,
                                   this->tagReconfigJson(selectedTag));
        return;
      }

    } else if (clickedColumn == 7) {

      QString description = {};
      description = QInputDialog::getText(
          this,
          QString("%1:%2 Tag Description")
              .arg(selectedTag.displayTk(), selectedTag.displayName()),
          tr("Tag Description"), QLineEdit::Normal, selectedTag.description,
          &ok);
      if (ok) {
        selectedTag.description = description;
        this->postTagConfigRequest(selectedTag.id,
                                   this->tagReconfigJson(selectedTag));
        return;
      }
    } else if (clickedColumn == 3) {
      int valueType = {};
      valueType = QInputDialog::getInt(
          this,
          QString("%1:%2 Tag Value Type")
              .arg(selectedTag.displayTk(), selectedTag.displayName()),
          "0 for INT, 1 for REAL, 3 for BIT.", selectedTag.value.type, 0, 2, 1,
          &ok);
      if (ok) {
        selectedTag.value.type = valueType;
        this->postTagConfigRequest(selectedTag.id,
                                   this->tagReconfigJson(selectedTag));
        return;
      }

    } else if (clickedColumn == 5) {
      if (selectedTag.address.type == ST_MODBUS_ADDRESS) {
        int address = {};
        address = QInputDialog::getInt(
            this,
            QString("%1:%2 Tag Modbus Address")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            "Holding Register.", selectedTag.address.modbusRegister, 0, 65535,
            1, &ok);
        if (ok) {
          selectedTag.address.modbusRegister = address;
          this->postTagConfigRequest(selectedTag.id,
                                     this->tagReconfigJson(selectedTag));
          return;
        }
      }
    } else {
      return;
    }

  } else if (this->linksBuffer[selectedLinkIndex].type == ST_INPUTS) {
    SentinelInputsTag selectedTag =
        this->linksBuffer[selectedLinkIndex].inputsLink.tags[clickedRow];

    if (clickedColumn == 2) {
      switch (selectedTag.value.type) {
      case ST_INT_VALUE:
        intInput = QInputDialog::getInt(
            this,
            QString("%1:%2 INT Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write INT Value:"), selectedTag.value.int_value, INT_MIN,
            INT_MAX, 1, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_INT_VALUE,
                                      .real_value = 0.0,
                                      .int_value = intInput,
                                      .bit_value = 0};
        }
        break;
      case ST_REAL_VALUE:
        realInput = QInputDialog::getDouble(
            this,
            QString("%1:%2 REAL Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write REAL Value:"), selectedTag.value.real_value, FLT_MIN,
            FLT_MAX, 5, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_REAL_VALUE,
                                      .real_value = realInput,
                                      .int_value = 0,
                                      .bit_value = 0};
        }
        break;
      case ST_BIT_VALUE:
        bitInput = QInputDialog::getInt(
            this,
            QString("%1:%2 Bit Input")
                .arg(selectedTag.displayTk(), selectedTag.displayName()),
            tr("Write BIT Value:"), selectedTag.value.bit_value, 0, 1, 1, &ok);
        if (ok) {
          tagValue = SentinelTagValue{.type = ST_BIT_VALUE,
                                      .real_value = 0.0,
                                      .int_value = 0,
                                      .bit_value = bitInput};
        }
        break;
      default:
        break;
      }
    } else {
      return;
    }
  } else if (this->linksBuffer[selectedLinkIndex].type == ST_EVALS) {

    SentinelEvalTag selectedTag =
        this->linksBuffer[selectedLinkIndex].evalLink.tags[clickedRow];
    this->selectedEvalBuffer = selectedTag;

    this->evalDialog = new QDialog(this);
    QLabel *nameLabel = new QLabel(this->evalDialog);
    nameLabel->setText("Name");

    QLabel *descriptionLabel = new QLabel(this->evalDialog);
    descriptionLabel->setText("Desc");

    QLineEdit *nameEdit = new QLineEdit(this->evalDialog);
    nameEdit->setText(QString("%1").arg(selectedTag.name));

    QLineEdit *unitEdit = new QLineEdit(this->evalDialog);
    unitEdit->setText(QString("%1").arg(selectedTag.unit));

    QLineEdit *descriptionEdit = new QLineEdit(this->evalDialog);
    descriptionEdit->setText(QString("%1").arg(selectedTag.description));

    QGridLayout *grid = new QGridLayout(this->evalDialog);
    grid->addWidget(nameLabel, 0, 0);
    grid->addWidget(nameEdit, 0, 1);
    grid->addWidget(unitEdit, 0, 2);
    grid->addWidget(descriptionLabel, 1, 0);
    grid->addWidget(descriptionEdit, 1, 1);

    QLabel *formulaLabel = new QLabel(this->evalDialog);
    formulaLabel->setText("Formula");

    QPlainTextEdit *formulaEdit = new QPlainTextEdit(this->evalDialog);
    formulaEdit->setPlainText(QString("%1").arg(selectedTag.formula));
    formulaEdit->setFixedHeight(300);

    grid->addWidget(formulaLabel, 2, 0);
    grid->addWidget(formulaEdit, 2, 1);

    QComboBox *typeCombo = new QComboBox(this->evalDialog);
    typeCombo->addItem("INT");
    typeCombo->addItem("REAL");
    typeCombo->addItem("BIT");
    // typeCombo->addItem("DINT");

    typeCombo->setCurrentIndex(selectedTag.value.type);

    grid->addWidget(typeCombo, 3, 0);
    grid->addWidget(typeCombo, 3, 1);

    QPushButton *applyButton = new QPushButton(this->evalDialog);
    applyButton->setText("Apply");
    grid->addWidget(applyButton, 1, 2);

    std::vector<QComboBox *> combosVec{};
    combosVec.reserve(selectedTag.vars.size());

    std::vector<QLineEdit *> lineEditVec{};
    lineEditVec.reserve(selectedTag.vars.size());

    for (int i = 0; i < selectedTag.vars.size(); i++) {
      EvalVar ev = selectedTag.vars[i];

      QComboBox *linkCombo = new QComboBox(this->evalDialog);
      for (int j = 0; j < this->linksBuffer.size(); j++) {
        switch (this->linksBuffer[j].type) {
        case ST_DEVICE:
          linkCombo->addItem(
              QString("%1").arg(this->linksBuffer[j].deviceLink.name));
          break;
        case ST_INPUTS:
          linkCombo->addItem(
              QString("%1").arg(this->linksBuffer[j].inputsLink.name));
          break;
        case ST_EVALS:
          linkCombo->addItem(
              QString("%1").arg(this->linksBuffer[j].evalLink.name));
          break;
        default:
          linkCombo->addItem("Unidentified");
          break;
        }
      }

      linkCombo->setCurrentIndex(selectedTag.vars[i].linkId);
      combosVec.push_back(linkCombo);

      QLabel *label = new QLabel(this->evalDialog);
      label->setText(QString("x%1").arg(i));

      QLineEdit *tagEdit = new QLineEdit(this->evalDialog);
      tagEdit->setText(QString("%1").arg(selectedTag.vars[i].tagId));
      tagEdit->setValidator(new QIntValidator(0, N_CHANNELS, this->evalDialog));

      lineEditVec.push_back(tagEdit);

      grid->addWidget(label, i + 4, 0);
      grid->addWidget(linkCombo, i + 4, 1);
      grid->addWidget(tagEdit, i + 4, 2);
    }

    this->evalDialog->setLayout(grid);
    connect(applyButton, &QPushButton::clicked, [=]() {
      this->selectedEvalBuffer.name = nameEdit->text();
      this->selectedEvalBuffer.unit = unitEdit->text();
      this->selectedEvalBuffer.description = descriptionEdit->text();
      this->selectedEvalBuffer.value.type = typeCombo->currentIndex();
      this->selectedEvalBuffer.formula = formulaEdit->toPlainText();

      for (int i = 0; i < this->selectedEvalBuffer.vars.size(); i++) {
        this->selectedEvalBuffer.vars[i].linkId = combosVec[i]->currentIndex();
        bool ok{};
        int tagId = lineEditVec[i]->text().toInt(&ok);
        if (!ok) {
          return;
        }
        this->selectedEvalBuffer.vars[i].tagId = tagId;
      }

      qDebug() << this->evalReconfigJson(this->selectedEvalBuffer);
      this->postEvalConfigRequest(
          this->selectedLinkIndex,
          this->evalReconfigJson(this->selectedEvalBuffer));
      this->evalDialog->accept();
    });
    this->evalDialog->exec();

    return;
  } else {
    QMessageBox::information(nullptr, "Unimplemented Link",
                             "Selected link doesn't accept writing.");
    return;
  }

  this->postWriteRequest(this->selectedLinkIndex, clickedRow, tagValue);
}

QByteArray MainWindow::evalReconfigJson(SentinelEvalTag eval) {
  QJsonDocument doc{};
  QJsonObject evalObject{};
  QJsonObject tagInfo{};
  QJsonObject tagValue{};
  QJsonObject tagReconfig{};
  QJsonArray varsArray{};

  switch (eval.value.type) {
  case ST_INT_VALUE:
    tagValue["Int"] = eval.value.int_value;
    break;
  case ST_REAL_VALUE:
    tagValue["Real"] = eval.value.real_value;
    break;
  case ST_BIT_VALUE:
    tagValue["Bit"] = (bool)eval.value.bit_value;
    break;
  default:
    break;
  }

  tagInfo["link_id"] = this->selectedLinkIndex;
  tagInfo["tag_id"] = eval.id;
  evalObject["id"] = eval.id;
  evalObject["tk"] = eval.tk;
  evalObject["name"] = eval.name;
  evalObject["enabled"] = eval.enabled;
  evalObject["formula"] = eval.formula;
  evalObject["unit"] = eval.unit;
  evalObject["description"] = eval.description;
  evalObject["value"] = tagValue;
  evalObject["status"] = QString("Normal");

  for (int i = 0; i < eval.vars.size(); i++) {
    QJsonObject evalVarObject{};
    evalVarObject["name"] = eval.vars[i].name;
    evalVarObject["link_id"] = eval.vars[i].linkId;
    evalVarObject["tag_id"] = eval.vars[i].tagId;
    QJsonObject varValue{};
    varValue["Real"] = 0.0;
    evalVarObject["value"] = varValue;

    varsArray.append(evalVarObject);
  }
  evalObject["vars"] = varsArray;

  tagReconfig["tag_info"] = tagInfo;
  tagReconfig["tag_data"] = evalObject;

  doc.setObject(tagReconfig);
  return doc.toJson();
}

void MainWindow::postEvalConfigRequest(int linkId, QByteArray data) {

  QUrl url = QUrl(QString(RECONFIG_EVAL_URL));
  QNetworkRequest postRequest = QNetworkRequest(url);
  qDebug() << data;
  postRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                        QString("application/json"));
  this->reconfigTagReply.reset(qnam.post(postRequest, data));
  connect(this->reconfigTagReply.get(), &QNetworkReply::finished, this,
          &MainWindow::reconfigTagFinished);
}

void MainWindow::aboutActionClicked() {
  QMessageBox::information(nullptr, "About",
                           "Sentinel Monitor V1.0. 2026 by Abdelkader Madoui.");
}

void MainWindow::sendConfigActionClicked() {
  if (this->isError()) {
    QMessageBox::information(
        nullptr, "Error", "There was an error while connecting to the server.");
  } else {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Select Config File"), QDir::currentPath(),
        tr("Text Files (*.json);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QMessageBox::critical(
          nullptr, "Error",
          "There was an error while trying to open config file.");
      return;
    }
    QByteArray configData = file.readAll();
    file.close();

    const QUrl url(QStringLiteral("http://localhost:3000/api/reconfig_links"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    this->reconfigLinksReply.reset(qnam.post(request, configData));
    connect(this->reconfigLinksReply.get(), &QNetworkReply::finished, this,
            &MainWindow::reconfigLinksFinished);
  }
}

void MainWindow::reconfigLinksFinished() {

  if (this->reconfigLinksReply->error() ==
      QNetworkReply::NetworkError::NoError) {
    int statusCode =
        reconfigLinksReply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
            .toInt();
    if (statusCode == 200) {
      QMessageBox::information(this, "Success",
                               "Configuration sent successfully.");
    } else {
      QMessageBox::critical(this, "Server Error",
                            "Could not send the configuration to the server.");
    }
  } else {
    QString errorMsg = QString("Could not reconfigure the server. %1")
                           .arg(reconfigLinksReply->errorString());
    QMessageBox::critical(this, "Reconfigure Error", errorMsg);
  }
}

void MainWindow::saveActionClicked() {
  if (this->isError()) {
    QMessageBox::information(
        nullptr, "Save Error",
        "There was an error while connecting to the server.");
  } else {
    QString fileName =
        QFileDialog::getSaveFileName(this, tr("Save Config"), QDir::homePath(),
                                     tr("Text Files (*.json);;All Files (*)"));

    if (!fileName.isEmpty()) {
      QSaveFile file(fileName);
      if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << this->configData;

        if (file.commit()) {
          QMessageBox::information(
              this, tr("Success"),
              tr("Configuration file saved successfully."));
        } else {
          QMessageBox::critical(this, tr("Error"),
                                tr("Could not save configuration to "
                                   "the selected file."));
        }
      } else {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file."));
      }
    }
  }
}

void MainWindow::selectedLinkChanged() {
  size_t arrayLen = linksBuffer.size();

  if (this->linksList->currentIndex() > arrayLen - 1) {
    this->selectedLinkIndex = 0;
    this->statusLabel->setText(
        QString("Selected link index exceeds links array bounds."));
  } else {
    this->selectedLinkIndex = this->linksList->currentIndex();
    this->updateView();
  }
}

void MainWindow::initRequest() {
  reply.reset(qnam.get(QNetworkRequest(url)));
  connect(reply.get(), &QNetworkReply::finished, this,
          &MainWindow::parseServerData);
}

// Parses the JSON data received from the server.
// This is a large function.

void MainWindow::parseServerData() {
  if (reply->error() != QNetworkReply::NoError) {
    this->error = true;
    this->serverError =
        QString("Error connecting to server. %1").arg(reply->errorString());
    this->statusLabel->setText(this->serverError);
    this->tableView->setDisabled(true);
    return;
  }

  QByteArray readData = reply->readAll();
  QJsonParseError jsonError;
  QJsonDocument doc = QJsonDocument::fromJson(readData, &jsonError);

  if (jsonError.error != QJsonParseError::NoError) {
    this->error = true;
    this->serverError = jsonError.errorString();
    this->statusLabel->setText(this->serverError);
    return;
  }

  if (!doc.isArray()) {
    this->error = true;
    this->serverError = QString("JSON is not an Array");
    this->statusLabel->setText(this->serverError);
    return;
  }
  qsizetype arrayLen = doc.array().count();
  this->numLinks = arrayLen;

  this->linksBuffer.clear();

  for (size_t i = 0; i < arrayLen; i++) {
    QJsonValue value = doc.array()[i];

    if (!value.isObject()) {
      this->error = true;
      this->serverError = QString("JSON Array doesn't contain objects.");
      this->statusLabel->setText(this->serverError);
      return;
    }

    if (value.toObject().value("Device").isObject()) {
      QJsonObject deviceLinkObject =
          value.toObject().value("Device").toObject();

      int idValue = deviceLinkObject.value("id").toInt();
      if (!deviceLinkObject.value("tk").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link tk value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString tkValue = deviceLinkObject.value("tk").toString();

      SentinelDeviceLink deviceLink = SentinelDeviceLink(idValue, tkValue);

      if (!deviceLinkObject.value("name").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link name value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString nameValue = deviceLinkObject.value("name").toString();
      deviceLink.name = nameValue;

      // Update the links Combobox.
      // This is a workaround

      this->linksList->setItemText(i, QString("%1 %2").arg(tkValue, nameValue));

      if (!deviceLinkObject.value("enabled").isBool()) {
        this->error = true;
        this->serverError = QString("Could not parse link enabled value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      bool enabledValue = deviceLinkObject.value("enabled").toBool();
      deviceLink.enable = enabledValue;

      if (!deviceLinkObject.value("tags").isArray()) {
        this->error = true;
        this->serverError = QString("Could not parse tags array.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QJsonArray tagsArray = deviceLinkObject.value("tags").toArray();

      if (tagsArray.count() != N_CHANNELS) {
        this->error = true;
        this->serverError =
            QString("Server tags count doesn't equal monitor tags count.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      for (size_t tag_index = 0; tag_index < N_CHANNELS; tag_index++) {
        // TODO
        // Parse the tags.
        QJsonObject tagObject = tagsArray[tag_index].toObject();

        if (!tagObject.value("tk").isString()) {
          this->error = true;
          this->serverError = QString("tag %1 tk parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagTk = tagObject.value("tk").toString();
        deviceLink.tags[tag_index].tk = tagTk;

        if (!tagObject.value("name").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 name parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagName = tagObject.value("name").toString();
        deviceLink.tags[tag_index].name = tagName;

        if (!tagObject.value("unit").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 unit parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagUnit = tagObject.value("unit").toString();
        deviceLink.tags[tag_index].unit = tagUnit;

        if (!tagObject.value("description").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 description parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagDescription = tagObject.value("description").toString();
        deviceLink.tags[tag_index].description = tagDescription;

        if (!tagObject.value("enabled").isBool()) {
          this->error = true;
          this->serverError =
              QString("tag %1 enabled parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        bool tagEnabled = tagObject.value("enabled").toBool();
        deviceLink.tags[tag_index].enabled = tagEnabled;

        if (!tagObject.value("address").isObject()) {
          this->error = true;
          this->serverError =
              QString("tag %1 address parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QJsonObject tagAddressObject = tagObject.value("address").toObject();

        if (tagAddressObject.value("ModbusAddr").isObject()) {
          QJsonObject modbusAddrObject =
              tagAddressObject.value("ModbusAddr").toObject();
          if (!modbusAddrObject.value("Holding").isDouble()) {
            this->error = true;
            this->serverError =
                QString("tag %1 modbus address parse failed.").arg(tag_index);
            this->statusLabel->setText(this->serverError);
            return;
          }
          int holdingRegister = modbusAddrObject.value("Holding").toInt();

          deviceLink.tags[tag_index].address.type = ST_MODBUS_ADDRESS;
          deviceLink.tags[tag_index].address.modbusRegister = holdingRegister;
          deviceLink.tags[tag_index].tagDetails =
              QString("%1,%2,Modbus,Holding=%3")
                  .arg(tagTk, tagName)
                  .arg(holdingRegister);

        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 address object is not implemented.")
                  .arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        if (!tagObject.value("value").isObject()) {
          this->error = true;
          this->serverError =
              QString("tag %1 value object parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QJsonObject tagValueObject = tagObject.value("value").toObject();

        if (tagValueObject.value("Real").isDouble()) {
          float tagRealValue = tagValueObject.value("Real").toDouble();
          deviceLink.tags[tag_index].value.type = ST_REAL_VALUE;
          deviceLink.tags[tag_index].value.real_value = tagRealValue;

        } else if (tagValueObject.value("Int").isDouble()) {
          int tagIntValue = tagValueObject.value("Int").toInt();
          deviceLink.tags[tag_index].value.type = ST_INT_VALUE;
          deviceLink.tags[tag_index].value.int_value = tagIntValue;

        } else if (tagValueObject.value("Bit").isDouble()) {
          int tagBitValue = tagValueObject.value("Bit").toInt();
          deviceLink.tags[tag_index].value.type = ST_BIT_VALUE;
          deviceLink.tags[tag_index].value.bit_value = tagBitValue;

        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 value type parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        if (tagObject.value("status").isObject()) {
          QJsonObject tagStatus = tagObject.value("status").toObject();

          if (!tagStatus.value("Error").isString()) {
            this->error = true;
            this->serverError =
                QString("tag %1 status error value parse failed.")
                    .arg(tag_index);
            this->statusLabel->setText(this->serverError);
            return;
          }

          QString tagErrorString = tagStatus.value("Error").toString();
          deviceLink.tags[tag_index].status = tagErrorString;

        } else if (tagObject.value("status").isString()) {
          QString tagStatus = tagObject.value("status").toString();
          deviceLink.tags[tag_index].status = tagStatus;
        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 status parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }
      }

      if (deviceLinkObject.value("status").isObject()) {
        QJsonObject statusObject = deviceLinkObject.value("status").toObject();

        if (statusObject.value("Error").isString()) {
          QString statusValue = statusObject.value("Error").toString();
          deviceLink.status = statusValue;
        } else {
          this->error = true;
          this->serverError = QString("Could not parse error state.");
          this->statusLabel->setText(this->serverError);
          return;
        }
      } else if (deviceLinkObject.value("status").isString()) {
        QString statusString = deviceLinkObject.value("status").toString();
        deviceLink.status = statusString;
      } else {
        this->error = true;
        this->serverError = QString("Could not parse status value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      if (!deviceLinkObject.value("last_poll_time").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse last poll time value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString lastPollString =
          deviceLinkObject.value("last_poll_time").toString();
      deviceLink.last_poll_time = lastPollString;

      if (!deviceLinkObject.value("protocol").isObject()) {
        this->error = true;
        this->serverError = QString("Could not parse protocol value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QJsonObject protocolObject =
          deviceLinkObject.value("protocol").toObject();

      if (protocolObject.value("ModbusTcp").isObject()) {
        QJsonObject modbusTcpObject =
            protocolObject.value("ModbusTcp").toObject();

        deviceLink.protocol = ST_MODBUS_TCP;

        if (!modbusTcpObject.value("ip").isString()) {
          this->error = true;
          this->serverError = QString("Could not parse ModbusTcp ip value.");
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString ipValue = modbusTcpObject.value("ip").toString();

        if (!modbusTcpObject.value("port").isDouble()) {
          this->error = true;
          this->serverError = QString("Could not parse ModbusTcp port value.");
          this->statusLabel->setText(this->serverError);
          return;
        }

        int portValue = modbusTcpObject.value("port").toInt();
        deviceLink.protocolDetails =
            QString("ModbusTcp:%1:%2").arg(ipValue).arg(portValue);

        SentinelModbusTcp modbusTcpConfig =
            SentinelModbusTcp(ipValue, portValue);

        deviceLink.setConfig(modbusTcpConfig);
      } else if (protocolObject.value("ModbusSerial").isObject()) {
        QJsonObject modbusSerialObject =
            protocolObject.value("ModbusSerial").toObject();

        if (!modbusSerialObject.value("ip").isString()) {
          this->error = true;
          this->serverError =
              QString("Could not parse ModbusSerial com port value.");
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString comPortValue = modbusSerialObject.value("com_port").toString();

        if (!modbusSerialObject.value("baudrate").isDouble()) {
          this->error = true;
          this->serverError =
              QString("Could not parse ModbusSerial baudrate value.");
          this->statusLabel->setText(this->serverError);
          return;
        }

        int baudrateValue = modbusSerialObject.value("baudrate").toInt();

        if (!modbusSerialObject.value("slave").isDouble()) {
          this->error = true;
          this->serverError =
              QString("Could not parse ModbusSerial slave value.");
          this->statusLabel->setText(this->serverError);
          return;
        }

        int slaveValue = modbusSerialObject.value("slave").toInt();
        SentinelModbusSerial modbusSerialConfig =
            SentinelModbusSerial(comPortValue, baudrateValue, slaveValue);

        deviceLink.protocolDetails =
            QString("ModbusSerial:%1:Baudrate(%2):Slave(%3)")
                .arg(comPortValue)
                .arg(baudrateValue)
                .arg(slaveValue);

        deviceLink.setConfig(modbusSerialConfig);

      } else {
        this->error = true;
        this->serverError = QString("Could not parse ModbusTcp value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      SentinelLink link = SentinelLink(deviceLink);

      this->linksBuffer.push_back(link);
      this->error = false;
      this->serverError = QString("Parse successful.");
      this->statusLabel->setText(this->serverError);
    } else if (value.toObject().value("Inputs").isObject()) {
      QJsonObject inputLinkObject = value.toObject().value("Inputs").toObject();

      int idValue = inputLinkObject.value("id").toInt();
      if (!inputLinkObject.value("tk").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link tk value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString tkValue = inputLinkObject.value("tk").toString();

      SentinelInputsLink inputLink = SentinelInputsLink(idValue, tkValue);

      if (!inputLinkObject.value("name").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link name value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString nameValue = inputLinkObject.value("name").toString();
      inputLink.name = nameValue;

      // Update the links Combobox.
      // This is a workaround

      this->linksList->setItemText(i, QString("%1 %2").arg(tkValue, nameValue));

      if (!inputLinkObject.value("tags").isArray()) {
        this->error = true;
        this->serverError = QString("Could not parse tags array.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QJsonArray tagsArray = inputLinkObject.value("tags").toArray();

      if (tagsArray.count() != N_CHANNELS) {
        this->error = true;
        this->serverError =
            QString("Server tags count doesn't equal monitor tags count.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      for (size_t tag_index = 0; tag_index < N_CHANNELS; tag_index++) {
        // TODO
        // Parse the tags.
        QJsonObject tagObject = tagsArray[tag_index].toObject();

        if (!tagObject.value("tk").isString()) {
          this->error = true;
          this->serverError = QString("tag %1 tk parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagTk = tagObject.value("tk").toString();
        inputLink.tags[tag_index].tk = tagTk;

        if (!tagObject.value("name").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 name parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagName = tagObject.value("name").toString();
        inputLink.tags[tag_index].name = tagName;

        if (!tagObject.value("unit").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 unit parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagUnit = tagObject.value("unit").toString();
        inputLink.tags[tag_index].unit = tagUnit;

        if (!tagObject.value("description").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 description parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagDescription = tagObject.value("description").toString();
        inputLink.tags[tag_index].description = tagDescription;

        if (!tagObject.value("enabled").isBool()) {
          this->error = true;
          this->serverError =
              QString("tag %1 enabled parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        bool tagEnabled = tagObject.value("enabled").toBool();
        inputLink.tags[tag_index].enabled = tagEnabled;

        if (!tagObject.value("value").isObject()) {
          this->error = true;
          this->serverError =
              QString("tag %1 value object parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QJsonObject tagValueObject = tagObject.value("value").toObject();

        if (tagValueObject.value("Real").isDouble()) {
          float tagRealValue = tagValueObject.value("Real").toDouble();
          inputLink.tags[tag_index].value.type = ST_REAL_VALUE;
          inputLink.tags[tag_index].value.real_value = tagRealValue;

        } else if (tagValueObject.value("Int").isDouble()) {
          int tagIntValue = tagValueObject.value("Int").toInt();
          inputLink.tags[tag_index].value.type = ST_INT_VALUE;
          inputLink.tags[tag_index].value.int_value = tagIntValue;

        } else if (tagValueObject.value("Bit").isDouble()) {
          int tagBitValue = tagValueObject.value("Bit").toInt();
          inputLink.tags[tag_index].value.type = ST_BIT_VALUE;
          inputLink.tags[tag_index].value.bit_value = tagBitValue;

        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 value type parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }
      }

      SentinelLink link = SentinelLink(inputLink);

      this->linksBuffer.push_back(link);
      this->error = false;
      this->serverError = QString("Parse successful.");
      this->statusLabel->setText(this->serverError);

    } else if (value.toObject().value("Eval").isObject()) {

      QJsonObject evalLinkObject = value.toObject().value("Eval").toObject();

      int idValue = evalLinkObject.value("id").toInt();
      if (!evalLinkObject.value("tk").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link tk value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString tkValue = evalLinkObject.value("tk").toString();

      SentinelEvalLink evalLink = SentinelEvalLink(idValue, tkValue);

      if (!evalLinkObject.value("name").isString()) {
        this->error = true;
        this->serverError = QString("Could not parse link name value.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QString nameValue = evalLinkObject.value("name").toString();
      evalLink.name = nameValue;

      // Update the links Combobox.
      // This is a workaround

      this->linksList->setItemText(i, QString("%1 %2").arg(tkValue, nameValue));

      if (!evalLinkObject.value("tags").isArray()) {
        this->error = true;
        this->serverError = QString("Could not parse tags array.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      QJsonArray tagsArray = evalLinkObject.value("tags").toArray();

      if (tagsArray.count() != N_CHANNELS) {
        this->error = true;
        this->serverError =
            QString("Server tags count doesn't equal monitor tags count.");
        this->statusLabel->setText(this->serverError);
        return;
      }

      for (size_t tag_index = 0; tag_index < N_CHANNELS; tag_index++) {
        // TODO
        // Parse the tags.
        QJsonObject tagObject = tagsArray[tag_index].toObject();

        if (!tagObject.value("tk").isString()) {
          this->error = true;
          this->serverError = QString("tag %1 tk parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagTk = tagObject.value("tk").toString();
        evalLink.tags[tag_index].tk = tagTk;

        if (!tagObject.value("name").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 name parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagName = tagObject.value("name").toString();
        evalLink.tags[tag_index].name = tagName;

        if (!tagObject.value("unit").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 unit parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagUnit = tagObject.value("unit").toString();
        evalLink.tags[tag_index].unit = tagUnit;

        if (!tagObject.value("description").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 description parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagDescription = tagObject.value("description").toString();
        evalLink.tags[tag_index].description = tagDescription;

        if (!tagObject.value("vars").isArray()) {
          this->error = true;
          this->serverError =
              QString("tag %1 vars parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QJsonArray tagVarsArray = tagObject.value("vars").toArray();
        int varsArraySize = tagVarsArray.size();

        for (int i = 0; i < varsArraySize; i++) {
          EvalVar evalVar;
          QJsonObject varObject = tagVarsArray[i].toObject();
          QString name = varObject.value("name").toString();
          int linkId = varObject.value("link_id").toInt();
          int tagId = varObject.value("tag_id").toInt();

          if (!varObject.value("value").isObject()) {
            this->error = true;
            this->serverError =
                QString("tag %1 vars parse failed.").arg(tag_index);
            this->statusLabel->setText(this->serverError);
            return;
          }

          QJsonObject varValueObject = varObject.value("value").toObject();

          evalVar.name = name;
          evalVar.linkId = linkId;
          evalVar.tagId = tagId;

          if (varValueObject.value("Real").isDouble()) {
            evalVar.value.type = ST_REAL_VALUE;
            evalVar.value.real_value = varValueObject.value("Real").toDouble();
          } else if (varValueObject.value("Int").isDouble()) {
            evalVar.value.type = ST_INT_VALUE;
            evalVar.value.int_value = varValueObject.value("Int").toInt();
          } else if (varValueObject.value("Bit").isBool()) {
            evalVar.value.type = ST_BIT_VALUE;
            evalVar.value.int_value = varValueObject.value("Bit").toBool();
          } else {
            this->error = true;
            this->serverError =
                QString("tag %1 vars value parse failed.").arg(tag_index);
            this->statusLabel->setText(this->serverError);
            return;
          }
          evalLink.tags[tag_index].vars.push_back(evalVar);
        }
        if (!tagObject.value("formula").isString()) {
          this->error = true;
          this->serverError =
              QString("tag %1 name parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QString tagFormula = tagObject.value("formula").toString();
        evalLink.tags[tag_index].formula = tagFormula;

        if (!tagObject.value("enabled").isBool()) {
          this->error = true;
          this->serverError =
              QString("tag %1 enabled parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        bool tagEnabled = tagObject.value("enabled").toBool();
        evalLink.tags[tag_index].enabled = tagEnabled;

        if (tagObject.value("status").isObject()) {
          QJsonObject tagStatus = tagObject.value("status").toObject();

          if (!tagStatus.value("Error").isString()) {
            this->error = true;
            this->serverError =
                QString("tag %1 status error value parse failed.")
                    .arg(tag_index);
            this->statusLabel->setText(this->serverError);
            return;
          }

          QString tagErrorString = tagStatus.value("Error").toString();
          evalLink.tags[tag_index].status = tagErrorString;

        } else if (tagObject.value("status").isString()) {
          QString tagStatus = tagObject.value("status").toString();
          evalLink.tags[tag_index].status = tagStatus;
        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 status parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }
        if (!tagObject.value("value").isObject()) {
          this->error = true;
          this->serverError =
              QString("tag %1 value object parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }

        QJsonObject tagValueObject = tagObject.value("value").toObject();

        if (tagValueObject.value("Real").isDouble()) {
          float tagRealValue = tagValueObject.value("Real").toDouble();
          evalLink.tags[tag_index].value.type = ST_REAL_VALUE;
          evalLink.tags[tag_index].value.real_value = tagRealValue;

        } else if (tagValueObject.value("Int").isDouble()) {
          int tagIntValue = tagValueObject.value("Int").toInt();
          evalLink.tags[tag_index].value.type = ST_INT_VALUE;
          evalLink.tags[tag_index].value.int_value = tagIntValue;

        } else if (tagValueObject.value("Bit").isBool()) {
          int tagBitValue = tagValueObject.value("Bit").toBool();
          evalLink.tags[tag_index].value.type = ST_BIT_VALUE;
          evalLink.tags[tag_index].value.bit_value = tagBitValue;

        } else {
          this->error = true;
          this->serverError =
              QString("tag %1 value type parse failed.").arg(tag_index);
          this->statusLabel->setText(this->serverError);
          return;
        }
      }

      SentinelLink link = SentinelLink(evalLink);

      this->linksBuffer.push_back(link);
      this->error = false;
      this->serverError = QString("Parse successful.");
      this->statusLabel->setText(this->serverError);

    } else {
      this->error = true;
      this->serverError = QString("Other links parsing is not implementd.");
      this->statusLabel->setText(this->serverError);
      return;
    }
  }
  // Save json data
  this->configData = QString("%1").arg(readData.toStdString());
  // Parse successfull. We update the GUI.
  this->updateView();
}

void MainWindow::updateView() {
  size_t arrayLen = this->numLinks;

  if (this->selectedLinkIndex > arrayLen - 1) {
    this->error = true;
    this->serverError =
        QString("Selected link index is outside the bounds of the links list.");
    this->statusLabel->setText(this->serverError);
    qDebug() << selectedLinkIndex;

    return;
  }
  // Edge case where vector is empty (size 0) and index is 0
  if (this->linksBuffer.empty()) {
    this->error = true;
    this->serverError = QString("Links list is empty.");
    this->statusLabel->setText(this->serverError);
    return;
  }

  if (this->linksBuffer.size() <= this->selectedLinkIndex) {
    qDebug() << "Selected Link index larger than array size. Index: "
             << this->selectedLinkIndex << "Size: " << this->linksBuffer.size();
    return;
  }

  Q_ASSERT(this->linksBuffer.size() > this->selectedLinkIndex);
  SentinelLink selectedLink = this->linksBuffer[this->selectedLinkIndex];

  SentinelDeviceLink selectedDeviceLink = selectedLink.deviceLink;
  SentinelInputsLink selectedInputsLink = selectedLink.inputsLink;
  SentinelEvalLink selectedEvalLink = selectedLink.evalLink;
  this->tableView->setDisabled(false);
  this->linksList->setDisabled(false);

  if (selectedLink.type == ST_DEVICE) {
    this->linkDetailsButton->setVisible(true);
  } else {
    this->linkDetailsButton->setVisible(false);
  }

  switch (selectedLink.type) {
  case ST_DEVICE:
    if (selectedLink.type == ST_MODBUS_TCP) {
      this->linkDetails->setText(
          QString("modbus:tcp:%1:%2")
              .arg(selectedDeviceLink.config.modbusTcp.ip)
              .arg(selectedDeviceLink.config.modbusTcp.port));
    } else if (selectedLink.type == ST_MODBUS_SERIAL) {
      this->linkDetails->setText(
          QString("modbus:rtu:%1:%2:%3")
              .arg(selectedDeviceLink.config.modbusSerial.comPort)
              .arg(selectedDeviceLink.config.modbusSerial.baudrate)
              .arg(selectedDeviceLink.config.modbusSerial.slave));
    } else {
      this->linkDetails->setText("Unimplemented link");
    }

    this->linkStatus->setDisabled(false);
    this->linkStatus->setText(selectedDeviceLink.status);
    this->model.setTableData(selectedDeviceLink);
    break;
  case ST_INPUTS:
    this->linkDetails->setText(
        QString("%1:%2").arg(selectedInputsLink.tk, selectedInputsLink.name));
    this->linkStatus->setDisabled(true);
    this->linkStatus->setText("INPUTS");
    this->model.setTableData(selectedInputsLink);
    break;
  case ST_EVALS:
    this->linkDetails->setText(
        QString("%1:%2").arg(selectedEvalLink.tk, selectedEvalLink.name));
    this->linkStatus->setDisabled(true);
    this->linkStatus->setText("EVALS");
    this->model.setTableData(selectedEvalLink);
    break;
  default:
    break;
  }
}

QByteArray MainWindow::tagReconfigJson(SentinelDeviceTag tag) {
  QJsonDocument doc{};
  QJsonObject tagObject{};
  QJsonObject tagInfo{};
  QJsonObject tagValue{};
  QJsonObject tagAddress{};
  QJsonObject modbusAddress{};
  QJsonObject tagReconfig{};

  switch (tag.value.type) {
  case ST_INT_VALUE:
    tagValue["Int"] = tag.value.int_value;
    break;
  case ST_REAL_VALUE:
    tagValue["Real"] = tag.value.real_value;
    break;
  case ST_BIT_VALUE:
    tagValue["Bit"] = tag.value.bit_value;
    break;
  default:
    break;
  }

  switch (tag.address.type) {
  case ST_MODBUS_ADDRESS:
    modbusAddress["Holding"] = tag.address.modbusRegister;
    tagAddress["ModbusAddr"] = modbusAddress;
    break;
  default:
    break;
  }

  tagInfo["link_id"] = this->selectedLinkIndex;
  tagInfo["tag_id"] = tag.id;
  tagObject["id"] = tag.id;
  tagObject["tk"] = tag.tk;
  tagObject["name"] = tag.name;
  tagObject["unit"] = tag.unit;
  tagObject["description"] = tag.description;
  tagObject["enabled"] = tag.enabled;
  tagObject["address"] = tagAddress;
  tagObject["value"] = tagValue;
  tagObject["status"] = QString("Normal");
  // tagObject["pending_write"] = QString("None");

  tagReconfig["tag_data"] = tagObject;
  tagReconfig["tag_info"] = tagInfo;

  doc.setObject(tagReconfig);
  return doc.toJson();
}

void MainWindow::postTagConfigRequest(int linkId, QByteArray data) {
  QUrl url = QUrl(QString(RECONFIG_TAG_URL));
  QNetworkRequest postRequest = QNetworkRequest(url);
  qDebug() << data;
  postRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                        QString("application/json"));
  this->reconfigTagReply.reset(qnam.post(postRequest, data));
  connect(this->reconfigTagReply.get(), &QNetworkReply::finished, this,
          &MainWindow::reconfigTagFinished);
}

void MainWindow::reconfigTagFinished() {

  if (this->reconfigTagReply->error() == QNetworkReply::NetworkError::NoError) {
    int statusCode =
        reconfigTagReply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
            .toInt();
    if (statusCode == 200) {
      // QMessageBox::information(this, "Success",
      //"Tag reconfigured successfull.");
    } else {
      QMessageBox::critical(
          this, "Server Error",
          "The server could not reconfigure the tag successfully.");
    }
  } else {
    QString errorMsg = QString("Could not reconfigure tag. %1")
                           .arg(reconfigTagReply->errorString());
    QMessageBox::critical(this, "Reconfigure Error", errorMsg);
  }
}
