/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_EXT_DATETIME_H_
#define incl_HPHP_EXT_DATETIME_H_

#include <runtime/base/base_includes.h>
#include <runtime/base/time/timestamp.h>
#include <runtime/base/time/datetime.h>
#include <runtime/base/time/timezone.h>
#include <runtime/base/time/dateinterval.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
// class DateTime

extern const StaticString q_DateTime$$ATOM;
extern const StaticString q_DateTime$$COOKIE;
extern const StaticString q_DateTime$$ISO8601;
extern const StaticString q_DateTime$$RFC822;
extern const StaticString q_DateTime$$RFC850;
extern const StaticString q_DateTime$$RFC1036;
extern const StaticString q_DateTime$$RFC1123;
extern const StaticString q_DateTime$$RFC2822;
extern const StaticString q_DateTime$$RFC3339;
extern const StaticString q_DateTime$$RSS;
extern const StaticString q_DateTime$$W3C;

FORWARD_DECLARE_CLASS_BUILTIN(DateTime);
class c_DateTime : public ExtObjectData {
 public:
  DECLARE_CLASS(DateTime, DateTime, ObjectData)

  // need to implement
  public: c_DateTime(VM::Class* cls = c_DateTime::s_cls);
  public: ~c_DateTime();
  public: Object t_add(CObjRef interval);
  public: void t___construct(CStrRef time = "now",
                             CObjRef timezone = null_object);
  public: static Object ti_createfromformat(const char* cls , CStrRef format, CStrRef time, CObjRef timezone = null_object);
  public: static Object t_createfromformat(CStrRef format, CStrRef time, CObjRef timezone = null_object) {
    return ti_createfromformat("datetime", format, time, timezone);
  }
  public: Object t_diff(CObjRef datetime2, bool absolute = false);
  public: String t_format(CStrRef format);
  public: static Array ti_getlasterrors(const char* cls );
  public: static Array t_getlasterrors() {
    return ti_getlasterrors("datetime");
  }
  public: int64_t t_getoffset();
  public: int64_t t_gettimestamp();
  public: Variant t_gettimezone();
  public: Object t_modify(CStrRef modify);
  public: Object t_setdate(int64_t year, int64_t month, int64_t day);
  public: Object t_setisodate(int64_t year, int64_t week, int64_t day = 1);
  public: Object t_settime(int64_t hour, int64_t minute, int64_t second = 0);
  public: Object t_settimestamp(int64_t unixtimestamp);
  public: Object t_settimezone(CObjRef timezone);
  public: Object t_sub(CObjRef interval);

  // Helper for DateTime -> c_DateTime conversion
  public: static Object wrap(SmartObject<DateTime> dt) {
    c_DateTime *cdt = NEWOBJ(c_DateTime)();
    Object ret(cdt);
    cdt->m_dt = dt;
    return ret;
  }

  // Helper for c_DateTime -> DateTime conversion
  public: static SmartObject<DateTime> unwrap(CObjRef datetime) {
    SmartObject<c_DateTime> cdt = datetime.getTyped<c_DateTime>(true);
    if (cdt.get() == NULL)
      return SmartObject<DateTime>();
    return cdt->m_dt;
  }

 private:
  SmartObject<DateTime> m_dt;
 public:
  virtual ObjectData *clone();
};

///////////////////////////////////////////////////////////////////////////////
// class DateTimeZone

extern const int64_t q_DateTimeZone$$AFRICA;
extern const int64_t q_DateTimeZone$$AMERICA;
extern const int64_t q_DateTimeZone$$ANTARCTICA;
extern const int64_t q_DateTimeZone$$ARCTIC;
extern const int64_t q_DateTimeZone$$ASIA;
extern const int64_t q_DateTimeZone$$ATLANTIC;
extern const int64_t q_DateTimeZone$$AUSTRALIA;
extern const int64_t q_DateTimeZone$$EUROPE;
extern const int64_t q_DateTimeZone$$INDIAN;
extern const int64_t q_DateTimeZone$$PACIFIC;
extern const int64_t q_DateTimeZone$$UTC;
extern const int64_t q_DateTimeZone$$ALL;
extern const int64_t q_DateTimeZone$$ALL_WITH_BC;
extern const int64_t q_DateTimeZone$$PER_COUNTRY;

