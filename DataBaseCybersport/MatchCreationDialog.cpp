#include "MatchCreationDialog.h"
#include "ui_MatchCreationDialog.h"

#include <QMessageBox>

MatchCreationDialog::MatchCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatchCreationDialog)
{
    ui->setupUi(this);

    teams_table_model = make_shared<TeamsTableModel>();
    studios_table_model = make_shared<StudiosTableModel>();
    commentators_table_model = make_shared<CommentatorsTableModel>();

    tournaments_repository = make_shared<TournamentsRepository>();
    teams_repository = make_shared<TeamsRepository>();
    studio_repository = make_shared<StudioRepository>();
    commentator_repository = make_shared<CommentatorRepository>();

    QList<QAbstractButton *> buttons = ui->buttonBox->buttons();
    for (auto &btn : buttons)
    {
        btn->setMinimumWidth(181);
        btn->setMinimumHeight(41);
    }
}

MatchCreationDialog::~MatchCreationDialog()
{
    delete ui;
}

void MatchCreationDialog::setup(int org_id)
{
    tournaments_id.clear();
    shared_ptr<vector<TournamentDTO>> tournaments_dto = tournaments_repository->getTournamentsDTOByOrgId(org_id);
    for (auto & tournament : *tournaments_dto)
    {
        tournaments_id.push_back(tournament.getId());
        ui->tournament_comboBox->addItem(QString::fromStdString(tournament.getName()));
    }
    updateStudiosList();
}


void MatchCreationDialog::on_tournament_comboBox_currentIndexChanged(int index)
{
    updateTeamsList(tournaments_id[index]);
}

void MatchCreationDialog::updateTeamsList(int tournament_id)
{
    shared_ptr<vector<TeamDTO>> teams_dto = teams_repository->getTeamsByTournament(tournament_id);
    teams_table_model = make_shared<TeamsTableModel>(teams_dto);

    ui->teams_tableView->setModel(teams_table_model.get());
    for (int i = 0; i < teams_table_model->columnCount(); i++)
        ui->teams_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void MatchCreationDialog::updateStudiosList()
{
    shared_ptr<vector<StudioDTO>> studios_dto = studio_repository->getAllStudios();
    studios_table_model = make_shared<StudiosTableModel>(studios_dto);

    ui->studios_tableView->setModel(studios_table_model.get());
    for (int i = 0; i < studios_table_model->columnCount(); i++)
        ui->studios_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void MatchCreationDialog::updateCommentatorsList()
{
    if (studio_id > 0)
    {
        shared_ptr<vector<CommentatorDTO>> commentators_dto = commentator_repository->getCommentatorsDTOByStudioId(studio_id);
        commentators_table_model = make_shared<CommentatorsTableModel>(commentators_dto);

        ui->commentatros_tableView->setModel(commentators_table_model.get());
        for (int i = 0; i < commentators_table_model->columnCount(); i++)
            ui->commentatros_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}


void MatchCreationDialog::on_teams_tableView_clicked(const QModelIndex &index)
{
    ui->teams_tableView->selectRow(index.row());
}


void MatchCreationDialog::on_studios_tableView_clicked(const QModelIndex &index)
{
    ui->studios_tableView->selectRow(index.row());
}


void MatchCreationDialog::on_commentatros_tableView_clicked(const QModelIndex &index)
{
    ui->commentatros_tableView->selectRow(index.row());
}


void MatchCreationDialog::on_choose_team1_btn_clicked()
{
    QModelIndexList selectedRows = ui->teams_tableView->selectionModel()->selectedRows();
    if (selectedRows.size() != 1)
    {
        QMessageBox::information(this, "Error", "Выберите только одну команду");
        return;
    }
    team1_id = ui->teams_tableView->model()->data(selectedRows[0]).toInt();

    if (team1_id == team2_id)
    {
        team1_id = 0;
        QMessageBox::information(this, "Error", "Эта команда уже выбрана, выберите другую команду");
        return;
    }

    QModelIndex name_index = teams_table_model->index(selectedRows[0].row(), 4);
    ui->team1_label->setText(ui->teams_tableView->model()->data(name_index).toString());
}


void MatchCreationDialog::on_choose_team2_btn_clicked()
{
    QModelIndexList selectedRows = ui->teams_tableView->selectionModel()->selectedRows();
    if (selectedRows.size() != 1)
    {
        QMessageBox::information(this, "Error", "Выберите только одну команду");
        return;
    }
    team2_id = ui->teams_tableView->model()->data(selectedRows[0]).toInt();

    if (team1_id == team2_id)
    {
        team2_id = 0;
        QMessageBox::information(this, "Error", "Эта команда уже выбрана, выберите другую команду");
        return;
    }

    QModelIndex name_index = teams_table_model->index(selectedRows[0].row(), 4);
    ui->team2_label->setText(ui->teams_tableView->model()->data(name_index).toString());
}


void MatchCreationDialog::on_choose_studio_btn_clicked()
{
    QModelIndexList selectedRows = ui->studios_tableView->selectionModel()->selectedRows();
    if (selectedRows.size() != 1)
    {
        QMessageBox::information(this, "Error", "Выберите только одну студию");
        return;
    }
    studio_id = ui->studios_tableView->model()->data(selectedRows[0]).toInt();

    QModelIndex name_index = studios_table_model->index(selectedRows[0].row(), 3);
    ui->studio_label->setText(ui->studios_tableView->model()->data(name_index).toString());

    updateCommentatorsList();
}


void MatchCreationDialog::on_choose_commentator_btn_clicked()
{
    QModelIndexList selectedRows = ui->commentatros_tableView->selectionModel()->selectedRows();
    if (selectedRows.size() != 1)
    {
        QMessageBox::information(this, "Error", "Выберите только одного комментатора");
        return;
    }
    commentator_id = ui->commentatros_tableView->model()->data(selectedRows[0]).toInt();

    QModelIndex name_index = commentators_table_model->index(selectedRows[0].row(), 3);
    ui->commentator_label->setText(ui->commentatros_tableView->model()->data(name_index).toString());
}


void MatchCreationDialog::on_dateEdit_dateChanged(const QDate &date)
{
    my_date = date;
}

