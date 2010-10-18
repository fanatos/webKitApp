#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QWebView;
class QSettings;
class QFile;
QT_END_NAMESPACE

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

protected:

    void closeEvent(QCloseEvent *event);

private slots:

    void openUrl();
    void openBmUrl();
    void about();
    void setHomePage();

    void resetSettings();

private:

    QWebView *view;

    QFile *bmFile;
    QMap<QString, QString> bmMap;

    QXmlStreamReader xml;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *editMenu;
    QMenu *bmSubMenu;

    QAction *openUrlAct;
    QList<QAction *> bmActList;
    QAction *exitAct;
    QAction *homePageAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *resetAct;

    QString m_homePage;

    void createActions();
    void createMenus();

    void readSettings();
    void writeSettings();

    void readBMFile();   

};

#endif // MAINWINDOW_H
