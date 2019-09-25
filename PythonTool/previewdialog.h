#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class PreviewDialog;
}

class QImage;
class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QImage* img, QWidget *parent = nullptr);
    ~PreviewDialog();

private slots:
    void on_btn_zoomin_clicked();

    void on_btn_zoomout_clicked();

    void on_btn_zoomorign_clicked();

    void on_btn_zoomfit_clicked();

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H
