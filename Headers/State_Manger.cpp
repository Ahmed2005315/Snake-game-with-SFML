#include "State_Manger.h"
Engine::State_Manger::State_Manger() {
	m_add = false;
	m_remove = false;
	m_replace = false;
	m_removeAll = false;
}
Engine::State_Manger::~State_Manger(){}

//unique_ptr<Engine::State>& Engine::State_Manger:: GetCurrent() {return StateStack.top();}

Engine::State* Engine::State_Manger::GetCurrent() {
	return StateStack.top().get();
}

void Engine::State_Manger::Add(unique_ptr<State>StateToAdd, bool replace ) {
	m_add = true;
	NewState = move(StateToAdd);
	m_replace = replace;
}
void Engine::State_Manger::PopCurrent() {
	m_remove = true;
}

void Engine::State_Manger::PopAll() {
	m_removeAll = true;
	m_remove = false;
}

void Engine::State_Manger::Process_State_Change() {
	if (m_removeAll) {
		while (!StateStack.empty()) {
			StateStack.pop();
		}
		m_removeAll = false;
	}
	
	if (m_remove && !StateStack.empty()) {
		StateStack.pop();
		if (!StateStack.empty()) {
			StateStack.top()->Start();
		}
		m_remove = false;
	}
	if (m_add) {
		if (m_replace && !StateStack.empty()) {
			StateStack.top()->Pause();
			StateStack.pop();
			m_replace = false;
		}
		if (!StateStack.empty())
		{
			StateStack.top()->Pause();
		}
		
		m_add = false;
		StateStack.push(move(NewState));
		StateStack.top()->Init();
		StateStack.top()->Start();
	}
}

bool Engine::State_Manger::IsEmpty() {
	return StateStack.empty();
}