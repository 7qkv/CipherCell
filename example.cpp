#include "ciphercell.hpp"
#include <iostream>
#include <string>

struct Player {
    int health;
    int gold;
    int level;
};

int main() {
    CipherCell<int> health(100);
    CipherCell<float> damage(45.5f);
    CipherCell<uint64_t> score(999999);
    
    std::cout << "Health: " << health.get() << "\n";
    std::cout << "Damage: " << damage.get() << "\n";
    std::cout << "Score: " << score.get() << "\n\n";
    
    health -= 25;
    damage *= 1.5f;
    score += 10000;
    
    std::cout << "After combat:\n";
    std::cout << "Health: " << health.get() << "\n";
    std::cout << "Damage: " << damage.get() << "\n";
    std::cout << "Score: " << score.get() << "\n\n";
    
    CipherCell<Player> player(Player{100, 5000, 10});
    Player p = player.get();
    std::cout << "Player - HP: " << p.health << " Gold: " << p.gold << " Level: " << p.level << "\n";
    
    p.gold += 500;
    p.level++;
    player = p;
    
    Player updated = player.get();
    std::cout << "Updated - HP: " << updated.health << " Gold: " << updated.gold << " Level: " << updated.level << "\n";
    
    return 0;
}