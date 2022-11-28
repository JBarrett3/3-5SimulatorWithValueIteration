#include <iostream>
#include <cstring>
#include <math.h>

struct State {
    int x;
    int y;
};

struct StateValue {
    struct State state;
    int value;
};

void tableGenerator();
double tableModifiedMultiEpisodicRunner(int xInput, int yInput, int numberTrials, int numberEpisodes);
double tableModifiedEpisodeRunner(struct State initialState, int numberTrials);
struct StateValue tableModifiedStateRunner(struct State initialState);

double multiEpisodicRunner();
double episodeRunner(struct State initialState, int numberTrials);
struct StateValue stateRunner(struct State initialState);

char* chooseDirection(struct State initialState);
char* randomDirectionGenerator(char* dirs[], int lenDirs);
struct StateValue valueFunction(struct State state, char* action);
void stateShiftNarrator(struct State initial, struct StateValue final);

int main() {
    int input;
    printf("Input 0 for IO, 1 for TableGenerator?:");
    scanf("%d", &input);
    if (input == 0) {
        double averagedValue = multiEpisodicRunner();
        printf("Averaged value : %f\n", averagedValue);
    } else if (input == 1) {
        tableGenerator();
    } else {
        printf("invalid input\n");
    }
}

void tableGenerator() {
    //This matches the table in 3.8 on page 87
    for (int j = 2; j >= -2; j--) {
        for (int i = -2; i <= 2; i++) {
            printf("%.1f ", tableModifiedMultiEpisodicRunner( i, j, 100, 10));
        }
        printf("\n");
    }
}

double tableModifiedMultiEpisodicRunner(int xInput, int yInput, int numberTrials, int numberEpisodes) {
    //runs multiple episodes
    struct State initialState;
    initialState.x = xInput;
    initialState.y = yInput;
    double cumulativeEpisodicValue = 0;
    for (int i = 0; i < numberEpisodes; i++) {
        cumulativeEpisodicValue += tableModifiedEpisodeRunner(initialState, numberTrials);
    }
    return cumulativeEpisodicValue/numberEpisodes;
}

double multiEpisodicRunner() {
    //runs multiple episodes
    printf("Input parameters as prompted. And note that about "
           "100 trials and 10 episodes are required for accuracy with textbook\n");
    int input;
    struct State initialState;
    printf("Inital X:");
    scanf("%d", &input);
    initialState.x = input;
    printf("Inital Y:");
    scanf("%d", &input);
    initialState.y = input;
    printf("Number of trials:");
    scanf("%d", &input);
    int numberTrials = input;
    printf("Number of Episodes:");
    scanf("%d", &input);
    int numberEpisodes = input;
    printf("Initial Position : (%d,%d), number of trials : %d, number of episodes : %d\n", initialState.x, initialState.y, numberTrials, numberEpisodes);
    double cumulativeEpisodicValue = 0;
    for (int i = 0; i < numberEpisodes; i++) {
        cumulativeEpisodicValue += episodeRunner(initialState, numberTrials);
    }
    return cumulativeEpisodicValue/numberEpisodes;
}

double tableModifiedEpisodeRunner(struct State initialState, int numberTrials) {
    //runs single episode
    struct State currentState {
            .x = initialState.x,
            .y = initialState.y
    };
    struct StateValue currentStateValue {
            .state = currentState,
            .value = 0
    };

    double gamma = 0.9;
    srand(time(0));
    double totalValue = 0;
    for (int i = 0; i < numberTrials; i++) {
        currentStateValue = tableModifiedStateRunner(currentStateValue.state);
        totalValue += currentStateValue.value * pow(gamma,i);
    }

    return totalValue;

}

double episodeRunner(struct State initialState, int numberTrials) {
    //runs single episode
    struct State currentState {
            .x = initialState.x,
            .y = initialState.y
    };
    struct StateValue currentStateValue {
            .state = currentState,
            .value = 0
    };

    double gamma = 0.9;
    srand(time(0));
    double totalValue = 0;
    for (int i = 0; i < numberTrials; i++) {
        currentStateValue = stateRunner(currentStateValue.state);
        totalValue += currentStateValue.value * pow(gamma,i);
        printf("so the cumulative value is %f\n", totalValue);
    }

    printf("Value of initialState (%d,%d) : %f\n", initialState.x, initialState.y,  totalValue);

    return totalValue;

}

struct StateValue tableModifiedStateRunner(State initialState) {
    //takes action and returns new state with value
    char* action = chooseDirection(initialState);
    struct StateValue stateValue = valueFunction(initialState, action);
    return stateValue;
}

