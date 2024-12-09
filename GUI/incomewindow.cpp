#include "incomewindow.h"
#include "mainappwindow.h" // Добавляем заголовок для MainAppWindow
#include "TextField.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

IncomeWindow::IncomeWindow(MainAppWindow *mainAppWindow, QWidget *parent)
    : QWidget(parent), mainAppWindow(mainAppWindow)
{
    setupUI();
}

void IncomeWindow::setupUI()
{
    // Устанавливаем фиксированный размер окна
    setFixedSize(600, 700);

    // Устанавливаем заголовок окна
    setWindowTitle("Доходы");

    // Устанавливаем градиентный фон окна
    setStyleSheet("background: #FCFAFA;");

    // Создаем главный вертикальный layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем TextField для ввода суммы доходов
    TextField *amountEdit = new TextField(this);
    amountEdit->setPlaceholderText("Сумма доходов");
    mainLayout->addWidget(amountEdit, 0, Qt::AlignCenter);

    // Создаем QLabel для надписи "Категории"
    categoryLabel = new QLabel("Категории", this);
    QFont categoryFont("Calibri Light", 14); // Увеличиваем размер шрифта
    categoryLabel->setFont(categoryFont);
    categoryLabel->setStyleSheet("color: black; background-color: #FCFAFA;");
    mainLayout->addWidget(categoryLabel);

    // Создаем радиокнопки для выбора категории
    QVBoxLayout *categoryLayout = new QVBoxLayout;
    salaryRadio = new QRadioButton("Зарплата", this);
    giftRadio = new QRadioButton("Подарок", this);

    QFont radioFont("Calibri Light", 12); // Увеличиваем размер шрифта
    salaryRadio->setFont(radioFont);
    giftRadio->setFont(radioFont);

    categoryLayout->addWidget(salaryRadio);
    categoryLayout->addWidget(giftRadio);

    mainLayout->addLayout(categoryLayout);

    // Создаем QLabel для надписи "Дата"
    dateLabel = new QLabel("Дата", this);
    QFont dateFont("Calibri Light", 14); // Увеличиваем размер шрифта
    dateLabel->setFont(dateFont);
    dateLabel->setStyleSheet("color: black; background-color: #FCFAFA;");

    // Создаем горизонтальный layout для ввода даты
    QHBoxLayout *dateLayout = new QHBoxLayout;
    TextField *dayEdit = new TextField(this);
    dayEdit->setPlaceholderText("День");
    TextField *monthEdit = new TextField(this);
    monthEdit->setPlaceholderText("Месяц");

    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(dayEdit);
    dateLayout->addWidget(monthEdit);

    mainLayout->addLayout(dateLayout);

    // Создаем кнопку "Сохранить"
    saveButton = new QPushButton("Сохранить", this);
    saveButton->setFixedSize(150, 40);
    saveButton->setStyleSheet("QPushButton {"
                              "background-color: #A4B8C4;"
                              "color: white;"
                              "font-size: 16px;"
                              "border-radius: 20px;"
                              "border: 2px solid #8E9EAB;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: #8E9EAB;"
                              "}");
    mainLayout->addWidget(saveButton, 0, Qt::AlignCenter);

    // Устанавливаем отступы и интервалы
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10); // Уменьшаем интервал между элементами

    // Устанавливаем центральный виджет и layout
    setLayout(mainLayout);

    // Подключаем сигнал нажатия кнопки к слоту
    connect(saveButton, &QPushButton::clicked, this, &IncomeWindow::onSaveButtonClicked);
}

void IncomeWindow::onSaveButtonClicked()
{
    QString amountText = amountEdit->text();
    QString day = dayEdit->text();
    QString month = monthEdit->text();

    bool ok;
    double amount = amountText.toDouble(&ok);

    if (!ok || amountText.isEmpty() || day.isEmpty() || month.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля корректно.");
    } else {
        QString category;
        if (salaryRadio->isChecked()) {
            category = "Зарплата";
        } else if (giftRadio->isChecked()) {
            category = "Подарок";
        } else {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите категорию.");
            return;
        }

        // Добавляем доход в основное окно
        mainAppWindow->addIncome(category, amount, QString("%1.%2").arg(day).arg(month));

        QMessageBox::information(this, "Сохранено", QString("Сумма: %1\nКатегория: %2\nДата: %3.%4")
                                                        .arg(amount)
                                                        .arg(category)
                                                        .arg(day)
                                                        .arg(month));

        this->close(); // Закрываем окно доходов
    }
}
