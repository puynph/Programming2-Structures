#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():
    top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    // allocate memory for new card
    // otherwise it would get deleted if we exit this function
    Card_data* card = new Card_data{id, top_};
    top_ = card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    // loop through linked list until we reach the last card
    Card_data* current = top_;
    int index = 1;
    while (current != nullptr)
    {
        s << index++ << ": " << current->data << std::endl;
        current = current->next;
    }
}

bool Cards::remove(int &id)
{
    // check if deck empty
    if (top_ == nullptr)
    {
        return false;
    }

    Card_data* temp = top_;
    top_ = temp->next;
    // set return value
    id = temp->data;

    // remove card
    delete temp;
    return true;
}

bool Cards::bottom_to_top()
{
    // check empty
    if (top_ == nullptr)
    {

        return false;
    }

    // when deck size is 1, nothing happens but we return true
    if (top_->next == nullptr)
    {
        return true;
    }
    // find the last two elements
    Card_data* last = top_, *second_last;
    while (last->next != nullptr)
    {
        second_last = last;
        last = last->next;
    }

    // move items around
    // set second last as last
    second_last->next = nullptr;

    // set last one on top
    last->next = top_;
    top_ = last;
    return true;
}

bool Cards::top_to_bottom()
{
    // check empty
    if (top_ == nullptr)
    {
        return false;
    }

    // when deck size is 1, nothing happens but we return true
    if (top_->next == nullptr)
    {
        return true;
    }

    // find the last card
    Card_data *last = top_, *temp;
    while (last->next != nullptr)
    {
        last = last->next;
    }

    // make the second top most the top card
    // and the currently top card the bottom card
    last->next = top_;
    temp = top_;
    top_ = top_->next;
    temp->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if (top_ == nullptr)
    {
        return;
    }
    recursive_print(top_,s);
}

Cards::~Cards()
{
    // deallocate all memory reserved with new
    // by looping through linked list and delete items
    Card_data* current = top_,* temp;
    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    if (top == nullptr)
        return 1;
    int index = recursive_print(top->next, s);
    s << index << ": " << top->data << std::endl;
    return index + 1;
}
