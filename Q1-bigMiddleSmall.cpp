// 1 输入：非升 or 非降
// 2 从大到小，最大值-中位数-最小值 max middle min
// 3 整数直接输出整数
// 4 分数四舍五入保留一位小数
// long: -2147483648 ~ 2147483647 (-2e9~2e9)
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
int main() {
    // 31ms VS 171ms (4 times or so)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long cnt;
    cin >> cnt;
    vector<long> data(cnt);
    for (size_t i = 0; i < cnt; ++ i) cin >> data[i];
    long mid = (data[cnt / 2] + data[(cnt - 1) / 2]);
    cout << max(data.front(), data.back()) << " ";
    if (mid & 1) // 如果不能整除
        cout << fixed << setprecision(1) << mid / 2.0; // int((mid + 0.05) * 10) / 10.0;
    else cout << mid / 2;
    cout << " " << min(data.front(), data.back()) << endl;
    return 0;
}
