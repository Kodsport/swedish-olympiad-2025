// Testing tool for the task Love Letter.
//
// Usage:
//
//   bash unix_compile.sh
//   bash unix_run.sh
//
// input.txt uses the following format:
//
// N K
// S
// L R
// Where N is the length of S,
// K is the maximum length of a message that the encoder may produce,
// S is the message that should be sent,
// L and R denote the interval that should be flipped.
// More precisely, the judge will corrupt m[L], m[L+1], ..., m[R]
//
// Example input:
//
// 5 10
// 01011
// 1 3
//
//
// If --silent is passed, the communication output will not be printed.
//
// The tool is provided as-is, and you should feel free to make
// whatever alterations or augmentations you like to it. Notably,
// this is not the grader used in Kattis.

using System;
using System.IO;

class LoveLetter
{
    static void Main(string[] args)
    {
        bool silent = false;

        if (args.Length > 0 && args[0] == "--silent")
        {
            silent = true;
        }

        if (args.Length > 0 && args[0] == "-h")
        {
            Console.WriteLine("Usage: program [--silent] < input.txt");
            return;
        }

        int N, K, L, R;
        string S;

        string[] parts = Console.ReadLine().Split();
        N = Int32.Parse(parts[0]);
        K = Int32.Parse(parts[1]);
        S = Console.ReadLine();
        parts = Console.ReadLine().Split();
        L = Int32.Parse(parts[0]);
        R = Int32.Parse(parts[1]);

        if (S.Length != N)
        {
            Console.WriteLine($"[X] Error: length(S)={S.Length} does not match N={N}");
            return;
        }

        foreach (char c in S)
        {
            if (c != '0' && c != '1')
            {
                Console.WriteLine($"[X] Error: S={S} contains character \"{c}\", which is not 0 or 1");
                return;
            }
        }

        if (!silent)
        {
            Console.WriteLine($"[*] Running with N={N}, K={K}, S={S}, L={L}, R={R}");
        }

        // Encode S
        string E = karleksbrev.encode(S);
        if (!silent)
        {
            Console.WriteLine($"[*] S={S}, encode(S)={E}");
        }

        // Sanity check E
        if (string.IsNullOrEmpty(E))
        {
            Console.WriteLine($"[X] Error: encoder gave an empty E for S={S}");
            return;
        }
        if (E.Length > K)
        {
            Console.WriteLine($"[X] Error: encoder gave too long E. length(E)={E.Length} > K={K}");
            return;
        }
        foreach (char c in E)
        {
            if (c != '0' && c != '1')
            {
                Console.WriteLine($"[X] Error: encoder gave E containing character \"{c}\", which is not 0 or 1");
                return;
            }
        }

        if (L < 0 || R < 0 || L >= E.Length || R >= E.Length)
        {
            Console.WriteLine($"[X] Error: L={L} or R={R} is out of bounds for length(E)={E.Length}");
            return;
        }

        // Corrupt E by flipping bits from L to R
        char[] EArray = E.ToCharArray();
        for (int i = L; i <= R; ++i)
        {
            EArray[i] = EArray[i] == '0' ? '1' : '0';
        }
        E = new string(EArray);

        if (!silent)
        {
            Console.WriteLine($"[*] E={E} after corrupting");
        }

        // Check that the decoder can decode flipped E
        string decoded = karleksbrev.decode(E);
        if (decoded != S)
        {
            Console.WriteLine($"[X] Error: decoder did not find S. E after corrupting={E}, S={S}, decode(E)={decoded}");
            return;
        }

        if (!silent)
        {
            Console.WriteLine($"[*] decode(E)={decoded}");
        }

        Console.WriteLine($"Success! N={N} len(E)={E.Length}");
    }
}
