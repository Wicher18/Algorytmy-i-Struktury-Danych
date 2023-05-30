#include <iostream>
#include <string>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::string name;
    int skills, villages, population;
    float height;
    int avgSpeed;

    std::string currName;
    int currSkills, currSpeed;
    float currHeight;
    std::cin >> villages;
    int fPriority, sPriority, tPriority;
    for(int i=0;i<villages;i++){
        std::cin >> population >> fPriority >> sPriority >> tPriority >> name >> skills >> height >> avgSpeed;

        for(int j=0;j<population-1;j++){
            std::cin >> currName >> currSkills >> currHeight >> currSpeed;
            //priority check
            if(fPriority<sPriority && fPriority<tPriority){ //p - 1 * *
                if(sPriority<tPriority){ // p - 1 2 3
                    if(currSkills>skills || (currSkills==skills && currHeight>height) || (currSkills==skills && currHeight==height && currSpeed>avgSpeed)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                } else { // p - 1 3 2
                    if(currSkills>skills || (currSkills==skills && currSpeed>avgSpeed) || (currSkills==skills && currSpeed==avgSpeed && currHeight>height)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                }
            } else if(fPriority>sPriority && fPriority>tPriority){ //p - 3 * *
                if(sPriority<tPriority){ // p - 3 1 2
                    if(currSpeed>avgSpeed || (currSpeed==avgSpeed && currSkills>skills) || (currSpeed==avgSpeed && currSkills==skills && currHeight>height)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                } else { // p - 3 2 1
                    if(currSpeed>avgSpeed || (currSpeed==avgSpeed && currHeight>height) || (currSpeed==avgSpeed && currHeight==height && currSkills>skills)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                }
            } else { // 2 * *               
                if(sPriority<tPriority){ // 2 1 3
                    if(currHeight>height || (currHeight==height && currSkills>skills) || (currHeight==height && currSkills==skills && currSpeed>avgSpeed)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                } else { // 2 3 1
                    if(currHeight>height || (currHeight==height && currSpeed>avgSpeed) || (currHeight==height && currSpeed==avgSpeed && currSkills>avgSpeed)){
                        name=currName;
                        skills=currSkills;
                        height=currHeight;
                        avgSpeed=currSpeed;
                    }
                }
            }
        }

        std::cout << name + "\n";
    }



    return 0;
}