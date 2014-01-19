#ifndef QMWM_GUI_SERIALPORTHANDLER_H
#define QMWM_GUI_SERIALPORTHANDLER_H

#include <functional>
#include <QObject>
#include <QSerialPort>

#include "gui/portinfomodel.h"

namespace qmwm {
namespace gui {

class SerialPortHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qmwm::gui::PortInfoModel* model READ model WRITE setModel NOTIFY modelChanged)
    //Q_PROPERTY(QSerialPort::BaudRate baudRate READ baudRate WRITE setbaudRate NOTIFY baudRateChanged)

public:
    explicit SerialPortHandler(QObject *parent = 0);

    PortInfoModel* model();
    void setModel(PortInfoModel* model);

public slots:
    void onRefresh();
    void onConnectPort(int index);
    void onSend(const QString &command);

signals:
    void output(QString data);
    void modelChanged();
    void error(QString message);

private slots:
    void onReadyRead();

private:
    QSerialPort* m_serialPort;
    PortInfoModel* m_model;

    void check(std::function<bool(QSerialPort* serialPort)> func);
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_SERIALPORTHANDLER_H
