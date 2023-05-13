#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);
    ~ErrorWindow();
    void setErrorText(std::string text);

private slots:
    void on_pushButtonDetails_clicked();

    void on_pushButtonWiederholen_clicked();

    void on_pushButtonAbbrechen_clicked();

private:
    Ui::ErrorWindow *ui;
    QString errorText;
};

#endif // ERRORWINDOW_H
