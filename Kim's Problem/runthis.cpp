#include<bits/stdc++.h>
using namespace std;

const string in_0 = "", out_0 = ".a";
const string in_1 = ".in", out_1 = ".sol";
const bool zero_prefix = false;

int main(int argc, char **argv){
	if(argc!=2&&argc!=3) return 0;
	auto cur_file=freopen(argv[1],"r",stdin);

	bool keep_file=1;
	if(argc==3 && (argv[2][0]=='0' || !strcmp(argv[2],"false"))) keep_file=0;
	
	int len=strlen(argv[1]);
	string name, ex, dir;
	for(int i=len-1;i>=0;--i){
		if(argv[1][i]!='\\') continue;
		for(int j=0;j<=i;++j) dir+=argv[1][j];
		++i;
		if(!zero_prefix) while(i<len && argv[1][i]=='0') ++i;
		while(i<len && argv[1][i]!='.') name+=argv[1][i++];
		while(i<len) ex+=argv[1][i++];
		break;
	}
	if(ex==in_0){
		auto target=fopen((dir+name+in_1).c_str(),"w");
		string tmp;
		while(getline(cin,tmp)) fprintf(target,"%s\n",tmp.c_str());
		cout<<" "<<argv[1]<<'\n'<<dir+name+in_1<<"\n\n";
		fclose(target);
		fclose(cur_file);
		if(!keep_file) remove(argv[1]);
	}
	else if(ex==out_0){
		auto target=fopen((dir+name+out_1).c_str(),"w");
		string tmp;
		while(getline(cin,tmp)) fprintf(target,"%s\n",tmp.c_str());
		cout<<" "<<argv[1]<<'\n'<<dir+name+out_1<<"\n\n";
		fclose(target);
		fclose(cur_file);
		if(!keep_file) remove(argv[1]);
	}
	else fclose(cur_file);

	return 0;
}
