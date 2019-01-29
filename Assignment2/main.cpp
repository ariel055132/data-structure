#include <string>
#include <iostream>
using namespace std;

//��dfs��greedy��h -> ���_�I�_�ۦP�B�۳s���r������N�r��M�Ŧ^��1�A�Ϥ��A�^��0
int dfs(string s)
{
    if (s == "")											//�Ŧr��i�M�Ŧ^��1
        return 1;
    string sub;
    int i, j;
    int ret = 0;
    for (i = 0; i < s.length(); i++)
    {
        for (j = i; j < s.length(); j++)
            if (s[i] != s[j])
                break;
        if (j >= i + 2)  	//�P�_�r�ꤤ�O�_��>=��ӥH�W�ۦP�r��
        {
            sub = s.substr(0, i) + s.substr(j); //�N�����쪺�r��I�_�ñN�e��s�����ͤl�r��
            ret = dfs(sub);	//�N�l�r��A���U�@����dfs
            if (ret)
                return ret;					//�^�ǤW�@��dfs�����G
        }
    }
    return ret;									//�Ҧ��l�r��ҵL�k�M�Ŧ^��0
}

int main()
{
    int testcase;
    string s;
    cin >> testcase;
    while (testcase--)
    {
        cin >> s;
        cout << dfs(s) << endl;
    }
    return 0;
}
