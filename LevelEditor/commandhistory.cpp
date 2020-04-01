#include "commandhistory.h"

CommandHistory::CommandHistory(CommandsListener *listener) :
    _current(0), _savePoint(0), _listener(listener)
{
    _commands = new std::vector<Command*>();
}

CommandHistory::~CommandHistory()
{
    clear();
    delete _commands;
}

void CommandHistory::add(Command * command)
{
    command->setCommandsListener(_listener);

    if (!hasNext()) {
        _commands->push_back(command);
        command->execute();
        ++_current;
    }
    else {
        for (int i=_current; i<(int)_commands->size(); ++i)
            delete _commands->at(i);

        _commands->erase(_commands->begin() + _current, _commands->end());
        _commands->push_back(command);
        command->execute();
        ++_current;
    }

    if (_listener != NULL)
        _listener->onChangeHistory();
}

void CommandHistory::undo()
{
    if (!hasPrevious()) return;

    _commands->at(_current - 1)->unexecute();
    --_current;

    if (_listener != NULL)
        _listener->onChangeHistory();
}

void CommandHistory::redo()
{
    if (!hasNext()) return;

    _commands->at(_current)->execute();
    ++_current;

    if (_listener != NULL)
        _listener->onChangeHistory();
}

bool CommandHistory::hasNext()
{
    if (_current == (int)_commands->size()) return false;
    return true;
}

bool CommandHistory::hasPrevious()
{
    if (_current == 0) return false;
    return true;
}

void CommandHistory::clear()
{
    std::vector<Command*>::iterator it;

    for (it=_commands->begin(); it != _commands->end(); ++it)
        delete (*it);

    _commands->clear();
    _savePoint = 0;
    _current = 0;

    if (_listener != NULL)
        _listener->onChangeHistory();
}

void CommandHistory::setSavePoint()
{
    _savePoint = _current;

    if (_listener != NULL)
        _listener->onChangeHistory();
}

bool CommandHistory::atSavePoint()
{
    return _savePoint == _current;
}
