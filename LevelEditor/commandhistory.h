#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "command.h"
#include "commandslistener.h"
#include <vector>
#include <cstdlib>

class CommandHistory
{

public:

    CommandHistory(CommandsListener *listener);

    ~CommandHistory();

    void add(Command * command);

    void undo();

    void redo();

    bool hasNext();

    bool hasPrevious();

    void clear();

    void setSavePoint();

    bool atSavePoint();

private:

    int _current;

    int _savePoint;

    std::vector<Command*> *_commands;

    CommandsListener *_listener;
};

#endif // COMMANDHISTORY_H
