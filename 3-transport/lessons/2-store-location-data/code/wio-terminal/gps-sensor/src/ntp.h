#pragma once

#include "DateTime.h"
#include <time.h>
#include "samd/NTPClientAz.h"
#include <sys/time.h>

static void initTime()
{
    WiFiUDP _udp;
    time_t epochTime = (time_t)-1;
    NTPClientAz ntpClient;

    ntpClient.begin();

    while (true)
    {
        epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

        if (epochTime == (time_t)-1)
        {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        }
        else
        {
            Serial.print("Fetched NTP epoch time is: ");

            char buff[32];
            sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
            Serial.println(buff);
            break;
        }
    }

    ntpClient.end();

    struct timeval tv;
    tv.tv_sec = epochTime;
    tv.tv_usec = 0;

    settimeofday(&tv, NULL);
}