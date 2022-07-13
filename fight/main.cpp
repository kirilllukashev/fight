#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

class Attacker {
public:
    virtual bool IsEnemy() = 0;
    virtual bool IsAlive() = 0;
    virtual void Init() = 0;
    int GetHealth() {return health_;}
    int GetAttack() {return attack_;}
    int GetExperience() {return experience_;}
    std::string GetName() {return name_;}
    void SetHealth(int health) {health_ = health;}
    void SetAttack(int attack) {attack_ = attack;}
    void SetExperience(int experience) {experience_ = experience;}
    void SetName(std::string name) {name_ = name;}
    void attack_smb(Attacker &other) {
        other.health_ -= attack_;
        other.health_ = std::max(other.health_, 0);
        ++experience_;
        --other.experience_;
        other.experience_ = std::max(other.experience_, 0);
        return;
    }

private:
    int health_;
    int attack_;
    int experience_;
    std::string name_;
};

class Hero : public Attacker {
public:
    Hero() {SetHealth(0), SetAttack(0), SetExperience(0), SetName("Kirill"),
                hero_answer_ = 0;}
    Hero(int health, int attack, std::string name)
    {SetHealth(health),SetAttack(attack), SetExperience(0), SetName(name),
                hero_answer_ = 0;}
    virtual ~Hero() {};
    bool IsEnemy() {
        return false;
    }
    int GetHeroAnswer() {return hero_answer_;}
    void SetHeroAnswer(int hero_answer) {hero_answer_ = hero_answer;}
    std::string GetHeroAnswerT() {return hero_answer_t_;}
    void SetHeroAnswerT(std::string hero_answer_t) {hero_answer_t_ = hero_answer_t;}
    bool IsAlive() {
        if (GetHealth() > 0) {
            return true;
        } else {
            return false;
        }
    }
    void Init() {
        std::cout << "Hello, " << GetName() << "!" << std::endl;
    }
private:
    int hero_answer_;
    std::string hero_answer_t_;
};

class Enemy : public Attacker {};

class Dragon : public Enemy{
public:
    virtual void greetings() = 0;
    bool IsEnemy() {
        return true;
    }
    int GetAnswer() {return answer_;}
    std::string GetColor() {return color_;}
    void SetAnswer(int answer) {answer_ = answer;}
    void SetColor(std::string color) {color_ = color; }
    virtual void Question() = 0;
    void CheckAnswer(Hero &my_hero) {
        if (my_hero.GetHeroAnswer() == answer_) {
            my_hero.attack_smb(*this);
            std::cout << "Good Job!" << std::endl;
        } else {
            this->attack_smb(my_hero);
            std::cout << "Wrong Answer!" << std::endl;
        }
        std::cout << "Your experience: " << my_hero.GetExperience() << std::endl;
        std::cout << "Your health: " << my_hero.GetHealth() << std::endl;
        std::cout << "Dragon health: " << GetHealth() << std::endl;
    }
    void Init() {
        std::cout << "Dragon name: " << GetName() << std::endl;
        std::cout << "Dragon color: " << GetColor() << std::endl;
    }
    bool IsAlive() {
        if (GetHealth() > 0) {
            return true;
        } else {
            std::cout << "The " << GetColor() << " dragon is dead!" << std::endl;
            return false;
        }
    }
    int GetRandom() {
        return (rng()) % 101;
    }
private:
    int answer_;
    std::string color_;
};

