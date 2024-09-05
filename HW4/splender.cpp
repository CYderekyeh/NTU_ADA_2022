#include "splender.h"
#include <bits/stdc++.h>
using namespace std;

#define mem(arr, value) memset(arr, value, sizeof(arr))



namespace Solution{
using namespace Solution;

int n[3] = {40, 30, 20};
vector<card> deck[3];
vector<card> stk;
int score[2], gem[6] = {4, 4, 4, 4, 4, 4}, player_gem[2][7], hand[2][5], cnt[3];
set<int> imprisoned[2], buffer[3];

vector<int> mem_score[2], mem_gem[6], mem_player_gem[2][7], mem_hand[2][5], mem_cnt[3];
vector<set<int>> mem_imprisoned[2], mem_buffer[3];

void save(){
  for (int i = 0; i < 2; i++){
    mem_score[i].push_back(score[i]);
    mem_imprisoned[i].push_back(imprisoned[i]);
    for (int j = 0; j < 7; j++){
      mem_player_gem[i][j].push_back(player_gem[i][j]);
    }
    for (int j = 0; j < 5; j++){
      mem_hand[i][j].push_back(hand[i][j]);
    }
  }
  for (int i = 0; i < 6; i++){
    mem_gem[i].push_back(gem[i]);
  }
  for (int i = 0; i < 3; i++){
    mem_cnt[i].push_back(cnt[i]);
    mem_buffer[i].push_back(buffer[i]);
  }  
}

template <typename T>
inline void reset(T a[], vector<T> mem[], int i){
  a[i] = mem[i].back();
  mem[i].pop_back();
}

void roll_back(){
  for (int i = 0; i < 2; i++){
    reset(score, mem_score, i);
    reset(imprisoned, mem_imprisoned, i);
    for (int j = 0; j < 7; j++){
      reset(player_gem[i], mem_player_gem[i], j);
    }
    for (int j = 0; j < 5; j++){
      reset(hand[i], mem_hand[i], j);
    }
  }
  for (int i = 0; i < 6; i++){
    reset(gem, mem_gem, i);
  }
  for (int i = 0; i < 3; i++){
    reset(cnt, mem_cnt, i);
    reset(buffer, mem_buffer, i);
  }
}

int find_stack_number (int id) {
  if (id < n[0]) {
    return 0;
  }
  if (id < n[0] + n[1]) {
    return 1;
  }
  if (id < n[0] + n[1] + n[2]) {
    return 2;
  }
  exit(-1);
}

bool fail (struct move m, int player) {
  int sum = 0, mx = INT_MIN, mn = INT_MAX, tmp = 0;
  bool flag = true;
  switch (m.type) {
    case 1:
      // check the combination is legal
      for (int i = 0; i < 5; i++) {
        sum +=  m.gem[i];
        mx = max(mx, m.gem[i]);
        mn = min(mn, m.gem[i]);
      }
      switch (sum) {
        case 2:
          if (mx != 2 || mn != 0) {
            return true;
          }
          break;
        case 3:
          if (mx != 1 || mn != 0) {
            return true;
          }
          break;
        default:
          return true;
      }
      // check the remain gem in pubilic is enough
      for (int i = 0; i < 5; i++) {
        if (m.gem[i] > gem[i]) {
          return true;
        }
      }
      // check over limit of hand
      return player_gem[player][6] + sum > 10;
    case 2:
      // check the card is on the board or imprisoned
      if ((!buffer[find_stack_number(m.card_id)].count(m.card_id)) && (!imprisoned[player].count(m.card_id))) {
        return true;
      }
      // check the player has enough gem
      for (int i = 0; i < 5; i++) {
        if (player_gem[player][i] + hand[player][i] < stk[m.card_id].cost[i]) {
          tmp += stk[m.card_id].cost[i] - player_gem[player][i] - hand[player][i];
        }
      }
      return tmp > player_gem[player][5];
    case 3:
      // check the card is on the board
      if (!buffer[find_stack_number(m.card_id)].count(m.card_id)) {
        return true;
      }
      // check whether take the gem lead to over 10
      if (player_gem[player][6] >= 10 || gem[5] <= 0) {
        return true;
      }
      // check over the limit of the imprison card
      return imprisoned[player].size() >= 3;
    default:
      return true;
  }
}

bool play (struct move m, int player) {
  switch (m.type) {
    case 0:
      break;
    case 1:
      // get the gem from the public area
      for (int i = 0; i < 5; i++) {
        gem[i] -= m.gem[i];
        player_gem[player][i] += m.gem[i];
        player_gem[player][6] += m.gem[i];
      }
      break;
    case 2:
      // put the gem into the public area
      for (int i = 0; i < 5; i++) {
        int tmp_gem = max(stk[m.card_id].cost[i] - hand[player][i], 0);
        if (tmp_gem > player_gem[player][i]) {
          player_gem[player][5] -= tmp_gem - player_gem[player][i];
          player_gem[player][6] -= tmp_gem - player_gem[player][i];
          gem[5] += tmp_gem - player_gem[player][i];
          tmp_gem = player_gem[player][i];
        }
        player_gem[player][i] -= tmp_gem;
        player_gem[player][6] -= tmp_gem;
        gem[i] += tmp_gem;
      }
      // get the card from the board or imprisoned
      if (buffer[find_stack_number(m.card_id)].count(m.card_id)) {
        buffer[find_stack_number(m.card_id)].erase(m.card_id);
      }
      else {
        imprisoned[player].erase(m.card_id);
      }
      hand[player][stk[m.card_id].gem]++;
      score[player] += stk[m.card_id].score;
      break;
    case 3:
      // imprison the card
      buffer[find_stack_number(m.card_id)].erase(m.card_id);
      imprisoned[player].insert(m.card_id);
      // get special gem
      gem[5]--;
      player_gem[player][5]++;
      player_gem[player][6]++;
      break;
  }
  // cout << score[player] << endl;
  return score[player] >= 15;
}


void check_buffer (vector<card> v[3]) {
  for (int i = 0; i < 3; i++) {
    while (buffer[i].size() < 4 && cnt[i] < n[i]) {
      buffer[i].insert(v[i][cnt[i]].id);
      cnt[i]++;
    }
  }
}


vector<struct move> get_moves(int player){
  vector<struct move> al;
  for (int i = 1; i <= 3; i++){
    struct move m;
    m.type = i;
    switch (m.type) {
      case 1: {
        // takes 2 gems
        for (int i = 0; i < 5; i++){
          m.gem[i] = 2;
          al.push_back(m);
          m.gem[i] = 0;
        }
        // takes 3 gems
        int num[5] = {0, 0, 1, 1, 1};
        do {
          for (int i = 0; i < 5; i++){
            m.gem[i] = num[i];
          }
          al.push_back(m);
        } while (next_permutation(num, num + 5));
        break;
      }
      case 2:{
        // buy cards from buffer
        for (int i = 0; i < 2; i++){
          for (auto &id:buffer[i]){
            m.card_id = id;
            al.push_back(m);
          }
        }
        // buy cards from imprisoned 
        for (auto &id:imprisoned[player]){
          m.card_id = id;
          al.push_back(m);
        }
        break;
      }
      case 3:{
        // imprison cards from buffer
        for (int i = 0; i < 3; i++){
          for (auto &id:buffer[i]){
            m.card_id = id;
            al.push_back(m);
          }
        }
        break;
      }
    }
  }
  vector<struct move> res;
  for (auto &m:al){
    if (!fail(m, player)){
      res.push_back(m);
    }
  }
  return res;
}

int eval(){
  int score_dif = score[1] - score[0];
  int gem_dif = player_gem[1][6] - player_gem[0][6];
  int golden_dif = player_gem[1][5] - player_gem[0][5];
  int bonus_dif = 0;
  for (int i = 0; i < 5; i++){
    bonus_dif += hand[1][i] - hand[0][i];
  }
  return 30 * score_dif + 10 * gem_dif + 20 * golden_dif + 50 * bonus_dif; 
}

}



