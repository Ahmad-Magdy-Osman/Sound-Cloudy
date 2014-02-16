#include <QtWidgets>
#include <QtNetwork>
#include <QtWebKitWidgets>
#include <QWebFrame>
#include "mainwindow.h"

MainWindow::MainWindow(const QUrl& url)
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    SCView = new QWebView(this);
    SCView->load(url);

    connect(SCView, SIGNAL(loadFinished(bool)), SLOT(urlEditEnable()));
    connect(SCView, SIGNAL(loadFinished(bool)), SLOT(LoadDynamicJS()));

    URL = new QLineEdit(this);
    URL->setSizePolicy(QSizePolicy::Expanding, URL->sizePolicy().verticalPolicy());
    connect(URL, SIGNAL(returnPressed()), SLOT(urlEdit()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addWidget(URL);
    toolBar->setMovable(false);

    QMenu *SCViewMenu = menuBar()->addMenu(tr("&View"));
    QAction* downloadHTMLAction = new QAction("Download HTML", this);
    connect(downloadHTMLAction, SIGNAL(triggered()), SLOT(downloadHTML()));
    SCViewMenu->addAction(downloadHTMLAction);

    setCentralWidget(SCView);
}

void MainWindow::urlEditEnable()
{
    URL->setText(SCView->url().toString());
}

void MainWindow::urlEdit()
{
    QUrl url = QUrl::fromUserInput(URL->text());
    SCView->load(url);
    SCView->setFocus();
}

void MainWindow::LoadDynamicJS()
{
    bool loadJS = true;
    while(SCView->page()->mainFrame()->scrollBarValue(Qt::Vertical)!=SCView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical) && loadJS==true)
    {
        SCView->page()->mainFrame()->setScrollBarValue(Qt::Vertical, SCView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical));
        SCView->page()->mainFrame()->setScrollBarValue(Qt::Vertical, SCView->page()->mainFrame()->scrollBarMinimum(Qt::Vertical));

        QString test = SCView->page()->mainFrame()->toHtml();

        if(test.contains("<div class=\"paging-eof sc-border-light-top\" title=\"This is the end… my only friend, the end.\"></div>",Qt::CaseSensitive))
        {
            loadJS = false;
        }
        else
            loadJS = true;
    }
}

void MainWindow::downloadHTML()
{
    QFile HTMLFile(QString(SCView->title() + ".html"));
    if ( HTMLFile.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&HTMLFile);
        stream << QString(SCView->page()->mainFrame()->toHtml()) << endl;
    }
}