class RedDragon : public Dragon{
public:
    RedDragon() {SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Red"), SetAnswer(0), SetName("Kirill");}
    RedDragon(int health, int attack, std::string name) {
        SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Red"), SetAnswer(0), SetName(name);}
    virtual ~RedDragon() {};
    void Question() {
        int first = GetRandom();
        int second = GetRandom();
        SetAnswer(first - second);
        std::cout << first << " - " << second << std::endl;
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Red dragon. Let's fight!" << std::endl;
    }
};

class BlackDragon : public Dragon{
public:
    BlackDragon() {SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Black"), SetAnswer(0), SetName("Kirill");}
    BlackDragon(int health, int attack, std::string name) {
        SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Black"), SetAnswer(0), SetName(name);}
    virtual ~BlackDragon() {};
    void Question() {
        int first = GetRandom();
        int second = GetRandom();
        SetAnswer(first * second);
        std::cout << first << " * " << second << std::endl;
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Black dragon. Let's fight!" << std::endl;
    }
};

class GreenDragon : public Dragon{
public:
    GreenDragon() {SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Green"), SetAnswer(0), SetName("Kirill");}
    GreenDragon(int health, int attack, std::string name) {
        SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Green"), SetAnswer(0), SetName(name);}
    virtual ~GreenDragon() {};
    void Question() {
        int first = GetRandom();
        int second = GetRandom();
        SetAnswer(first + second);
        std::cout << first << " + " << second << std::endl;
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Green dragon. Let's fight!" << std::endl;
    }
};

class Troll : public Enemy{
public:
    virtual void greetings() = 0;
    bool IsEnemy() {
        return true;
    }
    std::string GetAnswer() {return answer_; }
    void SetAnswer(std::string answer) {answer_ = answer;}
    std::string GetColor() {return color_;}
    void SetColor(std::string color) {color_ = color; }
    virtual void Question() = 0;
    void CheckAnswer(Hero &my_hero){
        //std::cout << my_hero.GetHeroAnswerT() << std::endl;
        //std::cout << answer_ << std::endl;
        if (my_hero.GetHeroAnswerT() == answer_) {
            my_hero.attack_smb(*this);
            std::cout << "Good Job!" << std::endl;
        } else {
            this->attack_smb(my_hero);
            std::cout << "Wrong Answer!" << std::endl;
        }
        std::cout << "Your experience: " << my_hero.GetExperience() << std::endl;
        std::cout << "Your health: " << my_hero.GetHealth() << std::endl;
        std::cout << "Troll health: " << GetHealth() << std::endl;
    }
    void Init() {
        std::cout << "Troll name: " << GetName() << std::endl;
        std::cout << "Troll color: " << GetColor() << std::endl;
    }
    bool IsAlive() {
        if (GetHealth() > 0) {
            return true;
        } else {
            std::cout << "The " << GetColor() << " troll is dead!" << std::endl;
            return false;
        }
    }
    int GetRandom() {
        return (rng()) % 101;
    }
private:
    std::string color_;
    std::string answer_;
};

class RedTroll : public Troll{
public:
    RedTroll(){SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Red"), SetAnswer(""), SetName("Kirill");}
    RedTroll(int health, int attack, std::string name) {SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Red"), SetAnswer(""), SetName(name);}
    virtual ~RedTroll() {};
    void Question() {
        int num = GetRandom() + 1;
        std::cout << num << std::endl;
        bool cur_ans  = IsPrime(num);
        SetAnswer(to_str(cur_ans));
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Red troll. Let's fight!" << std::endl;
    }
private:
    bool IsPrime(int num) {
        for (int ind = 2; ind * ind <= num; ++ind) {
            if (num % ind == 0) {
                return false;
            }
        }
        return true;
    }
    std::string to_str(bool num) {
        std::string ans = std::to_string(num);
        return ans;
    }
};

class BlackTroll : public Troll{
public:
    BlackTroll(){SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Black"), SetAnswer(""), SetName("Kirill");}
    BlackTroll(int health, int attack, std::string name) {SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Black"), SetAnswer(""), SetName(name);}
    virtual ~BlackTroll() {};
    void Question() {
        int num = (GetRandom()) % 51;
        num += 2;
        std::cout << num << std::endl;
        std::vector<int> cur = Fact(num);
        SetAnswer(to_str(cur));
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Black troll. Let's fight!" << std::endl;
    }
private:
    std::vector<int> Fact(int num) {
        std::vector<int> ans;
        int div = 2;
        while (num > 1) {
            while (num % div == 0) {
                ans.push_back(div);
                num /= div;
            }
            ++div;
        }
        return ans;
    }
    std::string to_str(std::vector<int> arr) {
        std::string ans = "";
        for (auto elem : arr) {
            ans += std::to_string(elem);
            ans += " ";
            //std::cout << ans << std::endl;
        }
        ans.pop_back();
        return ans;
    }
};

class GreenTroll : public Troll{
public:
    GreenTroll(){SetHealth(0), SetAttack(0), SetExperience(0),
                SetColor("Green"), SetAnswer(""), SetName("Kirill");}
    GreenTroll(int health, int attack, std::string name) {SetHealth(health), SetAttack(attack), SetExperience(0),
                SetColor("Green"), SetAnswer(""), SetName(name);}
    virtual ~GreenTroll() {};
    void Question() {
        int a = GetRandom() % 50;
        int b = GetRandom() % 50;
        ++a, ++b;
        std::cout << a << " " << b << std::endl;
        int answer = gcd(a, b);
        SetAnswer(to_str(answer));
    }
    void greetings() {
        std::cout << "Hello, hero! I'm Green troll. Let's fight!" << std::endl;
    }
private:
    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        else {
            return gcd (b, a % b);
        }
    }
    std::string to_str(int num) {
        std::string ans = std::to_string(num);
        return ans;
    }
};
int main() {
    std::string hero_name;
    std::cout << "Set Hero name: " << std::endl;
    std::cin >> hero_name;
    Hero my_hero(20, 2, hero_name);
    my_hero.Init();

    std::string green_dragon_name;
    std::cout << "Set Green dragon name: " << std::endl;
    std::cin >> green_dragon_name;
    GreenDragon green_dragon(20, 2, green_dragon_name);
    green_dragon.Init();

    std::string red_dragon_name;
    std::cout << "Set Red dragon name: " << std::endl;
    std::cin >> red_dragon_name;
    RedDragon red_dragon(20, 2, red_dragon_name);
    red_dragon.Init();

    std::string black_dragon_name;
    std::cout << "Set Black dragon name: " << std::endl;
    std::cin >> black_dragon_name;
    BlackDragon black_dragon(20, 2, black_dragon_name);
    black_dragon.Init();

    std::string red_troll_name;
    std::cout << "Set Red troll name: " << std::endl;
    std::cin >> red_troll_name;
    RedTroll red_troll(20, 2, red_troll_name);
    red_troll.Init();

    std::string black_troll_name;
    std::cout << "Set Black troll name: " << std::endl;
    std::cin >> black_troll_name;
    BlackTroll black_troll(20, 2, black_troll_name);
    black_troll.Init();

    std::string green_troll_name;
    std::cout << "Set Green troll name: " << std::endl;
    std::cin >> green_troll_name;
    GreenTroll green_troll(20, 2, green_troll_name);
    green_troll.Init();
    Dragon* enemies_d[] = {&green_dragon, &red_dragon, &black_dragon};
    for (Dragon* a: enemies_d) {
        (*a).greetings();
        while (my_hero.IsAlive() && (*a).IsAlive()) {
            (*a).Question();
            int hero_answer;
            std::cin >> hero_answer;
            my_hero.SetHeroAnswer(hero_answer);
            (*a).CheckAnswer(my_hero);
        }
        if (!my_hero.IsAlive()) {
            break;
        }
    }
    Troll* enemies_t[] = {&red_troll, &black_troll, &green_troll};
    std::string trash;
    std::getline(std::cin, trash);
    for (Troll* a: enemies_t) {
        (*a).greetings();
        while (my_hero.IsAlive() && (*a).IsAlive()) {
            (*a).Question();
            std::string hero_answer;
            std::getline(std::cin, hero_answer);
            my_hero.SetHeroAnswerT(hero_answer);
            (*a).CheckAnswer(my_hero);
        }
        if (!my_hero.IsAlive()) {
            break;
        }
    }
    if (my_hero.IsAlive()) {
        std::cout << "You are winner!\n";
    } else {
        std::cout << "You died" << std::endl;
    }
    return 0;
}