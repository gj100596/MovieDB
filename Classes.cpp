#include "iostream"

using namespace std;

/*
 * To be used for phase 3
 */

class movie {
    int id, vote_count, genre_ids;
    string title, poster_path, overview, date;
    float vote_average, popularity;


public:
    movie(int id, int vote_count, int genre_ids, const string &title, const string &poster_path, const string &overview,
          const string &date, float vote_average, float popularity) : id(id), vote_count(vote_count),
                                                                      genre_ids(genre_ids), title(title),
                                                                      poster_path(poster_path), overview(overview),
                                                                      date(date), vote_average(vote_average),
                                                                      popularity(popularity)
    {

    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        movie::id = id;
    }

    int getVote_count() const {
        return vote_count;
    }

    void setVote_count(int vote_count) {
        movie::vote_count = vote_count;
    }

    int getGenre_ids() const {
        return genre_ids;
    }

    void setGenre_ids(int genre_ids) {
        movie::genre_ids = genre_ids;
    }

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &title) {
        movie::title = title;
    }

    const string &getPoster_path() const {
        return poster_path;
    }

    void setPoster_path(const string &poster_path) {
        movie::poster_path = poster_path;
    }

    const string &getOverview() const {
        return overview;
    }

    void setOverview(const string &overview) {
        movie::overview = overview;
    }

    const string &getDate() const {
        return date;
    }

    void setDate(const string &date) {
        movie::date = date;
    }

    float getVote_average() const {
        return vote_average;
    }

    void setVote_average(float vote_average) {
        movie::vote_average = vote_average;
    }

    float getPopularity() const {
        return popularity;
    }

    void setPopularity(float popularity) {
        movie::popularity = popularity;
    }


    movie() {
    }

    movie(int id, const string &title) : id(id), title(title)
    {


    }

    bool operator==(const movie &rhs) const {
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

    bool operator!=(const movie &rhs) const {
        return !(rhs == *this);
    }

    void print_table(){
        cout<<id<<"\t"<<title<<endl;
    }

    friend ostream &operator<<(ostream &os, const movie &movie1) {
        os << "id: " << movie1.id << " vote_count: " << movie1.vote_count << " genre_ids: " << movie1.genre_ids
           << " title: " << movie1.title << " poster_path: " << movie1.poster_path << " overview: " << movie1.overview
           << " date: " << movie1.date << " vote_average: " << movie1.vote_average << " popularity: "
           << movie1.popularity;
        return os;
    }
};
