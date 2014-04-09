#include "mainwindowcontroller.h"

#include <QObject>
#include <QList>
#include <QtQml/QQmlContext>
#include "qqml.h"

#include "gui/serialporthandler.h"
#include "gui/portinfomodel.h"
#include "gui/bluetoothporthandler.h"
#include "gui/bluetoothdiscoveryhandler.h"
#include "gui/bluetoothdiscoverymodel.h"
#include "gui/metawatchhandler.h"
#include "devicetypemessage.h"
#include "watchpropertyoperationmessage.h"
#include "controlfullscreenmessage.h"

namespace qmwm {
namespace gui {

MainWindowController *MainWindowController::createInstance(const QString &qmlUrl)
{
    qmlRegisterType<qmwm::gui::PortInfoModel>("QMetaWatchManager", 1, 0, "PortInfoModel");
    qmlRegisterType<qmwm::gui::SerialPortHandler>("QMetaWatchManager", 1, 0, "SerialPortHandler");
    qmlRegisterType<qmwm::gui::BluetoothPortHandler>("QMetaWatchManager", 1, 0, "BluetoothPortHandler");
    qmlRegisterType<qmwm::gui::BluetoothDiscoveryHandler>("QMetaWatchManager", 1, 0, "BluetoothDiscoveryHandler");
    qmlRegisterType<qmwm::gui::BluetoothDiscoveryModel>("QMetaWatchManager", 1, 0, "BluetoothDiscoveryModel");
    qmlRegisterType<qmwm::gui::MetaWatchHandler>("QMetaWatchManager", 1, 0, "MetaWatchHandler");
    qmlRegisterType<qmwp::DeviceTypeMessage>("QMetaWatchManager", 1, 0, "DeviceTypeMessage");
    qmlRegisterType<qmwp::WatchPropertyOperationMessage>("QMetaWatchManager", 1, 0, "WatchPropertyOperationMessage");
    qmlRegisterType<qmwp::ControlFullScreenMessage>("QMetaWatchManager", 1, 0, "ControlFullScreenMessage");

    QQmlApplicationEngine* engine = new QQmlApplicationEngine();
    initContext(engine);
    engine->load(QUrl(qmlUrl));
    QQuickWindow* window = createAndInitWindow(engine);
    return new MainWindowController(engine, window);
}

void MainWindowController::initContext(QQmlApplicationEngine* engine)
{
    QQmlContext* context = engine->rootContext();

    // Memory Leak !!
    //PortInfoModel* model = new PortInfoModel();
    //context->setContextProperty("portinfomodel", model);
}

QQuickWindow* MainWindowController::createAndInitWindow(QQmlApplicationEngine* engine)
{
    QList<QObject *> list = engine->rootObjects();
    QObject *topLevel = list.value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow *>(topLevel);

    //m_databaseManager->connect(m_window, SIGNAL(qmlOpenSqlFile(QString)), SLOT(onLoadSqlFile(QString)));
    //m_window->connect(m_databaseManager, SIGNAL(databaseReady()), SLOT(onDatabaseReady()));

    return window;
}

void MainWindowController::show()
{
    m_window->show();
}

MainWindowController::MainWindowController(QQmlApplicationEngine *engine, QQuickWindow *window)
    : m_engine(engine), m_window(window)
{
}

MainWindowController::~MainWindowController()
{
    delete m_engine;
    delete m_window;
}

} // namespace gui
} // namespace qmwm
