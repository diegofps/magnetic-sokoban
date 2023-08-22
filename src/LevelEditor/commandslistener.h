#ifndef COMMANDSLISTENER_H
#define COMMANDSLISTENER_H

class CommandsListener {

public:

    virtual void onAddMap(int index) = 0;

    virtual void onRemoveMap(int oldIndex) = 0;

    virtual void onEditMap(int index) = 0;

    virtual void onChangeMap(int index, int hSlider, int vSlider) = 0;

    virtual void onMoveMap(int newIndex, int oldIndex) = 0;

    virtual void onChangeHistory() = 0;

};

#endif // COMMANDSLISTENER_H
