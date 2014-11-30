template <typename T>
StateMachine<T>::StateMachine(T& owner)
	: mOwner(owner)
	, mpCurrentState(nullptr)
{

}
	
template <typename T>
StateMachine<T>::~StateMachine()
{
	Purge();
}

template <typename T>
void StateMachine<T>::AddState(State<T>* newState)
{
	mStates.push_back(newState);
}

template <typename T>
void StateMachine<T>::Purge()
{
	mpCurrentState = nullptr;

	for (auto state : mStates)
	{
		delete state;
	}

	mStates.clear();
}

template <typename T>
void StateMachine<T>::Update()
{
	if (mpCurrentState != nullptr)
	{
		mpCurrentState->Update(mOwner);
	}
}

template <typename T>
void StateMachine<T>::ChangeState(int stateIndex)
{
	if (mpCurrentState != nullptr)
	{
		mpCurrentState->Exit(mOwner);
	}

	mpCurrentState = mStates[stateIndex];

	if (mpCurrentState != nullptr)
	{
		mpCurrentState->Enter(mOwner);
	}

}