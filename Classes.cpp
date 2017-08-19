#include "iostream"

using namespace std;

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


    movie() {
    }

    movie(int id, const string &title) : id(id), title(title)
    {


    }

};
