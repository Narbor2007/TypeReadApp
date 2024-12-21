/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *settingsButton;
    QLineEdit *getTextLine;
    QSpinBox *setTextSizeBox;
    QLabel *firstString;
    QLabel *secondString;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1055, 436);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(settingsButton);

        getTextLine = new QLineEdit(centralwidget);
        getTextLine->setObjectName("getTextLine");

        horizontalLayout->addWidget(getTextLine);

        setTextSizeBox = new QSpinBox(centralwidget);
        setTextSizeBox->setObjectName("setTextSizeBox");
        setTextSizeBox->setValue(36);

        horizontalLayout->addWidget(setTextSizeBox);


        verticalLayout->addLayout(horizontalLayout);

        firstString = new QLabel(centralwidget);
        firstString->setObjectName("firstString");

        verticalLayout->addWidget(firstString);

        secondString = new QLabel(centralwidget);
        secondString->setObjectName("secondString");

        verticalLayout->addWidget(secondString);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "settings", nullptr));
        firstString->setText(QString());
        secondString->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
