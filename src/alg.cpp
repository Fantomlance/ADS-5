// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char, 20> mpStack;
    std::string str;
    std::map<char, int> mp;
    mp['('] = 0;
    mp[')'] = 0;
    mp['+'] = 1;
    mp['-'] = 1;
    mp['*'] = 2;
    mp['/'] = 2;
    for (char ch : inf) {
        if (mp.find(ch) == mp.end()) {
            str += ch;
            str += ' ';
        } else {
            if (ch == ')') {
                while (mpStack.get() != '(') {
                    str += mpStack.get();
                    str += ' ';
                    mpStack.pop();
                }
                mpStack.pop();
            } else if (ch == '(' || mpStack.isEmpty()) {
                mpStack.push(ch);
            } else if (mp[ch] > mp[mpStack.get()]) {
                mpStack.push(ch);
            } else {
                while (!mpStack.isEmpty() && mp[mpStack.get()] >= mp[ch]) {
                    str += mpStack.get();
                    str += ' ';
                    mpStack.pop();
                }
                mpStack.push(ch);
            }
        }
    }
    while (!mpStack.isEmpty()) {
        str += mpStack.get();
        str += ' ';
        mpStack.pop();
    }
    str.pop_back();
    return str;
  }

int eval(std::string str) {
  TStack<int, 20> answStack;
  std::string mp = "+-*/";
  for (char ch : str) {
    if (ch == ' ') continue;
    std::size_t op = mp.find(ch);
    if (op == std::string::npos) {
      answStack.push(ch & 0xF);
    } else {
      int arg2 = answStack.get();
      answStack.pop();
      int arg1 = answStack.get();
      answStack.pop();
      int result;
      switch (mp[op]) {
      case '+':
        result = arg1 + arg2;
        break;
      case '-':
        result = arg1 - arg2;
        break;
      case '*':
        result = arg1 * arg2;
        break;
      case '/':
        result = arg1 / arg2;
        break;
      }
            answStack.push(result);
        }
    }
    return answStack.get();  return 0;
}
