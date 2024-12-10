#include <iostream>

#include "loginwindow.h"
#include "mainappwindow.h" // Добавляем заголовок для MainAppWindow
#include "TextField.h"
#include "data_base.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    // Устанавливаем фиксированный размер окна
    setFixedSize(450, 600);

    // Устанавливаем заголовок окна
    setWindowTitle("Авторизация");

    // Устанавливаем градиентный фон окна
    setStyleSheet("background: #FCFAFA;");

    // Создаем главный вертикальный layout
    QVBoxLayout *loginMainLayout = new QVBoxLayout(this);

    // Создаем QLabel для надписи "Логин"
    loginLabel = new QLabel("Логин", this);
    QFont loginFont("Calibri Light", 11); // Изменяем шрифт
    loginLabel->setFont(loginFont);
    loginLabel->setStyleSheet("color: black; background-color: #FCFAFA;");
    loginMainLayout->addWidget(loginLabel);

    // Создаем TextField для ввода логина
    TextField *loginEdit = new TextField(this);
    loginMainLayout->addWidget(loginEdit);

    // Создаем QLabel для надписи "Пароль"
    passwordLabel = new QLabel("Пароль", this);
    QFont passwordFont("Calibri Light", 11); // Изменяем шрифт
    passwordLabel->setFont(passwordFont);
    passwordLabel->setStyleSheet("color: black; background-color: #FCFAFA;");
    loginMainLayout->addWidget(passwordLabel);

    // Создаем TextField для ввода пароля
    TextField *passwordEdit = new TextField(this);
    passwordEdit->setEchoMode(QLineEdit::Password); // Скрываем вводимый пароль
    loginMainLayout->addWidget(passwordEdit);

    // Создаем кнопку "Показать пароль"
    showPasswordButton = new QPushButton("Показать пароль", this);
    showPasswordButton->setFixedSize(130, 30);
    showPasswordButton->setStyleSheet("QPushButton {"
                                      "background-color: #6E8387;"
                                      "color: white;"
                                      "font-size: 15px;"
                                      "border-radius: 15px;"
                                      "border: 2px solid #5A6E72;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #5A6E72;"
                                      "}");
    connect(showPasswordButton, &QPushButton::clicked, this, &LoginWindow::onShowPasswordButtonClicked);
    loginMainLayout->addWidget(showPasswordButton);

    // Создание горизонтального layout для кнопок "Войти" и "Отмена"
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Создаем кнопку "Войти"
    loginButton = new QPushButton("Войти", this);
    loginButton->setFixedSize(150, 40);
    loginButton->setStyleSheet( "QPushButton {"
                               "background-color: #A4B8C4;"
                               "color: white;"
                               "font-size: 16px;"
                               "border-radius: 20px;"
                               "border: 2px solid #8E9EAB;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #8E9EAB;"
                               "}");
    buttonLayout->addWidget(loginButton, 0, Qt::AlignLeft);

    // Создание кнопки "Отмена"
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    cancelButton->setFixedSize(100, 40);
    cancelButton->setStyleSheet("QPushButton {"
                                "background-color: #A4B8C4;"
                                "color: white;"
                                "font-size: 16px;"
                                "border-radius: 20px;"
                                "border: 2px solid #8E9EAB;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #8E9EAB;"
                                "}");
    buttonLayout->addWidget(cancelButton, 0, Qt::AlignRight);
    connect(cancelButton, &QPushButton::clicked, this, &LoginWindow::onCancelButtonClicked);

    // Добавляем тень к кнопке
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(0, 4);
    loginButton->setGraphicsEffect(shadowEffect);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    loginMainLayout->addWidget(showPasswordButton, 0, Qt::AlignCenter);
    loginMainLayout->addWidget(loginButton, 0, Qt::AlignCenter);

    // Создаем QLabel для сообщения об успешной авторизации
    successLabel = new QLabel("", this);
    successLabel->setStyleSheet("color: green; background-color: #FCFAFA;");
    successLabel->hide(); // Скрываем метку до нажатия кнопки "Войти"
    loginMainLayout->addWidget(successLabel);
    loginMainLayout->addLayout(buttonLayout);

    // Устанавливаем отступы и интервалы
    loginMainLayout->setContentsMargins(50, 50, 50, 50);
    loginMainLayout->setSpacing(20);

    // Устанавливаем центральный виджет и layout
    setLayout(loginMainLayout);
}

void LoginWindow::onLoginButtonClicked() {
    QString login = loginEdit->text();
    QString password = passwordEdit->text();

    DBManager dbManager("172.27.8.206", "financal_tracker", "project_user", "123");
    dbManager.connect();

    QString query = QString(
            "SELECT COUNT(*) "
            "FROM users "
            "WHERE login = '%1' AND password = '%2';"
        ).arg(login, password);

    if (dbManager.executeQuery(query)) {
        std::cout << "Данные успешно вставлены.\n";
    } else {
        std::cout << "Ошибка при вставке данных: " << dbManager.getLastError().toStdString() << "\n";
    }

    QMessageBox::information(this, "Информация", "Вы успешно авторизовались!");
    successLabel->setText("Вы успешно авторизовались!");
    successLabel->show();

    // Открываем основное окно приложения
    MainAppWindow *mainAppWindow = new MainAppWindow();
    mainAppWindow->show();
    this->close(); // Закрываем окно авторизации
}

void LoginWindow::onShowPasswordButtonClicked() {
    // Обработка нажатия кнопки "Показать пароль"
    if (passwordEdit->echoMode() == QLineEdit::Password) {
        passwordEdit->setEchoMode(QLineEdit::Normal);
        showPasswordButton->setText("Скрыть пароль");
    } else {
        passwordEdit->setEchoMode(QLineEdit::Password);
        showPasswordButton->setText("Показать пароль");
    }
}

void LoginWindow::onCancelButtonClicked() {
    emit cancelRequested(); // Отправка сигнала
    this->close(); // Закрытие текущего окна
}
