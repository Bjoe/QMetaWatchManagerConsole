#ifndef QMWM_GUI_BLUETOOTHDISCOVERYHANDLER_H
#define QMWM_GUI_BLUETOOTHDISCOVERYHANDLER_H

#include <QObject>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>

#include "gui/bluetoothdiscoverymodel.h"

namespace qmwm {
namespace gui {

class BluetoothDiscoveryHandler : public QObject
{
    Q_OBJECT

    Q_ENUMS(Error)
    Q_PROPERTY(Error error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(qmwm::gui::BluetoothDiscoveryModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
    explicit BluetoothDiscoveryHandler(QObject *parent = 0);

    enum Error
    {
        NoError,
        InputOutputError,
        PoweredOffError,
        UnknownError
    };

    Error error() const;

    bool running() const;
    void setRunning(bool running);

    BluetoothDiscoveryModel* model() const;
    void setModel(BluetoothDiscoveryModel* model);

public slots:
    void discover();

signals:
    void errorChanged();
    void runningChanged();
    void modelChanged();

private slots:
    void finishedDiscovery();
    void errorDiscovery(QBluetoothServiceDiscoveryAgent::Error error);

private:
    BluetoothDiscoveryHandler::Error m_error;
    BluetoothDiscoveryModel* m_model;
    QBluetoothServiceDiscoveryAgent* m_agent;
    bool m_running;
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_BLUETOOTHDISCOVERYHANDLER_H
