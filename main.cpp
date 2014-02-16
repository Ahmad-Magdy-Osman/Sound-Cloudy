#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QUrl url;
    if (argc > 1)
        url = QUrl::fromUserInput(argv[1]);
    else
        url = QUrl("http://www.soundcloud.com/XMasterrrr");
    MainWindow *browser = new MainWindow(url);
    browser->show();
    return app.exec();
}
