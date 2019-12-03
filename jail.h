#ifndef JAIL_H
#define JAIL_H

#include "box.h"
#include <queue>

enum Type{Pass, LockUp};

class jail : public Box
{
public:

    jail();
    ~jail();
    void lockUp(Player);
    void queueUp(Player) override;
private:
    queue<Player*> playerInJail;
    queue<Player*> playerInPassing;
};

#endif // JAIL_H
