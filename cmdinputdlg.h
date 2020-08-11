#ifndef CMDINPUTDLG_H
#define CMDINPUTDLG_H

#include <QDialog>
#include <QString>

namespace Ui {
class cmdInputDlg;
}

class cmdInputDlg : public QDialog
{
    Q_OBJECT

public:
    explicit cmdInputDlg(QWidget *parent = 0);
    ~cmdInputDlg();
    void setText(QString);

signals:
    void sendData(QString);

private slots:
    void on_exitBtn_clicked();

    void on_okBtn_clicked();

    void on_asciiRd_toggled(bool checked);

    void on_hexRd_toggled(bool checked);

private:
    Ui::cmdInputDlg *ui;
};

#endif // CMDINPUTDLG_H
