#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//declare constants
int const MAX_POINTS = 50,
          HALFWAY_POINTS = 25;

class Player
{
public:
    Player(std::string const &name);
    std::string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int pts);

private:
    std::string name_;
    int points_;
};

#endif // PLAYER_H
