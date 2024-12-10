#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

signals:
    void cancelRequested(); // Сигнал для уведомления MainWindow

private slots:
    void onLoginButtonClicked();
    void onShowPasswordButtonClicked();
    void onCancelButtonClicked(); // Слот для кнопки "Отмена"

private:
    QLabel *loginLabel;
    QLineEdit *loginEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *showPasswordButton;
    QLabel *successLabel;
};

#endif // LOGINWINDOW_H
