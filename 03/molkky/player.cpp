#include "player.hh"

Player::Player(std::string const &name):
    name_(name), points_(0)
{

}

std::string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return points_;
}

bool Player::has_won() const
{
    return points_ == MAX_POINTS;
}

void Player::add_points(int pts)
{
    points_ += pts;

    if(points_ > MAX_POINTS)
    {
        points_ = HALFWAY_POINTS;
    }
}
