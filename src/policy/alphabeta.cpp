#include <cstdlib>
#include <random>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

const int inf = 1e9+7;
const double eps = 1e-4;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int MinMax(State *state, int depth, int alpha, int beta, int MaxPlayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth == 0 || !state->legal_actions.size())
    return state->evaluate();
  if(MaxPlayer){
    int value = -inf;
    for(auto i : state->legal_actions){
      State *next_state = state->next_state(i);
      int x = MinMax(next_state, depth - 1, alpha, beta, 0);
      value = std::max(value, x);
      alpha = std::max(alpha, x);
      if(alpha >= beta)
        break;
    }
    return value;
  }
  else{
    int value = inf;
    for(auto i : state->legal_actions){
      State *next_state = state->next_state(i);
      int x = MinMax(next_state, depth - 1, alpha, beta, 1);
      value = std::min(value, x);
      beta = std::min(beta, x);
      if(beta <= alpha)
        break;
    }
    return value;
  }
}

Move AlphaBeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  int mx = -inf;
  std::vector<Move>vec;
  for(auto i : state->legal_actions){
    State *next_state = state->next_state(i);
    int ans = MinMax(next_state, depth, -inf, inf, 0);
    if(ans >= mx){
      if(ans > mx){
	vec.clear();
	mx = ans;
      }
      vec.push_back(i);
    }
  }
  if(vec.size())
    return vec[(rand() + depth)%vec.size()];
  auto actions = state->legal_actions;
  return actions[(rand()+depth)%actions.size()];
}
