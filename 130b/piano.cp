#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

bool sortByEnd(const tuple<int, int>& end1, const tuple<int, int>& end2) { //allows for sorting of the tuple array by second element
    return (get<1>(end1) < get<1>(end2)); 
} 

int main(){
    int total, jobs, tuners, start, end, pairs;
    bool needWeekend, jobDone;
    vector<tuple<int, int>> schedule;
    cin >> total;
    for(int i = 0; i < total; i++){
        cin >> jobs;
        cin >> tuners;
        pairs = tuners/2;
        jobDone = false;
        needWeekend = false;
        int days[100] = {0};
        for (int i = 0; i < jobs; i++){ //inputs the jobs into a vector as a tuple
            cin >> start;
            cin >> end;
            schedule.push_back(make_tuple(start, end));
        }
        sort(schedule.begin(), schedule.end(), sortByEnd); //sort array of jobs
        int a = 0;
        while( a < schedule.size()){ //weekend work
            jobDone = false;
            needWeekend = false;
            int j = get<0>(schedule[a]);
            while(j < get<1>(schedule[a]) + 1){ //iterate thorough the job time frame 
                if(days[j] < pairs && !(j%7 == 6 || j%7 == 0)){ //checks to see if job can be done and its not weekend
                    days[j]++;
                    jobDone = true;
                    break;
                }
                j++;
            }
            if(!jobDone){
                needWeekend = true;
                break;
            } 
            a++;
        }
        if(needWeekend){ //weekday work
            int days[100] = {0};
            int s = 0;
            while(s < schedule.size()){
                jobDone = false;
                int k = get<0>(schedule[s]);
                while(k < get<1>(schedule[s]) + 1){ //iterate thorough the job time frame 
                    if(days[k] < pairs){ //checks to see if job can be done
                        days[k]++;
                        jobDone = true;
                        break;
                    }
                    k++;
                }
                if(!jobDone){
                    cout << "serious trouble" << endl;
                    break;
                }
                s++;
            }
            if(jobDone)
                cout << "weekend work" << endl;
        }else{
            cout << "fine" << endl;
        }
        schedule.clear();
    }
    return 0;
}