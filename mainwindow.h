#include <QtWidgets>

class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);

protected slots:

    void urlEditEnable();
    void urlEdit();

    void LoadDynamicJS();
    void downloadHTML();

private:
    QWebView *SCView;
    QLineEdit *URL;
};
