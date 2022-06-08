// retirado de https://github.com/splucs/Competitive-Programming/tree/master/Macac%C3%A1rio

typedef vector< vector< double > > matrix;

matrix operator +(matrix a, matrix b) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++) {
		c[i].resize(m);
		for(int j=0; j<m; j++)
			c[i][j] = a[i][j] + b[i][j];
	}
	return c;
}

matrix operator *(matrix a, matrix b) {
	int n = (int)a.size();
	//assert(a[0].size() == b.size());
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c(n, vector<double>(p));
	vector<double> col(m);
	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++)
			col[k] = b[k][j];
		for (int i = 0; i < n; i++) {
			double s = 0;
			for (int k = 0; k < m; k++)
				s += a[i][k] * col[k];
			c[i][j] = s;
		}
	}
	return c;
}

matrix operator *(double k, matrix a) {
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i=0; i<n; i++) for(int j=0; j<m; j++)
		a[i][j] *= k;
	return a;
}

matrix operator -(matrix a, matrix b) {
	return a + ((-1.0) * b);
}

matrix id(int n) {
	matrix c(n, vector<double>(n));
	for(int i = 0; i < n; i++) c[i][i] = 1;
	return c;
}

void switchLines(matrix & a, int i, int j) {
	int m = (int)a[i].size();
	for(int k = 0; k < m; k++) swap(a[i][k], a[j][k]);
}

void lineSumTo(matrix & a, int i, int j, double c) {
	int m = (int)a[0].size();
	for(int k = 0; k < m; k++) a[j][k] += c*a[i][k];
}

bool gauss(matrix & a, matrix & b, int & switches) {
	switches = 0;
	int n = (int)a.size();
	int m = (int)a[0].size();
	for(int i = 0, l; i < min(n, m); i++) {
		l = i;
		while(l < n && fabs(a[l][i]) < EPS) l++;
		if (l == n) return false;
		switchLines(a, i, l);
		switchLines(b, i, l);
		switches++;
		for(int j=0; j<n; j++) {
			if (i == j) continue;
			double p = -a[j][i] / a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	return true;
}

double det(matrix a) {
	int n = a.size();
	matrix b(n);
	for(int i=0; i<n; i++) b[i].resize(1);
	int sw = 0;
	if (gauss(a, b, sw)) {
		double ans = 1;
		for(int i=0; i<n; i++) ans *= a[i][i];
		return sw % 2 == 0 ? ans : -ans;
	}
	return 0.0;
}
