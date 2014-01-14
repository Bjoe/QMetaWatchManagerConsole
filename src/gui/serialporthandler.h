#ifndef QMWM_GUI_SERIALPORTHANDLER_H
#define QMWM_GUI_SERIALPORTHANDLER_H

#include <functional>
#include <QObject>
#include <QSerialPort>

#include "gui/portinfomodel.h"
#include "core/devicehandler.h"

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
    void onSend();

signals:
    void modelChanged();

private:
    QSerialPort* m_serialPort;
    DeviceHandler* m_deviceHandler;
    PortInfoModel* m_model;

    void check(std::function<bool(QSerialPort* serialPort)> func);
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_SERIALPORTHANDLER_H
