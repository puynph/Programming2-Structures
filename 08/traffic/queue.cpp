#include "queue.hh"
#include <iostream>
using namespace std;
// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    first_(nullptr),
    last_(nullptr),
    is_green_(false),
    cycle_(cycle)
{

}

Queue::~Queue()
{
    Vehicle *current = first_, *temp;
    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

void Queue::enqueue(const string &reg)
{
    if (is_green_)
    {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        return;
    }
    Vehicle *vehicle = new Vehicle {reg, nullptr};
    if (first_ == nullptr)
    {
        first_ = vehicle;
        last_ = vehicle;
    }
    else
    {
        last_->next = vehicle;
        last_ = vehicle;
    }
}

void Queue::switch_light()
{
    if (!is_green_)
    {
        is_green_ = true;
        cout << "GREEN: ";
    }
    else
    {
        is_green_ = false;
        cout << "RED: ";
    }
    if (first_ == nullptr)
    {
        cout << "No vehicles waiting in traffic lights" << endl;
    }
    else
    {
        cout << "Vehicle(s) ";
        for(unsigned int i = 0; i < cycle_; i++)
        {
            if (first_ == nullptr) //???
            {
                break;
            }
            cout << first_->reg_num << ' ';
            dequeue();
        }
        cout << "can go on" << endl;
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    if (is_green_)
    {
        cout << "GREEN: ";
    }
    else
    {
        cout << "RED: ";
    }
    if (first_ != nullptr && !is_green_)
    {
        Vehicle *temp = first_;
        cout << "Vehicle(s) ";
        while (temp != nullptr)
        {
            cout << temp->reg_num << ' ';
            temp = temp->next;
        }
        cout << "waiting in traffic lights" << endl;
    }
    else
    {
        cout << "No vehicles waiting in traffic lights" << endl;
    }
}

void Queue::dequeue()
{
    Vehicle *temp = first_;
    first_ = temp->next;
    delete temp;
}
