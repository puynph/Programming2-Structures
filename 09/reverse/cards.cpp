#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    // check if the deck is empty or not
    if (top_.get() == nullptr)
    {
        return false;
    }

    // make the top card pointer the next one
    // the amount of references reduced to 0... reduce.. deallocate
    id = top_->data;
    top_ = top_->next;
    return true;
}

void Cards::reverse()
{
    // check empty
    if (top_.get() == nullptr)
    {
        return;
    }

    // create the copy of the original to reverse order
    Cards new_deck = Cards();
    while (top_->next.get() != nullptr)
    {
        new_deck.add(top_->data);
        top_ = top_->next;
    }
    new_deck.add(top_->data);

    // set new deck top
    top_ = new_deck.top_;
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
