#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QProgressBar>
#include <QMessageBox>
#include <QRegExp>
#include <QTranslator>
#include <QColorDialog>
#include <QDate>
#include <QCloseEvent>
#ifdef Q_OS_WIN
#include <QWinTaskbarProgress>
#include <QWinTaskbarButton>
#endif


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

protected slots:
    // this slot is called by the language menu actions
    void slotLanguageChanged(QAction* action);

private slots:
    QString getOutputFileName();
    void on_button_generate_clicked();
    void readOutput();
    void readError();
    void mapperFinisched(int exit);
    void error(QProcess::ProcessError error);
    void writeSettings();
    void readSettings();

    void on_browseWorld_clicked();

    void on_saveImage_clicked();

    void on_browseHeightmapNodes_clicked();

    void on_browse_HeightmapColors_clicked();

    void on_selectBgColor_clicked();

    void on_selectBlockColor_clicked();

    void on_selectScaleColor_clicked();

    void on_selectOriginColor_clicked();

    void on_selectPlayerColor_clicked();

    void on_selectTileBorderColor_clicked();

    void on_browseColorsTxt_clicked();

    void on_actionAbout_MinetestMapperGUI_triggered();

    void on_actionAbout_MinetestMapper_triggered();

    void on_path_OutputImage_textChanged();

    void on_selectHeightmapColor_clicked();

    void on_button_cancel_clicked();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QProcess *myProcess;
    #ifdef Q_OS_WIN
    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;
    #endif

    // loads a language by the given language shortcur (e.g. de, en)
    void loadLanguage(const QString& rLanguage);

    // creates the language menu dynamically from the content of m_langPath
    void createLanguageMenu(void);

    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString m_currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.
};

#endif // MAINWINDOW_H
