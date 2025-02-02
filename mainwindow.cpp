#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QLineEdit>
#include <QString>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>


QString currentText = "";
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


std::tuple<QString, QString> splitText(QString text) {
    // Разбиваем строку на слова
    QStringList words = text.split(" ", Qt::SkipEmptyParts);

    // Векторы для хранения слов
    QVector<QString> splittedStringV;

    // Добавляем по 5 слов в каждый вектор
    if (words.size() < 5 && words.size() != 0) {
        return {text, ""};
    }else if (words.size() == 0) {
        return {"", ""};
    }else if (words.size() >= 5) {
        for (int i = 0; i < words.size(); ++i) {
            if (i < 5) {
                splittedStringV.append(words[i]);
            } else {
                break;
            }
        }

        // Удаляем распределенные слова из текста
        words = words.mid(5);
        QString remainingText = words.join(" ");

        QString splittedString = splittedStringV[0];

        for (int i = 1; i < splittedStringV.size(); i++) {
            splittedString += " " + splittedStringV[i];
        };

        // Возвращаем векторы и оставшийся текст
        return {splittedString, remainingText};
    };
    return {"", ""};
}


void MainWindow::keyPressEvent(QKeyEvent *event) {



    QString currentTargetText = (currentStringNum == 1 ? firstString : secondString);



    if (currentCharacterIndex < currentTargetText.length()) {
        QChar expectedChar = currentTargetText[currentCharacterIndex];

        if (currentTargetText[currentCharacterIndex] == event->text()) {

            qDebug() << "Correct key pressed: " << event->text();

            ++currentCharacterIndex;

            renderTextInStrings(
                ( currentStringNum == 1 ? ui->firstString : ui->secondString ),
                ( currentStringNum == 1 ? firstString : secondString ),
                  currentCharacterIndex);

            if (currentCharacterIndex >
                    (currentStringNum == 1 ? firstString.size()*0.8 : secondString.size()*0.8) &&
                    isAnotherStringFinished) {

                auto [newStringT, currentTextT] = splitText(currentText);
                (currentStringNum == 1 ? secondString : firstString) = newStringT;
                currentText = currentTextT;

                renderTextInStrings(
                    ( currentStringNum == 1 ? ui->secondString : ui->firstString ), (currentStringNum == 1 ? secondString : firstString), 0);
                isAnotherStringFinished = false;
            };



            // if (currentStringNum == 1) {
            //     renderTextInStrings(ui->firstString, firstString, currentCharacterIndex);
            //     if (currentCharacterIndex > firstString.size()*0.8 && isAnotherStringFinished) {

            //             auto [newStringT, currentTextT] = splitText(currentText);
            //             secondString = newStringT;
            //             currentText = currentTextT;

            //             renderTextInStrings(ui->secondString, secondString, 0);
            //             isAnotherStringFinished = false;
            //         };
            // } else {
            //     renderTextInStrings(ui->secondString, secondString, currentCharacterIndex);
            //     if (currentCharacterIndex > secondString.size()*0.8 && isAnotherStringFinished) {
            //         auto [newStringT, currentTextT] = splitText(currentText);
            //         firstString = newStringT;
            //         currentText = currentTextT;
            //         renderTextInStrings(ui->firstString, firstString, 0);
            //         isAnotherStringFinished = false;
            //     };
        } else {
            qDebug() << "Incorrect key pressed " << event->text();

            if (event->text() != "") {
                renderTextInStrings((currentStringNum==1 ? ui->firstString : ui->secondString), (currentStringNum==1 ? firstString : secondString), currentCharacterIndex, true);
            };
        };
    } else {
        qDebug() << "End of string.";
        currentStringNum = (currentStringNum == 1 ? 2 : 1);
        currentCharacterIndex = 0;
        isAnotherStringFinished = true;
    }
}



QString formatTextForString(QString text, int currentCharacterIndex, bool pressedWrongCharacter = false) {

    QString formatedString;
    formatedString += "<html><head/><body><p><span style=\" font-size:"+ QString::number(textSize) +"pt; color:#020202;\">";
    for (int i = 0; i < currentCharacterIndex; i++) {
        formatedString += text[i];
    };
    formatedString += "</span>";
    if (currentCharacterIndex < text.size()) {
        formatedString += "<span style=\" font-size:"+ QString::number(textSize) +"pt; color:"+(pressedWrongCharacter ? "#D84040" : "#959595")+";\">" + text[currentCharacterIndex] + "</span>";
        };
    formatedString += "<span style=\" font-size:"+ QString::number(textSize) +"pt; color:#959595;\">";
    for (int i = currentCharacterIndex+1; i < text.size(); i++) {
        formatedString += text[i];
    };
    formatedString += "</span></p></body></html>";

    return formatedString;
};

void MainWindow::renderTextInStrings(QLabel *labelToRenderObj, QString text, int howManyCharactersPressed, bool pressedWrongCharacter) {
    labelToRenderObj->setText(formatTextForString(text, howManyCharactersPressed, pressedWrongCharacter));
};

void MainWindow::on_setTextSizeBox_valueChanged(int arg1)
{
    qDebug() << arg1;
    if (textSize != arg1) {
        textSize = arg1;
        if (currentStringNum == 1) {
            renderTextInStrings(ui->firstString, firstString, currentCharacterIndex);
            renderTextInStrings(ui->secondString, secondString, (isAnotherStringFinished ? secondString.size() : 0));
        } else if (currentStringNum == 2) {
            renderTextInStrings(ui->secondString, secondString, currentCharacterIndex);
            renderTextInStrings(ui->firstString , firstString, (isAnotherStringFinished ? firstString.size() : 0));
        };
    };
}

void MainWindow::on_getTextLine_returnPressed() {
    QString inText = ui->getTextLine->text();
    currentText = inText;

    auto [firstStringT, remainingText1] = splitText(currentText);
    currentText = remainingText1;
    auto [secondStringT, remainingText2] = splitText(currentText);
    currentText = remainingText2;
    renderTextInStrings(ui->firstString, firstStringT, 0);
    renderTextInStrings(ui->secondString, secondStringT, 0);
    firstString = firstStringT;
    secondString = secondStringT;

    qDebug() << "First vector:" << firstStringT;
    qDebug() << "Second vector:" << secondStringT;
    qDebug() << "Remaining text:" << currentText;
    qDebug() << "\n\n";
    on_settingsButton_clicked();

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


