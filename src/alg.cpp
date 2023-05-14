// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char x) {
if (x == '(')
return 0;
if (x == ')')
return 1;
if ((x == '+') || (x == '-'))
return 2;
if ((x == '*') || ( x == '/'))
return 3;
if ((x == '(') || (x ==')'))
return 0;
return -1;
}

std::string infx2pstfx(std::string inf) {
TStack<char, 100> stack1;
  std::string out = "";
  int res = 0;
  for (char a : inf) {
    bool flag = true;
    if (prior(a) == -1) {
      out += a;
      out += ' ';
      flag = false;
    }
    if (prior(a) == 0) {
      stack1.push(a);
      flag = false;
    }
    if (prior(a) > prior(stack1.pol())) {
      stack1.push(a);
      flag = false;
    }
    if (stack1.empty() && prior(a) != -1) {
      stack1.push(a);
      flag = false;
    }
    if (flag && a != ')') {
      while (prior(stack1.pol()) >= prior(a)) {
        out += stack1.pop();
        out += ' ';
      }
      stack1.push(a);
    }
    if (a == ')') {
      while (stack1.pol() != '(') {
        out += stack1.pop();
        out += ' ';
      }
      stack1.pop();
    }
    if (res == inf.size() - 1) {
      while (!stack1.empty()) {
        out += stack1.pop();
        if (stack1.pri() != -1) out += ' ';
      }
    }
    ++res;
  }
  return out;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  for (char a : pref) {
    if (a == '+') {
      int tmp = stack2.pop();
      tmp = tmp + stack2.pop();
      stack2.push(tmp);
    }
    if (a == '-') {
      int tmp = stack2.pop();
      tmp = stack2.pop() - tmp;
      stack2.push(tmp);
    }
    if (a == '/') {
      int tmp = stack2.pop();
      tmp = stack2.pop() / tmp;
      stack2.push(tmp);
    }
    if (a == '*') {
      int tmp = stack2.pop();
      tmp = tmp * stack2.pop();
      stack2.push(tmp);
    }
    if (a == ' ') {
      continue;
    }
    if ((a - '0') > 0) {
      int tmp = a - '0';
      stack2.push(tmp);
    }
  }
  return stack2.pol();
}
