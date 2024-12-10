#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "registrationform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void showMainWindow(); // Слот для отображения MainWindow

private:
    Ui::MainWindow *ui;
    LoginWindow *loginWindow;
    RegistrationForm *registrationWindow;
};

#endif // MAINWINDOW_H
