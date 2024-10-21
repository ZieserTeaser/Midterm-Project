#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    string name;
    int health;
    int speed;
    int attack;
};

struct Enemy {
    string type;
    int health;
    int speed;
    int attack;
    int id;
};

class Game {
public:
    Game() {
        setPlayerStats();
    }

    void play() {
        while (currentFloor <= 5) {
            if (player.health < 1) {
                return;
            }
            cout << "\n--- Floor " << currentFloor << " ---" << endl;

            int numBattles = 0;

            while (numBattles < 2) {
                if (!chooseRoom()) {
                    cout << "You have failed the Tower of Trials! Try again!" << endl;
                    return;
                }
                numBattles++;
            }

            if (currentFloor == 5) {
                cout << "You've reached the top of the tower! Prepare for the boss fight!" << endl;
                Enemy boss = generateBoss();
                if (!fight(boss)) {
                    cout << "You have been defeated by the boss. Game over." << endl;
                    return;
                }
            }
            if (currentFloor != 5) {
                cout << "You find yourself at cobblestone stairs. Only one way to go..." << endl;
            }
            currentFloor++;
        }
        cout << "Congratulations! You've conquered the Tower of Trials!\nDo you dare go again?" << endl;
    }
    

private:
    Player player;
    int currentFloor = 1;

    void setPlayerStats() {
        int choice;

        cout << "What is your name?" << endl;
        getline(cin, player.name);
        cout << "Welcome, " << player.name << ", to the Tower of Trials!" << endl;

        cout << "In front of you is a Sword (1), Double Daggers (2), and a Book (3)\nWhich do you choose?" << endl;
        cin >> choice;

        while (choice != 1 && choice != 2 && choice != 3) {
            cout << "Type in 1, 2, or 3" << endl;
            cin >> choice;
        }
        switch (choice) {
        case 1:
            cout << "The sword has a good weight to it" << endl;
            player.health = 100;
            player.speed = 50;
            player.attack = 100;
            break;
        case 2:
            cout << "The daggers make you feel lighter than before" << endl;
            player.health = 50;
            player.speed = 200;
            player.attack = 75;
            break;
        case 3:
            cout << "A dark presence drifts over you" << endl;
            player.health = 25;
            player.speed = 50;
            player.attack = 300;
        }
        if (!chooseRoom()) {
            cout << "You have failed the Tower of Trials! Try again!" << endl;
            return;
        }
    }

    bool chooseRoom() {
        int choice;

        cout << "You see a door on the left (1) and a door on the right (2)\nWhich door do you choose?" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "You head through the left door." << endl;
        }
        else if (choice == 2){
            cout << "You head through the right door." << endl;
        }

        while (choice != 1 && choice != 2) {
            cout << "Type in 1 or 2" << endl;
            cin >> choice;
        }

        Enemy enemy = generateEnemy();
        switch (enemy.id) {
        case 0:
            cout << "You encounter a " << enemy.type << ", it looks spooky!" << endl;
            break;
        case 1:
            cout << "You encounter a " << enemy.type << ", it looks oily!" << endl;
            break;
        case 2:
            cout << "You encounter a " << enemy.type << ", it looks fast!" << endl;
            break;
        case 3:
            cout << "You encounter a " << enemy.type << ", it's huge and looks electric!" << endl;
        }

        return fight(enemy);
    }

    Enemy generateEnemy() {
        Enemy enemy;
        int randomType = rand() % 3;
        switch (randomType) {
        case 0:
            enemy.type = "Skeleton";
            enemy.health = 30 + currentFloor * 5;
            enemy.attack = 10 + currentFloor * 2;
            enemy.speed = 10 + currentFloor * 3;
            enemy.id = 0;
            break;
        case 1:
            enemy.type = "Slime";
            enemy.health = 40 + currentFloor * 7;
            enemy.attack = 15 + currentFloor * 3;
            enemy.speed = 20 + currentFloor * 1.5;
            enemy.id = 1;
            break;
        case 2:
            enemy.type = "Snake";
            enemy.health = 25 + currentFloor * 4;
            enemy.attack = 5 + currentFloor;
            enemy.speed = 85 + currentFloor * 3;
            enemy.id = 2;
            break;
        }
        return enemy;
    }

    Enemy generateBoss() {
        Enemy enemy;
        enemy.type = "Boss";
        enemy.health = 125;
        enemy.attack = 75;
        enemy.speed = 1;
        enemy.id = 3;
        return enemy;
    }

    bool fight(Enemy& enemy) {
        bool dodged = false;
        bool charged = false;


        while (player.health > 0 && enemy.health > 0) { //add more text for each weapon
            cout << "\nYour health: " << player.health << endl;
            cout << "Do you want to:\nAttack (1)\nDodge (2)\nCharge (3)" << endl;
            int action;
            cin >> action;

            switch (action) {
            case 1: 
                if (charged) {
                    cout << "You unleash a charged attack for " << (player.attack * 2) << " damage!\n" << endl;
                    enemy.health -= (player.attack * 2); 
                    charged = false;
                }
                else {
                    cout << "You attack the " << enemy.type << " for " << player.attack << " damage!\n" << endl;
                    enemy.health -= player.attack;
                }
                break;
            case 2: 
                cout << "You prepare to dodge the next attack!\n" << endl;
                if (player.speed >= enemy.speed) {
                    dodged = true;
                }
                break;
            case 3:
                cout << "You charge your attack!\n" << endl;
                charged = true;
                break;
            }

            if (enemy.health > 0) {
                if (!dodged) {
                    
                    cout << "The " << enemy.type << " attacks you for " << enemy.attack << " damage!\n" << endl;
                    player.health -= enemy.attack;
                } 
                else {
                    cout << "You dodge the attack!" << endl;
                    dodged = false;
                }
            }
        }

        if (player.health <= 0) {
            cout << "Oh no! You were slain!" << endl;
            return false;
        }
        else {
            cout << "You have defeated the " << enemy.type << "!" << endl;
            return true;
        }
    }
};

int main(){
    srand(static_cast<unsigned int>(time(0)));
    Game game;
    game.play();
    return 0;
}