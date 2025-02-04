#ifndef CHOISEMODEWINDOW_H
#define CHOISEMODEWINDOW_H

#include <QDialog>

namespace Ui {
class ChoiseModeWindow;
}

class ChoiseModeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiseModeWindow(QWidget *parent = nullptr);
    ~ChoiseModeWindow();

private:
    Ui::ChoiseModeWindow *ui;
};

#endif // CHOISEMODEWINDOW_H
