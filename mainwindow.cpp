#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QLineEdit>

QString currentText = "Гори височать на горизонті, їх вершини сяють білосніжними ковпаками, які блискуче відбивають сонячні промені. Внизу, між пагорбами, розкинулися квітучі луки, де на зелених ковдрах трави розсипані яскраві плями жовтих, червоних і синіх кольорів. Струмки, немов срібні нитки, звиваються серед полів, утворюючи мереживо водних шляхів, що ведуть до величної річки. Лісові масиви, як безмежні смарагдові оази, витають у легкому серпанку, що додає їм загадковості і спокою. Навколо панує гармонія природи, і лише спів птахів порушує тишу, наповнюючи повітря мелодійними звуками життя. asdasd asda";
QString firstString, secondString;
int currentPressedSymbols = 0;
int currentStringNum = 1;
int currentCharacterIndex = 0;
bool isAnotherStringFinished = false;
int textSize = 36;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) {



    QString currentTargetText = (currentStringNum == 1 ? firstString : secondString);



    if (currentCharacterIndex < currentTargetText.length()) {
        QChar expectedChar = currentTargetText[currentCharacterIndex];

        if (currentTargetText[currentCharacterIndex] == event->text()) {
            qDebug() << "Correct key pressed: " << event->text();
            ++currentCharacterIndex;
            if (currentStringNum == 1) {
                renderTextInStrings(firstString, "empty");
            } else {
                renderTextInStrings("empty", secondString);
            };
        } else {
            qDebug() << "Incorrect key pressed " << event->text();
        }
    } else {
        qDebug() << "End of string.";
        currentStringNum = (currentStringNum == 1 ? 2 : 1);
        currentCharacterIndex = 0;
    }
}


std::tuple<QString, QString> splitText(QString text) {
    // Разбиваем строку на слова
    QStringList words = text.split(" ", Qt::SkipEmptyParts);

    // Векторы для хранения слов
    QVector<QString> firstStringV;
    QVector<QString> secondStringV;

    // Добавляем по 5 слов в каждый вектор
    if (words.size() < 5 && words.size() != 0) {
        return {text, ""};
    }else if (words.size() == 0) {
        return {"", ""};
    }else if (words.size() >= 5) {
        for (int i = 0; i < words.size(); ++i) {
            if (i < 5) {
                firstStringV.append(words[i]);
            } else {
                break;
            }
        }

        // Удаляем распределенные слова из текста
        words = words.mid(5);
        QString remainingText = words.join(" ");

        QString firstString = firstStringV[0];

        for (int i = 1; i < firstStringV.size(); i++) {
            firstString += " " + firstStringV[i];
        };

        // Возвращаем векторы и оставшийся текст
        return {firstString, remainingText};
    };
    return {"", ""};
}


QString formatTextForString(QString text, int currentCharacterIndex) {

    QString formatedString;
    formatedString += "<html><head/><body><p><span style=\" font-size:"+ QString::number(textSize) +"pt; color:#020202;\">";
    for (int i = 0; i < currentCharacterIndex; i++) {
        formatedString += text[i];
    };
    formatedString += "</span><span style=\" font-size:"+ QString::number(textSize) +"pt; color:#222222;\">";
    for (int i = currentCharacterIndex; i < text.size(); i++) {
        formatedString += text[i];
    };
    formatedString += "</span></p></body></html>";

    return formatedString;
};

void MainWindow::renderTextInStrings(QString firstString, QString secondString) {
    if (firstString != "empty") {
        ui->firstString->setText(formatTextForString(firstString, currentCharacterIndex));
    };
    if (secondString != "empty") {
        ui->secondString->setText(formatTextForString(secondString, currentCharacterIndex));
    };
};


void MainWindow::on_getTextLine_returnPressed() {
    // QString inText = ui->getTextLine->text();


    auto [firstStringT, remainingText1] = splitText(currentText);
    currentText = remainingText1;
    auto [secondStringT, remainingText2] = splitText(currentText);
    currentText = remainingText2;
    renderTextInStrings(firstStringT, secondStringT);

    firstString = firstStringT;
    secondString = secondStringT;

    qDebug() << "First vector:" << firstStringT;
    qDebug() << "Second vector:" << secondStringT;
    qDebug() << "Remaining text:" << currentText;
    qDebug() << "\n\n";

}


void MainWindow::on_setTextSizeBox_valueChanged(int arg1)
{
    qDebug() << arg1;
    textSize = arg1;
    renderTextInStrings(firstString, secondString);
}


void MainWindow::on_settingsButton_clicked()
{
    if (ui->getTextLine == nullptr) {
        ui->getTextLine = new QLineEdit(this);
        ui->setTextSizeBox = new QSpinBox(this);

        connect(ui->getTextLine, &QLineEdit::returnPressed, this, &MainWindow::on_getTextLine_returnPressed);
        connect(ui->setTextSizeBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_setTextSizeBox_valueChanged);

        ui->setTextSizeBox->setValue(textSize);
        ui->horizontalLayout->addWidget(ui->getTextLine);
        ui->horizontalLayout->addWidget(ui->setTextSizeBox);
    } else {
        ui->getTextLine->deleteLater();
        ui->getTextLine = nullptr;
        ui->setTextSizeBox->deleteLater();
        ui->setTextSizeBox = nullptr;
    };

}


