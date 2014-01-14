#ifndef QMWM_GUI_MAINWINDOWCONTROLLER_H
#define QMWM_GUI_MAINWINDOWCONTROLLER_H

#include <QString>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

namespace qmwm {
namespace gui {

class MainWindowController
{
public:
    ~MainWindowController();

    static MainWindowController *createInstance(const QString &qmlUrl);
    void show();

private:
    static void initContext(QQmlApplicationEngine *engine);
    static QQuickWindow *createAndInitWindow(QQmlApplicationEngine *engine);
    MainWindowController(QQmlApplicationEngine* engine, QQuickWindow* window);

    QQmlApplicationEngine* m_engine;
    QQuickWindow* m_window;
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_MAINWINDOWCONTROLLER_H