struct StateValue stateRunner(State initialState) {
    //takes action and returns new state with value
    char* action = chooseDirection(initialState);
    struct StateValue stateValue = valueFunction(initialState, action);
    stateShiftNarrator(initialState, stateValue);
    return stateValue;
}

char* chooseDirection(struct State state) {
    //randomly chooses direction with limitations from graph in textbook
    char* dirs[4];
    switch (state.y) {
        case -2:
            switch (state.x) {
                case -2:
                    dirs[0] = "up";
                    dirs[1] = "right";
                    return randomDirectionGenerator(dirs, 2);
                case -1:
                    dirs[0] = "up";
                    return randomDirectionGenerator(dirs, 1);
                case 0:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 1:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 2:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
            }
        case -1:
            switch (state.x) {
                case -2:
                    dirs[0] = "up";
                    dirs[1] = "right";
                    return randomDirectionGenerator(dirs, 2);
                case -1:
                    dirs[0] = "up";
                    return randomDirectionGenerator(dirs, 1);
                case 0:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 1:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 2:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
            }
        case 0:
            switch (state.x) {
                case -2:
                    dirs[0] = "up";
                    dirs[1] = "right";
                    return randomDirectionGenerator(dirs, 2);
                case -1:
                    dirs[0] = "up";
                    return randomDirectionGenerator(dirs, 1);
                case 0:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 1:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 2:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
            }
        case 1:
            switch (state.x) {
                case -2:
                    dirs[0] = "up";
                    dirs[1] = "right";
                    return randomDirectionGenerator(dirs, 2);
                case -1:
                    dirs[0] = "up";
                    return randomDirectionGenerator(dirs, 1);
                case 0:
                    dirs[0] = "up";
                    dirs[1] = "left";
                    return randomDirectionGenerator(dirs, 2);
                case 1:
                    dirs[0] = "left";
                    return randomDirectionGenerator(dirs, 1);
                case 2:
                    dirs[0] = "left";
                    return randomDirectionGenerator(dirs, 1);
            }
        case 2:
            switch (state.x) {
                case -2:
                    dirs[0] = "right";
                    return randomDirectionGenerator(dirs, 1);
                case -1:
                    dirs[0] = "left";
                    dirs[1] = "right";
                    dirs[2] = "up";
                    dirs[3] = "down";
                    return randomDirectionGenerator(dirs, 4);
                case 0:
                    dirs[0] = "left";
                    return randomDirectionGenerator(dirs, 1);
                case 1:
                    dirs[0] = "left";
                    dirs[1] = "right";
                    dirs[2] = "up";
                    dirs[3] = "down";
                    return randomDirectionGenerator(dirs, 4);
                case 2:
                    dirs[0] = "left";
                    return randomDirectionGenerator(dirs, 1);
            }
    }


}

char* randomDirectionGenerator(char* dirs[], int lenDirs) {
    char* direction;
    int num = (rand() % (lenDirs)); //generates random number between 0 and 3
    if (num == 0) {
        direction = dirs[0];
    } else if (num == 1) {
        direction = dirs[1];
    } else if (num == 2) {
        direction = dirs[3];
    } else { //if (num == 3)
        direction = dirs[4];
    }
    return direction;
}

struct StateValue valueFunction(struct State state, char* action) {
    //returns mew state and value of action

    struct StateValue stateValue {
            .state = state,
            .value = 0
    };

    if (stateValue.state.x == -1 && stateValue.state.y == 2) { //A
        stateValue.state.y -= 4;
        stateValue.value = 10;
    } else if (stateValue.state.x == 1 && stateValue.state.y == 2) { //B
        stateValue.state.y -= 2;
        stateValue.value = 5;
    } else if (strcmp(action, "left") == 0) { //1,1 fails
        if (stateValue.state.x == -2) {
            stateValue.value = -1;
        } else {
            stateValue.state.x--;
        }
    } else if (strcmp(action, "up") == 0) {
        if (stateValue.state.y == 2) {
            stateValue.value = -1;
        } else {
            stateValue.state.y++;
        }
    } else if (strcmp(action, "right") == 0) {
        if (stateValue.state.x == 2) {
            stateValue.value = -1;
        } else {
            stateValue.state.x++;
        }
    } else if (strcmp(action, "down") == 0) {
        if (stateValue.state.y == -2) {
            stateValue.value = -1;
        } else {
            stateValue.state.y--;
        }
    }

    return stateValue;
}

void stateShiftNarrator(struct State initial, struct StateValue final) {
    //narrates the shift
    printf("moving from (%d,%d) to (%d,%d) with reward "
           "%d, ", initial.x, initial.y, final.state.x, final.state.y, final.value);
}