This repo is a result of following Apriorit tasks: <br/>
1. Estimate the complexity of the function func by the code <br/>
<br/>
int func1(int i) { <br/>
    if (i == 0) { <br/>
        return 1; <br/>
    } <br/>
    return i*func1(i-1); <br/>
} <br/>
 <br/>
void func(std::vector<std::vector<int>>& v, int i) { <br/>
    if (i == 0) { <br/>
        return; <br/>
    } <br/>
    func(v, i/2); <br/>
    std::vector<int> r; <br/>
    for (int j = 0; j < i; j++) { <br/>
        r.emplace_back(func1(i)/func1(j)/func1(i-j)) <br/>
    } <br/>
} <br/>
 <br/>
 <br/>
 <br/>
2. Select the most suitable container for the telephone directory, in which the main operation is search. <br/>
The search csv file is provided. Find. <br/>
In your answer, provide the code of the program that reads the file data, fills the container and searches the container for the subscriber's name by phone number. <br/>
In the comments in the code, justify the choice of the container, for this, compare the complexity of the main operation on the O notation in several containers that you compared. <br/>
