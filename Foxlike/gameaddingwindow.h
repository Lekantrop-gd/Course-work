#ifndef GAMEADDINGWINDOW_H
#define GAMEADDINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameAddingWindow;
}

class GameAddingWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void gameAdded();
    void hidden();

public:
    explicit GameAddingWindow(QWidget *parent = nullptr);
    ~GameAddingWindow();

private slots:
    void on_bannerButton_clicked();

    void on_imageButton_clicked();

    void on_logoButton_clicked();

    void on_publishGameButton_clicked();

private:
    Ui::GameAddingWindow *ui;

    QString banner;
    QString image;
    QString logo;

    void closeEvent(QCloseEvent *event) override;
};

#endif // GAMEADDINGWINDOW_H
