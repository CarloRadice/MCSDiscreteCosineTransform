#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    int getF();
    int getD();
    QString getFilename();
    bool start();


private slots:
    void on_loadimage_clicked();

    //void on_fLine_editingFinished();

    //void on_dLine_returnPressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
