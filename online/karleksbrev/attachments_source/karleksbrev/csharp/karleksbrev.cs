using System;


public class karleksbrev
{
    public static string encode(string S)
    {
        string E = "";
        foreach (char c in S)
        {
            E += new string(c, 5);
        }
        return E;
    }

    // Note: this E is E after it has been corrupted
    public static string decode(string E)
    {
        string ret = "";
        while (E.Length > 0)
        {
            string chunk = E.Substring(0, 5);
            E = E.Substring(5);
            ret += chunk[2];
        }
        return ret;
    }
}
