#include <iostream>
#include<string>
using namespace std;
// Design a class hierarchy for the characters in the game
class Character // Including Health, mana point and defense(ex. resistance) 
{
protected:
    int Max_Health_point;
    int Max_Mana_point;
public:
    int Current_Health_point;
    int Current_Mana_point;
    int Magic_resistance;
    void Set_point(int health, int man);
}; 
void Character::Set_point(int health, int mana) 
{
    Max_Health_point = health;
    Max_Mana_point = mana;
    Current_Health_point = Max_Health_point;
    Current_Mana_point = Max_Mana_point;
}

class Warrior // Warrior character including normal attack power and special attack using nested class
{
private:
    int Weapon_strength;
    int Special_attacks;
public:
    Character point;
    Warrior();
    ~Warrior() {}
    void Weapon_str(Character &A) // Normal attack
    {
        A.Current_Health_point -= Weapon_strength;
    }
    void Special_atk(Character &A) // Special attack
    {
        if (this -> point.Current_Mana_point < 2)
        {
            cout << "Cannot attack because of no mana" << endl;
            return;
        }
        else
        {
            A.Current_Health_point -= (Weapon_strength * Special_attacks - A.Magic_resistance); // Calculate resistance
            this -> point.Current_Mana_point -=  Special_attacks; // reduce mana
        }
    }
};

Warrior::Warrior() // Initialize stats of warrior
{
    point.Set_point(100, 20);
    Weapon_strength = 8;
    Special_attacks = 2;
    point.Magic_resistance = 0;
}

class Mage : public Character // mage class derived by character class
{
private:
    int Spell_power;
public:
    Mage();
    ~Mage() {}
    void Spell_pw(Character &A) // Spell attack
    {
        if (this -> Current_Mana_point < 3)
        {
            cout << "Cannot attack because of no mana" << endl;
            return;
        }
        else
        {
            A.Current_Health_point -= (Spell_power * 5 - A.Magic_resistance);
            this -> Current_Mana_point -=  Spell_power;
        }
    }
};

Mage::Mage() // initialize stats of mage
{
    Set_point(70, 50);
    Spell_power = 3;
    Magic_resistance = 3;
}
void print(Mage A, Warrior B) // For interface
{
    cout << endl << "Warrior" << endl;
    cout << "Health" << B.point.Current_Health_point << "/" << 100 << endl;
    cout << "Mana" << B.point.Current_Mana_point << "/" << 20 << endl << endl;
    cout << "Mage" << endl;
    cout << "Health" << A.Current_Health_point << "/" << 70 << endl;
    cout << "Mana" << A.Current_Mana_point << "/" << 50 << endl << endl;
}

int main()
{
    int choose;
    Warrior Wr;
    Mage Mg;

    cout << "You are Warrior" << endl << "A.I is Mage" << endl;
    print(Mg, Wr);
    while (Wr.point.Current_Health_point > 0 && Mg.Current_Health_point > 0) // Fight simulator
    {
        cout << "Which one would you choose? (1 = Normal attack, 2 = Special attack) : ";
        cin >> choose;
        if(choose == 1)
        {
            Wr.Weapon_str(Mg);
        }
        if(choose == 2)            
        {
            Wr.Special_atk(Mg);
        }
        if(choose != 1 && choose != 2)
        {
            cout << "Your character is only standing";
        }
        if(Mg.Current_Health_point < 0){break;}
        Mg.Spell_pw(Wr.point);
        print(Mg, Wr);
    }
    if(Mg.Current_Health_point < 0) // show who is won.
    {
        cout << "You won!!!" << endl;
    }
    else
    {
        cout << "You lose..." << endl;
    }
    return 0;
}