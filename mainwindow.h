#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>
#include <QActionGroup>
#include <QCloseEvent>
#include <QColorDialog>
#include <QDataWidgetMapper>
#include <QDate>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QSettings>
#include <QStringListModel>
#include <QFileSystemModel>

#ifdef Q_OS_WIN
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#endif

#include "colorstxtwizard.h"
#include "configdialog.h"
#include "drawmapfigure.h"
#include "drawmapfiguretablemodel.h"
#include "figuredelegate.h"
#include "minetestmapperexe.h"
#include "translator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Translator *translator, QWidget *parent = nullptr);
    ~MainWindow() override;

    enum class GeometryGranularity {
        unspecified = -1,
        pixel = 0,
        block = 1
    };
    Q_ENUM(GeometryGranularity)
    const QMetaEnum meGeometryGranularity = QMetaEnum::fromType<GeometryGranularity>();

    enum class GeometrySizeMode {
        automatic = 0,
        fixed,
        shrink
    };
    Q_ENUM(GeometrySizeMode)
    const QMetaEnum meGeometrySizeMode = QMetaEnum::fromType<GeometrySizeMode>();

public slots:
    void startColorsTxtAssistant();
protected:
    void closeEvent(QCloseEvent* event) override;
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*) override;

    void showEvent(QShowEvent *event) override;
protected slots:
    // this slot is called by the language menu actions
    void slotLanguageChanged(QAction *action);
    void slotProfileChanged(QAction *action);

private slots:
    QString getOutputFileName();
    void on_button_generate_clicked();
    void readError(const QString &str);
    void mapperInitialized();
    void mapperFinisched(int exit);
    void error(QProcess::ProcessError error);
    void createProfilesMenu();
    void writeSettings();
    void writeProfile();
    void readSettings();
    void readProfile();

    void on_browseWorld_clicked();

    void on_saveImage_clicked();

    void on_browseHeightmapNodes_clicked();

    void on_browse_HeightmapColors_clicked();

    void on_browseColorsTxt_clicked();

    void on_actionAbout_MinetestMapperGUI_triggered();

    void on_actionAbout_MinetestMapper_triggered();

    void on_path_OutputImage_textChanged();

    void on_button_cancel_clicked();

    void on_actionNew_Profile_triggered();

    void on_actionEdit_colors_txt_triggered();

    void on_actionEdit_heightmap_nodes_txt_triggered();

    void on_actionEdit_heightmap_colors_txt_triggered();

    void on_drawScaleLeft_toggled(bool checked);

    void on_drawScaleTop_toggled(bool checked);

    void on_drawHeightscale_toggled(bool checked);
    
    void on_tilecenter_clicked();

    void on_tileorigin_clicked();

    void on_actionPreferences_triggered();

    void on_button_addFigure_clicked();

    void on_figure_geometry_apply_clicked();

    void on_button_deleteFigure_clicked();

    void on_figureSelect_currentIndexChanged(int index);

    void on_actionOpen_Terminal_triggered();

    void on_treeView_activated(const QModelIndex &index);

    void on_path_minetestWorlds_editingFinished();

    void on_treeView_clicked(const QModelIndex &index);

    void on_browseWorldsDir_clicked();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QProcess *myProcess;
    QActionGroup *profileGroup;
    #ifdef Q_OS_WIN
    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;
    #endif
    ConfigSettings currentSettings;

    void finishUiInitialisation();

    // creates the language menu dynamically from the content of m_langPath
    void createLanguageMenu();

    Translator *translator; // contains the translations for this application
    QString currentProfile; //contains the name of current loaded profile
    QString pathAppData; // Path where the settings should be stored.
    QString pathProfiles; // path where the profiles should be stored.
    QSettings *settings;
    QSettings *profile;
    QString getColorsTxtFilePath(QDir *appDir, QDir *worldDir);

    DrawMapFigureTableModel *drawMapFigureTable;
    QDataWidgetMapper *drawMapFigureTableMapper;
    MinetestMapperExe *minetestMapper;
    QStringListModel *backends = new QStringListModel();
    QFileSystemModel *minetestWorldsModel = new QFileSystemModel();

};

#endif // MAINWINDOW_H
