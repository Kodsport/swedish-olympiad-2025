#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "communication.h"

using namespace std;

static const int USER_FAIL = 120;

string SECRET_KEY = "07/27/1978 IS UNOFFICIAL EDITORIAL FOR ALL PROBLEMS";


int main() {
	ios_base::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	string x;
	cin >> x;
	int l, r;
	cin >> l >> r;

	int pipefds[2];
	ignore = pipe(pipefds);

	pid_t pid = fork();
	if (pid == 0) {
		close(pipefds[0]);
		string encoded = encode(n, k, x);

		if (encoded.size() > (size_t)k) {
			cerr << "Encoder gave string of length " << encoded.size() << ", expected at most " << k << endl;
			close(pipefds[1]);
			exit(USER_FAIL);
		}

		for (char c : encoded) {
			if (c != '0' && c != '1') {
				cerr << "Encoder gave string containing character " << c << ", expected either 0 or 1" << endl;
				close(pipefds[1]);
				exit(USER_FAIL);
			}
		}

		// flip the interval
		for (int i = l; i <= r; i++)
		{
			if (encoded[i]=='1') encoded[i]='0';
			else encoded[i]='1';
		}
		
		char nullbyte[1];
		nullbyte[0]=0;
		ignore = write(pipefds[1], encoded.c_str(), encoded.size());
		ignore = write(pipefds[1], nullbyte, 1);
		
		close(pipefds[1]);
		exit(EXIT_SUCCESS);
	}
	else {
		int status;
		vector<string> subset;
		char buf[1024];
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid fail");
			return EXIT_FAILURE;
		}
		if (WIFSIGNALED(status)) {
			kill(getpid(), WTERMSIG(status));
			exit(1);
		}
		int ex = WEXITSTATUS(status);
		if (ex == USER_FAIL) { exit(EXIT_SUCCESS); exit(1); }
		if (ex != EXIT_SUCCESS) { exit(ex); exit(1); }
		ignore = read(pipefds[0], buf, sizeof(buf));

		string encoded(buf);
		
		string decoded = decode(n, k, encoded);
		cout << SECRET_KEY << decoded << endl;
		exit(EXIT_SUCCESS);
	}

}
