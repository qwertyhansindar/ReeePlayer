#ifndef ICLIP_H
#define ICLIP_H

#include <time_types.h>
#include <srs_interfaces.h>

class File;
class Library;

namespace srs
{
    class ICardFactory;
}

class Clip
{
    friend File;

    File* m_file = nullptr;
    QString m_uid;
    std::time_t m_begin = 0;
    std::time_t m_end = 0;
    std::vector<QString> m_subtitles;
    TimePoint m_added;
    std::vector<TimePoint> m_repeats;
    bool m_is_favorite = false;
    srs::ICardUPtr m_card;

    void set_file(File*);
public:
    Clip();

    const File* get_file() const;
    File* get_file();

    QString get_uid() const;
    void set_uid(const QString&);
    void generate_uid();

    std::time_t get_begin() const;
    void set_begin(std::time_t);
    std::time_t get_end() const;
    void set_end(std::time_t);

    TimePoint get_adding_time() const;
    void set_adding_time(TimePoint);

    void add_repeat(TimePoint);
    const std::vector<TimePoint>& get_repeats() const;
    void set_repeats(std::vector<TimePoint>);

    QString get_subtitle(int index) const;
    const std::vector<QString>& get_subtitles() const;
    void set_subtitles(std::vector<QString>&&);

    bool is_favorite() const;
    void set_favorite(bool);

    srs::ICard* get_card();
    const srs::ICard* get_card() const;
    void set_card(srs::ICardUPtr);
};

using ClipsPtr = std::shared_ptr<std::vector<Clip*>>;

struct ClipCmp
{
    bool operator()(const Clip* l, const Clip* r) const
    {
        return l->get_begin() < r->get_begin();
    };
};

using Clips = std::multiset<Clip*, ClipCmp>;

class File
{
    QString m_path;
    Clips m_clips;
    Library* m_library = nullptr;
    int m_player_time = 0;
    int m_length = 0;
public:
    File(Library*, const QString& path);
    ~File();

    Library* get_library();
    const Library* get_library() const;

    QString get_path() const;

    int get_num_clips() const;
    const Clips& get_clips() const;

    void add_clip(Clip*);
    void remove_clip(Clip*);

    int get_player_time() const;
    void set_player_time(int);

    int get_length() const;
    void set_length(int);
};

class IClipStorage
{
public:
    virtual std::vector<Clip*> get_all_clips() const = 0;
    virtual std::vector<Clip*> get_all_repeatable_clips() const = 0;
    virtual std::vector<Clip*> find(QStringView, int max) const = 0;
};

bool export_txt(const std::vector<Clip*>&, const QString& filename);

File* load_file(Library* library, const QString& path, const srs::ICardFactory* card_factory);
void save_file(const File* file);

#endif // !ICLIP_H

