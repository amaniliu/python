#ifndef CORRECT_DIALOG_H
#define CORRECT_DIALOG_H

#include <QGroupBox>
#include <QLineEdit>
#include <QToolButton>

#define SIGNGLE_WIDTH 1272
#define CHANNEL_NUM 6

class CorrectDialog : public QGroupBox
{
	Q_OBJECT
public:
	CorrectDialog();
private:
	void initui();
	void getCorrectData(unsigned char* src, int width, int height, unsigned char* dst);
    void saveCorrectData(const char* filename, unsigned char* const black, unsigned char* const white, int length = SIGNGLE_WIDTH * CHANNEL_NUM);
private slots:
	void btn_dir1();
	void btn_dir2();
	void btn_correct();
	void getTextChanged(const QString& text);
private:
	QToolButton* m_dir1;
	QToolButton* m_dir2;
	QToolButton* m_correct;

	QLineEdit* m_lineEdit1;
	QLineEdit* m_lineEdit2;
};
#endif
