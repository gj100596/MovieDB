#include "iostream"

using namespace std;

/*
 * To be used for phase 3
 */

class Movies {
    int id, vote_count, genre_ids;
    string title, poster_path, overview, date;
    float vote_average, popularity;


public:
    Movies(int id, int vote_count, int genre_ids, const string &title,
          const string &poster_path, const string &overview,
          const string &date, float vote_average, float popularity) :
            id(id), vote_count(vote_count),
            genre_ids(genre_ids), title(title),
            poster_path(poster_path), overview(overview),
            date(date), vote_average(vote_average),
            popularity(popularity) {

    }
    Movies(int id){
        setId(id);
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        Movies::id = id;
    }

    int getVote_count() const {
        return vote_count;
    }

    void setVote_count(int vote_count) {
        Movies::vote_count = vote_count;
    }

    int getGenre_ids() const {
        return genre_ids;
    }

    void setGenre_ids(int genre_ids) {
        Movies::genre_ids = genre_ids;
    }

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &title) {
        Movies::title = title;
    }

    const string &getPoster_path() const {
        return poster_path;
    }

    void setPoster_path(const string &poster_path) {
        Movies::poster_path = poster_path;
    }

    const string &getOverview() const {
        return overview;
    }

    void setOverview(const string &overview) {
        Movies::overview = overview;
    }

    const string &getDate() const {
        return date;
    }

    void setDate(const string &date) {
        Movies::date = date;
    }

    float getVote_average() const {
        return vote_average;
    }

    void setVote_average(float vote_average) {
        Movies::vote_average = vote_average;
    }

    float getPopularity() const {
        return popularity;
    }

    void setPopularity(float popularity) {
        Movies::popularity = popularity;
    }


    Movies() {
    }

    Movies(int id, const string &title) : id(id), title(title) {


    }

    bool operator==(const Movies &rhs) const {
        return id == rhs.id &&
               vote_count == rhs.vote_count &&
               genre_ids == rhs.genre_ids &&
               title == rhs.title &&
               poster_path == rhs.poster_path &&
               overview == rhs.overview &&
               date == rhs.date &&
               vote_average == rhs.vote_average &&
               popularity == rhs.popularity;
    }

    bool operator!=(const Movies &rhs) const {
        return !(rhs == *this);
    }

    void print_table() {
        cout << id << "\t" << title << endl;
    }

    friend ostream &operator<<(ostream &os, const Movies &Movies1) {
        os << "id: " << Movies1.id << " vote_count: " << Movies1.vote_count << " genre_ids: " << Movies1.genre_ids
           << " title: " << Movies1.title << " poster_path: " << Movies1.poster_path << " overview: " << Movies1.overview
           << " date: " << Movies1.date << " vote_average: " << Movies1.vote_average << " popularity: "
           << Movies1.popularity;
        return os;
    }
};
