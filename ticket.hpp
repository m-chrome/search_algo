#ifndef TICKET_HPP
#define TICKET_HPP

#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

namespace ticket {

    class TicketData
    {
        public:

            size_t number;
            size_t cost;
            size_t prize;

            TicketData();
            TicketData(size_t tnum, long double tcost, long double tprize)
                : number(tnum), cost(tcost), prize(tprize)
            {}
    };

    ostream& operator<<(ostream& os, const TicketData& data)
    {
        os << data.number << ' ' << data.cost << ' ' << data.prize;
        return os;
    }

    class Ticket
    {
        public:

            size_t date;
            TicketData data;

            Ticket();

            Ticket(size_t tdate, size_t tnum, long double tcost, long double tprize)
                : date(tdate), data(tnum, tcost, tprize)
            {}


            ~Ticket()
            {}

            bool operator <(const Ticket& other)
            {
                if (date!=other.date) return date<other.date;
                if (data.cost!=other.data.cost) return data.cost<other.data.cost;
                return data.number<other.data.number;
            }


    };

    ostream& operator<<(ostream& out, const Ticket& item)
    {
        out << item.date << ' ' << item.data << endl;
        return out;
    }

}
#endif // TICKET_HPP

