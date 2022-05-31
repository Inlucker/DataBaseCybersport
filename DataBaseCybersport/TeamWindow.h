#ifndef TEAMWINDOW_H
#define TEAMWINDOW_H

#include <QWidget>

namespace Ui {
class TeamWindow;
}

class TeamWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeamWindow(QWidget *parent = nullptr);
    ~TeamWindow();

private slots:
    void on_exit_btn_clicked();

signals:
    void exit();

private:
    Ui::TeamWindow *ui;
};

#endif // TEAMWINDOW_H