FORWARD_DECLARE_CLASS_BUILTIN(DateTimeZone);
class c_DateTimeZone : public ExtObjectData {
 public:
  DECLARE_CLASS(DateTimeZone, DateTimeZone, ObjectData)

  // need to implement
  public: c_DateTimeZone(VM::Class* cls = c_DateTimeZone::s_cls);
  public: ~c_DateTimeZone();
  public: void t___construct(CStrRef timezone);
  public: Array t_getlocation();
  public: String t_getname();
  public: int64_t t_getoffset(CObjRef datetime);
  public: Array t_gettransitions();
  public: static Array ti_listabbreviations(const char* cls );
  public: static Array t_listabbreviations() {
    return ti_listabbreviations("datetimezone");
  }
  public: static Array ti_listidentifiers(const char* cls );
  public: static Array t_listidentifiers() {
    return ti_listidentifiers("datetimezone");
  }

  // Helper for TimeZone -> c_DateTimeZone conversion
  public: static Object wrap(SmartObject<TimeZone> tz) {
    c_DateTimeZone *ctz = NEWOBJ(c_DateTimeZone)();
    Object ret(ctz);
    ctz->m_tz = tz;
    return ret;
  }

  // Helper for c_DateTimeZone -> TimeZone conversion
  public: static SmartObject<TimeZone> unwrap(CObjRef timezone) {
    SmartObject<c_DateTimeZone> ctz = timezone.getTyped<c_DateTimeZone>(true);
    if (ctz.get() == NULL)
      return SmartObject<TimeZone>();
    return ctz->m_tz;
  }

 private:
  SmartObject<TimeZone> m_tz;
 public:
  virtual ObjectData *clone();
};

///////////////////////////////////////////////////////////////////////////////
// class DateInterval

FORWARD_DECLARE_CLASS_BUILTIN(DateInterval);
class c_DateInterval : public ExtObjectDataFlags<ObjectData::UseGet|ObjectData::UseSet> {
 public:
  DECLARE_CLASS(DateInterval, DateInterval, ObjectData)

  // need to implement
  public: c_DateInterval(VM::Class* cls = c_DateInterval::s_cls);
  public: ~c_DateInterval();
  public: void t___construct(CStrRef interval_spec);
  public: Variant t___get(Variant member);
  public: Variant t___set(Variant member, Variant value);
  public: static Object ti_createfromdatestring(const char* cls , CStrRef time);
  public: static Object t_createfromdatestring(CStrRef time) {
    return ti_createfromdatestring("dateinterval", time);
  }
  public: String t_format(CStrRef format);


  public: static Object wrap(SmartObject<DateInterval> di) {
    c_DateInterval *cdi = NEWOBJ(c_DateInterval)();
    Object ret(cdi);
    cdi->m_di = di;
    return ret;
  }

  public: static SmartObject<DateInterval> unwrap(CObjRef dateinterval) {
    SmartObject<c_DateInterval>
      cdi = dateinterval.getTyped<c_DateInterval>(true);
    if (cdi.get() == NULL)
      return SmartObject<DateInterval>();
    return cdi->m_di;
  }

 private:
  SmartObject<DateInterval> m_di;
 public:
  virtual ObjectData *clone();

};

///////////////////////////////////////////////////////////////////////////////
// timestamp

Variant f_gettimeofday(bool return_float = false);
Variant f_microtime(bool get_as_float = false);
int64_t f_time();
Variant f_mktime(int hour = INT_MAX, int minute = INT_MAX,
                 int second = INT_MAX, int month = INT_MAX,
                 int day = INT_MAX, int year = INT_MAX);
