#include<iostream>
using namespace std;
int main()
{
    int number_of_bars;
    double one_weight,total_weight;

    cout<<"����һ�������ж��ٿ���\n";

    cout<<"and the weight in ounces of one candy bar.\n";
    cout<<"Then press return.\n";
    cin>>number_of_bars;
    cin>>one_weight;

    total_weight = one_weight * number_of_bars;

    cout<<number_of_bars<<"candy bars\n";
    cout<<one_weight<<"ounces each\n";
    cout<<"Total weight is"<<total_weight<<"ounces.\n";

    cout<<"Try anther brand.\n";
    cout<<"����һ��������ǹ�������\n";
    cout<<"and the weight in ounces of one candy bar.\n";
    cout<<"Then press return.\n";
    cin>>number_of_bars;
    cin>>one_weight;

    total_weight = one_weight * number_of_bars;

    cout<<number_of_bars<<"candy bars\n";
    cout<<one_weight<<"ounces each\n";
    cout<<"Total weight is"<<total_weight<<"oucens.\n";

    cout<<"Perhaps an apple would be healther.\n";
    return 0;
}
