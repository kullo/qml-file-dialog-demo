#include <QQuickWindow>

#include "fileopendialog.h"

FileOpenDialog::FileOpenDialog(QQuickItem *parent) :
    QQuickItem(parent)
  , m_modality(Qt::WindowModal)
  , m_options(QSharedPointer<QFileDialogOptions>(new QFileDialogOptions()))
{
    m_dlgHelper = init_helper();

    connect(m_dlgHelper, SIGNAL(accept()), this, SLOT(accept()));
    connect(m_dlgHelper, SIGNAL(reject()), this, SLOT(reject()));
}

FileOpenDialog::~FileOpenDialog()
{
    if (m_dlgHelper)
        m_dlgHelper->hide();
    delete m_dlgHelper;
}

QUrl FileOpenDialog::fileUrl() const
{
    return fileUrl_;
}

QString FileOpenDialog::filename() const
{
    return filename_;
}

void FileOpenDialog::setFilename(QString filename)
{
    if (filename_ != filename)
    {
        filename_ = filename;
        emit filenameChanged();
    }
}

QString FileOpenDialog::title() const
{
    return title_;
}

void FileOpenDialog::setTitle(QString title)
{
    if (title_ != title)
    {
        title_ = title;
        emit titleChanged();
    }
}

QPlatformFileDialogHelper* FileOpenDialog::init_helper()
{
    m_dlgHelper = static_cast<QPlatformFileDialogHelper*>(QGuiApplicationPrivate::platformTheme()->createPlatformDialogHelper(QPlatformTheme::FileDialog));
    if (!m_dlgHelper)
        return NULL;

    return m_dlgHelper;
}

void FileOpenDialog::open()
{
    QQuickItem *parent = this->parentItem();
    Q_ASSERT(parent);

    QQuickWindow *window = parent->window();
    Q_ASSERT(window);

    m_parentWindow = window;

    m_options->setFileMode(QFileDialogOptions::ExistingFile);
    m_options->setAcceptMode(QFileDialogOptions::AcceptOpen);
    m_options->setWindowTitle(title());

    /*
     * Mac:
     * Set filename incl. directory via setInitiallySelectedFiles()
     *
     * Windows:
     * Set filename via setInitiallySelectedFiles() and let Windows choose the directory.
     * Default directory: C:\\Users\XYZ\Downloads
     *
     * Gnome:
     * Set directory via QPlatformFileDialogHelper::setDirectory() and leave
     * filename empty, since QGtk2FileDialogHelper can not set non-existing filenames.
     *
     */
#ifdef Q_OS_MACX // Use Q_OS_MACX for Qt 5.1+ code and Q_OS_OSX for Qt 5.2+ code.
    QString initialSelection = QFileInfo(QDir::homePath(), filename()).absoluteFilePath();
    qDebug() << "Initial file:" << initialSelection;
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
        m_options->setInitiallySelectedFiles(QList<QUrl>() << QUrl::fromLocalFile(initialSelection));
    #else
        m_options->setInitiallySelectedFiles(QStringList(initialSelection));
    #endif
#endif
#ifdef Q_OS_WIN
    qDebug() << "Initial filename:" << filename();
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
        m_options->setInitiallySelectedFiles(QList<QUrl>() << QUrl::fromLocalFile(filename()));
    #else
        m_options->setInitiallySelectedFiles(QStringList(filename()));
    #endif
#endif
#ifdef Q_OS_LINUX
    qDebug() << "Initial directory:" << QDir::homePath();
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
        m_dlgHelper->setDirectory(QUrl::fromLocalFile(QDir::homePath()));
    #else
        m_dlgHelper->setDirectory(QDir::homePath());
    #endif
#endif

    m_dlgHelper->setOptions(m_options);
    m_dlgHelper->setFilter(); // applyOptions();

    Qt::WindowFlags flags = Qt::Dialog;
    if (!title().isEmpty()) flags |= Qt::WindowTitleHint;

    m_visible = m_dlgHelper->show(flags, m_modality, m_parentWindow);
}

void FileOpenDialog::close()
{
    m_dlgHelper->hide();
    m_visible = false;
}

void FileOpenDialog::accept()
{
    m_dlgHelper->hide();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QList<QUrl> selectedUrls = m_dlgHelper->selectedFiles();
    if ( selectedUrls.count() )
    {
        setFileUrl(selectedUrls.at(0));
    }
#else
    QStringList selectedFiles = m_dlgHelper->selectedFiles();
    if ( selectedFiles.count() )
    {
        setFileUrl(QUrl(selectedFiles.at(0)));
    }
#endif

    emit accepted();
}

void FileOpenDialog::reject()
{
    m_dlgHelper->hide();
    emit rejected();
}

void FileOpenDialog::setFileUrl(QUrl fileUrl)
{
    if (fileUrl_ != fileUrl)
    {
        fileUrl_ = fileUrl;
        emit fileUrlChanged();
    }
}
