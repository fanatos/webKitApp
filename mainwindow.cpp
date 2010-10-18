#include <QtGui>
#include <QtWebKit>
#include "QDebug"

#include "mainwindow.h"

// comment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    setupUi(this);

    setWindowTitle(tr("Very tiny web browser"));

    readBMFile();

    createActions();
    createMenus();

    view = new QWebView(this);
    setCentralWidget(view);

    showMaximized();
    readSettings();

    view->setUrl(QUrl(m_homePage));
    view->show();

}

void MainWindow::readBMFile(){

    bmFile = new QFile("../webKitApp/bookmarks.xml", this);

    if (bmFile->open(QFile::ReadOnly));

    xml.setDevice(bmFile);

    QString name, url;

    while (!xml.atEnd()) {

        if (xml.readNextStartElement()) {

            if (xml.name() == "name") name = xml.readElementText();
            if (xml.name() == "url") url = xml.readElementText();
        }

        if (name != "" && url != "") {
            bmMap.insert(name,url);
        }

    }

    bmFile->close();
}

void MainWindow::readSettings(){

    QSettings settings("test1","test2");
    m_homePage = settings.value("home_page", "http://www.google.com").toString();

}

void MainWindow::writeSettings(){

    QSettings settings("test1","test2");
    settings.setValue("home_page", QUrl(m_homePage));

}

void MainWindow::closeEvent(QCloseEvent *event){

    writeSettings();
    event->accept();

}

void MainWindow::resetSettings(){

    QSettings settings("test1","test2");

    settings.clear();
    QMessageBox::about(this, tr("Reset settings"), tr("Settings reset successfully"));

    readSettings();

}

void MainWindow::createActions() {

    openUrlAct = new QAction(tr("&Open url..."), this);
    connect(openUrlAct, SIGNAL(triggered()), this, SLOT(openUrl()));

    for (int i = 0; i < bmMap.size(); ++i) {

        //bmActList.append(new QAction(bmMap.key(i), this));
        bmActList.append(new QAction("wtf", this));

        connect(bmActList.at(i), SIGNAL(triggered()), this, SLOT(openBmUrl()));
    }

    exitAct = new QAction(tr("&Exit"), this);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    homePageAct = new QAction(tr("Home page..."), this);
    connect(homePageAct, SIGNAL(triggered()), this, SLOT(setHomePage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    resetAct = new QAction(tr("Reset Settings"), this);
    connect(resetAct, SIGNAL(triggered()), this, SLOT(resetSettings()));

}

void MainWindow::openBmUrl() {

    QAction *action = qobject_cast<QAction *>(sender()); // ???
    //Q_UNUSED(action);
    if (action) qDebug() << "xxx";
        //loadFile(action->data().toString());

}

void MainWindow::createMenus() {

    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(openUrlAct);
    bmSubMenu = fileMenu->addMenu(tr("Bookmarks"));
    // -----------------------------

    for (int i=0; i < bmActList.size(); i++) {

        bmSubMenu->addAction(bmActList.at(i));

    }


    // -----------------------------
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(homePageAct);
    editMenu->addAction(resetAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));

    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}

void MainWindow::setHomePage(){

    bool ok;

    QString url = QInputDialog::getText(this, tr("Please enter url..."), tr("URL: "),
                                        QLineEdit::Normal, m_homePage, &ok);

    if (ok && !url.isEmpty()) {

        m_homePage = url;

    }

}

void MainWindow::openUrl(){

    bool ok;

    QString url = QInputDialog::getText(this, tr("Please enter url..."), tr("URL: "),
                                        QLineEdit::Normal, "http://", &ok);

    if (ok && !url.isEmpty()) {

        view->setUrl(QUrl(url));
    }

}

void MainWindow::about(){

    QMessageBox::about(this, tr("WebKit sample app"), tr("This is nothing special"));

}