Variant f_gmmktime(int hour = INT_MAX, int minute = INT_MAX,
                   int second = INT_MAX,
                   int month = INT_MAX, int day = INT_MAX,
                   int year = INT_MAX);
Variant f_idate(CStrRef format, int64_t timestamp = TimeStamp::Current());
Variant f_date(CStrRef format, int64_t timestamp = TimeStamp::Current());
Variant f_gmdate(CStrRef format,
                 int64_t timestamp = TimeStamp::Current());
Variant f_strftime(CStrRef format,
                   int64_t timestamp = TimeStamp::Current());
String f_gmstrftime(CStrRef format,
                    int64_t timestamp = TimeStamp::Current());
Array f_getdate(int64_t timestamp = TimeStamp::Current());
Array f_localtime(int64_t timestamp = TimeStamp::Current(),
                  bool is_associative = false);
Variant f_strptime(CStrRef date, CStrRef format);
Variant f_strtotime(CStrRef input,
                    int64_t timestamp = TimeStamp::Current());

///////////////////////////////////////////////////////////////////////////////
// timezone

String f_date_default_timezone_get();
bool f_date_default_timezone_set(CStrRef name);
Array f_timezone_identifiers_list();
Array f_timezone_abbreviations_list();
Variant f_timezone_name_from_abbr(CStrRef abbr, int gmtoffset = -1,
                                  bool isdst = true);
Object f_timezone_open(CStrRef timezone);
Array f_timezone_location_get(CObjRef timezone);
String f_timezone_name_get(CObjRef object);
int64_t f_timezone_offset_get(CObjRef object, CObjRef dt);
Array f_timezone_transitions_get(CObjRef object);
String f_timezone_version_get();

///////////////////////////////////////////////////////////////////////////////
// datetime

bool f_checkdate(int month, int day, int year);
Object f_date_add(CObjRef datetime, CObjRef interval);
Object f_date_create_from_format(CStrRef format,
                                 CStrRef time,
                                 CObjRef timezone = null_object);
Object f_date_create(CStrRef time = null_string,
                     CObjRef timezone = null_object);
void f_date_date_set(CObjRef object, int year, int month, int day);
Object f_date_diff(CObjRef datetime,
                   CObjRef datetime2,
                   bool absolute = false);
void f_date_isodate_set(CObjRef object, int year, int week,
                        int day = 1);
String f_date_format(CObjRef object, CStrRef format);
Array f_date_get_last_errors();
Object f_date_interval_create_from_date_string(CStrRef time);
String f_date_interval_format(CObjRef interval, CStrRef format_spec);
void f_date_modify(CObjRef object, CStrRef modify);
int64_t f_date_offset_get(CObjRef object);
Variant f_date_parse(CStrRef date);
void f_date_time_set(CObjRef object, int hour, int minute,
                     int second = 0);
int64_t f_date_timestamp_get(CObjRef datetime);
Object f_date_timestamp_set(CObjRef datetime, int64_t timestamp);
Variant f_date_timezone_get(CObjRef object);
void f_date_timezone_set(CObjRef object, CObjRef timezone);
Object f_date_sub(CObjRef datetime, CObjRef interval);

///////////////////////////////////////////////////////////////////////////////
// sun

Array f_date_sun_info(int64_t ts, double latitude, double longitude);
Variant f_date_sunrise(int64_t timestamp, int format = 0,
                       double latitude = 0.0, double longitude = 0.0,
                       double zenith = 0.0,
                       double gmt_offset = 99999.0);
Variant f_date_sunset(int64_t timestamp, int format = 0,
                      double latitude = 0.0, double longitude = 0.0,
                      double zenith = 0.0,
                      double gmt_offset = 99999.0);

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_EXT_DATETIME_H_