int minimax(int dep, bool ismax){
  if (Solution::score[0] >= 15){
    return -INT_MAX;
  }
  if (Solution::score[1] >= 15){
    return INT_MAX;
  }
  if (dep == 5){
    return Solution::eval();
  }
  if (ismax){
    Solution::check_buffer(Solution::deck);
    vector<struct move> legal_move = Solution::get_moves(1);
    vector<int> move_score;
    for (auto &m:legal_move){
      Solution::save(); 
      Solution::play(m, 0);
      int val = minimax(dep + 1, 0);
      move_score.push_back(val);
      Solution::roll_back();
    }
    int mx_idx = 0;
    for (int i = 0; i < (int)move_score.size(); i++){
      if (move_score[i] > move_score[mx_idx]){
        mx_idx = i;
      }
    }
    return move_score[mx_idx];
  }else{
    // get mini move
    Solution::check_buffer(Solution::deck);
    vector<struct move> legal_move = Solution::get_moves(0);
    vector<int> move_score;
    for (auto &m:legal_move){
      Solution::save(); 
      Solution::play(m, 0);
      int val = minimax(dep + 1, 1);
      move_score.push_back(val);
      Solution::roll_back();
    }
    int mn_idx = 0;
    for (int i = 0; i < (int)move_score.size(); i++){
      if (move_score[i] < move_score[mn_idx]){
        mn_idx = i;
      }
    }
    return move_score[mn_idx];
  }
}


void init (vector<card> stack_1, vector<card> stack_2, vector<card> stack_3) {
  Solution::deck[0] = stack_1;
  Solution::deck[1] = stack_2;
  Solution::deck[2] = stack_3;
  Solution::stk.resize(0);
  for (int i = 0; i < 3; i++){
    for (auto &c:Solution::deck[i]){
      Solution::stk.push_back(c);
    }
  }
  sort(Solution::stk.begin(), Solution::stk.end(), [&](const card &x, const card &y) {
    return x.id < y.id;
  });
  mem(Solution::score, 0);
  for (int i = 0; i < 6; i++){
    Solution::gem[i] = 4;
  }
  mem(Solution::player_gem, 0);
  mem(Solution::hand, 0);
  mem(Solution::cnt, 0);
}

struct move player_move (struct move server_move) {
  Solution::check_buffer(Solution::deck);
  if(Solution::play(server_move, 0)){
    cout << "WA!" << "\n";
    assert(false);
  }
  Solution::check_buffer(Solution::deck);

  vector<struct move> legal_move = Solution::get_moves(1);
  vector<int> score_move;
  for (auto &m:legal_move){
    Solution::save();
    Solution::play(m, 1);
    score_move.push_back(minimax(1, 0));
    Solution::roll_back();
  }
  int mx_idx = 0;
  for (int i = 0; i < (int)score_move.size(); i++){
    if (score_move[i] > score_move[mx_idx]){
      mx_idx = i;
    }
  }
  struct move my_move = legal_move[mx_idx];
  if (Solution::play(my_move, 1)){
    cout << "AC!" << "\n";
  }
  return my_move;
}
