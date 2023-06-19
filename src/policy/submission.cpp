#include <cstdlib>
#include <random>

#include "../state/state.hpp"
#include "./submission.hpp"

const int inf = 1e9+7;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int MinMax(State *state, int depth, int alpha, int beta, int MaxPlayer){
  if(depth == 0 || !state->legal_actions.size())
    return state->evaluate();
  if(MaxPlayer){
    int value = -inf;
    for(auto i : state->legal_actions){
      State *next_state = state->next_state(i);
      value = std::max(value, MinMax(next_state, depth - 1, alpha, beta, 0));
      alpha = std::max(alpha, value);
      if(alpha >= beta)
        break;
    }
    return value;
  }
  else{
    int value = inf;
    for(auto i : state->legal_actions){
      State *next_state = state->next_state(i);
      value = std::min(value, MinMax(next_state, depth - 1, alpha, beta, 1));
      beta = std::min(beta, value);
      if(beta <= alpha)
        break;
    }
    return value;
  }
}

Move Random::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  int ans = MinMax(state, 5, -inf, inf, 1);
  for(auto i : state->legal_actions){
    State *next_state = state->next_state(i);
    if(next_state->evaluate() == ans){
      return i;
    }
  }
  auto actions = state->legal_actions;
  return actions[(rand()+depth)%actions.size()];
}
