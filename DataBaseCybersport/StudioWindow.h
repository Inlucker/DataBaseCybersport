#ifndef STUDIOWINDOW_H
#define STUDIOWINDOW_H

#include <QWidget>

#include "Controllers/StudioController.h"
#include "Repositorys/CommentatorRepository.h"

namespace Ui {
class StudioWindow;
}

class StudioWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudioWindow(QWidget *parent = nullptr);
    ~StudioWindow();

    void login(shared_ptr<UserBL> user_bl, string role = "studio_owner");

signals:
    void exit();

private slots:
    void on_exit_btn_clicked();

private:
    void updateFreeCommentatorsList();
    void updateMyCommentatorsList();
    void updateStudiosList();
    void updateLists();

private:
    Ui::StudioWindow *ui;

    unique_ptr<StudioController> studio_controller;

    shared_ptr<CommentatorRepository> commentator_repository;
};

#endif // STUDIOWINDOW_H
