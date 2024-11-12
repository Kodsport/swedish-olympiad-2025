#!/bin/bash
# Note: Kattis uses the dotnet compiler. We use Mono here for convenience

/usr/bin/mcs -out:karleksbrev.exe -optimize+ -r:System.Numerics Main.cs karleksbrev.cs
