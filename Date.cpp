/**
 * Write functions for Date. 功能包含偵測日期格式是否正確並將格式統一轉成字串、判斷日期的關係，以及計算日期間相差的天數。
 *
 * @author 			熊亮茵
 * @ID 				B11505064
 * @Department 		Engineering Science and Ocean Engineering
 * @Affiliation 	National Taiwan University
 *
 * Date.cpp
 * version 1.0
 */

#include "Date.h"
#include <iostream>
using namespace std;

  /** 
   *  Constructs a Date with the given month, day and year.   If the date is
   *  not valid, the entire program will halt with an error message.
   *  @param month is a month, numbered in the range 1...12.
   *  @param day is between 1 and the number of days in the given month.
   *  @param year is the year in question, with no digits omitted.
   *
   *  Grade: 15%
   */
  Date::Date(int month, int day, int year) {
      //Detection for invalid date.
      if (!Date::isValidDate(month, day, year)) {
          cout << "\nInvalid input." << endl;
          std::exit(0);
      }
      //Turn interger into string
      s_m = to_string(month);
      s_d = to_string(day);
      s_y = to_string(year);
  }
  

  /** 
   *  Constructs a Date object corresponding to the given string.
   *  @param s should be a string of the form "month/day/year" where month must
   *  be one or two digits, day must be one or two digits, and year must be
   *  between 1 and 4 digits.  If s does not match these requirements or is not
   *  a valid date, the program halts with an error message.
   *
   *  Grade: 30%
   */
  Date::Date(const string& s) {
      string month;
      string day;
      string year;
      //when meet '/' use it as a breaking point, than check if the length of the digits are right
      size_t found = s.find(slash);
      if (found != string::npos) {
          pos_1 = int(found);
          for (int i = 0; i < pos_1; i++) {
              month += s[i];
          }
      }
      found = s.find(slash, found + 1);
      if (found != string::npos) {
          pos_2 = int(found);
          for (int i = pos_1+1; i < pos_2; i++) {
              day += s[i];
          }
      }
      for (int i = 0; i < sizeof(s); i++) {
          if (s[i] == NULL) {
              tail = i;
              for (int j = pos_2+1; j < tail; j++) {
                  year += s[j];
              }
              break;
          }
      }
      //Put the results in a global variable.
      s_m = month;
      s_d = day;
      s_y = year;
      //turn string into interger
      mn = stoi(s_m);
      dy = stoi(s_d);
      yr = stoi(s_y);
      //Check if the digits are right.
      if ((pos_1 != 1) && (pos_1 != 2)) {
          cout << "\nInvalid input." << endl;
          std::exit(0);
      }
      if ((pos_2 - pos_1 - 1 != 1) && (pos_2 - pos_1 - 1 != 2)) {
          cout << "\nInvalid input." << endl;
          std::exit(0);
      }
      if ((tail - pos_2 - 1 < 1) || (tail - pos_2 - 1 > 4)) {
          cout << "\nInvalid input." << endl;
          std::exit(0);
      }
      if (!Date::isValidDate(mn, dy, yr)) {
          cout << "\nInvalid input." << endl;
          std::exit(0);
      }
  }


  /** 
   *  Checks whether the given year is a leap year.
   *  @return true if and only if the input year is a leap year.
   *
   *  Grade: 10%
   */
  bool Date::isLeapYear(int year) {
      if ((year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0)) {
          return true;
      }
      else {
          return false;
      }
  }


  /** 
   *  Returns the number of days in a given month.
   *  @param month is a month, numbered in the range 1...12.
   *  @param year is the year in question, with no digits omitted.
   *  @return the number of days in the given month.
   *
   *  Grade: 10%
   */
  int Date::daysInMonth(int month, int year) {
      if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
          return 31;
      }
      else if (month == 4 || month == 6 || month == 9 || month == 11) {
          return 30;
      }
      else {
          if (Date::isLeapYear(year)) {
              return 29;
          }
          else {
              return 28;
          }
      }
  }

  /** 
   *  Checks whether the given date is valid.
   *  @return true if and only if month/day/year constitute a valid date.
   *
   *  Years prior to A.D. 1 are NOT valid.
   *
   *  Grade: 20%
   */
  bool Date::isValidDate(int month, int day, int year) {
      if (year >= 1) {
          if (month >= 1 && month <= 12) {
              if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                  if (day >= 1 && day <= 31) {
                      return true;
                  }
                  else {
                      return false;
                  }
              }
              else if (month == 4 || month == 6 || month == 9 || month == 11) {
                  if (day >= 1 && day <= 30) {
                      return true;
                  }
                  else {
                      return false;
                  }
              }
              else {
                  if (Date::isLeapYear(year) && (day >= 1 && day <= 29)) {
                      return true;
                  }
                  else if ((!Date::isLeapYear(year)) && (day >= 1 && day <= 28)) {
                      return true;
                  }
                  else {
                      return false;
                  }
              }
          }
          else {
              return false;
          }
      }
      else {
          return false;
      }
  }


  /** 
   *  Returns a string representation of this Date in the form month/day/year.
   *  The month, day, and year are expressed in full as integers; for example,
   *  10/17/2010 or 5/11/258.
   *  @return a String representation of this Date.
   *
   *  Grade: 20%
   */
  string Date::toString() {
      string str_date;
      //compose date in the form of month/day/year
      str_date.append(s_m);
      str_date += '/';
      str_date.append(s_d);
      str_date += '/';
      str_date.append(s_y);
      return str_date;                     // replace this line with your solution
  }


  /** 
   *  Determines whether this Date is before the Date d.
   *  @return true if and only if this Date is before d.
   *
   *  Grade: 10%
   */
  bool Date::isBefore(const Date& d) {
      if (s_y < d.s_y) {
          return true;
      }
      else if (s_y == d.s_y) {
          if (s_m < d.s_m) {
              return true;
          }
          else if (s_m == d.s_m) {
              if (s_d < d.s_d) {
                  return true;
              }
              else {
                  return false;
              }
          }
          else {
              return false;
          }
      }
      else {
          return false;
      }
  }
  

  /** 
   * 
   * 
   *  Determines whether this Date is after the Date d.
   *  @return true if and only if this Date is after d.
   *
   *  Grade: 10%
   */
  bool Date::isAfter(const Date& d) {
      if (s_y > d.s_y) {
          return true;
      }
      else if (s_y == d.s_y) {
          if (s_m > d.s_m) {
              return true;
          }
          else if (s_m == d.s_m) {
              if (s_d > d.s_d) {
                  return true;
              }
              else {
                  return false;
              }
          }
          else {
              return false;
          }
      }
      else {
          return false;
      }
  }
  
  
  /** 
   *  Determines whether this Date is equal to the Date d.
   *  @return true if and only if this Date is the same as d.
   *
   *  Grade: 10%
   */
  bool Date::isEqual(const Date& d) {
      if ((s_y == d.s_y) && (s_m == d.s_m) && (s_d == d.s_d)) {
          return true;
      }
      else {
          return false;
      }
  }
  
  

  /** 
   *  Returns the number of this Date in the year.
   *  @return a number n in the range 1...366, inclusive, such that this Date
   *  is the nth day of its year.  (366 is only used for December 31 in a leap
   *  year.)
   *
   *  Grade: 15%
   */
  
  int Date::dayInYear() {
      //turn month, day and year string into interger
      mn = stoi(s_m);
      dy = stoi(s_d);
      yr = stoi(s_y);
      int daysinyear = 0;
      for (int i = 1; i < mn; i++) {
          daysinyear += daysInMonth(i, yr);
      }
      daysinyear += dy;
      return daysinyear;
  }
  

  /** Determines the difference in days between d and this Date.  For example,
   *  if this Date is 6/16/2006 and d is 6/15/2006, the difference is 1.
   *  If this Date occurs before d, the result is negative.
   *  @return the difference in days between d and this Date.
   *
   *  Grade: 10%
   */
  
  int Date::difference(const Date& d) {
      int cnt = 0;
      Date d_1 = *this;
      Date d_2 = d;
      mn = stoi(s_m);
      dy = stoi(s_d);
      yr = stoi(s_y);
      if (d_1.yr >= d_2.yr) {
          for (int i = d_2.yr; i < d_1.yr; i++) {
              if (isLeapYear(i)) {
                  cnt += 366;
              }
              else {
                  cnt += 365;
              }
          }
          cnt = cnt - d_2.dayInYear() + d_1.dayInYear();
      }
      
      else {
          for (int i = d_1.yr; i < d_2.yr; i++) {
              if (isLeapYear(i)) {
                  cnt += 366;
              }
              else {
                  cnt += 365;
              }
          }
          cnt = (cnt - d_1.dayInYear() + d_2.dayInYear())*(-1);
      }
      return cnt;                           // replace this line with your solution
  }

