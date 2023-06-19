#include <cstdlib>
#include <random>

#include "../state/state.hpp"
#include "./submission.hpp"

std::mt19937 mt_rand(time(0));

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  return actions[(mt_rand()+depth)%actions.size()];
}
