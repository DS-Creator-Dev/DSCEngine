#include "DSCEngine/events/event.hpp"

#include "DSCEngine/debug/assert.hpp"

DSC::Event::Event()
{
	actions.clear();
}

DSC::Event& DSC::Event::operator += (const EventHandler& e)
{
	nds_assert(e != nullptr);
	actions.push_back(e);
	return *this;
}

DSC::Event& DSC::Event::operator -= (const EventHandler& e)
{
	actions.remove(e);
	return *this;
}

void DSC::Event::trigger(void* sender, void* event_args) const
{
	for(int i=0;i<actions.size();i++)
	{	
		nds_assert(actions[i]!=nullptr); // if this is raised, something's really messed up
		actions[i](sender, event_args);
	}
}

