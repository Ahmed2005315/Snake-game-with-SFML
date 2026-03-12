#pragma once
#include<stack>
#include<memory>
#include"State.h"
using namespace std;
namespace Engine {
	class State_Manger
	{
	private:
		bool m_add,m_remove,m_replace,m_removeAll;
		stack<unique_ptr<State>>StateStack;
		unique_ptr<State>NewState;
	public:
		State_Manger();
		~State_Manger();
		void Add(unique_ptr<State>StateToAdd, bool replace=false);
		void PopCurrent();
		//unique_ptr<State> &GetCurrent();
		Engine::State* GetCurrent();

		
		void Process_State_Change();
		bool IsEmpty();
		void PopAll();
	};
}

