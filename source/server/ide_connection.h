#pragma once

#include <string>
#include "core/json/object.h"

class Ide_connection
{
public:
    friend Ide_connection& operator<<(Ide_connection& ide, json::object& message);
    friend Ide_connection& operator>>(Ide_connection& ide, json::object& message);
};