#include "State.h"
#include <stack>

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
    StateMachine() = default;
    ~StateMachine() = default;

    void AddState(StateRef newState, bool isReplacing = true);
    void RemoveState();
    void Update();

    StateRef& GetActiveState();

private:
    std::stack<StateRef> m_states;
    StateRef m_newState;

    bool m_isRemoving;
    bool m_isAdding;
    bool m_isReplacing;
};