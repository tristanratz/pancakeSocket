/*
 * File:   Log.h
 * Author: Joshua Johannson
 *
  */

#include "Log.h"


// static
char Log::logLevelMask    = LOG_LEVEL_ALL;
bool Log::useLongLogNames = false;
bool Log::useColors       = false;
int  Log::maxNameLongLen  = 0;
int  Log::logNameShortLongest = 0;

Log::Log()
{}

// -- SET LOG NAME ----------------------
Log::Log(string nameShort)
{
    setLogName(nameShort);
}

void Log::setLogName(string nameShort)
{
    this->logNameShort = nameShort;
    this->logNameLong  = "";
    if (logNameShortLongest < nameShort.length())
        logNameShortLongest = nameShort.length();
}
void Log::setLogName(string nameShort, string nameLong)
{
    setLogName(nameShort);
    this->logNameLong = nameLong;

    if (logNameLong.length() > maxNameLongLen)
        maxNameLongLen = logNameLong.length();
}

void Log::setLogLevel(char log_levelMask)
{
    logLevelMask = log_levelMask;
}


void Log::setUseLongLogNames(bool use)
{
    useLongLogNames = use;
}

void Log::setUseColor(bool use)
{
    useColors = use;
}


// -- OUT -------------------------------
void Log::fatal(string text)
{
    lgMtx.lock();
    print("[❎fatal ❎] ", text, LOG_LEVEL_ERROR);
    lgMtx.unlock();
//  Frontend::send("fatal", {{"message",  text + "''"}});
}

void Log::fatal(string text, string error)
{
    lgMtx.lock();
    print("[❎fatal ❎] ", text + ": '" + error + "'", LOG_LEVEL_ERROR);
    lgMtx.unlock();
    //Frontend::send("fatal", {{"message",  text + "'" + error + "'"}});
}

void Log::err(string text)
{
    if ((logLevelMask & LOG_LEVEL_ERROR) > 0)
    {
        lgMtx.lock();
        print("[❌ err ❌] ", text, LOG_LEVEL_ERROR);
        lgMtx.unlock();
    }
}

void Log::err(string text, string error)
{
    if ((logLevelMask & LOG_LEVEL_ERROR) > 0) {
        lgMtx.lock();
        print("[❌ err ❌] ", text + ": '" + error + "'", LOG_LEVEL_ERROR);
        lgMtx.unlock();
    }

}

void Log::warn(string text)
{
    if ((logLevelMask & LOG_LEVEL_WARNING) > 0)
    {
        lgMtx.lock();
        print("[⚠ warn ⚠] ", text, LOG_LEVEL_WARNING);
        lgMtx.unlock();
    }
}

void Log::ok(string text)
{
    if ((logLevelMask & LOG_LEVEL_OK) > 0)
    {
        lgMtx.lock();
        print("[  ok ✅ ] ", text, LOG_LEVEL_OK);
        lgMtx.unlock();
    }
}

void Log::debug(string text)
{
    if ((logLevelMask & LOG_LEVEL_DEBUG) > 0)
    {
        lgMtx.lock();
        print("[ debug  ] ", text, LOG_LEVEL_DEBUG);
        lgMtx.unlock();
    }
}

void Log::info(string text) const
{
    if ((logLevelMask & LOG_LEVEL_INFORMATION) > 0)
    {
        lgMtx.lock();
        print("[ info ❄ ] ", text, LOG_LEVEL_INFORMATION);
        lgMtx.unlock();
    }
}

void Log::trace(string text)
{
    if ((logLevelMask & LOG_LEVEL_TRACE) > 0)
    {
        lgMtx.lock();
        print("[ trac   ] ", text, LOG_LEVEL_TRACE);
        lgMtx.unlock();
    }
}

void Log::outErr(string text, bool error, string errorText)
{
    if (error && ((logLevelMask & LOG_LEVEL_ERROR) > 0))
    {
        lgMtx.lock();
        print("[❌ err ❌] ", text + ": '" + errorText + "'", LOG_LEVEL_ERROR);
        lgMtx.unlock();
    }
    else
        this->ok(text);
}

void Log::outErr(string text, bool error)
{
    outErr(text, error, "");
}

void Log::outFat(string text, bool error, string errorText)
{
    if (error && ((logLevelMask & LOG_LEVEL_ERROR) > 0))
    {
        lgMtx.lock();
        print("[❎fatal ❎] ", text + ": '" + errorText + "'", LOG_LEVEL_ERROR);
        lgMtx.unlock();
    }
    else
        this->ok(text);
}

void Log::outFat(string text, bool error)
{
    outErr(text, error, "");
}



void Log::print(string tag, string text, char tagMask) const
{
    // output
    char name[256];
    lgMtx.lock();
    snprintf(name, 256, string("%-" + to_string(logNameShortLongest) + "s").c_str(), logNameShort.c_str());
    lgMtx.unlock();
    cout << "[ " << name << " ] " << tag << text  << endl;

    /*
    if (!useLongLogNames)
      cout << "[ " << logNameShort/*.substr(0, 14)*-/ << " ] " << tag << "" << text << endl;
    else
    {
      if (logNameLong != "")
        cout << "[ " << logNameLong.substr(0, maxNameLongLen) << " ] " << tag << text  << endl;
      else
        cout << "[ " << logNameShort.substr(0, maxNameLongLen) << " ] " << tag << text << endl;
    }
    */
}