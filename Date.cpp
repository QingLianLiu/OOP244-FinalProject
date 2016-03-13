#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict{
  int Date::value()const{
    return year_ * 372 + mon_ * 31 + day_;
  }

  void Date::errCode(int errorCode){
	  readErrorCode_ = 0;
  }

  Date::Date(){
	  year_ = 0;
	  mon_ = 0;
	  day_ = 0;
	  readErrorCode_ = NO_ERROR;
  }

  Date::Date(int year, int mon, int day){
	  year_ = year;
	  mon_ = mon;
	  day_ = day;
	  errCode(0);
  }

  bool Date::operator==(const Date& D)const{
	  // this-> is not needed here since there is no conflict
	  return value() == D.value();
  }
  
  bool Date::operator!=(const Date& D)const{
	  return value() != D.value();
  }
  
  bool Date::operator<(const Date& D)const{
	  return value() < D.value();
  }
  
  bool Date::operator>(const Date& D)const{
	  return value() > D.value();
  }
  
  bool Date::operator<=(const Date& D)const{
	  return value() <= D.value();
  }
  
  bool Date::operator>=(const Date& D)const{
	  return value() >= D.value();
  }

  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
    mon--;
    return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
  }

  int Date::errCode()const{
	  return readErrorCode_;
  }

  bool Date::bad()const{ 
	  return errCode()!= NO_ERROR;
  }

  void Date::validate(){
	  if(year_ < MIN_YEAR || year_ > MAX_YEAR){
		  readErrorCode_ = YEAR_ERROR;
	  }else if(mon_ < 1 || mon_ > 12){
		  readErrorCode_ = MON_ERROR;
	  }else if(day_ < 1 || day_ > mdays()){
		  readErrorCode_ = DAY_ERROR;
	  } else{
		  readErrorCode_ = NO_ERROR;
	  }
  }

//You don't need to check the istream::fail() for every entry, if one of the fails, istream becomes disableed and the reset will be ingored: you
//have multiple return statements that must be avoided, please consider changing the logic.  
  std::istream& Date::read(std::istream& istr){
	  istr >> year_;
	  cin.ignore();
//	  if(istr.fail()){
//		  readErrorCode_ = CIN_FAILED;
//		  return istr;
//	  } 
	  istr >> mon_;
	  cin.ignore();
//	  if(istr.fail()){
//		  readErrorCode_ = CIN_FAILED;
//		  return istr;
//	  }
	  istr >> day_;
	  if(istr.fail()){
		  readErrorCode_ = CIN_FAILED;
	  } else {
		  validate();
	  }
	  return istr;
  }

  std::ostream& Date::write(std::ostream& ostr)const{
	  ostr << year_ << "/";
	  ostr.width(2);
	  ostr.fill('0');
	  ostr << mon_ << "/";
	  ostr.width(2);
	  ostr.fill('0');
	  ostr << day_;
	  return ostr;
  }

  std:: istream& operator>>(std::istream& is, Date& D){
	  return D.read(is);
  }

  std::ostream& operator<<(std::ostream& os, const Date& D){
	  return D.write(os);
  }
}
