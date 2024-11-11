using System;


public class karleksbrev
{
    static readonly ulong mod = 1125899906842679;

    static ulong Hashf(string x)
    {
        ulong ret = 0;
        foreach (var v in x)
        {
            ret = (ret + (v == '1' ? 1UL : 0UL)) * 1087 % mod;
        }
        return ret;
    }

    static int k = 50;

    static string Hashstring(string x)
    {
        var ret = new char[k];
        for (int i = 0; i < k; i++)
        {
            ret[i] = '0';
        }

        ulong h = Hashf(x);

        for (int j = 0; j < k; j++)
        {
            if ((h & (1UL << j)) != 0)
            {
                ret[j] = '1';
            }
        }

        return new string(ret);
    }

    public static string encode(string x)
    {
        return x + Hashstring(x);
    }

    public static string decode(string x)
    {
        int n = x.Length;

        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                var u = x.ToCharArray();

                for (int l = i; l <= j; l++)
                {
                    u[l] = u[l] == '1' ? '0' : '1';
                }

                string meat = new string(u, 0, n - k);
                string encoded = encode(meat);

                if (new string(u) == encoded)
                {
                    return meat;
                }
            }
        }

        throw new InvalidOperationException("its joever");
    }
}
