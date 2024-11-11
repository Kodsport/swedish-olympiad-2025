using System;
using System.Diagnostics;
using System.Reflection;
using System.Collections.Generic;

public class main {

	private const int _NUM_TESTCASES = 50;
    private const int _USER_FAIL = 120;
    private const string _SECRET_KEY = "SUCCESSiujwefguiwehuioew";
    private const string _SECRET_FAIL = "FAILiujwefguiwehuioew";
	private static int test_type = 0;

    private static ulong rngState = 0;

    private static ulong NextRand()
    {
        rngState ^= (rngState << 21);  // Apply modulo 2^64 with bitmask
        rngState ^= (rngState >> 35);
        rngState ^= (rngState << 4);
        rngState = (rngState * 2685821657736338717UL);
        return rngState;
    }

    private static int RandInterval(int l, int r)
    {
        ulong rangeSize = (ulong)(r - l + 1);
        return l + (int)(NextRand() % rangeSize);
    }

    public static void PermuteVector(List<KeyValuePair<string, string>> vec)
    {
        for (int i = vec.Count - 1; i > 0; i--)
        {
            int j = RandInterval(0, i);
            // Swap elements at indices i and j
            KeyValuePair<string, string> temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }

	public static (int l, int r) GetLr(int elen)
    {
        int l, r;
        
        if (test_type == 0)
        {
            l = RandInterval(0, elen - 1);
            r = RandInterval(l, elen - 1);
            return (l, r);
        }
        
        if (test_type == 1)
        {
            l = RandInterval(0, elen - 1);
            return (l, l);
        }
        
        if (test_type == 2)
        {
            while (true)
            {
                l = RandInterval(0, elen - 3);
                if (l % 2 == 0)
                    break;
            }
            while (true)
            {
                r = RandInterval(l, elen - 1);
                if (r % 2 == 0)
                    break;
            }
            return (l, r);
        }
        
        if (test_type == 3)
        {
            while (true)
            {
                l = RandInterval(0, elen - 1);
                if (l % 2 == 0)
                    break;
            }
            r = RandInterval(l, elen - 1);
            return (l, r);
        }

        throw new InvalidOperationException("Invalid test_type");
    }

	public static int Main(string[] args) {
		if (args.Length == 0) {
			string codeBase = System.Reflection.Assembly.GetExecutingAssembly().CodeBase;
			UriBuilder uri = new UriBuilder(codeBase);
			string path = Uri.UnescapeDataString(uri.Path);
			Process enc = new Process();
			enc.StartInfo.FileName = "/usr/bin/mono";
			enc.StartInfo.Arguments = "\"" + path + "\" encoder";
			enc.StartInfo.UseShellExecute = false;
			enc.StartInfo.RedirectStandardOutput = true;
			enc.Start();

			Process dec = new Process();
			dec.StartInfo.FileName = "/usr/bin/mono";
			dec.StartInfo.Arguments = "\"" + path + "\" decoder";
			dec.StartInfo.UseShellExecute = false;
			dec.StartInfo.RedirectStandardInput = true;
			dec.Start();

			string buf;
			try {
				buf = enc.StandardOutput.ReadToEnd();
			} catch (Exception e) {
				buf = "-1 -1";
			}

			enc.WaitForExit();
			int encWF = enc.ExitCode;
			if (encWF != 0) {
				Console.Write(buf);
				buf = "-1 -1";
			}
			dec.StandardInput.Write(buf, 0, buf.Length);
			dec.StandardInput.Close();
			if (encWF != 0) {
				if (encWF==_USER_FAIL)
				{
					return 0;
				}
				return encWF;
			}

			dec.WaitForExit();
			int decWF = dec.ExitCode;
			if (decWF != 0) {
				if (encWF==_USER_FAIL)
				{
					return 0;
				}
				return encWF;
			}
		} else if (args[0].Equals("encoder")) {
			int n,k;
			string[] parts = Console.ReadLine().Split();
			n = Int32.Parse(parts[0]);
			k = Int32.Parse(parts[1]);
			int seed;
			parts = Console.ReadLine().Split();
			test_type = Int32.Parse(parts[0]);
			seed = Int32.Parse(parts[1]);
			rngState = (ulong)seed;

			List<KeyValuePair<string, string>> testcases = new List<KeyValuePair<string, string>>();
			for (int t = 0; t < _NUM_TESTCASES; t++)
			{
				char[] s = new char[n];
				for (int i = 0; i < n; i++)
				{
					s[i] = RandInterval(0,1) == 1 ? '1' : '0';
				}

				String encoded = karleksbrev.encode(new String(s));

				if (encoded.Length == 0)
				{
					Console.WriteLine($"{_SECRET_FAIL}Encoder gave an empty E");
					return _USER_FAIL;
				}

				if (encoded.Length > k)
				{
					Console.WriteLine($"{_SECRET_FAIL}Encoder gave too long E");
					return _USER_FAIL;
				}

				foreach (char c in encoded)
				{
					if (!(c=='1' || c=='0'))
					{
						Console.WriteLine($"{_SECRET_FAIL}Encoder gave E containing character which is not 0 or 1");
						return _USER_FAIL;
					}
				}

				char[] encoded_arr = encoded.ToCharArray();
				(int l, int r) = GetLr(encoded_arr.Length);
				for (int i = l; i <= r; i++)
				{
					if (encoded_arr[i] == '0') encoded_arr[i]='1';
					else encoded_arr[i]='0';
				}

	        	testcases.Add(new KeyValuePair<string, string>(new String(s), new String(encoded_arr)));
			}

			Console.WriteLine($"{n} {k}");
			Console.WriteLine($"{test_type} {seed}");
			foreach (var p in testcases)
			{
				Console.Write(p.Key);
				Console.Write("$");
				Console.Write(p.Value);
				Console.Write("@");
			}

		} else if (args[0].Equals("decoder")) {
			int n,k;
			string[] parts = Console.ReadLine().Split();
			n = Int32.Parse(parts[0]);
			k = Int32.Parse(parts[1]);
			if (n==-1) return 0;
			int seed;
			parts = Console.ReadLine().Split();
			test_type = Int32.Parse(parts[0]);
			seed = Int32.Parse(parts[1]);
			rngState = (ulong)seed;
			String buf = Console.ReadLine();

			List<string> pairs = new List<String>(buf.Split('@'));
			pairs.RemoveAt(pairs.Count - 1);
			List<KeyValuePair<string, string>> testcases = new List<KeyValuePair<string, string>>();

			foreach (var pair in pairs)
			{
				string[] pts = pair.Split('$');

				Debug.Assert(pts.Length == 2);
				testcases.Add(new KeyValuePair<string, string>(pts[0], pts[1]));
			}
			PermuteVector(testcases);
			
			ulong h = 0;
			foreach (var tc in testcases)
			{
				string S = tc.Key;
				string E = tc.Value;
				foreach (char c in S) h = (h+(ulong)c-48)*31;
				foreach (char c in E) h = (h+(ulong)c-48)*31;

				String decoded = karleksbrev.decode(E);
				if (decoded != S)
				{
					Console.WriteLine($"{_SECRET_FAIL}Decoder did not find S");
					return 0;
				}
			}

			Console.Error.WriteLine($"Hash of run: {h}");

			
			Console.WriteLine($"{_SECRET_KEY}" + seed);
		}
		return 0;
	}
	
}
