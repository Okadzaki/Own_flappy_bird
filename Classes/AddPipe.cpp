
#include "AddPipe.h"
#include "config.h"

AddPipe::AddPipe()
{
    setName("AddPipe");
    dura = 0;
}

void AddPipe::update(float delta)
{
    parent = (HelloWorld*)getOwner();
    if (parent == NULL) return;
    
    dura+= delta;
    if (dura >= ktimeToAddPipe )
    {
        dura = 0;
        parent->addPipe();
    }
}
