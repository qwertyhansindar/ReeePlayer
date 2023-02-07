#ifndef APP_H
#define APP_H

#include <QSettings>
#include <srs.h>

class Project;
class Library;

namespace srs
{
    class ICardFactory;
}

struct SubsCollection
{
    std::vector<QString> files;
    std::vector<int> indices;
};

enum class PLAYER_ENGINE { VLC = 0, Web = 1 };

class App
{
public:
    App();
    ~App();

    void open_dir(const QString&);

    QString get_recent_dir() const;

    Library* get_library();

    QSettings* get_settings();
    QVariant get_setting(const QString&, const QString&, const QVariant& default_value = QVariant()) const;
    void set_setting(const QString&, const QString&, const QVariant&);

    libvlc_instance_t* get_vlc_instance() const;

    SubsCollection get_subtitles(const QString& video_file);
    void save_subtitle_priority(const QString& video_file, const SubsCollection&);

    const srs::ICardFactory* get_card_factory() const;
private:
    SubsCollection get_subtitles(const QString& video_file, const QString& priorities);

    libvlc_instance_t* m_vlc_inst = nullptr;

    std::unique_ptr<QSettings> m_settings;
    std::unique_ptr<Library> m_library;
    std::unique_ptr<srs::ICardFactory> m_card_factory;
};

#endif // !APP_H

