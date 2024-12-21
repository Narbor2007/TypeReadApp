#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_getTextLine_returnPressed();

    void on_setTextSizeBox_valueChanged(int arg1);

    void renderTextInStrings(QString firstString, QString secondString);

    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
