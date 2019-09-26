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

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H
