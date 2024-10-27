#include <bits/stdc++.h>
using namespace std;

#include "communication.h"

string encode(int _, int __, string x)
{
    return x;
}

string decode(int _, int __, string x)
{
    if (x=="0") return "1";
    return "0";
}
