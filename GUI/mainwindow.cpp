#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginWindow(nullptr)
    , registrationWindow(nullptr)
{
    ui->setupUi(this);

    // Устанавливаем заголовок окна
    setWindowTitle("Финансовый трекер");

    // Устанавливаем фиксированный размер окна
    setFixedSize(400, 600);

    // Устанавливаем градиентный фон основного окна
    setStyleSheet("background: #FCFAFA");

    // Создаем главный виджет и основной вертикальный layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаем QLabel для надписи "Добро пожаловать!"
    QLabel *welcomeLabel = new QLabel("Добро пожаловать!", centralWidget);
    QFont welcomeFont("Candara Light", 15, QFont::Bold); // Изменяем шрифт
    welcomeLabel->setFont(welcomeFont);
    welcomeLabel->setAlignment(Qt::AlignCenter); // Выравниваем по центру
    welcomeLabel->setStyleSheet("color: black; background-color: #FCFAFA;"); // Изменение стиля
    mainLayout->addWidget(welcomeLabel);

    // Создаем QLabel для эмблемы
    QLabel *logoLabel = new QLabel(centralWidget);
    QPixmap logoPixmap("/home/maksson/financial-tracker/GUI/images/кошелек.png"); // Путь к изображению
    logoLabel->setPixmap(logoPixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // Масштабируем изображение
    logoLabel->setAlignment(Qt::AlignCenter); // Выравниваем по центру
    logoLabel->setStyleSheet("background-color: #FCFAFA;"); // Устанавливаем фоновый цвет
    mainLayout->addWidget(logoLabel);

    // Создаем QLabel для надписи "Финансовый трекер"
    QLabel *trackerLabel = new QLabel("Финансовый трекер", centralWidget);
    QFont trackerFont("Calibri Light", 11, QFont::Bold); // Изменяем шрифт
    trackerLabel->setFont(trackerFont);
    trackerLabel->setAlignment(Qt::AlignCenter); // Выравниваем по центру
    trackerLabel->setStyleSheet("color: #B7C6C8; background-color: #FCFAFA;"); // Изменение стиля
    mainLayout->addWidget(trackerLabel);

    // Создаем вертикальный layout для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter); // Выравниваем кнопки по центру

    // Создаем кнопки "Войти" и "Регистрация"
    QPushButton *loginButton = new QPushButton("Войти", centralWidget);
    QPushButton *registerButton = new QPushButton("Регистрация", centralWidget);

    // Устанавливаем фиксированный размер для кнопок
    int buttonWidth = 150;
    int buttonHeight = 40;
    loginButton->setFixedSize(buttonWidth, buttonHeight);
    registerButton->setFixedSize(buttonWidth, buttonHeight);

    // Изменение стилей кнопок для прямоугольных кнопок с гладкими углами и тенями
    QString buttonStyle = "QPushButton {"
                          "background-color: #A4B8C4;"
                          "color: white;"
                          "font-size: 16px;"
                          "border-radius: 20px;"
                          "border: 2px solid #8E9EAB;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #8E9EAB;"
                          "}";
    loginButton->setStyleSheet(buttonStyle);

    // Изменение стилей кнопок для овальных кнопок с тенями
    buttonStyle = "QPushButton {"
                  "background-color: #6E8387;"
                  "color: white;"
                  "font-size: 16px;"
                  "border-radius: 20px;"
                  "border: 2px solid #5A6E72;"
                  "}"
                  "QPushButton:hover {"
                  "background-color: #5A6E72;"
                  "}";
    registerButton->setStyleSheet(buttonStyle);

    // Добавляем кнопки в вертикальный layout
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);

    // Добавляем вертикальный layout в основной вертикальный layout
    mainLayout->addLayout(buttonLayout);

    // Устанавливаем отступы и интервалы
    mainLayout->setContentsMargins(50, 50, 50, 50);
    mainLayout->setSpacing(20);

    // Устанавливаем центральный виджет и layout
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    // Подключаем обработчики событий для кнопок
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (loginWindow) delete loginWindow;
}

void MainWindow::onLoginButtonClicked() {
    hide();
    if (!loginWindow) {
        loginWindow = new LoginWindow();
        connect(loginWindow, &LoginWindow::cancelRequested, this, &MainWindow::showMainWindow); // Подключаем сигнал
    }
    loginWindow->show();
}

void MainWindow::onRegisterButtonClicked() {
    hide();
    if (!registrationWindow) {
        registrationWindow = new RegistrationForm();
        connect(registrationWindow, &RegistrationForm::cancelRequested, this, &MainWindow::show); // Подключаем сигнал
    }
    registrationWindow->show();
}

void MainWindow::showMainWindow() {
    this->show(); // Показываем MainWindow
}

